#!/usr/bin/env python3

from __future__ import annotations

import argparse
import csv
import re
import shutil
import subprocess
import sys
import tempfile
from dataclasses import dataclass
from functools import lru_cache
from pathlib import Path

TOOLS_ROOT = Path(__file__).resolve().parent
HM64_ROOT = TOOLS_ROOT.parent
BLUEFEATHER_PROJECT_ROOT = HM64_ROOT.parent
HM64_DECOMP_ROOT = BLUEFEATHER_PROJECT_ROOT.parent / "hm64-decomp"
HM64_IMPORTED_ASSETS_ROOT = HM64_DECOMP_ROOT / "assets"
LD_SYMBOL_HEADER = HM64_ROOT / "include" / "ld_symbols.h"
SPLAT_CONFIG = HM64_DECOMP_ROOT / "config" / "us" / "splat.us.yaml"
RAM_SYMBOLS_FILE = HM64_DECOMP_ROOT / "config" / "us" / "symbol_addrs.txt"
sys.path.insert(0, str(TOOLS_ROOT))

from libhm64.fonts.assembler import assemble_font_palette, assemble_font_texture  # noqa: E402
from libhm64.sprites.addresses import get_all_sprites  # noqa: E402
from libhm64.sprites.assembler import assemble_sprite  # noqa: E402
from generate_rom_symbol_asm import parse_needed_symbols, parse_splat_ranges, resolve_range  # noqa: E402

MIPS_AS = Path("/opt/homebrew/bin/mips64-elf-as")
OBJCOPY = Path("llvm-objcopy")
RUNTIME_ROM_ROOT = Path("runtime/rom")

# Generated cutscene assembly still carries a few legacy segment names from older
# symbol databases. Resolve them to the active BlueFeather segment names at build
# time so the assembled archive blobs contain real ROM ranges instead of zeroed
# relocations.
ROM_SYMBOL_ALIASES = {
    "_logoTexturesSegmentRomStart": "_logossTexturesSegmentRomStart",
    "_logoTexturesSegmentRomEnd": "_logossTexturesSegmentRomEnd",
    "_logoAssetsIndexSegmentRomStart": "_logossAssetsIndexSegmentRomStart",
    "_logoAssetsIndexSegmentRomEnd": "_logossAssetsIndexSegmentRomEnd",
    "_logosTextureSegmentRomStart": "_logossTexturesSegmentRomStart",
    "_logosTextureSegmentRomEnd": "_logossTexturesSegmentRomEnd",
    "_logosAssetsIndexSegmentRomStart": "_logossAssetsIndexSegmentRomStart",
    "_logosAssetsIndexSegmentRomEnd": "_logossAssetsIndexSegmentRomEnd",
    "_fairiesTextureAssetsIndexSegmentRomStart": "_fairiesAssetsIndexSegmentRomStart",
    "_fairiesTextureAssetsIndexSegmentRomEnd": "_fairiesAssetsIndexSegmentRomEnd",
    "_funeralSpritesTextureSegmentRomStart": "_funeralIntroTextureSegmentRomStart",
    "_funeralSpritesTextureSegmentRomEnd": "_funeralIntroTextureSegmentRomEnd",
    "_funeralSpritesIndexSegmentRomStart": "_funeralIntroAssetsIndexSegmentRomStart",
    "_funeralSpritesIndexSegmentRomEnd": "_funeralIntroAssetsIndexSegmentRomEnd",
}

RAM_SYMBOL_ALIASES = {
    "D_80237A00": "D_80237A00f",
}


@dataclass(frozen=True)
class RuntimeAssetEntry:
    start: int
    end: int
    archive_path: Path


@dataclass(frozen=True)
class SpecEntry:
    name: str
    include: Path


@dataclass(frozen=True)
class CsvRangeEntry:
    start: int
    end: int
    name: str


def run(cmd: list[str]) -> None:
    subprocess.run(cmd, check=True)


@lru_cache(maxsize=1)
def get_segment_ranges_by_name() -> dict[str, tuple[int, int]]:
    return parse_splat_ranges(SPLAT_CONFIG)


@lru_cache(maxsize=1)
def get_rom_segment_symbol_values() -> dict[str, int]:
    values: dict[str, int] = {}
    missing: list[str] = []

    for name, edges in parse_needed_symbols(LD_SYMBOL_HEADER).items():
        resolved = resolve_range(name, get_segment_ranges_by_name())
        if resolved is None:
            missing.append(name)
            continue

        start, end = resolved
        if "Start" in edges:
            values[f"_{name}SegmentRomStart"] = start
        if "End" in edges:
            values[f"_{name}SegmentRomEnd"] = end

    if missing:
        preview = ", ".join(sorted(missing)[:20])
        if len(missing) > 20:
            preview += ", ..."
        raise RuntimeError(f"Missing ROM ranges for {len(missing)} symbols: {preview}")

    for alias, target in ROM_SYMBOL_ALIASES.items():
        value = values.get(target)
        if value is None:
            raise RuntimeError(f"Missing ROM alias target {target} for alias {alias}")
        values[alias] = value

    return values


@lru_cache(maxsize=1)
def get_ram_symbol_values() -> dict[str, int]:
    values: dict[str, int] = {}
    pattern = re.compile(r"^\s*([A-Za-z_][A-Za-z0-9_]*)\s*=\s*(0x[0-9A-Fa-f]+)\s*;")

    for raw_line in RAM_SYMBOLS_FILE.read_text().splitlines():
        match = pattern.match(raw_line)
        if not match:
            continue
        values[match.group(1)] = int(match.group(2), 16)

    for alias, target in RAM_SYMBOL_ALIASES.items():
        value = values.get(target)
        if value is not None:
            values[alias] = value

    return values


def ensure_exact_size(data: bytes, expected_size: int, label: str, *, allow_pad: bool = False) -> bytes:
    actual_size = len(data)
    if actual_size == expected_size:
        return data

    if allow_pad and actual_size < expected_size:
        return data + (b"\x00" * (expected_size - actual_size))

    raise RuntimeError(f"{label}: expected {expected_size} bytes, got {actual_size}")


def materialize_symbol_source(source: Path, dest: Path) -> None:
    text = source.read_text()

    symbol_values = {}
    symbol_values.update(get_rom_segment_symbol_values())
    symbol_values.update(get_ram_symbol_values())

    for symbol, addr in sorted(symbol_values.items(), key=lambda item: len(item[0]), reverse=True):
        text = re.sub(rf"\b{re.escape(symbol)}\b", f"0x{addr:08X}", text)

    dest.write_text(text)


def parse_spec(spec_path: Path) -> list[SpecEntry]:
    entries: list[SpecEntry] = []
    current_name: str | None = None
    current_include: Path | None = None

    for raw_line in spec_path.read_text().splitlines():
        line = raw_line.strip()
        if line.startswith("name "):
            current_name = line.split('"')[1]
        elif line.startswith("include "):
            current_include = Path(line.split('"')[1])
        elif line == "endseg":
            if current_name is not None and current_include is not None:
                entries.append(SpecEntry(current_name, current_include))
            current_name = None
            current_include = None

    return entries


def parse_range_csv(csv_path: Path) -> list[CsvRangeEntry]:
    entries: list[CsvRangeEntry] = []
    with csv_path.open(newline="", encoding="utf-8") as csv_file:
        reader = csv.reader(csv_file)
        for row in reader:
            if len(row) < 3:
                continue
            entries.append(CsvRangeEntry(int(row[0], 16), int(row[1], 16), row[2]))
    return entries


def segment_range(segment_name: str) -> tuple[int, int]:
    resolved = resolve_range(segment_name, get_segment_ranges_by_name())
    if resolved is None:
        raise KeyError(f"Missing ROM range for segment {segment_name}")
    return resolved


def archive_path_from_include(include_path: Path) -> Path:
    include_without_obj = include_path.with_suffix("") if include_path.suffix == ".o" else include_path
    parts = include_without_obj.parts
    if "assets" in parts:
        assets_index = parts.index("assets")
        return RUNTIME_ROM_ROOT / Path(*parts[assets_index + 1 :])
    if "bin" in parts:
        bin_index = parts.index("bin")
        return RUNTIME_ROM_ROOT / Path(*parts[bin_index + 1 :])
    return RUNTIME_ROM_ROOT / include_without_obj.name


def write_asset(output_root: Path, relative_path: Path, data: bytes) -> None:
    output_path = output_root / relative_path
    output_path.parent.mkdir(parents=True, exist_ok=True)
    output_path.write_bytes(data)


def dump_data_section(source: Path, temp_dir: Path) -> bytes:
    asm_path = temp_dir / source.name
    obj_path = temp_dir / f"{source.stem}.o"
    data_path = temp_dir / f"{source.stem}.bin"

    materialize_symbol_source(source, asm_path)
    run([str(MIPS_AS), "-march=vr4300", "-mabi=32", "-o", str(obj_path), str(asm_path)])
    run([str(OBJCOPY), f"--dump-section", f".data={data_path}", str(obj_path)])

    return data_path.read_bytes()


def stage_spec_asm_assets(
    spec_path: Path,
    source_root: Path,
    output_root: Path,
    temp_dir: Path,
) -> list[RuntimeAssetEntry]:
    entries: list[RuntimeAssetEntry] = []

    for spec_entry in parse_spec(spec_path):
        start, end = segment_range(spec_entry.name)
        expected_size = end - start
        source = source_root / f"{spec_entry.name}.s"
        archive_path = archive_path_from_include(spec_entry.include)
        data = ensure_exact_size(dump_data_section(source, temp_dir), expected_size, spec_entry.name, allow_pad=True)
        write_asset(output_root, archive_path, data)
        entries.append(RuntimeAssetEntry(start, end, archive_path))

    return entries


def stage_spec_asm_assets_by_order(
    spec_path: Path,
    source_root: Path,
    range_csv_path: Path,
    output_root: Path,
    temp_dir: Path,
) -> list[RuntimeAssetEntry]:
    entries: list[RuntimeAssetEntry] = []
    spec_entries = parse_spec(spec_path)
    range_entries = parse_range_csv(range_csv_path)

    if len(spec_entries) != len(range_entries):
        raise RuntimeError(
            f"{spec_path.name}: spec count ({len(spec_entries)}) does not match range count ({len(range_entries)})"
        )

    for spec_entry, range_entry in zip(spec_entries, range_entries):
        expected_size = range_entry.end - range_entry.start
        source = source_root / f"{spec_entry.name}.s"
        archive_path = archive_path_from_include(spec_entry.include)
        data = ensure_exact_size(dump_data_section(source, temp_dir), expected_size, spec_entry.name, allow_pad=True)
        write_asset(output_root, archive_path, data)
        entries.append(RuntimeAssetEntry(range_entry.start, range_entry.end, archive_path))

    return entries


def stage_spec_copy_assets(spec_path: Path, output_root: Path, source_resolver) -> list[RuntimeAssetEntry]:
    entries: list[RuntimeAssetEntry] = []

    for spec_entry in parse_spec(spec_path):
        start, end = segment_range(spec_entry.name)
        expected_size = end - start
        source = source_resolver(spec_entry)
        archive_path = archive_path_from_include(spec_entry.include)
        data = ensure_exact_size(source.read_bytes(), expected_size, spec_entry.name)
        write_asset(output_root, archive_path, data)
        entries.append(RuntimeAssetEntry(start, end, archive_path))

    return entries


def stage_font_assets(output_root: Path) -> list[RuntimeAssetEntry]:
    entries: list[RuntimeAssetEntry] = []
    font_assets_root = HM64_IMPORTED_ASSETS_ROOT / "font"

    with tempfile.TemporaryDirectory() as temp_dir_name:
        temp_dir = Path(temp_dir_name)
        built_texture = temp_dir / "fontTexture.bin"
        assemble_font_texture(font_assets_root / "fontTexture.ci2", built_texture)

        for name, built_path in (
            ("fontTexture", built_texture),
            ("fontPalette1", temp_dir / "fontPalette1.bin"),
            ("fontPalette2", temp_dir / "fontPalette2.bin"),
            ("fontPalette3", temp_dir / "fontPalette3.bin"),
        ):
            if name != "fontTexture":
                palette_index = name[-1]
                assemble_font_palette(font_assets_root / f"fontPalette{palette_index}.pal", built_path)

            start, end = segment_range(name)
            archive_path = RUNTIME_ROM_ROOT / "font" / built_path.name
            data = ensure_exact_size(built_path.read_bytes(), end - start, name)
            write_asset(output_root, archive_path, data)
            entries.append(RuntimeAssetEntry(start, end, archive_path))

    return entries


def stage_sprite_assets(output_root: Path) -> list[RuntimeAssetEntry]:
    entries: list[RuntimeAssetEntry] = []

    with tempfile.TemporaryDirectory() as temp_dir_name:
        sprite_work_root = Path(temp_dir_name)
        for info in get_all_sprites():
            source_dir = HM64_IMPORTED_ASSETS_ROOT / "sprites" / info.subdir / info.label
            staged_output = sprite_work_root / info.label
            if not assemble_sprite(source_dir, staged_output):
                raise RuntimeError(f"Failed to assemble sprite asset {source_dir}")

            archive_base = RUNTIME_ROM_ROOT / "sprites" / info.subdir / info.label
            texture_name = f"{info.label}Texture.bin"
            assets_index_name = f"{info.label}AssetsIndex.bin"

            texture_data = ensure_exact_size(
                (staged_output / texture_name).read_bytes(),
                info.addr_index - info.addr_base,
                texture_name,
                allow_pad=True,
            )
            write_asset(output_root, archive_base / texture_name, texture_data)
            entries.append(RuntimeAssetEntry(info.addr_base, info.addr_index, archive_base / texture_name))

            if info.is_type1:
                assert info.spritesheet_index_base is not None
                assert info.spritesheet_index_end is not None
                assets_index_end = info.spritesheet_index_base
            else:
                assert info.addr_extra is not None
                assets_index_end = info.addr_extra

            assets_index_data = ensure_exact_size(
                (staged_output / assets_index_name).read_bytes(),
                assets_index_end - info.addr_index,
                assets_index_name,
                allow_pad=True,
            )
            write_asset(output_root, archive_base / assets_index_name, assets_index_data)
            entries.append(RuntimeAssetEntry(info.addr_index, assets_index_end, archive_base / assets_index_name))

            if info.is_type1:
                spritesheet_index_name = f"{info.label}SpritesheetIndex.bin"
                spritesheet_index_data = ensure_exact_size(
                    (staged_output / spritesheet_index_name).read_bytes(),
                    info.spritesheet_index_end - info.spritesheet_index_base,
                    spritesheet_index_name,
                    allow_pad=True,
                )
                write_asset(output_root, archive_base / spritesheet_index_name, spritesheet_index_data)
                entries.append(
                    RuntimeAssetEntry(
                        info.spritesheet_index_base,
                        info.spritesheet_index_end,
                        archive_base / spritesheet_index_name,
                    )
                )

    return entries


def generate_runtime_table(table_header: Path, entries: list[RuntimeAssetEntry]) -> None:
    table_header.parent.mkdir(parents=True, exist_ok=True)

    sorted_entries = sorted(entries, key=lambda entry: entry.start)
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

    for entry in sorted_entries:
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

    table_header.write_text("\n".join(lines))


def stage_all_assets(output_root: Path, table_header: Path) -> None:
    entries: list[RuntimeAssetEntry] = []

    entries.extend(stage_font_assets(output_root))
    entries.extend(stage_sprite_assets(output_root))

    with tempfile.TemporaryDirectory() as temp_dir_name:
        temp_dir = Path(temp_dir_name)
        entries.extend(
            stage_spec_asm_assets_by_order(
                HM64_IMPORTED_ASSETS_ROOT / "cutscenes/cutscenes.spec",
                HM64_IMPORTED_ASSETS_ROOT / "cutscenes",
                HM64_ROOT / "tools/libhm64/data/cutscene_addresses.csv",
                output_root,
                temp_dir,
            )
        )
        entries.extend(
            stage_spec_asm_assets(
                HM64_IMPORTED_ASSETS_ROOT / "dialogues/dialogues.spec",
                HM64_IMPORTED_ASSETS_ROOT / "dialogues",
                output_root,
                temp_dir,
            )
        )
        entries.extend(
            stage_spec_asm_assets(
                HM64_IMPORTED_ASSETS_ROOT / "text/texts.spec",
                HM64_IMPORTED_ASSETS_ROOT / "text",
                output_root,
                temp_dir,
            )
        )

    entries.extend(
        stage_spec_copy_assets(
            HM64_IMPORTED_ASSETS_ROOT / "maps/maps.spec",
            output_root,
            lambda spec_entry: HM64_IMPORTED_ASSETS_ROOT / archive_path_from_include(spec_entry.include).relative_to(RUNTIME_ROM_ROOT),
        )
    )
    entries.extend(
        stage_spec_copy_assets(
            HM64_IMPORTED_ASSETS_ROOT / "audio/sequences.spec",
            output_root,
            lambda spec_entry: HM64_IMPORTED_ASSETS_ROOT / archive_path_from_include(spec_entry.include).relative_to(RUNTIME_ROM_ROOT),
        )
    )
    entries.extend(
        stage_spec_copy_assets(
            HM64_IMPORTED_ASSETS_ROOT / "audio/waveTable.spec",
            output_root,
            lambda spec_entry: HM64_DECOMP_ROOT / "bin" / "audio" / f"{spec_entry.name}.bin",
        )
    )

    generate_runtime_table(table_header, entries)


def main() -> int:
    parser = argparse.ArgumentParser(description="Stage archive-backed HM64 runtime assets")
    parser.add_argument("--output-dir", required=True, type=Path, help="Custom asset root directory")
    parser.add_argument("--table-header", required=True, type=Path, help="Generated ROM-range table header")
    args = parser.parse_args()

    output_root = args.output_dir.resolve()
    table_header = args.table_header.resolve()

    if output_root.exists():
        shutil.rmtree(output_root)
    output_root.mkdir(parents=True, exist_ok=True)

    stage_all_assets(output_root, table_header)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
