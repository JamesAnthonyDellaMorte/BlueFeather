#!/usr/bin/env python3

from __future__ import annotations

import argparse
import re
import shutil
import subprocess
import sys
import tempfile
from pathlib import Path

TOOLS_ROOT = Path(__file__).resolve().parent
HM64_ROOT = TOOLS_ROOT.parent
sys.path.insert(0, str(TOOLS_ROOT))

from libhm64.sprites.assembler import assemble_sprite  # noqa: E402
from libhm64.data import ROM_SEGMENT_START_SYMBOLS, ROM_SEGMENT_END_SYMBOLS  # noqa: E402

MIPS_AS = Path("/opt/homebrew/bin/mips64-elf-as")
OBJCOPY = Path("llvm-objcopy")

ROM_SEGMENT_SYMBOL_VALUES = {
    symbol: addr
    for mapping in (ROM_SEGMENT_START_SYMBOLS, ROM_SEGMENT_END_SYMBOLS)
    for addr, symbol in mapping.items()
}

SPRITE_TARGETS = (
    {
        "source": HM64_ROOT / "assets/sprites/overlayScreens/titleSprites",
        "dest_dir": Path("runtime/rom/title"),
        "files": {
            "titleSpritesTexture.bin": 0x00DD38F0 - 0x00DBA100,
            "titleSpritesAssetsIndex.bin": 0x00DD3910 - 0x00DD38F0,
        },
    },
    {
        "source": HM64_ROOT / "assets/sprites/overlayScreens/dialogueButtonIcons",
        "dest_dir": Path("runtime/rom/title"),
        "files": {
            "dialogueButtonIconsTexture.bin": 0x00D49B80 - 0x00D47F00,
            "dialogueButtonIconsAssetsIndex.bin": 0x00D49BA0 - 0x00D49B80,
        },
    },
    {
        "source": HM64_ROOT / "assets/sprites/entitySprites/animals/dog",
        "dest_dir": Path("runtime/rom/title"),
        "files": {
            "dogTexture.bin": 0x00630EC0 - 0x0060EC20,
            "dogAssetsIndex.bin": 0x00630EE0 - 0x00630EC0,
            "dogSpritesheetIndex.bin": 0x00631400 - 0x00630EE0,
        },
    },
    {
        "source": HM64_ROOT / "assets/sprites/overlayScreens/logos",
        "dest_dir": Path("runtime/rom/title"),
        "files": {
            "logosTexture.bin": 0x00DD7750 - 0x00DD4800,
            "logosAssetsIndex.bin": 0x00DD7770 - 0x00DD7750,
        },
    },
    {
        "source": HM64_ROOT / "assets/sprites/effects/funeralIntro",
        "dest_dir": Path("runtime/rom/title"),
        "files": {
            "funeralIntroTexture.bin": 0x00CB4D10 - 0x00CAD610,
            "funeralIntroAssetsIndex.bin": 0x00CB4D30 - 0x00CB4D10,
        },
    },
    {
        "source": HM64_ROOT / "assets/sprites/entitySprites/player",
        "dest_dir": Path("runtime/rom/entitySprites/player"),
        "files": {
            "playerTexture.bin": 0x002D0660 - 0x00159330,
            "playerAssetsIndex.bin": 0x002D0680 - 0x002D0660,
            "playerSpritesheetIndex.bin": 0x002D15E0 - 0x002D0680,
        },
    },
    {
        "source": HM64_ROOT / "assets/sprites/entitySprites/shadows",
        "dest_dir": Path("runtime/rom/entitySprites/shadows"),
        "files": {
            "shadowsTexture.bin": 0x007FD1E0 - 0x007FCD10,
            "shadowsAssetsIndex.bin": 0x007FD200 - 0x007FD1E0,
        },
    },
    {
        "source": HM64_ROOT / "assets/sprites/entitySprites/npc/mayor",
        "dest_dir": Path("runtime/rom/entitySprites/npc/mayor"),
        "files": {
            "mayorTexture.bin": 0x00483D20 - 0x00477410,
            "mayorAssetsIndex.bin": 0x00483D40 - 0x00483D20,
            "mayorSpritesheetIndex.bin": 0x00483E80 - 0x00483D40,
        },
    },
    {
        "source": HM64_ROOT / "assets/sprites/entitySprites/npc/mayorWife",
        "dest_dir": Path("runtime/rom/entitySprites/npc/mayorWife"),
        "files": {
            "mayorWifeTexture.bin": 0x0048B570 - 0x00483E80,
            "mayorWifeAssetsIndex.bin": 0x0048B590 - 0x0048B570,
            "mayorWifeSpritesheetIndex.bin": 0x0048B620 - 0x0048B590,
        },
    },
    {
        "source": HM64_ROOT / "assets/sprites/entitySprites/npc/kent",
        "dest_dir": Path("runtime/rom/entitySprites/npc/kent"),
        "files": {
            "kentTexture.bin": 0x004DEF80 - 0x004CD890,
            "kentAssetsIndex.bin": 0x004DEFA0 - 0x004DEF80,
            "kentSpritesheetIndex.bin": 0x004DF110 - 0x004DEFA0,
        },
    },
    {
        "source": HM64_ROOT / "assets/sprites/entitySprites/npc/stu",
        "dest_dir": Path("runtime/rom/entitySprites/npc/stu"),
        "files": {
            "stuTexture.bin": 0x004E85D0 - 0x004DF110,
            "stuAssetsIndex.bin": 0x004E85F0 - 0x004E85D0,
            "stuSpritesheetIndex.bin": 0x004E86B0 - 0x004E85F0,
        },
    },
    {
        "source": HM64_ROOT / "assets/sprites/entitySprites/npc/midwife",
        "dest_dir": Path("runtime/rom/entitySprites/npc/midwife"),
        "files": {
            "midwifeTexture.bin": 0x004EFE00 - 0x004E86B0,
            "midwifeAssetsIndex.bin": 0x004EFE20 - 0x004EFE00,
            "midwifeSpritesheetIndex.bin": 0x004EFEB0 - 0x004EFE20,
        },
    },
    {
        "source": HM64_ROOT / "assets/sprites/entitySprites/npc/may",
        "dest_dir": Path("runtime/rom/entitySprites/npc/may"),
        "files": {
            "mayTexture.bin": 0x004F47F0 - 0x004EFEB0,
            "mayAssetsIndex.bin": 0x004F4810 - 0x004F47F0,
            "maySpritesheetIndex.bin": 0x004F4890 - 0x004F4810,
        },
    },
    {
        "source": HM64_ROOT / "assets/sprites/entitySprites/npc/rick",
        "dest_dir": Path("runtime/rom/entitySprites/npc/rick"),
        "files": {
            "rickTexture.bin": 0x004FBFF0 - 0x004F4890,
            "rickAssetsIndex.bin": 0x004FC010 - 0x004FBFF0,
            "rickSpritesheetIndex.bin": 0x004FC140 - 0x004FC010,
        },
    },
    {
        "source": HM64_ROOT / "assets/sprites/entitySprites/npc/pastor",
        "dest_dir": Path("runtime/rom/entitySprites/npc/pastor"),
        "files": {
            "pastorTexture.bin": 0x00503AB0 - 0x004FC140,
            "pastorAssetsIndex.bin": 0x00503AD0 - 0x00503AB0,
            "pastorSpritesheetIndex.bin": 0x00503BC0 - 0x00503AD0,
        },
    },
    {
        "source": HM64_ROOT / "assets/sprites/entitySprites/npc/shipper",
        "dest_dir": Path("runtime/rom/entitySprites/npc/shipper"),
        "files": {
            "shipperTexture.bin": 0x00518B00 - 0x00503BC0,
            "shipperAssetsIndex.bin": 0x00518B20 - 0x00518B00,
            "shipperSpritesheetIndex.bin": 0x00518BB0 - 0x00518B20,
        },
    },
    {
        "source": HM64_ROOT / "assets/sprites/entitySprites/npc/saibara",
        "dest_dir": Path("runtime/rom/entitySprites/npc/saibara"),
        "files": {
            "saibaraTexture.bin": 0x00520D00 - 0x00518BB0,
            "saibaraAssetsIndex.bin": 0x00520D20 - 0x00520D00,
            "saibaraSpritesheetIndex.bin": 0x00520DB0 - 0x00520D20,
        },
    },
    {
        "source": HM64_ROOT / "assets/sprites/entitySprites/npc/duke",
        "dest_dir": Path("runtime/rom/entitySprites/npc/duke"),
        "files": {
            "dukeTexture.bin": 0x005249E0 - 0x00520DB0,
            "dukeAssetsIndex.bin": 0x00524A00 - 0x005249E0,
            "dukeSpritesheetIndex.bin": 0x00524AE0 - 0x00524A00,
        },
    },
    {
        "source": HM64_ROOT / "assets/sprites/entitySprites/npc/greg",
        "dest_dir": Path("runtime/rom/entitySprites/npc/greg"),
        "files": {
            "gregTexture.bin": 0x0052F260 - 0x00524AE0,
            "gregAssetsIndex.bin": 0x0052F280 - 0x0052F260,
            "gregSpritesheetIndex.bin": 0x0052F370 - 0x0052F280,
        },
    },
    {
        "source": HM64_ROOT / "assets/sprites/entitySprites/npc/assistantCarpenter",
        "dest_dir": Path("runtime/rom/entitySprites/npc/assistantCarpenter"),
        "files": {
            "assistantCarpenterTexture.bin": 0x005488A0 - 0x0052F370,
            "assistantCarpenterAssetsIndex.bin": 0x005488C0 - 0x005488A0,
            "assistantCarpenterSpritesheetIndex.bin": 0x005489C0 - 0x005488C0,
        },
    },
    {
        "source": HM64_ROOT / "assets/sprites/entitySprites/npc/masterCarpenter",
        "dest_dir": Path("runtime/rom/entitySprites/npc/masterCarpenter"),
        "files": {
            "masterCarpenterTexture.bin": 0x00555460 - 0x005489C0,
            "masterCarpenterAssetsIndex.bin": 0x00555480 - 0x00555460,
            "masterCarpenterSpritesheetIndex.bin": 0x00555570 - 0x00555480,
        },
    },
    {
        "source": HM64_ROOT / "assets/sprites/entitySprites/npc/harvestSprite",
        "dest_dir": Path("runtime/rom/entitySprites/npc/harvestSprite"),
        "files": {
            "harvestSpriteTexture.bin": 0x0055A640 - 0x00555570,
            "harvestSpriteAssetsIndex.bin": 0x0055A660 - 0x0055A640,
            "harvestSpriteSpritesheetIndex.bin": 0x0055A730 - 0x0055A660,
        },
    },
    {
        "source": HM64_ROOT / "assets/sprites/entitySprites/npc/barley",
        "dest_dir": Path("runtime/rom/entitySprites/npc/barley"),
        "files": {
            "barleyTexture.bin": 0x00560330 - 0x0055A730,
            "barleyAssetsIndex.bin": 0x00560350 - 0x00560330,
            "barleySpritesheetIndex.bin": 0x005603D0 - 0x00560350,
        },
    },
)

CUTSCENE_TARGETS = (
    {
        "source": HM64_ROOT / "assets/cutscenes/farmBusiness.s",
        "dest": Path("runtime/rom/cutscenes/farmBusiness.bin"),
        "size": 0x10100180 - 0x100FF5C0,
    },
    {
        "source": HM64_ROOT / "assets/cutscenes/funeralIntro.s",
        "dest": Path("runtime/rom/cutscenes/funeralIntro.bin"),
        "size": 0x1014B8F0 - 0x10149CC0,
    },
    {
        "source": HM64_ROOT / "assets/cutscenes/demos.s",
        "dest": Path("runtime/rom/cutscenes/demos.bin"),
        "size": 0x10150120 - 0x1014B8F0,
    },
)

AUDIO_TARGETS = (
    ("opening.seq", 0x10FDAD00 - 0x10FD8510),
    ("title.seq", 0x10FDD6C0 - 0x10FDAD00),
    ("spring.seq", 0x10FE27B0 - 0x10FE12F0),
    ("namingScreen.seq", 0x10FE7E00 - 0x10FE6E60),
    ("mountain.seq", 0x10FF1CD0 - 0x10FEF9F0),
    ("village.seq", 0x10FF3760 - 0x10FF1CD0),
)


def run(cmd: list[str]) -> None:
    subprocess.run(cmd, check=True)


def ensure_exact_size(data: bytes, expected_size: int, label: str, *, allow_pad: bool = False) -> bytes:
    actual_size = len(data)
    if actual_size == expected_size:
        return data

    if allow_pad and actual_size < expected_size:
        return data + (b"\x00" * (expected_size - actual_size))

    raise RuntimeError(f"{label}: expected {expected_size} bytes, got {actual_size}")


def materialize_cutscene_source(source: Path, dest: Path) -> None:
    text = source.read_text()

    for symbol, addr in ROM_SEGMENT_SYMBOL_VALUES.items():
        text = re.sub(rf"\b{re.escape(symbol)}\b", f"0x{addr:08X}", text)

    dest.write_text(text)


def assemble_sprite_targets(output_root: Path) -> None:
    with tempfile.TemporaryDirectory() as temp_dir_name:
        sprite_work_root = Path(temp_dir_name)
        for target in SPRITE_TARGETS:
            staged_output = sprite_work_root / target["source"].name
            if not assemble_sprite(target["source"], staged_output):
                raise RuntimeError(f"Failed to assemble sprite asset {target['source']}")

            final_dir = output_root / target["dest_dir"]
            final_dir.mkdir(parents=True, exist_ok=True)

            for filename, expected_size in target["files"].items():
                built_file = staged_output / filename
                if not built_file.exists():
                    raise RuntimeError(f"Missing assembled sprite file {built_file}")
                data = ensure_exact_size(built_file.read_bytes(), expected_size, filename)
                (final_dir / filename).write_bytes(data)


def assemble_cutscene_targets(output_root: Path) -> None:
    cutscene_dir = output_root / "runtime/rom/cutscenes"
    cutscene_dir.mkdir(parents=True, exist_ok=True)

    with tempfile.TemporaryDirectory() as temp_dir_name:
        temp_dir = Path(temp_dir_name)
        for target in CUTSCENE_TARGETS:
            asm_path = temp_dir / f"{target['source'].stem}.s"
            obj_path = temp_dir / f"{target['source'].stem}.o"
            bin_path = temp_dir / f"{target['source'].stem}.bin"
            materialize_cutscene_source(target["source"], asm_path)
            run([str(MIPS_AS), "-march=vr4300", "-mabi=32", "-o", str(obj_path), str(asm_path)])
            # Cutscene assembly lives in .data; exporting the whole object prepends
            # MIPS metadata sections before the bytecode.
            run([str(OBJCOPY), f"--dump-section", f".data={bin_path}", str(obj_path)])
            data = ensure_exact_size(bin_path.read_bytes(), target["size"], target["dest"].name, allow_pad=True)
            (output_root / target["dest"]).write_bytes(data)


def copy_audio_targets(output_root: Path) -> None:
    audio_dir = output_root / "runtime/rom/audio"
    audio_dir.mkdir(parents=True, exist_ok=True)
    source_dir = HM64_ROOT / "assets/audio/sequences"
    for filename, expected_size in AUDIO_TARGETS:
        source_file = source_dir / filename
        data = ensure_exact_size(source_file.read_bytes(), expected_size, filename)
        (audio_dir / filename).write_bytes(data)


def main() -> int:
    parser = argparse.ArgumentParser(description="Stage custom startup assets for Moonwright.o2r")
    parser.add_argument("--output-dir", required=True, type=Path, help="Custom asset root directory")
    args = parser.parse_args()

    output_root = args.output_dir.resolve()
    if output_root.exists():
        shutil.rmtree(output_root)
    output_root.mkdir(parents=True, exist_ok=True)

    assemble_sprite_targets(output_root)
    assemble_cutscene_targets(output_root)
    copy_audio_targets(output_root)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
