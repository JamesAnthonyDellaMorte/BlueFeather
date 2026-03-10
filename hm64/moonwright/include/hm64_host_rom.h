#ifndef HM64_HOST_ROM_H
#define HM64_HOST_ROM_H

#include <stdint.h>

#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

bool HM64Host_LoadTitleRomSegments(void);
bool HM64Host_ReadRom(uintptr_t romAddr, void* bufPtr, u32 size);
void HM64Host_SetExecutablePath(const char* executablePath);

// Full ROM loading
bool HM64Host_LoadFullRom(void);
const uint8_t* HM64Host_GetRomPointer(uintptr_t romAddr);
size_t HM64Host_GetRomSize(void);

#ifdef __cplusplus
}
#endif

// Macro to reference ROM symbols
// Returns a pointer that can have & taken (static const void*)
#define HM64_ROM_SYMBOL(addr) (*(const void**)(uintptr_t)(addr))

#define HM64_ROM_TITLE_SPRITES_TEXTURE_START 0x00DBA100u
#define HM64_ROM_TITLE_SPRITES_TEXTURE_END   0x00DD38F0u

#define HM64_ROM_TITLE_SPRITES_INDEX_START   0x00DD38F0u
#define HM64_ROM_TITLE_SPRITES_INDEX_END     0x00DD3910u

#define HM64_ROM_DIALOGUE_ICONS_TEXTURE_START 0x00D47F00u
#define HM64_ROM_DIALOGUE_ICONS_TEXTURE_END   0x00D49B80u

#define HM64_ROM_DIALOGUE_ICONS_INDEX_START 0x00D49B80u
#define HM64_ROM_DIALOGUE_ICONS_INDEX_END   0x00D49BA0u

#define HM64_ROM_DOG_TEXTURE_START 0x0060EC20u
#define HM64_ROM_DOG_TEXTURE_END   0x00630EC0u

#define HM64_ROM_DOG_INDEX_START 0x00630EC0u
#define HM64_ROM_DOG_INDEX_END   0x00630EE0u

#define HM64_ROM_DOG_SHEET_START 0x00630EE0u
#define HM64_ROM_DOG_SHEET_END   0x00631400u

#define HM64_ROM_LOGOS_TEXTURE_START 0x00DD4800u
#define HM64_ROM_LOGOS_TEXTURE_END   0x00DD7750u

#define HM64_ROM_LOGOS_INDEX_START 0x00DD7750u
#define HM64_ROM_LOGOS_INDEX_END   0x00DD7770u

#define HM64_ROM_FUNERAL_INTRO_SPRITES_TEXTURE_START 0x00CAD610u
#define HM64_ROM_FUNERAL_INTRO_SPRITES_TEXTURE_END   0x00CB4D10u

#define HM64_ROM_FUNERAL_INTRO_SPRITES_INDEX_START 0x00CB4D10u
#define HM64_ROM_FUNERAL_INTRO_SPRITES_INDEX_END   0x00CB4D30u

// Cutscene segments for intro (extracted from ROM)
// Addresses from tools/libhm64/data/symbols.py + 0x10000000 (ROM base)
#define HM64_ROM_FARM_BUSINESS_START 0x10149A50u
#define HM64_ROM_FARM_BUSINESS_END   0x10149CC0u  // ~624 bytes

#define HM64_ROM_FUNERAL_INTRO_START 0x10149CC0u
#define HM64_ROM_FUNERAL_INTRO_END   0x1014B8F0u  // ~7216 bytes

#define HM64_ROM_DEMOS_START 0x1014B8F0u
#define HM64_ROM_DEMOS_END   0x1014C880u  // ~3984 bytes

#endif
