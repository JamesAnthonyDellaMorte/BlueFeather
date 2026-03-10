#!/usr/bin/env python3
"""
Moonwright O2R Archive Generator

Generates an .o2r archive (zip format) from extracted HM64 assets.
This follows the Shipwright/Ship of Harkinian format.

Usage:
    python3 generate_o2r.py
"""

import os
import sys
import json
import zipfile
from pathlib import Path
from datetime import datetime

# Paths
SCRIPT_DIR = Path(__file__).parent.resolve()
ASSETS_DIR = SCRIPT_DIR.parent / "assets"
OUTPUT_FILE = SCRIPT_DIR / "build" / "bin" / "hm64.o2r"

def add_file_to_o2r(zf, source_path, archive_path):
    """Add a file to the O2R archive"""
    if source_path.is_file():
        print(f"  Adding: {archive_path}")
        zf.write(source_path, archive_path)
        return True
    return False

def generate_o2r():
    """Generate the Moonwright O2R archive"""
    
    print("=" * 60)
    print("Moonwright O2R Archive Generator")
    print("=" * 60)
    print(f"Assets source: {ASSETS_DIR}")
    print(f"Output file: {OUTPUT_FILE}")
    print()
    
    # Ensure output directory exists
    OUTPUT_FILE.parent.mkdir(parents=True, exist_ok=True)
    
    # Create O2R archive (it's just a zip file)
    with zipfile.ZipFile(OUTPUT_FILE, 'w', zipfile.ZIP_DEFLATED) as zf:
        
        # Add version info
        version_info = {
            "game": "Harvest Moon 64",
            "version": "1.0.0",
            "generated": datetime.now().isoformat(),
            "format": "o2r"
        }
        zf.writestr("version.json", json.dumps(version_info, indent=2))
        print("  Added: version.json")
        
        # Add manifest of all assets
        manifest = {
            "sprites": [],
            "textures": [],
            "audio": [],
            "maps": []
        }
        
        # Add sprite textures
        sprite_dirs = [
            "sprites/entitySprites/player/textures",
            "sprites/entitySprites/npc/textures", 
            "sprites/entitySprites/animals/textures",
            "sprites/mapObjects",
            "sprites/effects",
        ]
        
        for sprite_dir in sprite_dirs:
            full_path = ASSETS_DIR / sprite_dir
            if full_path.exists():
                for file in sorted(full_path.glob("*.png")):
                    archive_path = f"textures/{sprite_dir.replace('/', '_')}/{file.name}"
                    if add_file_to_o2r(zf, file, archive_path):
                        manifest["textures"].append({
                            "path": archive_path,
                            "source": str(file.relative_to(ASSETS_DIR)),
                            "format": "png"
                        })
        
        # Add map data
        map_dir = ASSETS_DIR / "maps"
        if map_dir.exists():
            for file in sorted(map_dir.rglob("*.json")):
                archive_path = f"maps/{file.relative_to(ASSETS_DIR)}"
                if add_file_to_o2r(zf, file, archive_path):
                    manifest["maps"].append({
                        "path": archive_path,
                        "source": str(file.relative_to(ASSETS_DIR))
                    })
        
        # Add dialogue
        dialogue_dir = ASSETS_DIR / "dialogues"
        if dialogue_dir.exists():
            for file in sorted(dialogue_dir.glob("*.json")):
                archive_path = f"dialogue/{file.name}"
                if add_file_to_o2r(zf, file, archive_path):
                    manifest["sprites"].append({
                        "path": archive_path,
                        "source": str(file.relative_to(ASSETS_DIR))
                    })
        
        # Add audio
        audio_dir = ASSETS_DIR / "audio"
        if audio_dir.exists():
            for file in sorted(audio_dir.rglob("*.wav")):
                archive_path = f"audio/{file.relative_to(ASSETS_DIR)}"
                if add_file_to_o2r(zf, file, archive_path):
                    manifest["audio"].append({
                        "path": archive_path,
                        "source": str(file.relative_to(ASSETS_DIR))
                    })
        
        # Write manifest
        zf.writestr("manifest.json", json.dumps(manifest, indent=2))
        print("  Added: manifest.json")
        
        # Add a simple README
        readme = """# Harvest Moon 64 O2R Archive

This archive contains assets for Moonwright.

## Structure

- `textures/` - Sprite and texture files (PNG format)
- `maps/` - Map data (JSON format)
- `dialogue/` - Dialogue text (JSON format)
- `audio/` - Audio files (WAV format)
- `manifest.json` - Asset manifest
- `version.json` - Version information

## Format

O2R files are standard ZIP archives with a custom extension.
They can be opened with any ZIP tool.
"""
        zf.writestr("README.txt", readme)
        print("  Added: README.txt")
    
    print()
    print(f"Successfully generated: {OUTPUT_FILE}")
    print(f"Archive size: {OUTPUT_FILE.stat().st_size / 1024:.1f} KB")
    
    # Print summary
    print()
    print("Asset Summary:")
    print(f"  Textures: {len(manifest['textures'])}")
    print(f"  Maps: {len(manifest['maps'])}")
    print(f"  Audio: {len(manifest['audio'])}")
    print(f"  Other: {len(manifest['sprites'])}")
    
    return True

if __name__ == "__main__":
    try:
        generate_o2r()
    except Exception as e:
        print(f"Error: {e}")
        sys.exit(1)
