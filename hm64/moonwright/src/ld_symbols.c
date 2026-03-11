#include "common.h"
#include "buffers/buffers.h"
#include "ld_symbols.h"
#include "hm64_ram.h"
#include "system/globalSprites.h"

typedef enum {
    VAR_NONE = 0,
    VAR_CUTSCENE_COMPLETION_FLAGS,
    VAR_CUTSCENE_INDEX,
    VAR_CUTSCENE_FLAGS,
    VAR_HOUR,
    VAR_COUNT
} CutsceneVariableIndex;

// Moonwright [Port]: cutscene bytecode stores small variable ids instead of
// embedding host pointers directly.
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

extern u8 messageBoxTextureBuffer[0x2900];
extern u16 messageBoxPaletteBuffer[0x80];
extern AnimationFrameMetadata messageBoxAnimationFrameMetadataBuffer[0x40];
extern u32 messageBoxAnimationTextureToPaletteLookupBuffer[0x40];

extern u8 dialogueIconTextureBuffer[0x1800];
extern u16 dialogueIconPaletteBuffer[0x100];
extern u32 dialogueIconAnimationFrameMetadataBuffer[0x40];
extern u32 dialogueIconTextureToPaletteLookupBuffer[0x100];

extern u8 characterAvatarsTexture1Buffer[0x800];
extern u8 characterAvatarsTexture2Buffer[0x800];
extern u16 characterAvatarsPaletteBuffer[0x600];
extern AnimationFrameMetadata characterAvatarsAnimationMetadataBuffer[0x400];
extern u32 characterAvatarsSpritesheetIndexBuffer[0x200];
extern u32 characterAvatarsTextureToPaletteLookupBuffer[0x40];

extern u8 shadowSpriteTextureBuffer[0x500];
extern u16 shadowSpritePaletteBuffer[0x100];
extern u32 shadowSpriteSpriteToPaletteBuffer[0x100];
extern u32 shadowSpriteSpritesheetIndexBuffer[0x100];

extern u8 playerTexture1Buffer[0x3000];
extern u8 playerTexture2Buffer[0x3000];
extern u16 playerPaletteBuffer[0x2000];
extern u32 playerAnimationMetadataBuffer[0x1E00];
extern u32 playerSpritesheetIndexBuffer[0x200];
extern u32 playerTextureToPaletteLookupBuffer[0x400];

extern u8 namingScreenBuffer[0x1500];
extern u8 mapDataBuffer[0x1A000];
extern u8 spriteBuffer[0x73CC0];
extern u8 mapObjectsBuffer[0x10000];
extern u8 cutsceneBytecodeBuffer[0xB000];
extern u8 fontTextureBuffer[0xB000];
extern u16 font1PaletteBuffer[0x200];
extern u16 font2PaletteBuffer[0x200];
extern u8 textAddressesIndexBuffer[0x800];
extern u8 messageBox1TextBuffer[0x400];
extern u8 messageBox2TextBuffer[0x400];
extern u8 messageBox3TextBuffer[0x400];
extern u8 messageBox4TextBuffer[0x400];
extern u8 messageBox5TextBuffer[0x400];
extern u8 messageBox6TextBuffer[0x400];
extern u8 dialogueBytecodeBuffer[0x800];
extern SramBuffer sramBuffer;
extern FarmRankingsBuffer farmRankingsBuffer;
extern u8 frameBuffer[0x70800];

#define HM64_OFFSET_PTR(buffer, base, addr) ((u8*)(buffer) + ((addr) - (base)))

void* g_PC_CutsceneBytecodeBuffer1 = cutsceneBytecodeBuffer;
void* g_PC_CutsceneBytecodeBuffer2 = &cutsceneBytecodeBuffer[0x1000];

void* CUTSCENE_BYTECODE_BUFFER_1_PTR = cutsceneBytecodeBuffer;
void* CUTSCENE_BYTECODE_BUFFER_2_PTR = &cutsceneBytecodeBuffer[0x1000];
void* ENTITY_REGION_CHICKEN_BASE_PTR = HM64_OFFSET_PTR(spriteBuffer, ENTITY_VRAM_START, ENTITY_REGION_CHICKEN_BASE);
void* ENTITY_REGION_CHICK_BASE_PTR = HM64_OFFSET_PTR(spriteBuffer, ENTITY_VRAM_START, ENTITY_REGION_CHICK_BASE);
void* SHADOW_TEXTURE_BUFFER_PTR = shadowSpriteTextureBuffer;
void* SHADOW_PALETTE_BUFFER_PTR = shadowSpritePaletteBuffer;
void* SHADOW_ANIMATION_FRAME_METADATA_BUFFER_PTR = shadowSpriteSpriteToPaletteBuffer;
void* SHADOW_TEXTURE_TO_PALETTE_LOOKUP_BUFFER_PTR = shadowSpriteSpritesheetIndexBuffer;
void* PLAYER_TEXTURE_1_BUFFER_PTR = playerTexture1Buffer;
void* PLAYER_TEXTURE_2_BUFFER_PTR = playerTexture2Buffer;
void* PLAYER_PALETTE_BUFFER_PTR = playerPaletteBuffer;
void* PLAYER_ANIMATION_FRAME_METADATA_BUFFER_PTR = playerAnimationMetadataBuffer;
void* PLAYER_SPRITESHEET_INDEX_BUFFER_PTR = playerSpritesheetIndexBuffer;
void* PLAYER_TEXTURE_TO_PALETTE_LOOKUP_BUFFER_PTR = playerTextureToPaletteLookupBuffer;
void* ENTITY_SLOTS_1_20_PALETTE_PTR = HM64_OFFSET_PTR(spriteBuffer, ENTITY_VRAM_START, ENTITY_SLOTS_1_20_PALETTE);
void* ENTITY_SLOTS_1_20_ANIM_METADATA_PTR = HM64_OFFSET_PTR(spriteBuffer, ENTITY_VRAM_START, ENTITY_SLOTS_1_20_ANIM_METADATA);
void* ENTITY_SLOTS_1_20_SPRITESHEET_INDEX_PTR = HM64_OFFSET_PTR(spriteBuffer, ENTITY_VRAM_START, ENTITY_SLOTS_1_20_SPRITESHEET_INDEX);
void* ENTITY_SLOTS_1_20_TEXTURE_TO_PALETTE_LOOKUP_PTR = HM64_OFFSET_PTR(spriteBuffer, ENTITY_VRAM_START, ENTITY_SLOTS_1_20_TEXTURE_TO_PALETTE_LOOKUP);
void* ENTITY_SLOTS_2_7_PALETTE_PTR = HM64_OFFSET_PTR(spriteBuffer, ENTITY_VRAM_START, ENTITY_SLOTS_2_7_PALETTE);
void* ENTITY_SLOTS_2_7_ANIM_METADATA_PTR = HM64_OFFSET_PTR(spriteBuffer, ENTITY_VRAM_START, ENTITY_SLOTS_2_7_ANIM_METADATA);
void* ENTITY_SLOTS_2_7_SPRITESHEET_INDEX_PTR = HM64_OFFSET_PTR(spriteBuffer, ENTITY_VRAM_START, ENTITY_SLOTS_2_7_SPRITESHEET_INDEX);
void* ENTITY_SLOTS_2_7_TEXTURE_TO_PALETTE_LOOKUP_PTR = HM64_OFFSET_PTR(spriteBuffer, ENTITY_VRAM_START, ENTITY_SLOTS_2_7_TEXTURE_TO_PALETTE_LOOKUP);
void* GROUND_OBJECTS_TEXTURE_BUFFER_PTR = HM64_OFFSET_PTR(mapObjectsBuffer, MAP_OBJECT_SLOT_1_TEXTURE_1, GROUND_OBJECTS_TEXTURE_BUFFER);
void* GROUND_OBJECTS_PALETTE_BUFFER_PTR = HM64_OFFSET_PTR(mapObjectsBuffer, MAP_OBJECT_SLOT_1_TEXTURE_1, GROUND_OBJECTS_PALETTE_BUFFER);
void* GROUND_OBJECTS_SPRITE_TO_PALETTE_LOOKUP_BUFFER_PTR = HM64_OFFSET_PTR(mapObjectsBuffer, MAP_OBJECT_SLOT_1_TEXTURE_1, GROUND_OBJECTS_SPRITE_TO_PALETTE_LOOKUP_BUFFER);
void* g_PC_ShadowTextureBuffer = shadowSpriteTextureBuffer;
void* g_PC_ShadowPaletteBuffer = shadowSpritePaletteBuffer;
void* g_PC_PlayerTexture1Buffer = playerTexture1Buffer;
void* g_PC_PlayerTexture2Buffer = playerTexture2Buffer;
void* g_PC_PlayerPaletteBuffer = playerPaletteBuffer;
void* g_PC_EntityChickenBase = HM64_OFFSET_PTR(spriteBuffer, ENTITY_VRAM_START, ENTITY_REGION_CHICKEN_BASE);
void* g_PC_EntityChickBase = HM64_OFFSET_PTR(spriteBuffer, ENTITY_VRAM_START, ENTITY_REGION_CHICK_BASE);
void* g_PC_GroundObjectsTextureBuffer = HM64_OFFSET_PTR(mapObjectsBuffer, MAP_OBJECT_SLOT_1_TEXTURE_1, GROUND_OBJECTS_TEXTURE_BUFFER);
void* g_PC_FontTextureBuffer = fontTextureBuffer;
void* g_PC_FontPalette1Buffer = font1PaletteBuffer;
void* g_PC_FontPalette2Buffer = font2PaletteBuffer;

#pragma clang optimize off
void* HM64_TranslateAddress(u32 n64Addr) {
    if (n64Addr >= MESSAGE_BOX_TEXTURE_BUFFER && n64Addr < MESSAGE_BOX_PALETTE_BUFFER) {
        return HM64_OFFSET_PTR(messageBoxTextureBuffer, MESSAGE_BOX_TEXTURE_BUFFER, n64Addr);
    }
    if (n64Addr >= MESSAGE_BOX_PALETTE_BUFFER && n64Addr < MESSAGE_BOX_ANIMATION_FRAME_METADATA_BUFFER) {
        return HM64_OFFSET_PTR(messageBoxPaletteBuffer, MESSAGE_BOX_PALETTE_BUFFER, n64Addr);
    }
    if (n64Addr >= MESSAGE_BOX_ANIMATION_FRAME_METADATA_BUFFER && n64Addr < MESSAGE_BOX_TEXTURE_TO_PALETTE_LOOKUP_BUFFER) {
        return HM64_OFFSET_PTR(messageBoxAnimationFrameMetadataBuffer, MESSAGE_BOX_ANIMATION_FRAME_METADATA_BUFFER, n64Addr);
    }
    if (n64Addr >= MESSAGE_BOX_TEXTURE_TO_PALETTE_LOOKUP_BUFFER && n64Addr < DIALOGUE_ICON_TEXTURE_BUFFER) {
        return HM64_OFFSET_PTR(messageBoxAnimationTextureToPaletteLookupBuffer, MESSAGE_BOX_TEXTURE_TO_PALETTE_LOOKUP_BUFFER, n64Addr);
    }

    if (n64Addr >= DIALOGUE_ICON_TEXTURE_BUFFER && n64Addr < DIALOGUE_ICON_PALETTE_BUFFER) {
        return HM64_OFFSET_PTR(dialogueIconTextureBuffer, DIALOGUE_ICON_TEXTURE_BUFFER, n64Addr);
    }
    if (n64Addr >= DIALOGUE_ICON_PALETTE_BUFFER && n64Addr < DIALOGUE_ICON_ANIMATION_FRAME_METADATA_BUFFER) {
        return HM64_OFFSET_PTR(dialogueIconPaletteBuffer, DIALOGUE_ICON_PALETTE_BUFFER, n64Addr);
    }
    if (n64Addr >= DIALOGUE_ICON_ANIMATION_FRAME_METADATA_BUFFER && n64Addr < DIALOGUE_ICON_TEXTURE_TO_PALETTE_LOOKUP_BUFFER) {
        return HM64_OFFSET_PTR(dialogueIconAnimationFrameMetadataBuffer, DIALOGUE_ICON_ANIMATION_FRAME_METADATA_BUFFER, n64Addr);
    }
    if (n64Addr >= DIALOGUE_ICON_TEXTURE_TO_PALETTE_LOOKUP_BUFFER && n64Addr < CHARACTER_AVATAR_TEXTURE_1_BUFFER) {
        return HM64_OFFSET_PTR(dialogueIconTextureToPaletteLookupBuffer, DIALOGUE_ICON_TEXTURE_TO_PALETTE_LOOKUP_BUFFER, n64Addr);
    }

    if (n64Addr >= CHARACTER_AVATAR_TEXTURE_1_BUFFER && n64Addr < CHARACTER_AVATAR_TEXTURE_2_BUFFER) {
        return HM64_OFFSET_PTR(characterAvatarsTexture1Buffer, CHARACTER_AVATAR_TEXTURE_1_BUFFER, n64Addr);
    }
    if (n64Addr >= CHARACTER_AVATAR_TEXTURE_2_BUFFER && n64Addr < CHARACTER_AVATAR_PALETTE_BUFFER) {
        return HM64_OFFSET_PTR(characterAvatarsTexture2Buffer, CHARACTER_AVATAR_TEXTURE_2_BUFFER, n64Addr);
    }
    if (n64Addr >= CHARACTER_AVATAR_PALETTE_BUFFER && n64Addr < CHARACTER_AVATAR_ANIMATION_FRAME_METADATA_BUFFER) {
        return HM64_OFFSET_PTR(characterAvatarsPaletteBuffer, CHARACTER_AVATAR_PALETTE_BUFFER, n64Addr);
    }
    if (n64Addr >= CHARACTER_AVATAR_ANIMATION_FRAME_METADATA_BUFFER && n64Addr < CHARACTER_AVATAR_SPRITESHEET_INDEX_BUFFER) {
        return HM64_OFFSET_PTR(characterAvatarsAnimationMetadataBuffer, CHARACTER_AVATAR_ANIMATION_FRAME_METADATA_BUFFER, n64Addr);
    }
    if (n64Addr >= CHARACTER_AVATAR_SPRITESHEET_INDEX_BUFFER && n64Addr < CHARACTER_AVATAR_TEXTURE_TO_PALETTE_LOOKUP_BUFFER) {
        return HM64_OFFSET_PTR(characterAvatarsSpritesheetIndexBuffer, CHARACTER_AVATAR_SPRITESHEET_INDEX_BUFFER, n64Addr);
    }
    if (n64Addr >= CHARACTER_AVATAR_TEXTURE_TO_PALETTE_LOOKUP_BUFFER && n64Addr < SHADOW_TEXTURE_BUFFER) {
        return HM64_OFFSET_PTR(characterAvatarsTextureToPaletteLookupBuffer, CHARACTER_AVATAR_TEXTURE_TO_PALETTE_LOOKUP_BUFFER, n64Addr);
    }

    if (n64Addr >= SHADOW_TEXTURE_BUFFER && n64Addr < SHADOW_PALETTE_BUFFER) {
        return HM64_OFFSET_PTR(shadowSpriteTextureBuffer, SHADOW_TEXTURE_BUFFER, n64Addr);
    }
    if (n64Addr >= SHADOW_PALETTE_BUFFER && n64Addr < SHADOW_ANIMATION_FRAME_METADATA_BUFFER) {
        return HM64_OFFSET_PTR(shadowSpritePaletteBuffer, SHADOW_PALETTE_BUFFER, n64Addr);
    }
    if (n64Addr >= SHADOW_ANIMATION_FRAME_METADATA_BUFFER && n64Addr < SHADOW_TEXTURE_TO_PALETTE_LOOKUP_BUFFER) {
        return HM64_OFFSET_PTR(shadowSpriteSpriteToPaletteBuffer, SHADOW_ANIMATION_FRAME_METADATA_BUFFER, n64Addr);
    }
    if (n64Addr >= SHADOW_TEXTURE_TO_PALETTE_LOOKUP_BUFFER && n64Addr < PLAYER_TEXTURE_1_BUFFER) {
        return HM64_OFFSET_PTR(shadowSpriteSpritesheetIndexBuffer, SHADOW_TEXTURE_TO_PALETTE_LOOKUP_BUFFER, n64Addr);
    }

    if (n64Addr >= PLAYER_TEXTURE_1_BUFFER && n64Addr < PLAYER_TEXTURE_2_BUFFER) {
        return HM64_OFFSET_PTR(playerTexture1Buffer, PLAYER_TEXTURE_1_BUFFER, n64Addr);
    }
    if (n64Addr >= PLAYER_TEXTURE_2_BUFFER && n64Addr < PLAYER_PALETTE_BUFFER) {
        return HM64_OFFSET_PTR(playerTexture2Buffer, PLAYER_TEXTURE_2_BUFFER, n64Addr);
    }
    if (n64Addr >= PLAYER_PALETTE_BUFFER && n64Addr < PLAYER_ANIMATION_FRAME_METADATA_BUFFER) {
        return HM64_OFFSET_PTR(playerPaletteBuffer, PLAYER_PALETTE_BUFFER, n64Addr);
    }
    if (n64Addr >= PLAYER_ANIMATION_FRAME_METADATA_BUFFER && n64Addr < PLAYER_SPRITESHEET_INDEX_BUFFER) {
        return HM64_OFFSET_PTR(playerAnimationMetadataBuffer, PLAYER_ANIMATION_FRAME_METADATA_BUFFER, n64Addr);
    }
    if (n64Addr >= PLAYER_SPRITESHEET_INDEX_BUFFER && n64Addr < PLAYER_TEXTURE_TO_PALETTE_LOOKUP_BUFFER) {
        return HM64_OFFSET_PTR(playerSpritesheetIndexBuffer, PLAYER_SPRITESHEET_INDEX_BUFFER, n64Addr);
    }
    if (n64Addr >= PLAYER_TEXTURE_TO_PALETTE_LOOKUP_BUFFER && n64Addr < NAMING_SCREEN_TEXTURE_BUFFER) {
        return HM64_OFFSET_PTR(playerTextureToPaletteLookupBuffer, PLAYER_TEXTURE_TO_PALETTE_LOOKUP_BUFFER, n64Addr);
    }

    if (n64Addr >= NAMING_SCREEN_TEXTURE_BUFFER && n64Addr < MAP_DATA_BUFFER) {
        return HM64_OFFSET_PTR(namingScreenBuffer, NAMING_SCREEN_TEXTURE_BUFFER, n64Addr);
    }
    if (n64Addr >= MAP_DATA_BUFFER && n64Addr < ENTITY_VRAM_START) {
        return HM64_OFFSET_PTR(mapDataBuffer, MAP_DATA_BUFFER, n64Addr);
    }
    if (n64Addr >= ENTITY_VRAM_START && n64Addr < 0x802E2CC0) {
        return HM64_OFFSET_PTR(spriteBuffer, ENTITY_VRAM_START, n64Addr);
    }
    if (n64Addr >= MAP_OBJECT_SLOT_1_TEXTURE_1 && n64Addr < CUTSCENE_BYTECODE_BUFFER_1) {
        return HM64_OFFSET_PTR(mapObjectsBuffer, MAP_OBJECT_SLOT_1_TEXTURE_1, n64Addr);
    }
    if (n64Addr >= CUTSCENE_BYTECODE_BUFFER_1 && n64Addr < FONT_TEXTURE_BUFFER) {
        return HM64_OFFSET_PTR(cutsceneBytecodeBuffer, CUTSCENE_BYTECODE_BUFFER_1, n64Addr);
    }

    if (n64Addr >= FONT_TEXTURE_BUFFER && n64Addr < FONT_PALETTE_1_BUFFER) {
        return HM64_OFFSET_PTR(fontTextureBuffer, FONT_TEXTURE_BUFFER, n64Addr);
    }
    if (n64Addr >= FONT_PALETTE_1_BUFFER && n64Addr < FONT_PALETTE_2_BUFFER) {
        return HM64_OFFSET_PTR(font1PaletteBuffer, FONT_PALETTE_1_BUFFER, n64Addr);
    }
    if (n64Addr >= FONT_PALETTE_2_BUFFER && n64Addr < TEXT_ADDRESSES_INDEX_BUFFER) {
        return HM64_OFFSET_PTR(font2PaletteBuffer, FONT_PALETTE_2_BUFFER, n64Addr);
    }
    if (n64Addr >= TEXT_ADDRESSES_INDEX_BUFFER && n64Addr < MESSAGE_BOX_1_TEXT_BUFFER) {
        return HM64_OFFSET_PTR(textAddressesIndexBuffer, TEXT_ADDRESSES_INDEX_BUFFER, n64Addr);
    }
    if (n64Addr >= MESSAGE_BOX_1_TEXT_BUFFER && n64Addr < MESSAGE_BOX_2_TEXT_BUFFER) {
        return HM64_OFFSET_PTR(messageBox1TextBuffer, MESSAGE_BOX_1_TEXT_BUFFER, n64Addr);
    }
    if (n64Addr >= MESSAGE_BOX_2_TEXT_BUFFER && n64Addr < MESSAGE_BOX_3_TEXT_BUFFER) {
        return HM64_OFFSET_PTR(messageBox2TextBuffer, MESSAGE_BOX_2_TEXT_BUFFER, n64Addr);
    }
    if (n64Addr >= MESSAGE_BOX_3_TEXT_BUFFER && n64Addr < MESSAGE_BOX_4_TEXT_BUFFER) {
        return HM64_OFFSET_PTR(messageBox3TextBuffer, MESSAGE_BOX_3_TEXT_BUFFER, n64Addr);
    }
    if (n64Addr >= MESSAGE_BOX_4_TEXT_BUFFER && n64Addr < MESSAGE_BOX_5_TEXT_BUFFER) {
        return HM64_OFFSET_PTR(messageBox4TextBuffer, MESSAGE_BOX_4_TEXT_BUFFER, n64Addr);
    }
    if (n64Addr >= MESSAGE_BOX_5_TEXT_BUFFER && n64Addr < MESSAGE_BOX_6_TEXT_BUFFER) {
        return HM64_OFFSET_PTR(messageBox5TextBuffer, MESSAGE_BOX_5_TEXT_BUFFER, n64Addr);
    }
    if (n64Addr >= MESSAGE_BOX_6_TEXT_BUFFER && n64Addr < DIALOGUE_BYTECODE_INDEX_BUFFER) {
        return HM64_OFFSET_PTR(messageBox6TextBuffer, MESSAGE_BOX_6_TEXT_BUFFER, n64Addr);
    }
    if (n64Addr >= DIALOGUE_BYTECODE_INDEX_BUFFER && n64Addr < SRAM_BUFFER) {
        return HM64_OFFSET_PTR(dialogueBytecodeBuffer, DIALOGUE_BYTECODE_INDEX_BUFFER, n64Addr);
    }
    if (n64Addr >= SRAM_BUFFER && n64Addr < FARM_RANKINGS_BUFFER) {
        return HM64_OFFSET_PTR(&sramBuffer, SRAM_BUFFER, n64Addr);
    }
    if (n64Addr >= FARM_RANKINGS_BUFFER && n64Addr < 0x8030F800) {
        return HM64_OFFSET_PTR(&farmRankingsBuffer, FARM_RANKINGS_BUFFER, n64Addr);
    }
    if (n64Addr >= FRAME_BUFFER && n64Addr < (FRAME_BUFFER + sizeof(frameBuffer))) {
        return HM64_OFFSET_PTR(frameBuffer, FRAME_BUFFER, n64Addr);
    }

    if (n64Addr >= 0x801891D4 && n64Addr < 0x801891D8) {
        extern s32 gCutsceneCompletionFlags;
        return HM64_OFFSET_PTR(&gCutsceneCompletionFlags, 0x801891D4, n64Addr);
    }
    if (n64Addr >= 0x801C3B66 && n64Addr < 0x801C3B68) {
        extern u16 gCutsceneIndex;
        return HM64_OFFSET_PTR(&gCutsceneIndex, 0x801C3B66, n64Addr);
    }

    if (n64Addr >= HM64_RAM_BASE && n64Addr < (HM64_RAM_BASE + HM64_RAM_SIZE)) {
        return HM64_RAM_PTR(n64Addr);
    }

    return NULL;
}
#pragma clang optimize on
