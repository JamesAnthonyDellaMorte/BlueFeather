#!/usr/bin/env python3
"""
HM64 Cutscene Bytecode Converter
Converts raw N64 bytecode to PC-friendly format with variable indices.

Shipwright-style approach:
- Parse raw bytecode from ROM
- Identify pointer fields (N64 addresses starting with 0x80)
- Replace with variable indices
- Output clean bytecode for PC runtime
"""

import struct
import sys
from pathlib import Path
from typing import Optional, Dict, Tuple

# Variable address to index mapping
# These addresses are from config/us/symbol_addrs.txt
VARIABLE_MAP = {
    0x801891D4: 1,  # VAR_CUTSCENE_COMPLETION_FLAGS
    0x801C3B66: 2,  # VAR_CUTSCENE_INDEX
    0x8016FE00: 3,  # VAR_CUTSCENE_FLAGS
    0x801FB5CA: 4,  # VAR_HOUR
}

# Command handlers that contain pointers (need conversion)
# Format: opcode -> (command_size, pointer_offsets)
# pointer_offsets is list of byte offsets within command where pointers are stored
# These indices are from cutsceneCommandHandlers[] array in cutscene.c
POINTER_COMMANDS = {
    # gameStatus commands - verified from cutscene.h structs
    17: (8, [4]),      # SET_U8_VALUE - u8 at offset 0, then padding, ptr at offset 4?
    18: (8, [4]),      # SET_U16_VALUE - u16 unk_2 at offset 2, u16* unk_4 at offset 4
    19: (12, [8]),     # SET_U32_VALUE - u32 cutsceneIndex at offset 4, u32* cutsceneIndexPtr at offset 8
    20: (12, [8]),     # BRANCH_U8_VAR_IN_RANGE - u8* variablePtr at offset 8
    21: (16, [8]),     # BRANCH_U16_VAR_IN_RANGE - u16* variablePtr at offset 8 (after functionIndex, min, max, unk_6)
    22: (16, [12]),    # BRANCH_U32_VAR_IN_RANGE - u32* variablePtr at offset 12
    23: (8, [4]),      # SET_SPECIAL_BIT - s32* bitfield at offset 4
    24: (8, [4]),      # CLEAR_SPECIAL_BIT - u32* bitfield at offset 4
    25: (12, [4]),     # BRANCH_ON_SPECIAL_BIT - u32* bitfield at offset 4
    
    # graphics update commands
    43: (12, [8]),     # UPDATE_U8_VALUE - u8* valuePtr at offset 8
    44: (12, [8]),     # UPDATE_U16_VALUE - u16* valuePtr at offset 8
    45: (16, [12]),    # UPDATE_U32_VALUE - u32* valuePtr at offset 12
    
    # branch commands with pointer comparisons
    61: (20, [8, 12]), # BRANCH_IF_U16_PTR_IN_RANGE - u16* unk_4 at offset 8, u16* unk_8 at offset 12
    67: (20, [8, 12]), # BRANCH_IF_U8_PTR_IN_RANGE - u8* unk_4 at offset 8, u8* unk_8 at offset 12
    
    # audio commands
    68: (16, [8, 12]), # SET_AUDIO_SEQUENCE - u8* sequenceStart at offset 8, u8* sequenceEnd at offset 12
}

# Commands that may need special handling:
# - SET_CALLBACK_BYTECODE_PTR (40): Uses relative offset, not absolute pointer
# - SPAWN_EXECUTOR (11): Uses executor index, not pointer


def convert_pointer_field(data: bytes, offset: int) -> bytes:
    """Convert a 32-bit pointer field from N64 address to variable index."""
    # Read big-endian 32-bit value
    ptr = struct.unpack('>I', data[offset:offset+4])[0]
    
    # Check if it's a known variable address
    if ptr in VARIABLE_MAP:
        # Replace with variable index
        index = VARIABLE_MAP[ptr]
        return struct.pack('>I', index)
    
    # Check if it's in N64 RAM range
    if 0x80000000 <= ptr < 0x80400000:
        # Unknown N64 address - print warning
        print(f"Warning: Unknown N64 address 0x{ptr:08X}", file=sys.stderr)
        # Keep original for now (will need manual mapping)
        return data[offset:offset+4]
    
    # Not a pointer (probably an offset or other data)
    return data[offset:offset+4]


def convert_command(opcode: int, data: bytes) -> bytes:
    """Convert a single bytecode command."""
    if opcode not in POINTER_COMMANDS:
        # No pointers in this command
        return data
    
    expected_size, pointer_offsets = POINTER_COMMANDS[opcode]
    
    if len(data) != expected_size:
        print(f"Warning: Command 0x{opcode:02X} has unexpected size {len(data)}, expected {expected_size}", 
              file=sys.stderr)
        return data
    
    # Convert each pointer field
    result = bytearray(data)
    for offset in pointer_offsets:
        converted = convert_pointer_field(data, offset)
        result[offset:offset+4] = converted
    
    return bytes(result)


def convert_bytecode(input_data: bytes) -> bytes:
    """Convert entire bytecode buffer."""
    output = bytearray(input_data)  # Start with copy of input
    pos = 0
    converted_count = 0
    
    while pos < len(input_data):
        if pos + 2 > len(input_data):
            break
        
        # Read opcode (big-endian 16-bit)
        opcode = struct.unpack('>H', input_data[pos:pos+2])[0]
        
        # Check if this command has pointers to convert
        if opcode in POINTER_COMMANDS:
            cmd_size, pointer_offsets = POINTER_COMMANDS[opcode]
            
            # Ensure we have full command
            if pos + cmd_size > len(input_data):
                print(f"Warning: Truncated command at offset 0x{pos:04X}")
                break
            
            # Convert each pointer field
            for offset in pointer_offsets:
                ptr_pos = pos + offset
                if ptr_pos + 4 > len(input_data):
                    continue
                
                # Read original pointer
                old_ptr = struct.unpack('>I', input_data[ptr_pos:ptr_pos+4])[0]
                
                # Check if it's a known variable
                if old_ptr in VARIABLE_MAP:
                    new_val = VARIABLE_MAP[old_ptr]
                    # Write converted value (as 32-bit big-endian)
                    output[ptr_pos:ptr_pos+4] = struct.pack('>I', new_val)
                    converted_count += 1
                    print(f"  0x{pos:04X}: opcode {opcode} - Converted 0x{old_ptr:08X} -> index {new_val}")
                elif 0x80000000 <= old_ptr < 0x80400000:
                    print(f"  0x{pos:04X}: opcode {opcode} - WARNING: Unknown N64 address 0x{old_ptr:08X}")
            
            pos += cmd_size
        else:
            # Unknown command - skip just the opcode and try to continue
            # This is risky but helps us find more commands
            pos += 2
    
    print(f"Converted {converted_count} pointers")
    return bytes(output)


def extract_from_rom(rom_path: Path, start_addr: int, end_addr: int) -> bytes:
    """Extract bytecode from ROM file."""
    with open(rom_path, 'rb') as f:
        f.seek(start_addr)
        size = end_addr - start_addr
        return f.read(size)


def main():
    if len(sys.argv) < 3:
        print(f"Usage: {sys.argv[0]} <input.bin> <output.bin>", file=sys.stderr)
        print(f"   or: {sys.argv[0]} --rom <rom.z64> <start_addr> <end_addr> <output.bin>", file=sys.stderr)
        sys.exit(1)
    
    if sys.argv[1] == '--rom':
        # Extract from ROM
        rom_path = Path(sys.argv[2])
        start_addr = int(sys.argv[3], 0)  # Auto-detect base (0x prefix = hex)
        end_addr = int(sys.argv[4], 0)
        output_path = Path(sys.argv[5])
        
        print(f"Extracting from ROM: {rom_path}")
        print(f"Address range: 0x{start_addr:06X} - 0x{end_addr:06X}")
        
        input_data = extract_from_rom(rom_path, start_addr, end_addr)
    else:
        # Read from file
        input_path = Path(sys.argv[1])
        output_path = Path(sys.argv[2])
        
        print(f"Converting: {input_path}")
        
        with open(input_path, 'rb') as f:
            input_data = f.read()
    
    # Convert bytecode
    print(f"Input size: {len(input_data)} bytes")
    output_data = convert_bytecode(input_data)
    print(f"Output size: {len(output_data)} bytes")
    
    # Write output
    output_path.parent.mkdir(parents=True, exist_ok=True)
    with open(output_path, 'wb') as f:
        f.write(output_data)
    
    print(f"Written: {output_path}")


if __name__ == '__main__':
    main()
