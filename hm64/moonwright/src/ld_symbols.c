#include "common.h"
#include "ld_symbols.h"
#include "hm64_ram.h"

// ============================================================================
// PC port: Variable index system (Shipwright-style)
// Instead of embedding N64 addresses in bytecode, use indices
// ============================================================================

typedef enum {
    VAR_NONE = 0,
    VAR_CUTSCENE_COMPLETION_FLAGS,  // 0x801891D4
    VAR_CUTSCENE_INDEX,             // 0x801C3B66
    VAR_CUTSCENE_FLAGS,             // 0x8016FE00
    VAR_HOUR,                       // 0x801FB5CA
    VAR_COUNT
} CutsceneVariableIndex;

// Map variable indices to PC pointers
void* HM64_GetVariablePointer(CutsceneVariableIndex index) {
    switch (index) {
        case VAR_CUTSCENE_COMPLETION_FLAGS: {
            extern s32 gCutsceneCompletionFlags;
            return &gCutsceneCompletionFlags;
        }
        case VAR_CUTSCENE_INDEX: {
            extern u16 gCutsceneIndex;
            return &gCutsceneIndex;
        }
        case VAR_CUTSCENE_FLAGS: {
            extern u32 gCutsceneFlags;
            return &gCutsceneFlags;
        }
        case VAR_HOUR: {
            extern u8 gHour;
            return &gHour;
        }
        default:
            return NULL;
    }
}

// ============================================================================
// PC RAM buffer storage - actual allocated memory
// Maps N64 RAM addresses to PC pointers
// ============================================================================

// Cutscene bytecode lives inside the host RAM shadow so the N64 virtual layout
// remains contiguous across both 64 KB banks.
#define HM64_CUTSCENE_BYTECODE_BUFFER_1 (&gHM64Ram[0x002F4000])
#define HM64_CUTSCENE_BYTECODE_BUFFER_2 (&gHM64Ram[0x002F5000])

// Shadow buffers (0x8023B400 - 0x8023BC00)
static u8 gShadowTextureBuffer[0x2000];
static u16 gShadowPaletteBuffer[256];

// Player buffers (0x8023C000 - 0x80244200)
static u8 gPlayerTexture1[0x4000];
static u8 gPlayerTexture2[0x4000];
static u16 gPlayerPalette[256];

// Chicken/entity slot 2-7 buffers
static u8 gEntityRegionChickenBase[0x4000];
static u8 gEntityRegionChickBase[0x1000];

// Ground objects
static u8 gGroundObjectsTexture[0x10000];

// Font buffers (0x802FF000 - 0x8030A800)
static u8 gFontTexture[0xB000];
static u16 gFontPalette1[256];
static u16 gFontPalette2[256];

// ============================================================================
// PC port runtime buffer pointer exports
// ============================================================================

void* g_PC_CutsceneBytecodeBuffer1 = HM64_CUTSCENE_BYTECODE_BUFFER_1;
void* g_PC_CutsceneBytecodeBuffer2 = HM64_CUTSCENE_BYTECODE_BUFFER_2;

// Pointer aliases for pc_buffers.h
void* CUTSCENE_BYTECODE_BUFFER_1_PTR = HM64_CUTSCENE_BYTECODE_BUFFER_1;
void* CUTSCENE_BYTECODE_BUFFER_2_PTR = HM64_CUTSCENE_BYTECODE_BUFFER_2;
void* ENTITY_REGION_CHICKEN_BASE_PTR = gEntityRegionChickenBase;
void* ENTITY_REGION_CHICK_BASE_PTR = gEntityRegionChickBase;
void* SHADOW_TEXTURE_BUFFER_PTR = gShadowTextureBuffer;
void* SHADOW_PALETTE_BUFFER_PTR = gShadowPaletteBuffer;
void* SHADOW_ANIMATION_FRAME_METADATA_BUFFER_PTR = NULL;  // TODO: allocate
void* SHADOW_TEXTURE_TO_PALETTE_LOOKUP_BUFFER_PTR = NULL;  // TODO: allocate
void* PLAYER_TEXTURE_1_BUFFER_PTR = gPlayerTexture1;
void* PLAYER_TEXTURE_2_BUFFER_PTR = gPlayerTexture2;
void* PLAYER_PALETTE_BUFFER_PTR = gPlayerPalette;
void* PLAYER_ANIMATION_FRAME_METADATA_BUFFER_PTR = NULL;  // TODO: allocate
void* PLAYER_SPRITESHEET_INDEX_BUFFER_PTR = NULL;  // TODO: allocate
void* PLAYER_TEXTURE_TO_PALETTE_LOOKUP_BUFFER_PTR = NULL;  // TODO: allocate
void* ENTITY_SLOTS_1_20_PALETTE_PTR = NULL;  // TODO: allocate
void* ENTITY_SLOTS_1_20_ANIM_METADATA_PTR = NULL;  // TODO: allocate
void* ENTITY_SLOTS_1_20_SPRITESHEET_INDEX_PTR = NULL;  // TODO: allocate
void* ENTITY_SLOTS_1_20_TEXTURE_TO_PALETTE_LOOKUP_PTR = NULL;  // TODO: allocate
void* ENTITY_SLOTS_2_7_PALETTE_PTR = NULL;  // TODO: allocate
void* ENTITY_SLOTS_2_7_ANIM_METADATA_PTR = NULL;  // TODO: allocate
void* ENTITY_SLOTS_2_7_SPRITESHEET_INDEX_PTR = NULL;  // TODO: allocate
void* ENTITY_SLOTS_2_7_TEXTURE_TO_PALETTE_LOOKUP_PTR = NULL;  // TODO: allocate
void* GROUND_OBJECTS_TEXTURE_BUFFER_PTR = gGroundObjectsTexture;
void* GROUND_OBJECTS_PALETTE_BUFFER_PTR = NULL;  // TODO: allocate
void* GROUND_OBJECTS_SPRITE_TO_PALETTE_LOOKUP_BUFFER_PTR = NULL;  // TODO: allocate
void* g_PC_ShadowTextureBuffer = gShadowTextureBuffer;
void* g_PC_ShadowPaletteBuffer = gShadowPaletteBuffer;
void* g_PC_PlayerTexture1Buffer = gPlayerTexture1;
void* g_PC_PlayerTexture2Buffer = gPlayerTexture2;
void* g_PC_PlayerPaletteBuffer = gPlayerPalette;
void* g_PC_EntityChickenBase = gEntityRegionChickenBase;
void* g_PC_EntityChickBase = gEntityRegionChickBase;
void* g_PC_GroundObjectsTextureBuffer = gGroundObjectsTexture;
void* g_PC_FontTextureBuffer = gFontTexture;
void* g_PC_FontPalette1Buffer = gFontPalette1;
void* g_PC_FontPalette2Buffer = gFontPalette2;

// ============================================================================
// Address translation function
// Maps N64 RAM addresses to PC pointers
// ============================================================================

// Prevent compiler from breaking this with bad optimizations
#pragma clang optimize off
void* HM64_TranslateAddress(u32 n64Addr) {
    // Keep cutscene bytecode in the mirrored N64 RAM image so banks 1 and 2
    // are contiguous and preserve the original virtual-address layout.
    if (n64Addr >= 0x802F4000 && n64Addr < 0x80300000) {
        return &gHM64Ram[(uintptr_t)n64Addr - (uintptr_t)HM64_RAM_BASE];
    }
    
    // Shadow buffers (0x8023B400 - 0x8023BC00)
    if (n64Addr >= 0x8023B400 && n64Addr < 0x8023B600) {
        return (u8*)gShadowTextureBuffer + (n64Addr - 0x8023B400);
    }
    if (n64Addr >= 0x8023B600 && n64Addr < 0x8023B800) {
        return (u8*)gShadowPaletteBuffer + (n64Addr - 0x8023B600);
    }
    
    // Player buffers (0x8023C000 - 0x80244200)
    if (n64Addr >= 0x8023C000 && n64Addr < 0x80240000) {
        return (u8*)gPlayerTexture1 + (n64Addr - 0x8023C000);
    }
    if (n64Addr >= 0x80240000 && n64Addr < 0x80244000) {
        return (u8*)gPlayerTexture2 + (n64Addr - 0x80240000);
    }
    if (n64Addr >= 0x80244000 && n64Addr < 0x80244200) {
        return (u8*)gPlayerPalette + (n64Addr - 0x80244000);
    }
    
    // Entity chicken base (0x80272800 - 0x80276800)
    if (n64Addr >= 0x80272800 && n64Addr < 0x80276800) {
        return (u8*)gEntityRegionChickenBase + (n64Addr - 0x80272800);
    }
    
    // Entity chick base (0x80277300 - 0x80278300)
    if (n64Addr >= 0x80277300 && n64Addr < 0x80278300) {
        return (u8*)gEntityRegionChickBase + (n64Addr - 0x80277300);
    }
    
    // Ground objects (0x80255600 - 0x80265600)
    if (n64Addr >= 0x80255600 && n64Addr < 0x80265600) {
        return (u8*)gGroundObjectsTexture + (n64Addr - 0x80255600);
    }
    
    // Font texture (0x802FF000 - 0x8030A000)
    if (n64Addr >= 0x802FF000 && n64Addr < 0x8030A000) {
        return (u8*)gFontTexture + (n64Addr - 0x802FF000);
    }
    
    // Font palette 1 (0x8030A000 - 0x8030A400)
    if (n64Addr >= 0x8030A000 && n64Addr < 0x8030A400) {
        return (u8*)gFontPalette1 + (n64Addr - 0x8030A000);
    }
    
    // Font palette 2 (0x8030A400 - 0x8030A800)
    if (n64Addr >= 0x8030A400 && n64Addr < 0x8030A800) {
        return (u8*)gFontPalette2 + (n64Addr - 0x8030A400);
    }
    
    // gCutsceneCompletionFlags (0x801891D4 - 0x801891D8)
    if (n64Addr >= 0x801891D4 && n64Addr < 0x801891D8) {
        extern s32 gCutsceneCompletionFlags;
        return (u8*)&gCutsceneCompletionFlags + (n64Addr - 0x801891D4);
    }

    // gCutsceneIndex (0x801C3B66 - 0x801C3B68)
    if (n64Addr >= 0x801C3B66 && n64Addr < 0x801C3B68) {
        extern u16 gCutsceneIndex;
        return (u8*)&gCutsceneIndex + (n64Addr - 0x801C3B66);
    }

    // Generic fallback for any remaining N64 RAM address.
    // This keeps host-side sprite/cutscene buffers working even when they
    // haven't been broken out into dedicated native allocations yet.
    if (n64Addr >= HM64_RAM_BASE && n64Addr < (HM64_RAM_BASE + HM64_RAM_SIZE)) {
        return HM64_RAM_PTR(n64Addr);
    }

    // If no translation found, return NULL
    return NULL;
}
#pragma clang optimize on
