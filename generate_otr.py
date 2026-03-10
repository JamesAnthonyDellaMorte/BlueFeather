#!/usr/bin/env python3
"""
HM64 OTR Archive Generator
Creates a minimal .otr archive for libultraship from extracted assets

The OTR format is MPQ-compatible (Blizzard archive format)
"""

import os
import sys
import struct
import json
from pathlib import Path

# Paths
SCRIPT_DIR = Path(__file__).parent.resolve()
ASSETS_DIR = SCRIPT_DIR.parent / "assets"
OUTPUT_DIR = SCRIPT_DIR / "build" / "bin"
OTR_FILE = OUTPUT_DIR / "hm64.otr"

def create_minimal_otr():
    """Create a minimal OTR file with just enough structure for libultraship"""
    
    print("[INFO] Creating minimal OTR archive for HM64...")
    print(f"[INFO] Assets source: {ASSETS_DIR}")
    print(f"[INFO] OTR output: {OTR_FILE}")
    
    # Ensure output directory exists
    OUTPUT_DIR.mkdir(parents=True, exist_ok=True)
    
    # For now, we'll create a simple placeholder
    # A real implementation would use StormLib to create a proper MPQ archive
    
    # Check if we have extracted assets
    if not ASSETS_DIR.exists():
        print(f"[ERROR] Assets directory not found: {ASSETS_DIR}")
        print("[INFO] Run 'make setup' in the main project first to extract assets")
        return False
    
    # List what assets we have
    print("\n[DEBUG] Found assets:")
    for category in ASSETS_DIR.iterdir():
        if category.is_dir():
            count = len(list(category.iterdir()))
            print(f"  - {category.name}: {count} files")
    
    # For now, create a placeholder file
    # A real OTR needs to be a valid MPQ with specific file structure
    # This is just to prevent the "archive not found" error
    
    # Create an empty file as placeholder
    # libultraship will likely fail to load this, but it won't crash on missing file
    OTR_FILE.touch()
    print(f"\n[WARN] Created placeholder OTR: {OTR_FILE}")
    print("[WARN] This is not a valid OTR file yet!")
    print("[INFO] A proper OTR generator needs to be implemented using StormLib")
    
    return True

def check_libultraship_otr_format():
    """Check what libultraship expects in an OTR file"""
    print("\n[DEBUG] Checking libultraship OTR requirements...")
    
    # Based on libultraship source, OTR files should contain:
    # - version info
    # - manifest.json or similar
    # - Assets in specific paths like:
    #   - textures/
    #   - models/
    #   - audio/
    #   - etc.
    
    print("[INFO] libultraship expects:")
    print("  - MPQ format archive (.otr extension)")
    print("  - Contains assets with specific path structure")
    print("  - May require version metadata")
    print("  - Asset loading through ResourceManager")

def main():
    print("=" * 60)
    print("HM64 OTR Archive Generator")
    print("=" * 60)
    
    # For now, just document what's needed
    check_libultraship_otr_format()
    
    if create_minimal_otr():
        print("\n[NOTE] To generate a proper OTR file, you need:")
        print("  1. StormLib library (MPQ read/write)")
        print("  2. Asset conversion pipeline (N64 formats → modern formats)")
        print("  3. Proper path structure for each asset type")
        print("\n[NOTE] See Ship of Harkinian's OTRExporter for reference implementation")
        return 0
    else:
        return 1

if __name__ == "__main__":
    sys.exit(main())
