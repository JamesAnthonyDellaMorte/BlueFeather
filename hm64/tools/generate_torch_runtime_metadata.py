#!/usr/bin/env python3

from __future__ import annotations

import argparse
import csv
import re
from dataclasses import dataclass
from pathlib import Path, PurePosixPath

from generate_rom_symbol_asm import parse_splat_ranges
from libhm64.sprites.addresses import get_all_sprites


TOOLS_ROOT = Path(__file__).resolve().parent
HM64_ROOT = TOOLS_ROOT.parent
PROJECT_ROOT = HM64_ROOT.parent
SPLAT_CONFIG = HM64_ROOT / "config" / "us" / "splat.us.yaml"
TEXT_ADDRESSES_CSV = TOOLS_ROOT / "libhm64" / "data" / "text_addresses.csv"
DIALOGUE_ADDRESSES_CSV = TOOLS_ROOT / "libhm64" / "data" / "dialogue_bytecode_addresses.csv"
CUTSCENE_ADDRESSES_CSV = TOOLS_ROOT / "libhm64" / "data" / "cutscene_addresses.csv"
MAP_ADDRESSES_CSV = TOOLS_ROOT / "libhm64" / "data" / "map_addresses.csv"
DEFAULT_YAML_OUTPUT = HM64_ROOT / "assets" / "yaml" / "us" / "runtime" / "rom.yml"

ENTRY_NAME_PATTERN = re.compile(r"^\s*-\s+name:\s*([A-Za-z0-9_]+)\s*$")
ENTRY_DIR_PATTERN = re.compile(r"^\s*dir:\s*([A-Za-z0-9_./-]+)\s*$")
ENTRY_TYPE_PATTERN = re.compile(r"^\s*type:\s*([A-Za-z0-9_:.-]+)\s*$")
ENTRY_START_PATTERN = re.compile(r"^\s*start:\s*(0x[0-9A-Fa-f]+)\s*$")
FINAL_PATTERN = re.compile(r"^\s*-\s*\[\s*(0x[0-9A-Fa-f]+)\s*\]\s*$")


@dataclass(frozen=True)
class RuntimeBlobEntry:
    start: int
    end: int
    archive_path: PurePosixPath

    @property
    def size(self) -> int:
        return self.end - self.start

    @property
    def yaml_key(self) -> str:
        return self.archive_path.relative_to(PurePosixPath("runtime/rom")).as_posix()

    @property
    def symbol(self) -> str:
        safe = re.sub(r"[^A-Za-z0-9_]", "_", self.yaml_key)
        safe = re.sub(r"_+", "_", safe).strip("_")
        if not safe:
            safe = "runtime_blob"
        if safe[0].isdigit():
            safe = f"asset_{safe}"
        return safe


def parse_splat_entries(splat_path: Path) -> list[dict[str, object]]:
    entries: list[dict[str, object]] = []
    current: dict[str, object] | None = None
    final_rom_end: int | None = None

    for raw_line in splat_path.read_text().splitlines():
        if match := FINAL_PATTERN.match(raw_line):
            final_rom_end = int(match.group(1), 16)
            continue

        if match := ENTRY_NAME_PATTERN.match(raw_line):
            if current is not None and "start" in current:
                entries.append(current)
            current = {"name": match.group(1)}
            continue

        if current is None:
            if match := FINAL_PATTERN.match(raw_line):
                final_rom_end = int(match.group(1), 16)
            continue

        if match := ENTRY_DIR_PATTERN.match(raw_line):
            current["dir"] = match.group(1)
            continue

        if match := ENTRY_TYPE_PATTERN.match(raw_line):
            current["type"] = match.group(1)
            continue

        if match := ENTRY_START_PATTERN.match(raw_line):
            current["start"] = int(match.group(1), 16)
            continue

    if current is not None and "start" in current:
        entries.append(current)

    if final_rom_end is None:
        raise RuntimeError(f"Could not find final ROM size sentinel in {splat_path}")

    for index, entry in enumerate(entries):
        if index + 1 < len(entries):
            entry["end"] = entries[index + 1]["start"]
        else:
            entry["end"] = final_rom_end

    return entries


def parse_text_entries(csv_path: Path) -> list[RuntimeBlobEntry]:
    entries: list[RuntimeBlobEntry] = []
    with csv_path.open(newline="", encoding="utf-8") as csv_file:
        reader = csv.reader(csv_file)
        next(reader, None)
        for row in reader:
            index_start, index_end, text_start, name, _game_index = row
            entries.append(
                RuntimeBlobEntry(
                    start=int(text_start, 16),
                    end=int(index_start, 16),
                    archive_path=PurePosixPath(f"runtime/rom/text/{name}.bin"),
                )
            )
            entries.append(
                RuntimeBlobEntry(
                    start=int(index_start, 16),
                    end=int(index_end, 16),
                    archive_path=PurePosixPath(f"runtime/rom/text/{name}Index.bin"),
                )
            )
    return entries


def parse_dialogue_entries(csv_path: Path) -> list[RuntimeBlobEntry]:
    entries: list[RuntimeBlobEntry] = []
    with csv_path.open(newline="", encoding="utf-8") as csv_file:
        reader = csv.reader(csv_file)
        for row in reader:
            index_start, index_end, bytecode_start, _game_index, name = row
            entries.append(
                RuntimeBlobEntry(
                    start=int(bytecode_start, 16),
                    end=int(index_start, 16),
                    archive_path=PurePosixPath(f"runtime/rom/dialogues/{name}.bin"),
                )
            )
            entries.append(
                RuntimeBlobEntry(
                    start=int(index_start, 16),
                    end=int(index_end, 16),
                    archive_path=PurePosixPath(f"runtime/rom/dialogues/{name}Index.bin"),
                )
            )
    return entries


def parse_cutscene_entries(csv_path: Path) -> list[RuntimeBlobEntry]:
    entries: list[RuntimeBlobEntry] = []
    with csv_path.open(newline="", encoding="utf-8") as csv_file:
        reader = csv.reader(csv_file)
        for row in reader:
            start, end, name = row
            entries.append(
                RuntimeBlobEntry(
                    start=int(start, 16),
                    end=int(end, 16),
                    archive_path=PurePosixPath(f"runtime/rom/cutscenes/{name}.bin"),
                )
            )
    return entries


def parse_map_entries(csv_path: Path) -> list[RuntimeBlobEntry]:
    raw_rows: list[tuple[int, str]] = []
    with csv_path.open(newline="", encoding="utf-8") as csv_file:
        reader = csv.reader(csv_file)
        for row in reader:
            if len(row) < 2:
                continue
            raw_rows.append((int(row[0], 16), row[1]))

    entries: list[RuntimeBlobEntry] = []
    for index, (start, name) in enumerate(raw_rows):
        if name == "end":
            continue
        end = raw_rows[index + 1][0]
        entries.append(
            RuntimeBlobEntry(
                start=start,
                end=end,
                archive_path=PurePosixPath(f"runtime/rom/maps/{name}.bin"),
            )
        )
    return entries


def collect_font_entries(ranges: dict[str, tuple[int, int]]) -> list[RuntimeBlobEntry]:
    entries: list[RuntimeBlobEntry] = []
    for name in ("fontTexture", "fontPalette1", "fontPalette2", "fontPalette3"):
        start, end = ranges[name]
        entries.append(
            RuntimeBlobEntry(
                start=start,
                end=end,
                archive_path=PurePosixPath(f"runtime/rom/font/{name}.bin"),
            )
        )
    return entries


def collect_sprite_entries() -> list[RuntimeBlobEntry]:
    entries: list[RuntimeBlobEntry] = []
    for sprite in get_all_sprites():
        base = PurePosixPath(f"runtime/rom/sprites/{sprite.subdir}/{sprite.label}")
        entries.append(
            RuntimeBlobEntry(
                start=sprite.addr_base,
                end=sprite.addr_index,
                archive_path=base / f"{sprite.label}Texture.bin",
            )
        )

        if sprite.is_type1:
            assert sprite.spritesheet_index_base is not None
            assert sprite.spritesheet_index_end is not None
            entries.append(
                RuntimeBlobEntry(
                    start=sprite.addr_index,
                    end=sprite.spritesheet_index_base,
                    archive_path=base / f"{sprite.label}AssetsIndex.bin",
                )
            )
            entries.append(
                RuntimeBlobEntry(
                    start=sprite.spritesheet_index_base,
                    end=sprite.spritesheet_index_end,
                    archive_path=base / f"{sprite.label}SpritesheetIndex.bin",
                )
            )
        else:
            assert sprite.addr_extra is not None
            entries.append(
                RuntimeBlobEntry(
                    start=sprite.addr_index,
                    end=sprite.addr_extra,
                    archive_path=base / f"{sprite.label}AssetsIndex.bin",
                )
            )
    return entries


def collect_audio_entries(splat_entries: list[dict[str, object]]) -> list[RuntimeBlobEntry]:
    entries: list[RuntimeBlobEntry] = []
    for entry in splat_entries:
        name = entry["name"]
        start = entry["start"]
        end = entry["end"]
        entry_dir = entry.get("dir")
        entry_type = entry.get("type")

        if entry_dir == "audio" and name in ("waveTablePointer", "waveTableData"):
            archive_path = PurePosixPath(f"runtime/rom/audio/{name}.bin")
        elif entry_dir == "audio/sequences" and entry_type == "seq":
            archive_path = PurePosixPath(f"runtime/rom/audio/sequences/{name}.seq")
        else:
            continue

        entries.append(RuntimeBlobEntry(start=start, end=end, archive_path=archive_path))
    return entries


def build_runtime_manifest() -> list[RuntimeBlobEntry]:
    splat_entries = parse_splat_entries(SPLAT_CONFIG)
    ranges = parse_splat_ranges(SPLAT_CONFIG)

    entries: list[RuntimeBlobEntry] = []
    entries.extend(collect_font_entries(ranges))
    entries.extend(collect_sprite_entries())
    entries.extend(parse_cutscene_entries(CUTSCENE_ADDRESSES_CSV))
    entries.extend(parse_dialogue_entries(DIALOGUE_ADDRESSES_CSV))
    entries.extend(parse_text_entries(TEXT_ADDRESSES_CSV))
    entries.extend(parse_map_entries(MAP_ADDRESSES_CSV))
    entries.extend(collect_audio_entries(splat_entries))

    seen_paths: set[str] = set()
    for entry in entries:
        path = entry.archive_path.as_posix()
        if path in seen_paths:
            raise RuntimeError(f"Duplicate archive path in runtime manifest: {path}")
        seen_paths.add(path)

    return entries


def render_yaml(entries: list[RuntimeBlobEntry]) -> str:
    lines = [
        ":config:",
        "  logging: INFO",
        "",
    ]

    for entry in sorted(entries, key=lambda item: item.archive_path.as_posix()):
        lines.append(
            f'"{entry.yaml_key}": {{ type: BLOB, offset: 0x{entry.start:08X}, size: 0x{entry.size:X}, symbol: {entry.symbol} }}'
        )

    lines.append("")
    return "\n".join(lines)


def render_table(entries: list[RuntimeBlobEntry]) -> str:
    lines = [
        "#ifndef BLUEFEATHER_RUNTIME_ARCHIVE_ROM_TABLE_H",
        "#define BLUEFEATHER_RUNTIME_ARCHIVE_ROM_TABLE_H",
        "",
        "#include <cstddef>",
        "#include <cstdint>",
        "",
        "struct MWRuntimeArchiveRomRange {",
        "    uintptr_t Start;",
        "    uintptr_t End;",
        "    const char* Path;",
        "};",
        "",
        "static constexpr MWRuntimeArchiveRomRange kMWRuntimeArchiveRomRanges[] = {",
    ]

    for entry in sorted(entries, key=lambda item: item.start):
        lines.append(
            f'    {{ 0x{entry.start:08X}u, 0x{entry.end:08X}u, "{entry.archive_path.as_posix()}" }},'
        )

    lines.extend(
        [
            "};",
            "",
            "#endif",
            "",
        ]
    )
    return "\n".join(lines)


def main() -> int:
    parser = argparse.ArgumentParser(description="Generate BlueFeather Torch runtime metadata")
    parser.add_argument("--yaml-output", type=Path, help="Write the Torch runtime blob YAML here")
    parser.add_argument("--table-header", type=Path, help="Write the runtime ROM-range header here")
    args = parser.parse_args()

    if args.yaml_output is None and args.table_header is None:
        parser.error("at least one of --yaml-output or --table-header is required")

    entries = build_runtime_manifest()

    if args.yaml_output is not None:
        args.yaml_output.parent.mkdir(parents=True, exist_ok=True)
        args.yaml_output.write_text(render_yaml(entries))

    if args.table_header is not None:
        args.table_header.parent.mkdir(parents=True, exist_ok=True)
        args.table_header.write_text(render_table(entries))

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
