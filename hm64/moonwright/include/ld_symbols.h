#ifndef HM64_PC_LD_SYMBOLS_H
#define HM64_PC_LD_SYMBOLS_H

#include "common.h"

// ROM segment symbols - defined in rom_symbols.s
// These are absolute symbols at specific addresses, so &symbol returns the ROM address
// Title screen sprites
extern char _titleSpritesTextureSegmentRomStart[];
extern char _titleSpritesTextureSegmentRomEnd[];
extern char _titleSpritesAssetsIndexSegmentRomStart[];
extern char _titleSpritesAssetsIndexSegmentRomEnd[];
// Dialogue icons
extern char _dialogueButtonIconsTextureSegmentRomStart[];
extern char _dialogueButtonIconsTextureSegmentRomEnd[];
extern char _dialogueButtonIconsAssetsIndexSegmentRomStart[];
extern char _dialogueButtonIconsAssetsIndexSegmentRomEnd[];
// Dog sprites
extern char _dogTextureSegmentRomStart[];
extern char _dogTextureSegmentRomEnd[];
extern char _dogAssetsIndexSegmentRomStart[];
extern char _dogAssetsIndexSegmentRomEnd[];
extern char _dogSpritesheetIndexSegmentRomStart[];
extern char _dogSpritesheetIndexSegmentRomEnd[];
// Cutscene segments
extern char _farmBusinessSegmentRomStart[];
extern char _farmBusinessSegmentRomEnd[];
extern char _funeralIntroSegmentRomStart[];
extern char _funeralIntroSegmentRomEnd[];
extern char _demosSegmentRomStart[];
extern char _demosSegmentRomEnd[];
extern char _farmVisitsSegmentRomStart[];
extern char _farmVisitsSegmentRomEnd[];
extern char _familyCutscenesSegmentRomStart[];
extern char _familyCutscenesSegmentRomEnd[];
extern char _roadCutscenesSegmentRomStart[];
static const void* _roadCutscenesSegmentRomEnd = (const void*)0x01000000;
static const void* _mountainCutscenesSegmentRomStart = (const void*)0x01000000;
static const void* _mountainCutscenesSegmentRomEnd = (const void*)0x01000000;
static const void* _ranchCutscenesSegmentRomStart = (const void*)0x01000000;
static const void* _ranchCutscenesSegmentRomEnd = (const void*)0x01000000;
static const void* _vineyardCutscenesSegmentRomStart = (const void*)0x01000000;
static const void* _vineyardCutscenesSegmentRomEnd = (const void*)0x01000000;
static const void* _village1CutscenesSegmentRomStart = (const void*)0x01000000;
static const void* _village1CutscenesSegmentRomEnd = (const void*)0x01000000;
static const void* _village2CutscenesSegmentRomStart = (const void*)0x01000000;
static const void* _village2CutscenesSegmentRomEnd = (const void*)0x01000000;
static const void* _beachCutscenesSegmentRomStart = (const void*)0x01000000;
static const void* _beachCutscenesSegmentRomEnd = (const void*)0x01000000;
// Player sprites
static const void* _playerTextureSegmentRomStart = (const void*)0x01000000;
static const void* _playerTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _playerAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _playerAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _playerSpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _playerSpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
// NPC sprites
static const void* _mariaTextureSegmentRomStart = (const void*)0x01000000;
static const void* _mariaTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _mariaAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _mariaAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _mariaSpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _mariaSpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _popuriTextureSegmentRomStart = (const void*)0x01000000;
static const void* _popuriTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _popuriAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _popuriAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _popuriSpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _popuriSpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _elliTextureSegmentRomStart = (const void*)0x01000000;
static const void* _elliTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _elliAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _elliAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _elliSpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _elliSpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _annTextureSegmentRomStart = (const void*)0x01000000;
static const void* _annTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _annAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _annAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _annSpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _annSpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _karenTextureSegmentRomStart = (const void*)0x01000000;
static const void* _karenTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _karenAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _karenAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _karenSpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _karenSpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _babyTextureSegmentRomStart = (const void*)0x01000000;
static const void* _babyTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _babyAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _babyAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _babySpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _babySpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _harrisTextureSegmentRomStart = (const void*)0x01000000;
static const void* _harrisTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _harrisAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _harrisAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _harrisSpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _harrisSpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
// Gray sprites
static const void* _grayTextureSegmentRomStart = (const void*)0x01000000;
static const void* _grayTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _grayAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _grayAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _graySpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _graySpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
// Jeff sprites
static const void* _jeffTextureSegmentRomStart = (const void*)0x01000000;
static const void* _jeffTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _jeffAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _jeffAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _jeffSpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _jeffSpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
// Cliff sprites
static const void* _cliffTextureSegmentRomStart = (const void*)0x01000000;
static const void* _cliffTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _cliffAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _cliffAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _cliffSpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _cliffSpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
// Kai sprites
static const void* _kaiTextureSegmentRomStart = (const void*)0x01000000;
static const void* _kaiTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _kaiAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _kaiAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _kaiSpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _kaiSpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
// Shadow sprite
static const void* _shadowsTextureSegmentRomStart = (const void*)0x01000000;
static const void* _shadowsTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _shadowsAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _shadowsAssetsIndexSegmentRomEnd = (const void*)0x01000000;
// Ground objects
static const void* _groundObjectsTextureSegmentRomStart = (const void*)0x01000000;
static const void* _groundObjectsTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _groundObjectsAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _groundObjectsAssetsIndexSegmentRomEnd = (const void*)0x01000000;
// Festival segments
static const void* _sowingFestivalSegmentRomStart = (const void*)0x01000000;
static const void* _sowingFestivalSegmentRomEnd = (const void*)0x01000000;
static const void* _horseRaceSegmentRomStart = (const void*)0x01000000;
static const void* _horseRaceSegmentRomEnd = (const void*)0x01000000;
static const void* _flowerFestivalSegmentRomStart = (const void*)0x01000000;
static const void* _flowerFestivalSegmentRomEnd = (const void*)0x01000000;
static const void* _vegetableFestivalSegmentRomStart = (const void*)0x01000000;
static const void* _vegetableFestivalSegmentRomEnd = (const void*)0x01000000;
static const void* _fireworksFestivalSegmentRomStart = (const void*)0x01000000;
static const void* _fireworksFestivalSegmentRomEnd = (const void*)0x01000000;
static const void* _fireflyFestivalSegmentRomStart = (const void*)0x01000000;
static const void* _fireflyFestivalSegmentRomEnd = (const void*)0x01000000;
static const void* _seaFestivalSegmentRomStart = (const void*)0x01000000;
static const void* _seaFestivalSegmentRomEnd = (const void*)0x01000000;
static const void* _cowFestivalSegmentRomStart = (const void*)0x01000000;
static const void* _cowFestivalSegmentRomEnd = (const void*)0x01000000;
static const void* _harvestFestivalSegmentRomStart = (const void*)0x01000000;
static const void* _harvestFestivalSegmentRomEnd = (const void*)0x01000000;
static const void* _eggFestivalSegmentRomStart = (const void*)0x01000000;
static const void* _eggFestivalSegmentRomEnd = (const void*)0x01000000;
static const void* _dogRaceSegmentRomStart = (const void*)0x01000000;
static const void* _dogRaceSegmentRomEnd = (const void*)0x01000000;
static const void* _spiritFestivalSegmentRomStart = (const void*)0x01000000;
static const void* _spiritFestivalSegmentRomEnd = (const void*)0x01000000;
static const void* _newYearFestivalSegmentRomStart = (const void*)0x01000000;
static const void* _newYearFestivalSegmentRomEnd = (const void*)0x01000000;
static const void* _evaluationEndingSegmentRomStart = (const void*)0x01000000;
static const void* _evaluationEndingSegmentRomEnd = (const void*)0x01000000;
static const void* _howToPlaySegmentRomStart = (const void*)0x01000000;
static const void* _howToPlaySegmentRomEnd = (const void*)0x01000000;
// Font segments
static const void* _fontTextureSegmentRomStart = (const void*)0x01000000;
static const void* _fontTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _fontPalette1SegmentRomStart = (const void*)0x01000000;
static const void* _fontPalette1SegmentRomEnd = (const void*)0x01000000;
static const void* _fontPalette2SegmentRomStart = (const void*)0x01000000;
static const void* _fontPalette2SegmentRomEnd = (const void*)0x01000000;
static const void* _fontPalette3SegmentRomStart = (const void*)0x01000000;
static const void* _fontPalette3SegmentRomEnd = (const void*)0x01000000;
// ============================================================================
// RAM Buffers - N64 addresses for compile-time compatibility
// The PC port maps these addresses to actual allocated buffers at runtime
// Use original N64 addresses for compile-time constants
#define CUTSCENE_BYTECODE_BUFFER_1 0x802F4000
#define CUTSCENE_BYTECODE_BUFFER_2 0x802F5000
#define SHADOW_TEXTURE_BUFFER 0x8023B400
#define SHADOW_PALETTE_BUFFER 0x8023B600
#define SHADOW_ANIMATION_FRAME_METADATA_BUFFER 0x8023B800
#define SHADOW_TEXTURE_TO_PALETTE_LOOKUP_BUFFER 0x8023BC00
#define PLAYER_TEXTURE_1_BUFFER 0x8023C000
#define PLAYER_TEXTURE_2_BUFFER 0x80240000
#define PLAYER_PALETTE_BUFFER 0x80244000
#define PLAYER_ANIMATION_FRAME_METADATA_BUFFER 0x80244200
#define PLAYER_SPRITESHEET_INDEX_BUFFER 0x80252300
#define PLAYER_TEXTURE_TO_PALETTE_LOOKUP_BUFFER 0x80252B00
#define ENTITY_SLOTS_1_20_PALETTE 0x80253200
#define ENTITY_SLOTS_1_20_ANIM_METADATA 0x80253400
#define ENTITY_SLOTS_1_20_SPRITESHEET_INDEX 0x80253C00
#define ENTITY_SLOTS_1_20_TEXTURE_TO_PALETTE_LOOKUP 0x80254000
#define ENTITY_SLOTS_2_7_PALETTE 0x80254400
#define ENTITY_SLOTS_2_7_ANIM_METADATA 0x80254600
#define ENTITY_SLOTS_2_7_SPRITESHEET_INDEX 0x80254E00
#define ENTITY_SLOTS_2_7_TEXTURE_TO_PALETTE_LOOKUP 0x80255200
#define ENTITY_REGION_CHICKEN_BASE 0x80272800
#define ENTITY_REGION_CHICK_BASE 0x80277300
#define GROUND_OBJECTS_TEXTURE_BUFFER 0x80255600
#define GROUND_OBJECTS_PALETTE_BUFFER 0x80265600
#define GROUND_OBJECTS_SPRITE_TO_PALETTE_LOOKUP_BUFFER 0x80265800
#define ENTITY_REGION_SLOT_1_BASE 0x8026F000
// Font buffers
#define FONT_TEXTURE_BUFFER 0x802FF000
#define FONT_PALETTE_1_BUFFER 0x8030A000
#define FONT_PALETTE_2_BUFFER 0x8030A400
// Message box buffers
#define MESSAGE_BOX_TEXTURE_BUFFER 0x80238800
#define MESSAGE_BOX_PALETTE_BUFFER 0x8023B100
#define MESSAGE_BOX_ANIMATION_FRAME_METADATA_BUFFER 0x8023B200
#define MESSAGE_BOX_TEXTURE_TO_PALETTE_LOOKUP_BUFFER 0x8023B300
// Dialogue icon buffers
#define DIALOGUE_ICON_TEXTURE_BUFFER 0x8023B400
#define DIALOGUE_ICON_PALETTE_BUFFER 0x8023CC00
#define DIALOGUE_ICON_ANIMATION_FRAME_METADATA_BUFFER 0x8023CE00
#define DIALOGUE_ICON_TEXTURE_TO_PALETTE_LOOKUP_BUFFER 0x8023D200
// Character avatar buffers
#define CHARACTER_AVATAR_TEXTURE_1_BUFFER 0x8023D300
#define CHARACTER_AVATAR_TEXTURE_2_BUFFER 0x8023DB00
#define CHARACTER_AVATAR_PALETTE_BUFFER 0x8023E300
#define CHARACTER_AVATAR_ANIMATION_FRAME_METADATA_BUFFER 0x8023EF00
#define CHARACTER_AVATAR_SPRITESHEET_INDEX_BUFFER 0x8023FF00
#define CHARACTER_AVATAR_TEXTURE_TO_PALETTE_LOOKUP_BUFFER 0x80240000
// Title screen buffers
#define TITLE_SCREEN_SPRITES_TEXTURE_BUFFER 0x8026B900
#define TITLE_SCREEN_SPRITES_PALETTE_BUFFER 0x8026F000
#define TITLE_SCREEN_SPRITE_ANIMATION_FRAME_METADATA_BUFFER 0x8026F100
#define TITLE_SCREEN_SPRITES_TEXTURE_TO_PALETTE_LOOKUP_BUFFER 0x8026F200
// Text buffers
#define TEXT_ADDRESSES_INDEX_BUFFER 0x8030A800
// Message box text buffers
#define MESSAGE_BOX_1_TEXT_BUFFER 0x8030B000
#define MESSAGE_BOX_2_TEXT_BUFFER 0x8030B400
#define MESSAGE_BOX_3_TEXT_BUFFER 0x8030B800
#define MESSAGE_BOX_4_TEXT_BUFFER 0x8030BC00
#define MESSAGE_BOX_5_TEXT_BUFFER 0x8030C000
#define MESSAGE_BOX_6_TEXT_BUFFER 0x8030C400
// Dialogue bytecode buffers
#define DIALOGUE_BYTECODE_INDEX_BUFFER 0x8030C800
#define DIALOGUE_BYTECODE_BUFFER 0x8030CC00
// PC port runtime buffer pointers - used by host to map N64 addresses to PC memory
extern void* g_PC_CutsceneBytecodeBuffer1;
extern void* g_PC_CutsceneBytecodeBuffer2;
extern void* g_PC_ShadowTextureBuffer;
extern void* g_PC_ShadowPaletteBuffer;
extern void* g_PC_PlayerTexture1Buffer;
extern void* g_PC_PlayerTexture2Buffer;
extern void* g_PC_PlayerPaletteBuffer;
extern void* g_PC_EntityChickenBase;
extern void* g_PC_EntityChickBase;
extern void* g_PC_GroundObjectsTextureBuffer;
extern void* g_PC_FontTextureBuffer;
extern void* g_PC_FontPalette1Buffer;
extern void* g_PC_FontPalette2Buffer;
// Function to translate N64 RAM address to PC pointer
void* HM64_TranslateAddress(u32 n64Addr);
// Mayor sprites
static const void* _mayorTextureSegmentRomStart = (const void*)0x01000000;
static const void* _mayorTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _mayorAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _mayorAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _mayorSpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _mayorSpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
// Mayor Wife sprites
static const void* _mayorWifeTextureSegmentRomStart = (const void*)0x01000000;
static const void* _mayorWifeTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _mayorWifeAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _mayorWifeAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _mayorWifeSpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _mayorWifeSpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
// Lillia sprites
static const void* _lilliaTextureSegmentRomStart = (const void*)0x01000000;
static const void* _lilliaTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _lilliaAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _lilliaAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _lilliaSpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _lilliaSpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
// Basil sprites
static const void* _basilTextureSegmentRomStart = (const void*)0x01000000;
static const void* _basilTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _basilAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _basilAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _basilSpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _basilSpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
// Ellen sprites
static const void* _ellenTextureSegmentRomStart = (const void*)0x01000000;
static const void* _ellenTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _ellenAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _ellenAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _ellenSpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _ellenSpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
// Doug sprites
static const void* _dougTextureSegmentRomStart = (const void*)0x01000000;
static const void* _dougTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _dougAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _dougAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _dougSpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _dougSpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
// Gotz sprites
static const void* _gotzTextureSegmentRomStart = (const void*)0x01000000;
static const void* _gotzTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _gotzAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _gotzAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _gotzSpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _gotzSpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
// Sasha sprites
static const void* _sashaTextureSegmentRomStart = (const void*)0x01000000;
static const void* _sashaTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _sashaAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _sashaAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _sashaSpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _sashaSpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
// Potion Shop Dealer sprites
static const void* _potionShopDealerTextureSegmentRomStart = (const void*)0x01000000;
static const void* _potionShopDealerTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _potionShopDealerAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _potionShopDealerAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _potionShopDealerSpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _potionShopDealerSpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
// Kent sprites
static const void* _kentTextureSegmentRomStart = (const void*)0x01000000;
static const void* _kentTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _kentAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _kentAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _kentSpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _kentSpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
// Stu sprites
static const void* _stuTextureSegmentRomStart = (const void*)0x01000000;
static const void* _stuTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _stuAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _stuAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _stuSpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _stuSpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
// Midwife sprites
static const void* _midwifeTextureSegmentRomStart = (const void*)0x01000000;
static const void* _midwifeTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _midwifeAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _midwifeAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _midwifeSpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _midwifeSpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
// May sprites
static const void* _mayTextureSegmentRomStart = (const void*)0x01000000;
static const void* _mayTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _mayAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _mayAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _maySpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _maySpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
// Rick sprites
static const void* _rickTextureSegmentRomStart = (const void*)0x01000000;
static const void* _rickTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _rickAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _rickAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _rickSpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _rickSpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
// Pastor sprites
static const void* _pastorTextureSegmentRomStart = (const void*)0x01000000;
static const void* _pastorTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _pastorAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _pastorAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _pastorSpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _pastorSpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
// Shipper sprites
static const void* _shipperTextureSegmentRomStart = (const void*)0x01000000;
static const void* _shipperTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _shipperAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _shipperAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _shipperSpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _shipperSpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
// Saibara sprites
static const void* _saibaraTextureSegmentRomStart = (const void*)0x01000000;
static const void* _saibaraTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _saibaraAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _saibaraAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _saibaraSpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _saibaraSpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
// Duke sprites
static const void* _dukeTextureSegmentRomStart = (const void*)0x01000000;
static const void* _dukeTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _dukeAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _dukeAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _dukeSpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _dukeSpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
// Greg sprites
static const void* _gregTextureSegmentRomStart = (const void*)0x01000000;
static const void* _gregTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _gregAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _gregAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _gregSpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _gregSpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
// Assistant Carpenter sprites
static const void* _assistantCarpenterTextureSegmentRomStart = (const void*)0x01000000;
static const void* _assistantCarpenterTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _assistantCarpenterAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _assistantCarpenterAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _assistantCarpenterSpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _assistantCarpenterSpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
// Master Carpenter sprites
static const void* _masterCarpenterTextureSegmentRomStart = (const void*)0x01000000;
static const void* _masterCarpenterTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _masterCarpenterAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _masterCarpenterAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _masterCarpenterSpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _masterCarpenterSpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
// Harvest Sprite sprites
static const void* _harvestSpriteTextureSegmentRomStart = (const void*)0x01000000;
static const void* _harvestSpriteTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _harvestSpriteAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _harvestSpriteAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _harvestSpriteSpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _harvestSpriteSpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
// Barley sprites
static const void* _barleyTextureSegmentRomStart = (const void*)0x01000000;
static const void* _barleyTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _barleyAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _barleyAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _barleySpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _barleySpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
// Sydney sprites
static const void* _sydneyTextureSegmentRomStart = (const void*)0x01000000;
static const void* _sydneyTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _sydneyAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _sydneyAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _sydneySpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _sydneySpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
// Entomologist sprites
static const void* _entomologistTextureSegmentRomStart = (const void*)0x01000000;
static const void* _entomologistTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _entomologistAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _entomologistAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _entomologistSpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _entomologistSpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
// Gourmet Judge sprites
static const void* _gourmetJudgeTextureSegmentRomStart = (const void*)0x01000000;
static const void* _gourmetJudgeTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _gourmetJudgeAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _gourmetJudgeAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _gourmetJudgeSpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _gourmetJudgeSpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
// Photographer sprites
static const void* _photographerTextureSegmentRomStart = (const void*)0x01000000;
static const void* _photographerTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _photographerAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _photographerAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _photographerSpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _photographerSpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
// Shady Salesman sprites
static const void* _shadySalesmanTextureSegmentRomStart = (const void*)0x01000000;
static const void* _shadySalesmanTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _shadySalesmanAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _shadySalesmanAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _shadySalesmanSpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _shadySalesmanSpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
// Mrs Mana Son sprites
static const void* _mrsManaSonTextureSegmentRomStart = (const void*)0x01000000;
static const void* _mrsManaSonTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _mrsManaSonAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _mrsManaSonAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _mrsManaSonSpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _mrsManaSonSpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
// Mrs Mana sprites
static const void* _mrsManaTextureSegmentRomStart = (const void*)0x01000000;
static const void* _mrsManaTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _mrsManaAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _mrsManaAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _mrsManaSpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _mrsManaSpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
// Old Man sprites
static const void* _oldManTextureSegmentRomStart = (const void*)0x01000000;
static const void* _oldManTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _oldManAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _oldManAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _oldManSpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _oldManSpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
// Old Woman sprites
static const void* _oldWomanTextureSegmentRomStart = (const void*)0x01000000;
static const void* _oldWomanTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _oldWomanAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _oldWomanAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _oldWomanSpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _oldWomanSpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
// Tourist Couple Man sprites
static const void* _touristCoupleManTextureSegmentRomStart = (const void*)0x01000000;
static const void* _touristCoupleManTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _touristCoupleManAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _touristCoupleManAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _touristCoupleManSpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _touristCoupleManSpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
// Tourist Couple Woman sprites
static const void* _touristCoupleWomanTextureSegmentRomStart = (const void*)0x01000000;
static const void* _touristCoupleWomanTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _touristCoupleWomanAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _touristCoupleWomanAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _touristCoupleWomanSpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _touristCoupleWomanSpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
// Festival Girl1 sprites
static const void* _festivalGirl1TextureSegmentRomStart = (const void*)0x01000000;
static const void* _festivalGirl1TextureSegmentRomEnd = (const void*)0x01000000;
static const void* _festivalGirl1AssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _festivalGirl1AssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _festivalGirl1SpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _festivalGirl1SpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
// Festival Girl2 sprites
static const void* _festivalGirl2TextureSegmentRomStart = (const void*)0x01000000;
static const void* _festivalGirl2TextureSegmentRomEnd = (const void*)0x01000000;
static const void* _festivalGirl2AssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _festivalGirl2AssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _festivalGirl2SpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _festivalGirl2SpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
// Festival Girl3 sprites
static const void* _festivalGirl3TextureSegmentRomStart = (const void*)0x01000000;
static const void* _festivalGirl3TextureSegmentRomEnd = (const void*)0x01000000;
static const void* _festivalGirl3AssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _festivalGirl3AssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _festivalGirl3SpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _festivalGirl3SpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
// Harvest Goddess sprites
static const void* _harvestGoddessTextureSegmentRomStart = (const void*)0x01000000;
static const void* _harvestGoddessTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _harvestGoddessAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _harvestGoddessAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _harvestGoddessSpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _harvestGoddessSpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
// Spirit Festival Ocarina Performer sprites
static const void* _spiritFestivalOcarinaPerformerTextureSegmentRomStart = (const void*)0x01000000;
static const void* _spiritFestivalOcarinaPerformerTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _spiritFestivalOcarinaPerformerAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _spiritFestivalOcarinaPerformerAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _spiritFestivalOcarinaPerformerSpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _spiritFestivalOcarinaPerformerSpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
// Kappa sprites
static const void* _kappaTextureSegmentRomStart = (const void*)0x01000000;
static const void* _kappaTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _kappaAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _kappaAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _kappaSpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _kappaSpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
// Princess sprites
static const void* _princessTextureSegmentRomStart = (const void*)0x01000000;
static const void* _princessTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _princessAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _princessAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _princessSpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _princessSpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
// Empty NPC sprites
static const void* _emptyNPCTextureSegmentRomStart = (const void*)0x01000000;
static const void* _emptyNPCTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _emptyNPCAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _emptyNPCAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _emptyNPCSpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _emptyNPCSpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
// Bunny sprites
static const void* _bunnyTextureSegmentRomStart = (const void*)0x01000000;
static const void* _bunnyTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _bunnyAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _bunnyAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _bunnySpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _bunnySpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
// Mouse sprites
static const void* _mouseTextureSegmentRomStart = (const void*)0x01000000;
static const void* _mouseTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _mouseAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _mouseAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _mouseSpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _mouseSpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
// Fox sprites
static const void* _foxTextureSegmentRomStart = (const void*)0x01000000;
static const void* _foxTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _foxAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _foxAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _foxSpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _foxSpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
// Monkey sprites
static const void* _monkeyTextureSegmentRomStart = (const void*)0x01000000;
static const void* _monkeyTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _monkeyAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _monkeyAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _monkeySpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _monkeySpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
// Hawk sprites
static const void* _hawkTextureSegmentRomStart = (const void*)0x01000000;
static const void* _hawkTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _hawkAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _hawkAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _hawkSpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _hawkSpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
// Mole sprites
static const void* _moleTextureSegmentRomStart = (const void*)0x01000000;
static const void* _moleTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _moleAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _moleAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _moleSpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _moleSpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
// Squirrel sprites
static const void* _squirrelTextureSegmentRomStart = (const void*)0x01000000;
static const void* _squirrelTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _squirrelAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _squirrelAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _squirrelSpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _squirrelSpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
// Bird sprites
static const void* _birdTextureSegmentRomStart = (const void*)0x01000000;
static const void* _birdTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _birdAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _birdAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _birdSpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _birdSpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
// Cat sprites
static const void* _catTextureSegmentRomStart = (const void*)0x01000000;
static const void* _catTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _catAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _catAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _catSpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _catSpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
// Dog Village sprites
static const void* _dogVillageTextureSegmentRomStart = (const void*)0x01000000;
static const void* _dogVillageTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _dogVillageAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _dogVillageAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _dogVillageSpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _dogVillageSpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
// Horse Pony sprites
static const void* _horsePonyTextureSegmentRomStart = (const void*)0x01000000;
static const void* _horsePonyTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _horsePonyAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _horsePonyAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _horsePonySpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _horsePonySpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
// Horse Grown sprites
static const void* _horseGrownTextureSegmentRomStart = (const void*)0x01000000;
static const void* _horseGrownTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _horseGrownAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _horseGrownAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _horseGrownSpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _horseGrownSpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
// Chick sprites
static const void* _chickTextureSegmentRomStart = (const void*)0x01000000;
static const void* _chickTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _chickAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _chickAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _chickSpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _chickSpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
// Chicken sprites
static const void* _chickenTextureSegmentRomStart = (const void*)0x01000000;
static const void* _chickenTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _chickenAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _chickenAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _chickenSpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _chickenSpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
// Calf sprites
static const void* _calfTextureSegmentRomStart = (const void*)0x01000000;
static const void* _calfTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _calfAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _calfAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _calfSpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _calfSpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
// Young Cow sprites
static const void* _youngCowTextureSegmentRomStart = (const void*)0x01000000;
static const void* _youngCowTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _youngCowAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _youngCowAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _youngCowSpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _youngCowSpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
// Cow sprites
static const void* _cowTextureSegmentRomStart = (const void*)0x01000000;
static const void* _cowTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _cowAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _cowAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _cowSpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _cowSpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
// Lamb sprites
static const void* _lambTextureSegmentRomStart = (const void*)0x01000000;
static const void* _lambTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _lambAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _lambAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _lambSpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _lambSpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
// Sheep sprites
static const void* _sheepTextureSegmentRomStart = (const void*)0x01000000;
static const void* _sheepTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _sheepAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _sheepAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _sheepSpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _sheepSpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
// Frog sprites
static const void* _frogTextureSegmentRomStart = (const void*)0x01000000;
static const void* _frogTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _frogAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _frogAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _frogSpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _frogSpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
// Crab sprites
static const void* _crabTextureSegmentRomStart = (const void*)0x01000000;
static const void* _crabTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _crabAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _crabAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _crabSpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _crabSpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
// Horned Beetle sprites
static const void* _hornedBeetleTextureSegmentRomStart = (const void*)0x01000000;
static const void* _hornedBeetleTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _hornedBeetleAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _hornedBeetleAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _hornedBeetleSpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _hornedBeetleSpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
// Stag Beetle sprites
static const void* _stagBeetleTextureSegmentRomStart = (const void*)0x01000000;
static const void* _stagBeetleTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _stagBeetleAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _stagBeetleAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _stagBeetleSpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _stagBeetleSpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
// Cricket sprites
static const void* _cricketTextureSegmentRomStart = (const void*)0x01000000;
static const void* _cricketTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _cricketAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _cricketAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _cricketSpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _cricketSpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
// Cicada sprites
static const void* _cicadaTextureSegmentRomStart = (const void*)0x01000000;
static const void* _cicadaTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _cicadaAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _cicadaAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _cicadaSpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _cicadaSpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
// White Butterfly sprites
static const void* _whiteButterflyTextureSegmentRomStart = (const void*)0x01000000;
static const void* _whiteButterflyTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _whiteButterflyAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _whiteButterflyAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _whiteButterflySpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _whiteButterflySpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
// Ladybug sprites
static const void* _ladybugTextureSegmentRomStart = (const void*)0x01000000;
static const void* _ladybugTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _ladybugAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _ladybugAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _ladybugSpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _ladybugSpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
// Dragonfly sprites
static const void* _dragonflyTextureSegmentRomStart = (const void*)0x01000000;
static const void* _dragonflyTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _dragonflyAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _dragonflyAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _dragonflySpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _dragonflySpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
// Grasshopper sprites
static const void* _grasshopperTextureSegmentRomStart = (const void*)0x01000000;
static const void* _grasshopperTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _grasshopperAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _grasshopperAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _grasshopperSpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _grasshopperSpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
// Snake sprites
static const void* _snakeTextureSegmentRomStart = (const void*)0x01000000;
static const void* _snakeTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _snakeAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _snakeAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _snakeSpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _snakeSpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
// Purple Butterfly sprites
static const void* _purpleButterflyTextureSegmentRomStart = (const void*)0x01000000;
static const void* _purpleButterflyTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _purpleButterflyAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _purpleButterflyAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _purpleButterflySpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _purpleButterflySpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
// Dad sprites
static const void* _dadTextureSegmentRomStart = (const void*)0x01000000;
static const void* _dadTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _dadAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _dadAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _dadSpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _dadSpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
// Cow Indoors sprites
static const void* _cowIndoorsTextureSegmentRomStart = (const void*)0x01000000;
static const void* _cowIndoorsTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _cowIndoorsAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _cowIndoorsAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _cowIndoorsSpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _cowIndoorsSpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
// Horse Unbridled sprites
static const void* _horseUnbridledTextureSegmentRomStart = (const void*)0x01000000;
static const void* _horseUnbridledTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _horseUnbridledAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _horseUnbridledAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _horseUnbridledSpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _horseUnbridledSpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
// Horse Racer sprites
static const void* _horseRacerTextureSegmentRomStart = (const void*)0x01000000;
static const void* _horseRacerTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _horseRacerAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _horseRacerAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _horseRacerSpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _horseRacerSpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
// Empty Entity sprites
static const void* _emptyEntityTextureSegmentRomStart = (const void*)0x01000000;
static const void* _emptyEntityTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _emptyEntityAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _emptyEntityAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _emptyEntitySpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _emptyEntitySpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
// Holdable Items sprites
static const void* _holdableItemsTextureSegmentRomStart = (const void*)0x01000000;
static const void* _holdableItemsTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _holdableItemsAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _holdableItemsAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _holdableItemsSpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _holdableItemsSpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
// Extra Festival sprites
static const void* _extraFestivalTextureSegmentRomStart = (const void*)0x01000000;
static const void* _extraFestivalTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _extraFestivalAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _extraFestivalAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _extraFestivalSpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _extraFestivalSpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
// Tools sprites
static const void* _toolsTextureSegmentRomStart = (const void*)0x01000000;
static const void* _toolsTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _toolsAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _toolsAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _toolsSpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _toolsSpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
// Maria Harris Baby sprites
static const void* _mariaHarrisBabyTextureSegmentRomStart = (const void*)0x01000000;
static const void* _mariaHarrisBabyTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _mariaHarrisBabyAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _mariaHarrisBabyAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _mariaHarrisBabySpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _mariaHarrisBabySpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
// Popuri Gray Baby sprites
static const void* _popuriGrayBabyTextureSegmentRomStart = (const void*)0x01000000;
static const void* _popuriGrayBabyTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _popuriGrayBabyAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _popuriGrayBabyAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _popuriGrayBabySpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _popuriGrayBabySpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
// Elli Jeff Baby sprites
static const void* _elliJeffBabyTextureSegmentRomStart = (const void*)0x01000000;
static const void* _elliJeffBabyTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _elliJeffBabyAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _elliJeffBabyAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _elliJeffBabySpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _elliJeffBabySpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
// Ann Cliff Baby sprites
static const void* _annCliffBabyTextureSegmentRomStart = (const void*)0x01000000;
static const void* _annCliffBabyTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _annCliffBabyAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _annCliffBabyAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _annCliffBabySpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _annCliffBabySpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
// Karen Kai Baby sprites
static const void* _karenKaiBabyTextureSegmentRomStart = (const void*)0x01000000;
static const void* _karenKaiBabyTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _karenKaiBabyAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _karenKaiBabyAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _karenKaiBabySpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _karenKaiBabySpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
// Map segments - Spring
static const void* _ranchSpringMapSegmentRomStart = (const void*)0x01000000;
static const void* _ranchSpringMapSegmentRomEnd = (const void*)0x01000000;
static const void* _beachSpringMapSegmentRomStart = (const void*)0x01000000;
static const void* _beachSpringMapSegmentRomEnd = (const void*)0x01000000;
static const void* _village1SpringMapSegmentRomStart = (const void*)0x01000000;
static const void* _village1SpringMapSegmentRomEnd = (const void*)0x01000000;
static const void* _village2SpringMapSegmentRomStart = (const void*)0x01000000;
static const void* _village2SpringMapSegmentRomEnd = (const void*)0x01000000;
static const void* _mountain1SpringMapSegmentRomStart = (const void*)0x01000000;
static const void* _mountain1SpringMapSegmentRomEnd = (const void*)0x01000000;
static const void* _mountain2SpringMapSegmentRomStart = (const void*)0x01000000;
static const void* _mountain2SpringMapSegmentRomEnd = (const void*)0x01000000;
static const void* _roadSpringMapSegmentRomStart = (const void*)0x01000000;
static const void* _roadSpringMapSegmentRomEnd = (const void*)0x01000000;
static const void* _farmSpringMapSegmentRomStart = (const void*)0x01000000;
static const void* _farmSpringMapSegmentRomEnd = (const void*)0x01000000;
static const void* _carpenterSpringMapSegmentRomStart = (const void*)0x01000000;
static const void* _carpenterSpringMapSegmentRomEnd = (const void*)0x01000000;
static const void* _flowerShopSpringMapSegmentRomStart = (const void*)0x01000000;
static const void* _flowerShopSpringMapSegmentRomEnd = (const void*)0x01000000;
static const void* _generalStoreSpringMapSegmentRomStart = (const void*)0x01000000;
static const void* _generalStoreSpringMapSegmentRomEnd = (const void*)0x01000000;
static const void* _potionShopSpringMapSegmentRomStart = (const void*)0x01000000;
static const void* _potionShopSpringMapSegmentRomEnd = (const void*)0x01000000;
static const void* _restaurantSpringMapSegmentRomStart = (const void*)0x01000000;
static const void* _restaurantSpringMapSegmentRomEnd = (const void*)0x01000000;
static const void* _churchSpringMapSegmentRomStart = (const void*)0x01000000;
static const void* _churchSpringMapSegmentRomEnd = (const void*)0x01000000;
static const void* _barSpringMapSegmentRomStart = (const void*)0x01000000;
static const void* _barSpringMapSegmentRomEnd = (const void*)0x01000000;
static const void* _mayorHouseSpringMapSegmentRomStart = (const void*)0x01000000;
static const void* _mayorHouseSpringMapSegmentRomEnd = (const void*)0x01000000;
static const void* _librarySpringMapSegmentRomStart = (const void*)0x01000000;
static const void* _librarySpringMapSegmentRomEnd = (const void*)0x01000000;
static const void* _bakerySpringMapSegmentRomStart = (const void*)0x01000000;
static const void* _bakerySpringMapSegmentRomEnd = (const void*)0x01000000;
static const void* _shedSpringMapSegmentRomStart = (const void*)0x01000000;
static const void* _shedSpringMapSegmentRomEnd = (const void*)0x01000000;
// Map segments - Summer
static const void* _ranchSummerMapSegmentRomStart = (const void*)0x01000000;
static const void* _ranchSummerMapSegmentRomEnd = (const void*)0x01000000;
static const void* _beachSummerMapSegmentRomStart = (const void*)0x01000000;
static const void* _beachSummerMapSegmentRomEnd = (const void*)0x01000000;
static const void* _village1SummerMapSegmentRomStart = (const void*)0x01000000;
static const void* _village1SummerMapSegmentRomEnd = (const void*)0x01000000;
static const void* _village2SummerMapSegmentRomStart = (const void*)0x01000000;
static const void* _village2SummerMapSegmentRomEnd = (const void*)0x01000000;
static const void* _mountain1SummerMapSegmentRomStart = (const void*)0x01000000;
static const void* _mountain1SummerMapSegmentRomEnd = (const void*)0x01000000;
static const void* _mountain2SummerMapSegmentRomStart = (const void*)0x01000000;
static const void* _mountain2SummerMapSegmentRomEnd = (const void*)0x01000000;
static const void* _roadSummerMapSegmentRomStart = (const void*)0x01000000;
static const void* _roadSummerMapSegmentRomEnd = (const void*)0x01000000;
static const void* _farmSummerMapSegmentRomStart = (const void*)0x01000000;
static const void* _farmSummerMapSegmentRomEnd = (const void*)0x01000000;
static const void* _carpenterSummerMapSegmentRomStart = (const void*)0x01000000;
static const void* _carpenterSummerMapSegmentRomEnd = (const void*)0x01000000;
static const void* _flowerShopSummerMapSegmentRomStart = (const void*)0x01000000;
static const void* _flowerShopSummerMapSegmentRomEnd = (const void*)0x01000000;
static const void* _generalStoreSummerMapSegmentRomStart = (const void*)0x01000000;
static const void* _generalStoreSummerMapSegmentRomEnd = (const void*)0x01000000;
static const void* _potionShopSummerMapSegmentRomStart = (const void*)0x01000000;
static const void* _potionShopSummerMapSegmentRomEnd = (const void*)0x01000000;
static const void* _restaurantSummerMapSegmentRomStart = (const void*)0x01000000;
static const void* _restaurantSummerMapSegmentRomEnd = (const void*)0x01000000;
static const void* _churchSummerMapSegmentRomStart = (const void*)0x01000000;
static const void* _churchSummerMapSegmentRomEnd = (const void*)0x01000000;
static const void* _barSummerMapSegmentRomStart = (const void*)0x01000000;
static const void* _barSummerMapSegmentRomEnd = (const void*)0x01000000;
static const void* _mayorHouseSummerMapSegmentRomStart = (const void*)0x01000000;
static const void* _mayorHouseSummerMapSegmentRomEnd = (const void*)0x01000000;
static const void* _librarySummerMapSegmentRomStart = (const void*)0x01000000;
static const void* _librarySummerMapSegmentRomEnd = (const void*)0x01000000;
static const void* _bakerySummerMapSegmentRomStart = (const void*)0x01000000;
static const void* _bakerySummerMapSegmentRomEnd = (const void*)0x01000000;
static const void* _shedSummerMapSegmentRomStart = (const void*)0x01000000;
static const void* _shedSummerMapSegmentRomEnd = (const void*)0x01000000;
// Map segments - Fall
static const void* _ranchFallMapSegmentRomStart = (const void*)0x01000000;
static const void* _ranchFallMapSegmentRomEnd = (const void*)0x01000000;
static const void* _beachFallMapSegmentRomStart = (const void*)0x01000000;
static const void* _beachFallMapSegmentRomEnd = (const void*)0x01000000;
static const void* _village1FallMapSegmentRomStart = (const void*)0x01000000;
static const void* _village1FallMapSegmentRomEnd = (const void*)0x01000000;
static const void* _village2FallMapSegmentRomStart = (const void*)0x01000000;
static const void* _village2FallMapSegmentRomEnd = (const void*)0x01000000;
static const void* _mountain1FallMapSegmentRomStart = (const void*)0x01000000;
static const void* _mountain1FallMapSegmentRomEnd = (const void*)0x01000000;
static const void* _mountain2FallMapSegmentRomStart = (const void*)0x01000000;
static const void* _mountain2FallMapSegmentRomEnd = (const void*)0x01000000;
static const void* _roadFallMapSegmentRomStart = (const void*)0x01000000;
static const void* _roadFallMapSegmentRomEnd = (const void*)0x01000000;
static const void* _farmFallMapSegmentRomStart = (const void*)0x01000000;
static const void* _farmFallMapSegmentRomEnd = (const void*)0x01000000;
static const void* _carpenterFallMapSegmentRomStart = (const void*)0x01000000;
static const void* _carpenterFallMapSegmentRomEnd = (const void*)0x01000000;
static const void* _flowerShopFallMapSegmentRomStart = (const void*)0x01000000;
static const void* _flowerShopFallMapSegmentRomEnd = (const void*)0x01000000;
static const void* _generalStoreFallMapSegmentRomStart = (const void*)0x01000000;
static const void* _generalStoreFallMapSegmentRomEnd = (const void*)0x01000000;
static const void* _potionShopFallMapSegmentRomStart = (const void*)0x01000000;
static const void* _potionShopFallMapSegmentRomEnd = (const void*)0x01000000;
static const void* _restaurantFallMapSegmentRomStart = (const void*)0x01000000;
static const void* _restaurantFallMapSegmentRomEnd = (const void*)0x01000000;
static const void* _churchFallMapSegmentRomStart = (const void*)0x01000000;
static const void* _churchFallMapSegmentRomEnd = (const void*)0x01000000;
static const void* _barFallMapSegmentRomStart = (const void*)0x01000000;
static const void* _barFallMapSegmentRomEnd = (const void*)0x01000000;
static const void* _mayorHouseFallMapSegmentRomStart = (const void*)0x01000000;
static const void* _mayorHouseFallMapSegmentRomEnd = (const void*)0x01000000;
static const void* _libraryFallMapSegmentRomStart = (const void*)0x01000000;
static const void* _libraryFallMapSegmentRomEnd = (const void*)0x01000000;
static const void* _bakeryFallMapSegmentRomStart = (const void*)0x01000000;
static const void* _bakeryFallMapSegmentRomEnd = (const void*)0x01000000;
static const void* _shedFallMapSegmentRomStart = (const void*)0x01000000;
static const void* _shedFallMapSegmentRomEnd = (const void*)0x01000000;
// Map segments - Winter
static const void* _ranchWinterMapSegmentRomStart = (const void*)0x01000000;
static const void* _ranchWinterMapSegmentRomEnd = (const void*)0x01000000;
static const void* _beachWinterMapSegmentRomStart = (const void*)0x01000000;
static const void* _beachWinterMapSegmentRomEnd = (const void*)0x01000000;
static const void* _village1WinterMapSegmentRomStart = (const void*)0x01000000;
static const void* _village1WinterMapSegmentRomEnd = (const void*)0x01000000;
static const void* _village2WinterMapSegmentRomStart = (const void*)0x01000000;
static const void* _village2WinterMapSegmentRomEnd = (const void*)0x01000000;
static const void* _mountain1WinterMapSegmentRomStart = (const void*)0x01000000;
static const void* _mountain1WinterMapSegmentRomEnd = (const void*)0x01000000;
static const void* _mountain2WinterMapSegmentRomStart = (const void*)0x01000000;
static const void* _mountain2WinterMapSegmentRomEnd = (const void*)0x01000000;
static const void* _roadWinterMapSegmentRomStart = (const void*)0x01000000;
static const void* _roadWinterMapSegmentRomEnd = (const void*)0x01000000;
static const void* _farmWinterMapSegmentRomStart = (const void*)0x01000000;
static const void* _farmWinterMapSegmentRomEnd = (const void*)0x01000000;
static const void* _carpenterWinterMapSegmentRomStart = (const void*)0x01000000;
static const void* _carpenterWinterMapSegmentRomEnd = (const void*)0x01000000;
static const void* _flowerShopWinterMapSegmentRomStart = (const void*)0x01000000;
static const void* _flowerShopWinterMapSegmentRomEnd = (const void*)0x01000000;
static const void* _generalStoreWinterMapSegmentRomStart = (const void*)0x01000000;
static const void* _generalStoreWinterMapSegmentRomEnd = (const void*)0x01000000;
static const void* _potionShopWinterMapSegmentRomStart = (const void*)0x01000000;
static const void* _potionShopWinterMapSegmentRomEnd = (const void*)0x01000000;
static const void* _restaurantWinterMapSegmentRomStart = (const void*)0x01000000;
static const void* _restaurantWinterMapSegmentRomEnd = (const void*)0x01000000;
static const void* _churchWinterMapSegmentRomStart = (const void*)0x01000000;
static const void* _churchWinterMapSegmentRomEnd = (const void*)0x01000000;
static const void* _barWinterMapSegmentRomStart = (const void*)0x01000000;
static const void* _barWinterMapSegmentRomEnd = (const void*)0x01000000;
static const void* _mayorHouseWinterMapSegmentRomStart = (const void*)0x01000000;
static const void* _mayorHouseWinterMapSegmentRomEnd = (const void*)0x01000000;
static const void* _libraryWinterMapSegmentRomStart = (const void*)0x01000000;
static const void* _libraryWinterMapSegmentRomEnd = (const void*)0x01000000;
static const void* _bakeryWinterMapSegmentRomStart = (const void*)0x01000000;
static const void* _bakeryWinterMapSegmentRomEnd = (const void*)0x01000000;
static const void* _shedWinterMapSegmentRomStart = (const void*)0x01000000;
static const void* _shedWinterMapSegmentRomEnd = (const void*)0x01000000;
// Interior maps
static const void* _annsRoomMapSegmentRomStart = (const void*)0x01000000;
static const void* _annsRoomMapSegmentRomEnd = (const void*)0x01000000;
static const void* _ranchBarnMapSegmentRomStart = (const void*)0x01000000;
static const void* _ranchBarnMapSegmentRomEnd = (const void*)0x01000000;
static const void* _ranchStoreMapSegmentRomStart = (const void*)0x01000000;
static const void* _ranchStoreMapSegmentRomEnd = (const void*)0x01000000;
static const void* _ranchHouseMapSegmentRomStart = (const void*)0x01000000;
static const void* _ranchHouseMapSegmentRomEnd = (const void*)0x01000000;
static const void* _emptyMap1SegmentRomStart = (const void*)0x01000000;
static const void* _emptyMap1SegmentRomEnd = (const void*)0x01000000;
static const void* _titleScreenSpritesTextureSegmentRomStart = (const void*)0x01000000;
static const void* _titleScreenSpritesTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _titleScreenSpritesAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _titleScreenSpritesAssetsIndexSegmentRomEnd = (const void*)0x01000000;
// Message box sprites
static const void* _messageBoxTextureSegmentRomStart = (const void*)0x01000000;
static const void* _messageBoxTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _messageBoxAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _messageBoxAssetsIndexSegmentRomEnd = (const void*)0x01000000;
// Dialogue icon sprites
static const void* _dialogueIconTextureSegmentRomStart = (const void*)0x01000000;
static const void* _dialogueIconTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _dialogueIconAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _dialogueIconAssetsIndexSegmentRomEnd = (const void*)0x01000000;
// Character avatar sprites (both singular and plural names)
static const void* _characterAvatarTextureSegmentRomStart = (const void*)0x01000000;
static const void* _characterAvatarTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _characterAvatarAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _characterAvatarAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _characterAvatarsTextureSegmentRomStart = (const void*)0x01000000;
static const void* _characterAvatarsTextureSegmentRomEnd = (const void*)0x01000000;
static const void* _characterAvatarsAssetsIndexSegmentRomStart = (const void*)0x01000000;
static const void* _characterAvatarsAssetsIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _characterAvatarsSpritesheetIndexSegmentRomStart = (const void*)0x01000000;
static const void* _characterAvatarsSpritesheetIndexSegmentRomEnd = (const void*)0x01000000;
// Race Track maps
static const void* _raceTrackSpringMapSegmentRomStart = (const void*)0x01000000;
static const void* _raceTrackSpringMapSegmentRomEnd = (const void*)0x01000000;
static const void* _raceTrackSummerMapSegmentRomStart = (const void*)0x01000000;
static const void* _raceTrackSummerMapSegmentRomEnd = (const void*)0x01000000;
static const void* _raceTrackFallMapSegmentRomStart = (const void*)0x01000000;
static const void* _raceTrackFallMapSegmentRomEnd = (const void*)0x01000000;
static const void* _raceTrackWinterMapSegmentRomStart = (const void*)0x01000000;
static const void* _raceTrackWinterMapSegmentRomEnd = (const void*)0x01000000;
// Top of Mountain 1 maps
static const void* _topOfMountain1SpringMapSegmentRomStart = (const void*)0x01000000;
static const void* _topOfMountain1SpringMapSegmentRomEnd = (const void*)0x01000000;
static const void* _topOfMountain1SummerMapSegmentRomStart = (const void*)0x01000000;
static const void* _topOfMountain1SummerMapSegmentRomEnd = (const void*)0x01000000;
static const void* _topOfMountain1FallMapSegmentRomStart = (const void*)0x01000000;
static const void* _topOfMountain1FallMapSegmentRomEnd = (const void*)0x01000000;
static const void* _topOfMountain1WinterMapSegmentRomStart = (const void*)0x01000000;
static const void* _topOfMountain1WinterMapSegmentRomEnd = (const void*)0x01000000;
// Moon Mountain maps
static const void* _moonMountainSpringMapSegmentRomStart = (const void*)0x01000000;
static const void* _moonMountainSpringMapSegmentRomEnd = (const void*)0x01000000;
static const void* _moonMountainSummerMapSegmentRomStart = (const void*)0x01000000;
static const void* _moonMountainSummerMapSegmentRomEnd = (const void*)0x01000000;
static const void* _moonMountainFallMapSegmentRomStart = (const void*)0x01000000;
static const void* _moonMountainFallMapSegmentRomEnd = (const void*)0x01000000;
static const void* _moonMountainWinterMapSegmentRomStart = (const void*)0x01000000;
static const void* _moonMountainWinterMapSegmentRomEnd = (const void*)0x01000000;
// Square maps
static const void* _squareSpringMapSegmentRomStart = (const void*)0x01000000;
static const void* _squareSpringMapSegmentRomEnd = (const void*)0x01000000;
static const void* _squareSummerMapSegmentRomStart = (const void*)0x01000000;
static const void* _squareSummerMapSegmentRomEnd = (const void*)0x01000000;
static const void* _squareFallMapSegmentRomStart = (const void*)0x01000000;
static const void* _squareFallMapSegmentRomEnd = (const void*)0x01000000;
static const void* _squareWinterMapSegmentRomStart = (const void*)0x01000000;
static const void* _squareWinterMapSegmentRomEnd = (const void*)0x01000000;
// Harvest Sprite Cave maps
static const void* _harvestSpriteCaveSpringMapSegmentRomStart = (const void*)0x01000000;
static const void* _harvestSpriteCaveSpringMapSegmentRomEnd = (const void*)0x01000000;
static const void* _harvestSpriteCaveSummerMapSegmentRomStart = (const void*)0x01000000;
static const void* _harvestSpriteCaveSummerMapSegmentRomEnd = (const void*)0x01000000;
static const void* _harvestSpriteCaveFallMapSegmentRomStart = (const void*)0x01000000;
static const void* _harvestSpriteCaveFallMapSegmentRomEnd = (const void*)0x01000000;
static const void* _harvestSpriteCaveWinterMapSegmentRomStart = (const void*)0x01000000;
static const void* _harvestSpriteCaveWinterMapSegmentRomEnd = (const void*)0x01000000;
// Cave maps
static const void* _caveMapSegmentRomStart = (const void*)0x01000000;
static const void* _caveMapSegmentRomEnd = (const void*)0x01000000;
// House expansion maps
static const void* _houseExpansion1MapSegmentRomStart = (const void*)0x01000000;
static const void* _houseExpansion1MapSegmentRomEnd = (const void*)0x01000000;
static const void* _houseExpansion2MapSegmentRomStart = (const void*)0x01000000;
static const void* _houseExpansion2MapSegmentRomEnd = (const void*)0x01000000;
// Additional interior maps
static const void* _midwifesHouseMapSegmentRomStart = (const void*)0x01000000;
static const void* _midwifesHouseMapSegmentRomEnd = (const void*)0x01000000;
static const void* _churchMapSegmentRomStart = (const void*)0x01000000;
static const void* _churchMapSegmentRomEnd = (const void*)0x01000000;
static const void* _flowerShopMapSegmentRomStart = (const void*)0x01000000;
static const void* _flowerShopMapSegmentRomEnd = (const void*)0x01000000;
static const void* _bakeryMapSegmentRomStart = (const void*)0x01000000;
static const void* _bakeryMapSegmentRomEnd = (const void*)0x01000000;
static const void* _generalStoreMapSegmentRomStart = (const void*)0x01000000;
static const void* _generalStoreMapSegmentRomEnd = (const void*)0x01000000;
static const void* _barMapSegmentRomStart = (const void*)0x01000000;
static const void* _barMapSegmentRomEnd = (const void*)0x01000000;
static const void* _carpenterMapSegmentRomStart = (const void*)0x01000000;
static const void* _carpenterMapSegmentRomEnd = (const void*)0x01000000;
static const void* _potionShopMapSegmentRomStart = (const void*)0x01000000;
static const void* _potionShopMapSegmentRomEnd = (const void*)0x01000000;
static const void* _mayorHouseMapSegmentRomStart = (const void*)0x01000000;
static const void* _mayorHouseMapSegmentRomEnd = (const void*)0x01000000;
static const void* _libraryMapSegmentRomStart = (const void*)0x01000000;
static const void* _libraryMapSegmentRomEnd = (const void*)0x01000000;
static const void* _restaurantMapSegmentRomStart = (const void*)0x01000000;
static const void* _restaurantMapSegmentRomEnd = (const void*)0x01000000;
// Bathhouse and other special maps
static const void* _bathhouseMapSegmentRomStart = (const void*)0x01000000;
static const void* _bathhouseMapSegmentRomEnd = (const void*)0x01000000;
static const void* _goddessPondMapSegmentRomStart = (const void*)0x01000000;
static const void* _goddessPondMapSegmentRomEnd = (const void*)0x01000000;
// More interior maps
static const void* _carpentersHutMapSegmentRomStart = (const void*)0x01000000;
static const void* _carpentersHutMapSegmentRomEnd = (const void*)0x01000000;
static const void* _dumplingHouseMapSegmentRomStart = (const void*)0x01000000;
static const void* _dumplingHouseMapSegmentRomEnd = (const void*)0x01000000;
static const void* _ellisRoomMapSegmentRomStart = (const void*)0x01000000;
static const void* _ellisRoomMapSegmentRomEnd = (const void*)0x01000000;
static const void* _popurisRoomMapSegmentRomStart = (const void*)0x01000000;
static const void* _popurisRoomMapSegmentRomEnd = (const void*)0x01000000;
static const void* _souvenirShopMapSegmentRomStart = (const void*)0x01000000;
static const void* _souvenirShopMapSegmentRomEnd = (const void*)0x01000000;
static const void* _ricksShopMapSegmentRomStart = (const void*)0x01000000;
static const void* _ricksShopMapSegmentRomEnd = (const void*)0x01000000;
// Pond maps
static const void* _pondSpringMapSegmentRomStart = (const void*)0x01000000;
static const void* _pondSpringMapSegmentRomEnd = (const void*)0x01000000;
static const void* _pondSummerMapSegmentRomStart = (const void*)0x01000000;
static const void* _pondSummerMapSegmentRomEnd = (const void*)0x01000000;
static const void* _pondFallMapSegmentRomStart = (const void*)0x01000000;
static const void* _pondFallMapSegmentRomEnd = (const void*)0x01000000;
static const void* _pondWinterMapSegmentRomStart = (const void*)0x01000000;
static const void* _pondWinterMapSegmentRomEnd = (const void*)0x01000000;
// Vineyard maps
static const void* _vineyardSpringMapSegmentRomStart = (const void*)0x01000000;
static const void* _vineyardSpringMapSegmentRomEnd = (const void*)0x01000000;
static const void* _vineyardSummerMapSegmentRomStart = (const void*)0x01000000;
static const void* _vineyardSummerMapSegmentRomEnd = (const void*)0x01000000;
static const void* _vineyardFallMapSegmentRomStart = (const void*)0x01000000;
static const void* _vineyardFallMapSegmentRomEnd = (const void*)0x01000000;
static const void* _vineyardWinterMapSegmentRomStart = (const void*)0x01000000;
static const void* _vineyardWinterMapSegmentRomEnd = (const void*)0x01000000;
static const void* _vineyardHouseMapSegmentRomStart = (const void*)0x01000000;
static const void* _vineyardHouseMapSegmentRomEnd = (const void*)0x01000000;
static const void* _vineyardCellar1MapSegmentRomStart = (const void*)0x01000000;
static const void* _vineyardCellar1MapSegmentRomEnd = (const void*)0x01000000;
static const void* _vineyardCellar2MapSegmentRomStart = (const void*)0x01000000;
static const void* _vineyardCellar2MapSegmentRomEnd = (const void*)0x01000000;
// Additional room maps
static const void* _tavernMapSegmentRomStart = (const void*)0x01000000;
static const void* _tavernMapSegmentRomEnd = (const void*)0x01000000;
static const void* _mariasRoomMapSegmentRomStart = (const void*)0x01000000;
static const void* _mariasRoomMapSegmentRomEnd = (const void*)0x01000000;
static const void* _mayorsHouseMapSegmentRomStart = (const void*)0x01000000;
static const void* _mayorsHouseMapSegmentRomEnd = (const void*)0x01000000;
static const void* _potionShopBackroomMapSegmentRomStart = (const void*)0x01000000;
static const void* _potionShopBackroomMapSegmentRomEnd = (const void*)0x01000000;
static const void* _spriteCaveMapSegmentRomStart = (const void*)0x01000000;
static const void* _spriteCaveMapSegmentRomEnd = (const void*)0x01000000;
static const void* _emptyMineMapSegmentRomStart = (const void*)0x01000000;
static const void* _emptyMineMapSegmentRomEnd = (const void*)0x01000000;
static const void* _mineMapSegmentRomStart = (const void*)0x01000000;
static const void* _mineMapSegmentRomEnd = (const void*)0x01000000;
static const void* _karensRoomMapSegmentRomStart = (const void*)0x01000000;
static const void* _karensRoomMapSegmentRomEnd = (const void*)0x01000000;
static const void* _greenhouseMapSegmentRomStart = (const void*)0x01000000;
static const void* _greenhouseMapSegmentRomEnd = (const void*)0x01000000;
static const void* _barnMapSegmentRomStart = (const void*)0x01000000;
static const void* _barnMapSegmentRomEnd = (const void*)0x01000000;
static const void* _coopMapSegmentRomStart = (const void*)0x01000000;
static const void* _coopMapSegmentRomEnd = (const void*)0x01000000;
static const void* _shedMapSegmentRomStart = (const void*)0x01000000;
static const void* _shedMapSegmentRomEnd = (const void*)0x01000000;
static const void* _houseMapSegmentRomStart = (const void*)0x01000000;
static const void* _houseMapSegmentRomEnd = (const void*)0x01000000;
static const void* _kitchenMapSegmentRomStart = (const void*)0x01000000;
static const void* _kitchenMapSegmentRomEnd = (const void*)0x01000000;
static const void* _bathroomMapSegmentRomStart = (const void*)0x01000000;
static const void* _bathroomMapSegmentRomEnd = (const void*)0x01000000;
static const void* _basementMapSegmentRomStart = (const void*)0x01000000;
static const void* _basementMapSegmentRomEnd = (const void*)0x01000000;
static const void* _babyRoomMapSegmentRomStart = (const void*)0x01000000;
static const void* _babyRoomMapSegmentRomEnd = (const void*)0x01000000;
// Starry Night Festival maps
static const void* _starryNightFestivalVillage2MapSegmentRomStart = (const void*)0x01000000;
static const void* _starryNightFestivalVillage2MapSegmentRomEnd = (const void*)0x01000000;
// Hill maps
static const void* _hillSpringMapSegmentRomStart = (const void*)0x01000000;
static const void* _hillSpringMapSegmentRomEnd = (const void*)0x01000000;
static const void* _hillSummerMapSegmentRomStart = (const void*)0x01000000;
static const void* _hillSummerMapSegmentRomEnd = (const void*)0x01000000;
static const void* _hillFallMapSegmentRomStart = (const void*)0x01000000;
static const void* _hillFallMapSegmentRomEnd = (const void*)0x01000000;
static const void* _hillWinterMapSegmentRomStart = (const void*)0x01000000;
static const void* _hillWinterMapSegmentRomEnd = (const void*)0x01000000;
// Empty maps for padding
static const void* _emptyMap2SegmentRomStart = (const void*)0x01000000;
static const void* _emptyMap2SegmentRomEnd = (const void*)0x01000000;
static const void* _emptyMap3SegmentRomStart = (const void*)0x01000000;
static const void* _emptyMap3SegmentRomEnd = (const void*)0x01000000;
static const void* _emptyMap4SegmentRomStart = (const void*)0x01000000;
static const void* _emptyMap4SegmentRomEnd = (const void*)0x01000000;
// PC Port buffer pointer exports (for pc_buffers.h)
#ifdef __cplusplus
extern "C" {
#endif
extern void* CUTSCENE_BYTECODE_BUFFER_1_PTR;
extern void* CUTSCENE_BYTECODE_BUFFER_2_PTR;
extern void* ENTITY_REGION_CHICKEN_BASE_PTR;
extern void* ENTITY_REGION_CHICK_BASE_PTR;
extern void* SHADOW_TEXTURE_BUFFER_PTR;
extern void* SHADOW_PALETTE_BUFFER_PTR;
extern void* SHADOW_ANIMATION_FRAME_METADATA_BUFFER_PTR;
extern void* SHADOW_TEXTURE_TO_PALETTE_LOOKUP_BUFFER_PTR;
extern void* PLAYER_TEXTURE_1_BUFFER_PTR;
extern void* PLAYER_TEXTURE_2_BUFFER_PTR;
extern void* PLAYER_PALETTE_BUFFER_PTR;
extern void* PLAYER_ANIMATION_FRAME_METADATA_BUFFER_PTR;
extern void* PLAYER_SPRITESHEET_INDEX_BUFFER_PTR;
extern void* PLAYER_TEXTURE_TO_PALETTE_LOOKUP_BUFFER_PTR;
extern void* ENTITY_SLOTS_1_20_PALETTE_PTR;
extern void* ENTITY_SLOTS_1_20_ANIM_METADATA_PTR;
extern void* ENTITY_SLOTS_1_20_SPRITESHEET_INDEX_PTR;
extern void* ENTITY_SLOTS_1_20_TEXTURE_TO_PALETTE_LOOKUP_PTR;
extern void* ENTITY_SLOTS_2_7_PALETTE_PTR;
extern void* ENTITY_SLOTS_2_7_ANIM_METADATA_PTR;
extern void* ENTITY_SLOTS_2_7_SPRITESHEET_INDEX_PTR;
extern void* ENTITY_SLOTS_2_7_TEXTURE_TO_PALETTE_LOOKUP_PTR;
extern void* GROUND_OBJECTS_TEXTURE_BUFFER_PTR;
extern void* GROUND_OBJECTS_PALETTE_BUFFER_PTR;
extern void* GROUND_OBJECTS_SPRITE_TO_PALETTE_LOOKUP_BUFFER_PTR;
#ifdef __cplusplus
}
#endif

#endif
// Text segments
typedef struct { const void* start; const void* end; } TextSegmentDef;
// Text 1
static const void* _text1TextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _text1TextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _text1TextSegmentRomStart = (const void*)0x01000000;
static const void* _text1TextSegmentRomEnd = (const void*)0x01000000;
// Library text
static const void* _libraryTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _libraryTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _libraryTextSegmentRomStart = (const void*)0x01000000;
static const void* _libraryTextSegmentRomEnd = (const void*)0x01000000;
// Diary text
static const void* _diaryTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _diaryTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _diaryTextSegmentRomStart = (const void*)0x01000000;
static const void* _diaryTextSegmentRomEnd = (const void*)0x01000000;
// Recipes Japanese text
static const void* _recipesJapaneseTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _recipesJapaneseTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _recipesJapaneseTextSegmentRomStart = (const void*)0x01000000;
static const void* _recipesJapaneseTextSegmentRomEnd = (const void*)0x01000000;
// Festival overlay selections text
static const void* _festivalOverlaySelectionsTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _festivalOverlaySelectionsTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _festivalOverlaySelectionsTextSegmentRomStart = (const void*)0x01000000;
static const void* _festivalOverlaySelectionsTextSegmentRomEnd = (const void*)0x01000000;
// Letters text
static const void* _lettersTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _lettersTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _lettersTextSegmentRomStart = (const void*)0x01000000;
static const void* _lettersTextSegmentRomEnd = (const void*)0x01000000;
// Shop text
static const void* _shopTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _shopTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _shopTextSegmentRomStart = (const void*)0x01000000;
static const void* _shopTextSegmentRomEnd = (const void*)0x01000000;
// Animal interactions text
static const void* _animalInteractionsTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _animalInteractionsTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _animalInteractionsTextSegmentRomStart = (const void*)0x01000000;
static const void* _animalInteractionsTextSegmentRomEnd = (const void*)0x01000000;
// TV text
static const void* _tvTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _tvTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _tvTextSegmentRomStart = (const void*)0x01000000;
static const void* _tvTextSegmentRomEnd = (const void*)0x01000000;
// Text 10
static const void* _text10TextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _text10TextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _text10TextSegmentRomStart = (const void*)0x01000000;
static const void* _text10TextSegmentRomEnd = (const void*)0x01000000;
// Naming screen text
static const void* _namingScreenTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _namingScreenTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _namingScreenTextSegmentRomStart = (const void*)0x01000000;
static const void* _namingScreenTextSegmentRomEnd = (const void*)0x01000000;
// NPC Text segments - Maria
static const void* _mariaTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _mariaTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _mariaTextSegmentRomStart = (const void*)0x01000000;
static const void* _mariaTextSegmentRomEnd = (const void*)0x01000000;
// Popuri
static const void* _popuriTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _popuriTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _popuriTextSegmentRomStart = (const void*)0x01000000;
static const void* _popuriTextSegmentRomEnd = (const void*)0x01000000;
// Elli
static const void* _elliTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _elliTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _elliTextSegmentRomStart = (const void*)0x01000000;
static const void* _elliTextSegmentRomEnd = (const void*)0x01000000;
// Ann
static const void* _annTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _annTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _annTextSegmentRomStart = (const void*)0x01000000;
static const void* _annTextSegmentRomEnd = (const void*)0x01000000;
// Karen
static const void* _karenTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _karenTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _karenTextSegmentRomStart = (const void*)0x01000000;
static const void* _karenTextSegmentRomEnd = (const void*)0x01000000;
// Baby
static const void* _babyTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _babyTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _babyTextSegmentRomStart = (const void*)0x01000000;
static const void* _babyTextSegmentRomEnd = (const void*)0x01000000;
// Harris
static const void* _harrisTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _harrisTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _harrisTextSegmentRomStart = (const void*)0x01000000;
static const void* _harrisTextSegmentRomEnd = (const void*)0x01000000;
// Gray
static const void* _grayTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _grayTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _grayTextSegmentRomStart = (const void*)0x01000000;
static const void* _grayTextSegmentRomEnd = (const void*)0x01000000;
// Jeff
static const void* _jeffTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _jeffTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _jeffTextSegmentRomStart = (const void*)0x01000000;
static const void* _jeffTextSegmentRomEnd = (const void*)0x01000000;
// Cliff
static const void* _cliffTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _cliffTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _cliffTextSegmentRomStart = (const void*)0x01000000;
static const void* _cliffTextSegmentRomEnd = (const void*)0x01000000;
// Kai
static const void* _kaiTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _kaiTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _kaiTextSegmentRomStart = (const void*)0x01000000;
static const void* _kaiTextSegmentRomEnd = (const void*)0x01000000;
// Mayor
static const void* _mayorTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _mayorTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _mayorTextSegmentRomStart = (const void*)0x01000000;
static const void* _mayorTextSegmentRomEnd = (const void*)0x01000000;
// Mayor Wife
static const void* _mayorWifeTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _mayorWifeTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _mayorWifeTextSegmentRomStart = (const void*)0x01000000;
static const void* _mayorWifeTextSegmentRomEnd = (const void*)0x01000000;
// Lillia
static const void* _lilliaTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _lilliaTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _lilliaTextSegmentRomStart = (const void*)0x01000000;
static const void* _lilliaTextSegmentRomEnd = (const void*)0x01000000;
// Basil
static const void* _basilTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _basilTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _basilTextSegmentRomStart = (const void*)0x01000000;
static const void* _basilTextSegmentRomEnd = (const void*)0x01000000;
// Ellen
static const void* _ellenTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _ellenTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _ellenTextSegmentRomStart = (const void*)0x01000000;
static const void* _ellenTextSegmentRomEnd = (const void*)0x01000000;
// Doug
static const void* _dougTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _dougTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _dougTextSegmentRomStart = (const void*)0x01000000;
static const void* _dougTextSegmentRomEnd = (const void*)0x01000000;
// Gotz
static const void* _gotzTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _gotzTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _gotzTextSegmentRomStart = (const void*)0x01000000;
static const void* _gotzTextSegmentRomEnd = (const void*)0x01000000;
// Sasha
static const void* _sashaTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _sashaTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _sashaTextSegmentRomStart = (const void*)0x01000000;
static const void* _sashaTextSegmentRomEnd = (const void*)0x01000000;
// More NPC text segments
static const void* _potionShopDealerTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _potionShopDealerTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _potionShopDealerTextSegmentRomStart = (const void*)0x01000000;
static const void* _potionShopDealerTextSegmentRomEnd = (const void*)0x01000000;
static const void* _kentTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _kentTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _kentTextSegmentRomStart = (const void*)0x01000000;
static const void* _kentTextSegmentRomEnd = (const void*)0x01000000;
static const void* _stuTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _stuTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _stuTextSegmentRomStart = (const void*)0x01000000;
static const void* _stuTextSegmentRomEnd = (const void*)0x01000000;
static const void* _midwifeTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _midwifeTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _midwifeTextSegmentRomStart = (const void*)0x01000000;
static const void* _midwifeTextSegmentRomEnd = (const void*)0x01000000;
static const void* _mayTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _mayTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _mayTextSegmentRomStart = (const void*)0x01000000;
static const void* _mayTextSegmentRomEnd = (const void*)0x01000000;
static const void* _rickTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _rickTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _rickTextSegmentRomStart = (const void*)0x01000000;
static const void* _rickTextSegmentRomEnd = (const void*)0x01000000;
static const void* _pastorTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _pastorTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _pastorTextSegmentRomStart = (const void*)0x01000000;
static const void* _pastorTextSegmentRomEnd = (const void*)0x01000000;
static const void* _shipperTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _shipperTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _shipperTextSegmentRomStart = (const void*)0x01000000;
static const void* _shipperTextSegmentRomEnd = (const void*)0x01000000;
static const void* _saibaraTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _saibaraTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _saibaraTextSegmentRomStart = (const void*)0x01000000;
static const void* _saibaraTextSegmentRomEnd = (const void*)0x01000000;
static const void* _dukeTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _dukeTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _dukeTextSegmentRomStart = (const void*)0x01000000;
static const void* _dukeTextSegmentRomEnd = (const void*)0x01000000;
static const void* _gregTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _gregTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _gregTextSegmentRomStart = (const void*)0x01000000;
static const void* _gregTextSegmentRomEnd = (const void*)0x01000000;
static const void* _assistantCarpenterTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _assistantCarpenterTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _assistantCarpenterTextSegmentRomStart = (const void*)0x01000000;
static const void* _assistantCarpenterTextSegmentRomEnd = (const void*)0x01000000;
static const void* _masterCarpenterTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _masterCarpenterTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _masterCarpenterTextSegmentRomStart = (const void*)0x01000000;
static const void* _masterCarpenterTextSegmentRomEnd = (const void*)0x01000000;
static const void* _harvestSpriteTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _harvestSpriteTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _harvestSpriteTextSegmentRomStart = (const void*)0x01000000;
static const void* _harvestSpriteTextSegmentRomEnd = (const void*)0x01000000;
// Harvest sprites (plural) text segments
static const void* _harvestSpritesTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _harvestSpritesTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _harvestSpritesTextSegmentRomStart = (const void*)0x01000000;
static const void* _harvestSpritesTextSegmentRomEnd = (const void*)0x01000000;
static const void* _barleyTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _barleyTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _barleyTextSegmentRomStart = (const void*)0x01000000;
static const void* _barleyTextSegmentRomEnd = (const void*)0x01000000;
static const void* _sydneyTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _sydneyTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _sydneyTextSegmentRomStart = (const void*)0x01000000;
static const void* _sydneyTextSegmentRomEnd = (const void*)0x01000000;
static const void* _entomologistTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _entomologistTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _entomologistTextSegmentRomStart = (const void*)0x01000000;
static const void* _entomologistTextSegmentRomEnd = (const void*)0x01000000;
static const void* _gourmetJudgeTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _gourmetJudgeTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _gourmetJudgeTextSegmentRomStart = (const void*)0x01000000;
static const void* _gourmetJudgeTextSegmentRomEnd = (const void*)0x01000000;
static const void* _photographerTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _photographerTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _photographerTextSegmentRomStart = (const void*)0x01000000;
static const void* _photographerTextSegmentRomEnd = (const void*)0x01000000;
static const void* _shadySalesmanTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _shadySalesmanTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _shadySalesmanTextSegmentRomStart = (const void*)0x01000000;
static const void* _shadySalesmanTextSegmentRomEnd = (const void*)0x01000000;
static const void* _mrsManaSonTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _mrsManaSonTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _mrsManaSonTextSegmentRomStart = (const void*)0x01000000;
static const void* _mrsManaSonTextSegmentRomEnd = (const void*)0x01000000;
static const void* _mrsManaTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _mrsManaTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _mrsManaTextSegmentRomStart = (const void*)0x01000000;
static const void* _mrsManaTextSegmentRomEnd = (const void*)0x01000000;
static const void* _oldManTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _oldManTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _oldManTextSegmentRomStart = (const void*)0x01000000;
static const void* _oldManTextSegmentRomEnd = (const void*)0x01000000;
static const void* _oldWomanTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _oldWomanTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _oldWomanTextSegmentRomStart = (const void*)0x01000000;
static const void* _oldWomanTextSegmentRomEnd = (const void*)0x01000000;
static const void* _touristCoupleManTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _touristCoupleManTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _touristCoupleManTextSegmentRomStart = (const void*)0x01000000;
static const void* _touristCoupleManTextSegmentRomEnd = (const void*)0x01000000;
static const void* _touristCoupleWomanTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _touristCoupleWomanTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _touristCoupleWomanTextSegmentRomStart = (const void*)0x01000000;
static const void* _touristCoupleWomanTextSegmentRomEnd = (const void*)0x01000000;
static const void* _festivalGirl1TextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _festivalGirl1TextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _festivalGirl1TextSegmentRomStart = (const void*)0x01000000;
static const void* _festivalGirl1TextSegmentRomEnd = (const void*)0x01000000;
static const void* _festivalGirl2TextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _festivalGirl2TextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _festivalGirl2TextSegmentRomStart = (const void*)0x01000000;
static const void* _festivalGirl2TextSegmentRomEnd = (const void*)0x01000000;
static const void* _festivalGirl3TextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _festivalGirl3TextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _festivalGirl3TextSegmentRomStart = (const void*)0x01000000;
static const void* _festivalGirl3TextSegmentRomEnd = (const void*)0x01000000;
static const void* _harvestGoddessTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _harvestGoddessTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _harvestGoddessTextSegmentRomStart = (const void*)0x01000000;
static const void* _harvestGoddessTextSegmentRomEnd = (const void*)0x01000000;
static const void* _spiritFestivalOcarinaPerformerTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _spiritFestivalOcarinaPerformerTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _spiritFestivalOcarinaPerformerTextSegmentRomStart = (const void*)0x01000000;
static const void* _spiritFestivalOcarinaPerformerTextSegmentRomEnd = (const void*)0x01000000;
static const void* _kappaTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _kappaTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _kappaTextSegmentRomStart = (const void*)0x01000000;
static const void* _kappaTextSegmentRomEnd = (const void*)0x01000000;
static const void* _princessTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _princessTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _princessTextSegmentRomStart = (const void*)0x01000000;
static const void* _princessTextSegmentRomEnd = (const void*)0x01000000;
// Additional NPC text segments
static const void* _mrsManaAndJohnTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _mrsManaAndJohnTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _mrsManaAndJohnTextSegmentRomStart = (const void*)0x01000000;
static const void* _mrsManaAndJohnTextSegmentRomEnd = (const void*)0x01000000;
static const void* _bakerAndPotionShopDealerTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _bakerAndPotionShopDealerTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _bakerAndPotionShopDealerTextSegmentRomStart = (const void*)0x01000000;
static const void* _bakerAndPotionShopDealerTextSegmentRomEnd = (const void*)0x01000000;
static const void* _ellenAndMariaTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _ellenAndMariaTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _ellenAndMariaTextSegmentRomStart = (const void*)0x01000000;
static const void* _ellenAndMariaTextSegmentRomEnd = (const void*)0x01000000;
static const void* _elliAndPopuriTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _elliAndPopuriTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _elliAndPopuriTextSegmentRomStart = (const void*)0x01000000;
static const void* _elliAndPopuriTextSegmentRomEnd = (const void*)0x01000000;
static const void* _annAndKarenTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _annAndKarenTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _annAndKarenTextSegmentRomStart = (const void*)0x01000000;
static const void* _annAndKarenTextSegmentRomEnd = (const void*)0x01000000;
static const void* _pastorAndMayTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _pastorAndMayTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _pastorAndMayTextSegmentRomStart = (const void*)0x01000000;
static const void* _pastorAndMayTextSegmentRomEnd = (const void*)0x01000000;
static const void* _dougAndGotzTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _dougAndGotzTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _dougAndGotzTextSegmentRomStart = (const void*)0x01000000;
static const void* _dougAndGotzTextSegmentRomEnd = (const void*)0x01000000;
static const void* _rickAndCliffTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _rickAndCliffTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _rickAndCliffTextSegmentRomStart = (const void*)0x01000000;
static const void* _rickAndCliffTextSegmentRomEnd = (const void*)0x01000000;
static const void* _harrisAndGrayTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _harrisAndGrayTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _harrisAndGrayTextSegmentRomStart = (const void*)0x01000000;
static const void* _harrisAndGrayTextSegmentRomEnd = (const void*)0x01000000;
static const void* _kaiAndJeffTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _kaiAndJeffTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _kaiAndJeffTextSegmentRomStart = (const void*)0x01000000;
static const void* _kaiAndJeffTextSegmentRomEnd = (const void*)0x01000000;
static const void* _dukeAndSaibaraTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _dukeAndSaibaraTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _dukeAndSaibaraTextSegmentRomStart = (const void*)0x01000000;
static const void* _dukeAndSaibaraTextSegmentRomEnd = (const void*)0x01000000;
static const void* _basilAndLilliaTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _basilAndLilliaTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _basilAndLilliaTextSegmentRomStart = (const void*)0x01000000;
static const void* _basilAndLilliaTextSegmentRomEnd = (const void*)0x01000000;
static const void* _mayorAndMayorWifeTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _mayorAndMayorWifeTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _mayorAndMayorWifeTextSegmentRomStart = (const void*)0x01000000;
static const void* _mayorAndMayorWifeTextSegmentRomEnd = (const void*)0x01000000;
static const void* _kentAndStuTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _kentAndStuTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _kentAndStuTextSegmentRomStart = (const void*)0x01000000;
static const void* _kentAndStuTextSegmentRomEnd = (const void*)0x01000000;
static const void* _midwifeAndBarleyTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _midwifeAndBarleyTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _midwifeAndBarleyTextSegmentRomStart = (const void*)0x01000000;
static const void* _midwifeAndBarleyTextSegmentRomEnd = (const void*)0x01000000;
static const void* _sydneyAndSashaTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _sydneyAndSashaTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _sydneyAndSashaTextSegmentRomStart = (const void*)0x01000000;
static const void* _sydneyAndSashaTextSegmentRomEnd = (const void*)0x01000000;
static const void* _shipperAndGregTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _shipperAndGregTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _shipperAndGregTextSegmentRomStart = (const void*)0x01000000;
static const void* _shipperAndGregTextSegmentRomEnd = (const void*)0x01000000;
static const void* _carpentersTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _carpentersTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _carpentersTextSegmentRomStart = (const void*)0x01000000;
static const void* _carpentersTextSegmentRomEnd = (const void*)0x01000000;
static const void* _spiritsTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _spiritsTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _spiritsTextSegmentRomStart = (const void*)0x01000000;
static const void* _spiritsTextSegmentRomEnd = (const void*)0x01000000;
static const void* _bachelorettesTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _bachelorettesTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _bachelorettesTextSegmentRomStart = (const void*)0x01000000;
static const void* _bachelorettesTextSegmentRomEnd = (const void*)0x01000000;
static const void* _villagersTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _villagersTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _villagersTextSegmentRomStart = (const void*)0x01000000;
static const void* _villagersTextSegmentRomEnd = (const void*)0x01000000;
static const void* _weddingTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _weddingTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _weddingTextSegmentRomStart = (const void*)0x01000000;
static const void* _weddingTextSegmentRomEnd = (const void*)0x01000000;
static const void* _newYearsTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _newYearsTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _newYearsTextSegmentRomStart = (const void*)0x01000000;
static const void* _newYearsTextSegmentRomEnd = (const void*)0x01000000;
static const void* _ranchStoryTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _ranchStoryTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _ranchStoryTextSegmentRomStart = (const void*)0x01000000;
static const void* _ranchStoryTextSegmentRomEnd = (const void*)0x01000000;
// Final NPC text segments
static const void* _additionalNpcsTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _additionalNpcsTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _additionalNpcsTextSegmentRomStart = (const void*)0x01000000;
static const void* _additionalNpcsTextSegmentRomEnd = (const void*)0x01000000;
static const void* _harvestSpritesAndGoddessTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _harvestSpritesAndGoddessTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _harvestSpritesAndGoddessTextSegmentRomStart = (const void*)0x01000000;
static const void* _harvestSpritesAndGoddessTextSegmentRomEnd = (const void*)0x01000000;
static const void* _oldPeopleTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _oldPeopleTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _oldPeopleTextSegmentRomStart = (const void*)0x01000000;
static const void* _oldPeopleTextSegmentRomEnd = (const void*)0x01000000;
static const void* _touristsTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _touristsTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _touristsTextSegmentRomStart = (const void*)0x01000000;
static const void* _touristsTextSegmentRomEnd = (const void*)0x01000000;
// Final text segments
static const void* _farmVisitsTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _farmVisitsTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _farmVisitsTextSegmentRomStart = (const void*)0x01000000;
static const void* _farmVisitsTextSegmentRomEnd = (const void*)0x01000000;
static const void* _text65TextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _text65TextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _text65TextSegmentRomStart = (const void*)0x01000000;
static const void* _text65TextSegmentRomEnd = (const void*)0x01000000;
static const void* _cutscenes1TextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _cutscenes1TextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _cutscenes1TextSegmentRomStart = (const void*)0x01000000;
static const void* _cutscenes1TextSegmentRomEnd = (const void*)0x01000000;
static const void* _text54TextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _text54TextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _text54TextSegmentRomStart = (const void*)0x01000000;
static const void* _text54TextSegmentRomEnd = (const void*)0x01000000;
// More final text segments
static const void* _marriedDialoguesTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _marriedDialoguesTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _marriedDialoguesTextSegmentRomStart = (const void*)0x01000000;
static const void* _marriedDialoguesTextSegmentRomEnd = (const void*)0x01000000;
static const void* _text61TextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _text61TextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _text61TextSegmentRomStart = (const void*)0x01000000;
static const void* _text61TextSegmentRomEnd = (const void*)0x01000000;
// Vineyard cutscenes text
static const void* _vineyardCutscenesTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _vineyardCutscenesTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _vineyardCutscenesTextSegmentRomStart = (const void*)0x01000000;
static const void* _vineyardCutscenesTextSegmentRomEnd = (const void*)0x01000000;
static const void* _text63TextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _text63TextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _text63TextSegmentRomStart = (const void*)0x01000000;
static const void* _text63TextSegmentRomEnd = (const void*)0x01000000;
// Beach cutscenes text
static const void* _beachCutscenesTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _beachCutscenesTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _beachCutscenesTextSegmentRomStart = (const void*)0x01000000;
static const void* _beachCutscenesTextSegmentRomEnd = (const void*)0x01000000;
static const void* _text55TextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _text55TextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _text55TextSegmentRomStart = (const void*)0x01000000;
static const void* _text55TextSegmentRomEnd = (const void*)0x01000000;
// Horse race text
static const void* _horseRaceTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _horseRaceTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _horseRaceTextSegmentRomStart = (const void*)0x01000000;
static const void* _horseRaceTextSegmentRomEnd = (const void*)0x01000000;
static const void* _text49TextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _text49TextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _text49TextSegmentRomStart = (const void*)0x01000000;
static const void* _text49TextSegmentRomEnd = (const void*)0x01000000;
// Vegetable festival text
static const void* _vegetableFestivalTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _vegetableFestivalTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _vegetableFestivalTextSegmentRomStart = (const void*)0x01000000;
static const void* _vegetableFestivalTextSegmentRomEnd = (const void*)0x01000000;
static const void* _text48TextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _text48TextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _text48TextSegmentRomStart = (const void*)0x01000000;
static const void* _text48TextSegmentRomEnd = (const void*)0x01000000;
static const void* _text52TextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _text52TextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _text52TextSegmentRomStart = (const void*)0x01000000;
static const void* _text52TextSegmentRomEnd = (const void*)0x01000000;
static const void* _text50TextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _text50TextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _text50TextSegmentRomStart = (const void*)0x01000000;
static const void* _text50TextSegmentRomEnd = (const void*)0x01000000;
static const void* _text51TextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _text51TextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _text51TextSegmentRomStart = (const void*)0x01000000;
static const void* _text51TextSegmentRomEnd = (const void*)0x01000000;
static const void* _text56TextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _text56TextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _text56TextSegmentRomStart = (const void*)0x01000000;
static const void* _text56TextSegmentRomEnd = (const void*)0x01000000;
// Festival text segments
static const void* _eggFestivalTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _eggFestivalTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _eggFestivalTextSegmentRomStart = (const void*)0x01000000;
static const void* _eggFestivalTextSegmentRomEnd = (const void*)0x01000000;
static const void* _dogRaceTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _dogRaceTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _dogRaceTextSegmentRomStart = (const void*)0x01000000;
static const void* _dogRaceTextSegmentRomEnd = (const void*)0x01000000;
static const void* _spiritFestivalTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _spiritFestivalTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _spiritFestivalTextSegmentRomStart = (const void*)0x01000000;
static const void* _spiritFestivalTextSegmentRomEnd = (const void*)0x01000000;
static const void* _harvestFestivalTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _harvestFestivalTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _harvestFestivalTextSegmentRomStart = (const void*)0x01000000;
static const void* _harvestFestivalTextSegmentRomEnd = (const void*)0x01000000;
static const void* _sowingFestivalTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _sowingFestivalTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _sowingFestivalTextSegmentRomStart = (const void*)0x01000000;
static const void* _sowingFestivalTextSegmentRomEnd = (const void*)0x01000000;
static const void* _fireflyFestivalTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _fireflyFestivalTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _fireflyFestivalTextSegmentRomStart = (const void*)0x01000000;
static const void* _fireflyFestivalTextSegmentRomEnd = (const void*)0x01000000;
static const void* _cowFestivalTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _cowFestivalTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _cowFestivalTextSegmentRomStart = (const void*)0x01000000;
static const void* _cowFestivalTextSegmentRomEnd = (const void*)0x01000000;
static const void* _seaFestivalTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _seaFestivalTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _seaFestivalTextSegmentRomStart = (const void*)0x01000000;
static const void* _seaFestivalTextSegmentRomEnd = (const void*)0x01000000;
static const void* _fireworksFestivalTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _fireworksFestivalTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _fireworksFestivalTextSegmentRomStart = (const void*)0x01000000;
static const void* _fireworksFestivalTextSegmentRomEnd = (const void*)0x01000000;
static const void* _flowerFestivalTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _flowerFestivalTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _flowerFestivalTextSegmentRomStart = (const void*)0x01000000;
static const void* _flowerFestivalTextSegmentRomEnd = (const void*)0x01000000;
static const void* _thanksgivingTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _thanksgivingTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _thanksgivingTextSegmentRomStart = (const void*)0x01000000;
static const void* _thanksgivingTextSegmentRomEnd = (const void*)0x01000000;
static const void* _starNightFestivalTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _starNightFestivalTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _starNightFestivalTextSegmentRomStart = (const void*)0x01000000;
static const void* _starNightFestivalTextSegmentRomEnd = (const void*)0x01000000;
// Funeral intro text
static const void* _funeralIntroTextIndexSegmentRomStart = (const void*)0x00E583C0;
static const void* _funeralIntroTextIndexSegmentRomEnd = (const void*)0x00E583F0;
static const void* _funeralIntroTextSegmentRomStart = (const void*)0x00E58160;
static const void* _funeralIntroTextSegmentRomEnd = (const void*)0x00E583C0;
// How to play text
static const void* _howToPlayTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _howToPlayTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _howToPlayTextSegmentRomStart = (const void*)0x01000000;
static const void* _howToPlayTextSegmentRomEnd = (const void*)0x01000000;
// Dialogue bytecode segments (auto-generated)
static const void* _additionalNpcs1DialogueIndexSegmentRomStart = (const void*)0x01000000;
static const void* _additionalNpcs1DialogueIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _additionalNpcs1DialogueSegmentRomStart = (const void*)0x01000000;
static const void* _additionalNpcs1DialogueSegmentRomEnd = (const void*)0x01000000;
static const void* _additionalNpcs2DialogueIndexSegmentRomStart = (const void*)0x01000000;
static const void* _additionalNpcs2DialogueIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _additionalNpcs2DialogueSegmentRomStart = (const void*)0x01000000;
static const void* _additionalNpcs2DialogueSegmentRomEnd = (const void*)0x01000000;
static const void* _annDialogueIndexSegmentRomStart = (const void*)0x01000000;
static const void* _annDialogueIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _annDialogueSegmentRomStart = (const void*)0x01000000;
static const void* _annDialogueSegmentRomEnd = (const void*)0x01000000;
static const void* _assistantCarpenters1DialogueIndexSegmentRomStart = (const void*)0x01000000;
static const void* _assistantCarpenters1DialogueIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _assistantCarpenters1DialogueSegmentRomStart = (const void*)0x01000000;
static const void* _assistantCarpenters1DialogueSegmentRomEnd = (const void*)0x01000000;
static const void* _assistantCarpenters2DialogueIndexSegmentRomStart = (const void*)0x01000000;
static const void* _assistantCarpenters2DialogueIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _assistantCarpenters2DialogueSegmentRomStart = (const void*)0x01000000;
static const void* _assistantCarpenters2DialogueSegmentRomEnd = (const void*)0x01000000;
static const void* _babyDialogueIndexSegmentRomStart = (const void*)0x01000000;
static const void* _babyDialogueIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _babyDialogueSegmentRomStart = (const void*)0x01000000;
static const void* _babyDialogueSegmentRomEnd = (const void*)0x01000000;
static const void* _barleyDialogueIndexSegmentRomStart = (const void*)0x01000000;
static const void* _barleyDialogueIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _barleyDialogueSegmentRomStart = (const void*)0x01000000;
static const void* _barleyDialogueSegmentRomEnd = (const void*)0x01000000;
static const void* _basilDialogueIndexSegmentRomStart = (const void*)0x01000000;
static const void* _basilDialogueIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _basilDialogueSegmentRomStart = (const void*)0x01000000;
static const void* _basilDialogueSegmentRomEnd = (const void*)0x01000000;
static const void* _beachCutscenesDialogueIndexSegmentRomStart = (const void*)0x01000000;
static const void* _beachCutscenesDialogueIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _beachCutscenesDialogueSegmentRomStart = (const void*)0x01000000;
static const void* _beachCutscenesDialogueSegmentRomEnd = (const void*)0x01000000;
static const void* _cliffDialogueIndexSegmentRomStart = (const void*)0x01000000;
static const void* _cliffDialogueIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _cliffDialogueSegmentRomStart = (const void*)0x01000000;
static const void* _cliffDialogueSegmentRomEnd = (const void*)0x01000000;
static const void* _cutscenes1DialogueIndexSegmentRomStart = (const void*)0x01000000;
static const void* _cutscenes1DialogueIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _cutscenes1DialogueSegmentRomStart = (const void*)0x01000000;
static const void* _cutscenes1DialogueSegmentRomEnd = (const void*)0x01000000;
static const void* _diaryDialogueIndexSegmentRomStart = (const void*)0x01000000;
static const void* _diaryDialogueIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _diaryDialogueSegmentRomStart = (const void*)0x01000000;
static const void* _diaryDialogueSegmentRomEnd = (const void*)0x01000000;
static const void* _dogRaceDialogueIndexSegmentRomStart = (const void*)0x01000000;
static const void* _dogRaceDialogueIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _dogRaceDialogueSegmentRomStart = (const void*)0x01000000;
static const void* _dogRaceDialogueSegmentRomEnd = (const void*)0x01000000;
static const void* _dougDialogueIndexSegmentRomStart = (const void*)0x01000000;
static const void* _dougDialogueIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _dougDialogueSegmentRomStart = (const void*)0x01000000;
static const void* _dougDialogueSegmentRomEnd = (const void*)0x01000000;
static const void* _dukeDialogueIndexSegmentRomStart = (const void*)0x01000000;
static const void* _dukeDialogueIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _dukeDialogueSegmentRomStart = (const void*)0x01000000;
static const void* _dukeDialogueSegmentRomEnd = (const void*)0x01000000;
static const void* _eggFestivalDialogueIndexSegmentRomStart = (const void*)0x01000000;
static const void* _eggFestivalDialogueIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _eggFestivalDialogueSegmentRomStart = (const void*)0x01000000;
static const void* _eggFestivalDialogueSegmentRomEnd = (const void*)0x01000000;
static const void* _ellenDialogueIndexSegmentRomStart = (const void*)0x01000000;
static const void* _ellenDialogueIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _ellenDialogueSegmentRomStart = (const void*)0x01000000;
static const void* _ellenDialogueSegmentRomEnd = (const void*)0x01000000;
static const void* _elliDialogueIndexSegmentRomStart = (const void*)0x01000000;
static const void* _elliDialogueIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _elliDialogueSegmentRomStart = (const void*)0x01000000;
static const void* _elliDialogueSegmentRomEnd = (const void*)0x01000000;
static const void* _farmVisitsDialogueIndexSegmentRomStart = (const void*)0x01000000;
static const void* _farmVisitsDialogueIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _farmVisitsDialogueSegmentRomStart = (const void*)0x01000000;
static const void* _farmVisitsDialogueSegmentRomEnd = (const void*)0x01000000;
static const void* _festivalOverlaySelectionsDialogueIndexSegmentRomStart = (const void*)0x01000000;
static const void* _festivalOverlaySelectionsDialogueIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _festivalOverlaySelectionsDialogueSegmentRomStart = (const void*)0x01000000;
static const void* _festivalOverlaySelectionsDialogueSegmentRomEnd = (const void*)0x01000000;
static const void* _gotzDialogueIndexSegmentRomStart = (const void*)0x01000000;
static const void* _gotzDialogueIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _gotzDialogueSegmentRomStart = (const void*)0x01000000;
static const void* _gotzDialogueSegmentRomEnd = (const void*)0x01000000;
static const void* _grayDialogueIndexSegmentRomStart = (const void*)0x01000000;
static const void* _grayDialogueIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _grayDialogueSegmentRomStart = (const void*)0x01000000;
static const void* _grayDialogueSegmentRomEnd = (const void*)0x01000000;
static const void* _gregDialogueIndexSegmentRomStart = (const void*)0x01000000;
static const void* _gregDialogueIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _gregDialogueSegmentRomStart = (const void*)0x01000000;
static const void* _gregDialogueSegmentRomEnd = (const void*)0x01000000;
static const void* _harrisDialogueIndexSegmentRomStart = (const void*)0x01000000;
static const void* _harrisDialogueIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _harrisDialogueSegmentRomStart = (const void*)0x01000000;
static const void* _harrisDialogueSegmentRomEnd = (const void*)0x01000000;
static const void* _harvestSprites1DialogueIndexSegmentRomStart = (const void*)0x01000000;
static const void* _harvestSprites1DialogueIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _harvestSprites1DialogueSegmentRomStart = (const void*)0x01000000;
static const void* _harvestSprites1DialogueSegmentRomEnd = (const void*)0x01000000;
static const void* _harvestSprites2DialogueIndexSegmentRomStart = (const void*)0x01000000;
static const void* _harvestSprites2DialogueIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _harvestSprites2DialogueSegmentRomStart = (const void*)0x01000000;
static const void* _harvestSprites2DialogueSegmentRomEnd = (const void*)0x01000000;
static const void* _harvestSprites3DialogueIndexSegmentRomStart = (const void*)0x01000000;
static const void* _harvestSprites3DialogueIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _harvestSprites3DialogueSegmentRomStart = (const void*)0x01000000;
static const void* _harvestSprites3DialogueSegmentRomEnd = (const void*)0x01000000;
static const void* _horseRaceDialogueIndexSegmentRomStart = (const void*)0x01000000;
static const void* _horseRaceDialogueIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _horseRaceDialogueSegmentRomStart = (const void*)0x01000000;
static const void* _horseRaceDialogueSegmentRomEnd = (const void*)0x01000000;
static const void* _jeffDialogueIndexSegmentRomStart = (const void*)0x01000000;
static const void* _jeffDialogueIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _jeffDialogueSegmentRomStart = (const void*)0x01000000;
static const void* _jeffDialogueSegmentRomEnd = (const void*)0x01000000;
static const void* _kaiDialogueIndexSegmentRomStart = (const void*)0x01000000;
static const void* _kaiDialogueIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _kaiDialogueSegmentRomStart = (const void*)0x01000000;
static const void* _kaiDialogueSegmentRomEnd = (const void*)0x01000000;
static const void* _karenDialogueIndexSegmentRomStart = (const void*)0x01000000;
static const void* _karenDialogueIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _karenDialogueSegmentRomStart = (const void*)0x01000000;
static const void* _karenDialogueSegmentRomEnd = (const void*)0x01000000;
static const void* _kentDialogueIndexSegmentRomStart = (const void*)0x01000000;
static const void* _kentDialogueIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _kentDialogueSegmentRomStart = (const void*)0x01000000;
static const void* _kentDialogueSegmentRomEnd = (const void*)0x01000000;
static const void* _libraryDialogueIndexSegmentRomStart = (const void*)0x01000000;
static const void* _libraryDialogueIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _libraryDialogueSegmentRomStart = (const void*)0x01000000;
static const void* _libraryDialogueSegmentRomEnd = (const void*)0x01000000;
static const void* _lilliaDialogueIndexSegmentRomStart = (const void*)0x01000000;
static const void* _lilliaDialogueIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _lilliaDialogueSegmentRomStart = (const void*)0x01000000;
static const void* _lilliaDialogueSegmentRomEnd = (const void*)0x01000000;
static const void* _mariaDialogueIndexSegmentRomStart = (const void*)0x01000000;
static const void* _mariaDialogueIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _mariaDialogueSegmentRomStart = (const void*)0x01000000;
static const void* _mariaDialogueSegmentRomEnd = (const void*)0x01000000;
static const void* _marriedDialogueIndexSegmentRomStart = (const void*)0x01000000;
static const void* _marriedDialogueIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _marriedDialogueSegmentRomStart = (const void*)0x01000000;
static const void* _marriedDialogueSegmentRomEnd = (const void*)0x01000000;
static const void* _masterCarpenterDialogueIndexSegmentRomStart = (const void*)0x01000000;
static const void* _masterCarpenterDialogueIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _masterCarpenterDialogueSegmentRomStart = (const void*)0x01000000;
static const void* _masterCarpenterDialogueSegmentRomEnd = (const void*)0x01000000;
static const void* _mayDialogueIndexSegmentRomStart = (const void*)0x01000000;
static const void* _mayDialogueIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _mayDialogueSegmentRomStart = (const void*)0x01000000;
static const void* _mayDialogueSegmentRomEnd = (const void*)0x01000000;
static const void* _mayorDialogueIndexSegmentRomStart = (const void*)0x01000000;
static const void* _mayorDialogueIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _mayorDialogueSegmentRomStart = (const void*)0x01000000;
static const void* _mayorDialogueSegmentRomEnd = (const void*)0x01000000;
static const void* _mayorWifeDialogueIndexSegmentRomStart = (const void*)0x01000000;
static const void* _mayorWifeDialogueIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _mayorWifeDialogueSegmentRomStart = (const void*)0x01000000;
static const void* _mayorWifeDialogueSegmentRomEnd = (const void*)0x01000000;
static const void* _midwifeDialogueIndexSegmentRomStart = (const void*)0x01000000;
static const void* _midwifeDialogueIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _midwifeDialogueSegmentRomStart = (const void*)0x01000000;
static const void* _midwifeDialogueSegmentRomEnd = (const void*)0x01000000;
static const void* _mrsManaAndJohn1DialogueIndexSegmentRomStart = (const void*)0x01000000;
static const void* _mrsManaAndJohn1DialogueIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _mrsManaAndJohn1DialogueSegmentRomStart = (const void*)0x01000000;
static const void* _mrsManaAndJohn1DialogueSegmentRomEnd = (const void*)0x01000000;
static const void* _mrsManaAndJohn2DialogueIndexSegmentRomStart = (const void*)0x01000000;
static const void* _mrsManaAndJohn2DialogueIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _mrsManaAndJohn2DialogueSegmentRomStart = (const void*)0x01000000;
static const void* _mrsManaAndJohn2DialogueSegmentRomEnd = (const void*)0x01000000;
static const void* _namingScreenDialogueIndexSegmentRomStart = (const void*)0x01000000;
static const void* _namingScreenDialogueIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _namingScreenDialogueSegmentRomStart = (const void*)0x01000000;
static const void* _namingScreenDialogueSegmentRomEnd = (const void*)0x01000000;
static const void* _newYearFestivalDialogueIndexSegmentRomStart = (const void*)0x01000000;
static const void* _newYearFestivalDialogueIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _newYearFestivalDialogueSegmentRomStart = (const void*)0x01000000;
static const void* _newYearFestivalDialogueSegmentRomEnd = (const void*)0x01000000;
static const void* _npcBabyDialogueIndexSegmentRomStart = (const void*)0x01000000;
static const void* _npcBabyDialogueIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _npcBabyDialogueSegmentRomStart = (const void*)0x01000000;
static const void* _npcBabyDialogueSegmentRomEnd = (const void*)0x01000000;
static const void* _pastorDialogueIndexSegmentRomStart = (const void*)0x01000000;
static const void* _pastorDialogueIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _pastorDialogueSegmentRomStart = (const void*)0x01000000;
static const void* _pastorDialogueSegmentRomEnd = (const void*)0x01000000;
static const void* _popuriDialogueIndexSegmentRomStart = (const void*)0x01000000;
static const void* _popuriDialogueIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _popuriDialogueSegmentRomStart = (const void*)0x01000000;
static const void* _popuriDialogueSegmentRomEnd = (const void*)0x01000000;
static const void* _potionShopDealerDialogueIndexSegmentRomStart = (const void*)0x01000000;
static const void* _potionShopDealerDialogueIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _potionShopDealerDialogueSegmentRomStart = (const void*)0x01000000;
static const void* _potionShopDealerDialogueSegmentRomEnd = (const void*)0x01000000;
static const void* _rickDialogueIndexSegmentRomStart = (const void*)0x01000000;
static const void* _rickDialogueIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _rickDialogueSegmentRomStart = (const void*)0x01000000;
static const void* _rickDialogueSegmentRomEnd = (const void*)0x01000000;
static const void* _saibaraDialogueIndexSegmentRomStart = (const void*)0x01000000;
static const void* _saibaraDialogueIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _saibaraDialogueSegmentRomStart = (const void*)0x01000000;
static const void* _saibaraDialogueSegmentRomEnd = (const void*)0x01000000;
static const void* _sashaDialogueIndexSegmentRomStart = (const void*)0x01000000;
static const void* _sashaDialogueIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _sashaDialogueSegmentRomStart = (const void*)0x01000000;
static const void* _sashaDialogueSegmentRomEnd = (const void*)0x01000000;
static const void* _shipperDialogueIndexSegmentRomStart = (const void*)0x01000000;
static const void* _shipperDialogueIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _shipperDialogueSegmentRomStart = (const void*)0x01000000;
static const void* _shipperDialogueSegmentRomEnd = (const void*)0x01000000;
static const void* _shopDialogueIndexSegmentRomStart = (const void*)0x01000000;
static const void* _shopDialogueIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _shopDialogueSegmentRomStart = (const void*)0x01000000;
static const void* _shopDialogueSegmentRomEnd = (const void*)0x01000000;
static const void* _stuDialogueIndexSegmentRomStart = (const void*)0x01000000;
static const void* _stuDialogueIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _stuDialogueSegmentRomStart = (const void*)0x01000000;
static const void* _stuDialogueSegmentRomEnd = (const void*)0x01000000;
static const void* _sydneyDialogueIndexSegmentRomStart = (const void*)0x01000000;
static const void* _sydneyDialogueIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _sydneyDialogueSegmentRomStart = (const void*)0x01000000;
static const void* _sydneyDialogueSegmentRomEnd = (const void*)0x01000000;
static const void* _text1DialogueIndexSegmentRomStart = (const void*)0x01000000;
static const void* _text1DialogueIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _text1DialogueSegmentRomStart = (const void*)0x01000000;
static const void* _text1DialogueSegmentRomEnd = (const void*)0x01000000;
static const void* _text48DialogueIndexSegmentRomStart = (const void*)0x01000000;
static const void* _text48DialogueIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _text48DialogueSegmentRomStart = (const void*)0x01000000;
static const void* _text48DialogueSegmentRomEnd = (const void*)0x01000000;
static const void* _text49DialogueIndexSegmentRomStart = (const void*)0x01000000;
static const void* _text49DialogueIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _text49DialogueSegmentRomStart = (const void*)0x01000000;
static const void* _text49DialogueSegmentRomEnd = (const void*)0x01000000;
static const void* _text50DialogueIndexSegmentRomStart = (const void*)0x01000000;
static const void* _text50DialogueIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _text50DialogueSegmentRomStart = (const void*)0x01000000;
static const void* _text50DialogueSegmentRomEnd = (const void*)0x01000000;
static const void* _text51DialogueIndexSegmentRomStart = (const void*)0x01000000;
static const void* _text51DialogueIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _text51DialogueSegmentRomStart = (const void*)0x01000000;
static const void* _text51DialogueSegmentRomEnd = (const void*)0x01000000;
static const void* _text52DialogueIndexSegmentRomStart = (const void*)0x01000000;
static const void* _text52DialogueIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _text52DialogueSegmentRomStart = (const void*)0x01000000;
static const void* _text52DialogueSegmentRomEnd = (const void*)0x01000000;
static const void* _text54DialogueIndexSegmentRomStart = (const void*)0x01000000;
static const void* _text54DialogueIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _text54DialogueSegmentRomStart = (const void*)0x01000000;
static const void* _text54DialogueSegmentRomEnd = (const void*)0x01000000;
static const void* _text55DialogueIndexSegmentRomStart = (const void*)0x01000000;
static const void* _text55DialogueIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _text55DialogueSegmentRomStart = (const void*)0x01000000;
static const void* _text55DialogueSegmentRomEnd = (const void*)0x01000000;
static const void* _text56DialogueIndexSegmentRomStart = (const void*)0x01000000;
static const void* _text56DialogueIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _text56DialogueSegmentRomStart = (const void*)0x01000000;
static const void* _text56DialogueSegmentRomEnd = (const void*)0x01000000;
static const void* _text61DialogueIndexSegmentRomStart = (const void*)0x01000000;
static const void* _text61DialogueIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _text61DialogueSegmentRomStart = (const void*)0x01000000;
static const void* _text61DialogueSegmentRomEnd = (const void*)0x01000000;
static const void* _text63DialogueIndexSegmentRomStart = (const void*)0x01000000;
static const void* _text63DialogueIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _text63DialogueSegmentRomStart = (const void*)0x01000000;
static const void* _text63DialogueSegmentRomEnd = (const void*)0x01000000;
static const void* _text65DialogueIndexSegmentRomStart = (const void*)0x01000000;
static const void* _text65DialogueIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _text65DialogueSegmentRomStart = (const void*)0x01000000;
static const void* _text65DialogueSegmentRomEnd = (const void*)0x01000000;
static const void* _vegetableFestivalDialogueIndexSegmentRomStart = (const void*)0x01000000;
static const void* _vegetableFestivalDialogueIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _vegetableFestivalDialogueSegmentRomStart = (const void*)0x01000000;
static const void* _vegetableFestivalDialogueSegmentRomEnd = (const void*)0x01000000;
static const void* _vineyardCutscenesDialogueIndexSegmentRomStart = (const void*)0x01000000;
static const void* _vineyardCutscenesDialogueIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _vineyardCutscenesDialogueSegmentRomStart = (const void*)0x01000000;
static const void* _vineyardCutscenesDialogueSegmentRomEnd = (const void*)0x01000000;
// Additional missing text segments
static const void* _newYearFestivalTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _newYearFestivalTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _newYearFestivalTextSegmentRomStart = (const void*)0x01000000;
static const void* _newYearFestivalTextSegmentRomEnd = (const void*)0x01000000;
// Additional missing text segments (auto-generated)
static const void* _additionalNpcsTextIndexSegmentRomStartTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _additionalNpcsTextIndexSegmentRomStartTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _additionalNpcsTextIndexSegmentRomStartTextSegmentRomStart = (const void*)0x01000000;
static const void* _additionalNpcsTextIndexSegmentRomStartTextSegmentRomEnd = (const void*)0x01000000;
static const void* _animalInteractionsTextIndexSegmentRomStartTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _animalInteractionsTextIndexSegmentRomStartTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _animalInteractionsTextIndexSegmentRomStartTextSegmentRomStart = (const void*)0x01000000;
static const void* _animalInteractionsTextIndexSegmentRomStartTextSegmentRomEnd = (const void*)0x01000000;
static const void* _annTextIndexSegmentRomStartTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _annTextIndexSegmentRomStartTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _annTextIndexSegmentRomStartTextSegmentRomStart = (const void*)0x01000000;
static const void* _annTextIndexSegmentRomStartTextSegmentRomEnd = (const void*)0x01000000;
static const void* _assistantCarpentersTextIndexSegmentRomStartTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _assistantCarpentersTextIndexSegmentRomStartTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _assistantCarpentersTextIndexSegmentRomStartTextSegmentRomStart = (const void*)0x01000000;
static const void* _assistantCarpentersTextIndexSegmentRomStartTextSegmentRomEnd = (const void*)0x01000000;
static const void* _babyTextIndexSegmentRomStartTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _babyTextIndexSegmentRomStartTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _babyTextIndexSegmentRomStartTextSegmentRomStart = (const void*)0x01000000;
static const void* _babyTextIndexSegmentRomStartTextSegmentRomEnd = (const void*)0x01000000;
static const void* _barleyTextIndexSegmentRomStartTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _barleyTextIndexSegmentRomStartTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _barleyTextIndexSegmentRomStartTextSegmentRomStart = (const void*)0x01000000;
static const void* _barleyTextIndexSegmentRomStartTextSegmentRomEnd = (const void*)0x01000000;
static const void* _basilTextIndexSegmentRomStartTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _basilTextIndexSegmentRomStartTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _basilTextIndexSegmentRomStartTextSegmentRomStart = (const void*)0x01000000;
static const void* _basilTextIndexSegmentRomStartTextSegmentRomEnd = (const void*)0x01000000;
static const void* _beachCutscenesTextIndexSegmentRomStartTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _beachCutscenesTextIndexSegmentRomStartTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _beachCutscenesTextIndexSegmentRomStartTextSegmentRomStart = (const void*)0x01000000;
static const void* _beachCutscenesTextIndexSegmentRomStartTextSegmentRomEnd = (const void*)0x01000000;
static const void* _cliffTextIndexSegmentRomStartTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _cliffTextIndexSegmentRomStartTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _cliffTextIndexSegmentRomStartTextSegmentRomStart = (const void*)0x01000000;
static const void* _cliffTextIndexSegmentRomStartTextSegmentRomEnd = (const void*)0x01000000;
static const void* _diaryTextIndexSegmentRomStartTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _diaryTextIndexSegmentRomStartTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _diaryTextIndexSegmentRomStartTextSegmentRomStart = (const void*)0x01000000;
static const void* _diaryTextIndexSegmentRomStartTextSegmentRomEnd = (const void*)0x01000000;
static const void* _dogRaceTextIndexSegmentRomStartTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _dogRaceTextIndexSegmentRomStartTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _dogRaceTextIndexSegmentRomStartTextSegmentRomStart = (const void*)0x01000000;
static const void* _dogRaceTextIndexSegmentRomStartTextSegmentRomEnd = (const void*)0x01000000;
static const void* _dougTextIndexSegmentRomStartTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _dougTextIndexSegmentRomStartTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _dougTextIndexSegmentRomStartTextSegmentRomStart = (const void*)0x01000000;
static const void* _dougTextIndexSegmentRomStartTextSegmentRomEnd = (const void*)0x01000000;
static const void* _dukeTextIndexSegmentRomStartTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _dukeTextIndexSegmentRomStartTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _dukeTextIndexSegmentRomStartTextSegmentRomStart = (const void*)0x01000000;
static const void* _dukeTextIndexSegmentRomStartTextSegmentRomEnd = (const void*)0x01000000;
static const void* _eggFestivalTextIndexSegmentRomStartTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _eggFestivalTextIndexSegmentRomStartTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _eggFestivalTextIndexSegmentRomStartTextSegmentRomStart = (const void*)0x01000000;
static const void* _eggFestivalTextIndexSegmentRomStartTextSegmentRomEnd = (const void*)0x01000000;
static const void* _ellenTextIndexSegmentRomStartTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _ellenTextIndexSegmentRomStartTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _ellenTextIndexSegmentRomStartTextSegmentRomStart = (const void*)0x01000000;
static const void* _ellenTextIndexSegmentRomStartTextSegmentRomEnd = (const void*)0x01000000;
static const void* _elliTextIndexSegmentRomStartTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _elliTextIndexSegmentRomStartTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _elliTextIndexSegmentRomStartTextSegmentRomStart = (const void*)0x01000000;
static const void* _elliTextIndexSegmentRomStartTextSegmentRomEnd = (const void*)0x01000000;
static const void* _farmVisitsTextIndexSegmentRomStartTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _farmVisitsTextIndexSegmentRomStartTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _farmVisitsTextIndexSegmentRomStartTextSegmentRomStart = (const void*)0x01000000;
static const void* _farmVisitsTextIndexSegmentRomStartTextSegmentRomEnd = (const void*)0x01000000;
static const void* _festivalOverlaySelectionsTextIndexSegmentRomStartTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _festivalOverlaySelectionsTextIndexSegmentRomStartTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _festivalOverlaySelectionsTextIndexSegmentRomStartTextSegmentRomStart = (const void*)0x01000000;
static const void* _festivalOverlaySelectionsTextIndexSegmentRomStartTextSegmentRomEnd = (const void*)0x01000000;
static const void* _funeralIntroTextIndexSegmentRomStartTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _funeralIntroTextIndexSegmentRomStartTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _funeralIntroTextIndexSegmentRomStartTextSegmentRomStart = (const void*)0x01000000;
static const void* _funeralIntroTextIndexSegmentRomStartTextSegmentRomEnd = (const void*)0x01000000;
static const void* _gotzTextIndexSegmentRomStartTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _gotzTextIndexSegmentRomStartTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _gotzTextIndexSegmentRomStartTextSegmentRomStart = (const void*)0x01000000;
static const void* _gotzTextIndexSegmentRomStartTextSegmentRomEnd = (const void*)0x01000000;
static const void* _grayTextIndexSegmentRomStartTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _grayTextIndexSegmentRomStartTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _grayTextIndexSegmentRomStartTextSegmentRomStart = (const void*)0x01000000;
static const void* _grayTextIndexSegmentRomStartTextSegmentRomEnd = (const void*)0x01000000;
static const void* _gregTextIndexSegmentRomStartTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _gregTextIndexSegmentRomStartTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _gregTextIndexSegmentRomStartTextSegmentRomStart = (const void*)0x01000000;
static const void* _gregTextIndexSegmentRomStartTextSegmentRomEnd = (const void*)0x01000000;
static const void* _harrisTextIndexSegmentRomStartTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _harrisTextIndexSegmentRomStartTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _harrisTextIndexSegmentRomStartTextSegmentRomStart = (const void*)0x01000000;
static const void* _harrisTextIndexSegmentRomStartTextSegmentRomEnd = (const void*)0x01000000;
static const void* _harvestSpritesTextIndexSegmentRomStartTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _harvestSpritesTextIndexSegmentRomStartTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _harvestSpritesTextIndexSegmentRomStartTextSegmentRomStart = (const void*)0x01000000;
static const void* _harvestSpritesTextIndexSegmentRomStartTextSegmentRomEnd = (const void*)0x01000000;
static const void* _horseRaceTextIndexSegmentRomStartTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _horseRaceTextIndexSegmentRomStartTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _horseRaceTextIndexSegmentRomStartTextSegmentRomStart = (const void*)0x01000000;
static const void* _horseRaceTextIndexSegmentRomStartTextSegmentRomEnd = (const void*)0x01000000;
static const void* _howToPlayTextIndexSegmentRomStartTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _howToPlayTextIndexSegmentRomStartTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _howToPlayTextIndexSegmentRomStartTextSegmentRomStart = (const void*)0x01000000;
static const void* _howToPlayTextIndexSegmentRomStartTextSegmentRomEnd = (const void*)0x01000000;
static const void* _jeffTextIndexSegmentRomStartTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _jeffTextIndexSegmentRomStartTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _jeffTextIndexSegmentRomStartTextSegmentRomStart = (const void*)0x01000000;
static const void* _jeffTextIndexSegmentRomStartTextSegmentRomEnd = (const void*)0x01000000;
static const void* _kaiTextIndexSegmentRomStartTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _kaiTextIndexSegmentRomStartTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _kaiTextIndexSegmentRomStartTextSegmentRomStart = (const void*)0x01000000;
static const void* _kaiTextIndexSegmentRomStartTextSegmentRomEnd = (const void*)0x01000000;
static const void* _karenTextIndexSegmentRomStartTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _karenTextIndexSegmentRomStartTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _karenTextIndexSegmentRomStartTextSegmentRomStart = (const void*)0x01000000;
static const void* _karenTextIndexSegmentRomStartTextSegmentRomEnd = (const void*)0x01000000;
static const void* _kentTextIndexSegmentRomStartTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _kentTextIndexSegmentRomStartTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _kentTextIndexSegmentRomStartTextSegmentRomStart = (const void*)0x01000000;
static const void* _kentTextIndexSegmentRomStartTextSegmentRomEnd = (const void*)0x01000000;
static const void* _lettersTextIndexSegmentRomStartTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _lettersTextIndexSegmentRomStartTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _lettersTextIndexSegmentRomStartTextSegmentRomStart = (const void*)0x01000000;
static const void* _lettersTextIndexSegmentRomStartTextSegmentRomEnd = (const void*)0x01000000;
static const void* _libraryTextIndexSegmentRomStartTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _libraryTextIndexSegmentRomStartTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _libraryTextIndexSegmentRomStartTextSegmentRomStart = (const void*)0x01000000;
static const void* _libraryTextIndexSegmentRomStartTextSegmentRomEnd = (const void*)0x01000000;
static const void* _lilliaTextIndexSegmentRomStartTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _lilliaTextIndexSegmentRomStartTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _lilliaTextIndexSegmentRomStartTextSegmentRomStart = (const void*)0x01000000;
static const void* _lilliaTextIndexSegmentRomStartTextSegmentRomEnd = (const void*)0x01000000;
static const void* _mariaTextIndexSegmentRomStartTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _mariaTextIndexSegmentRomStartTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _mariaTextIndexSegmentRomStartTextSegmentRomStart = (const void*)0x01000000;
static const void* _mariaTextIndexSegmentRomStartTextSegmentRomEnd = (const void*)0x01000000;
static const void* _marriedDialoguesTextIndexSegmentRomStartTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _marriedDialoguesTextIndexSegmentRomStartTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _marriedDialoguesTextIndexSegmentRomStartTextSegmentRomStart = (const void*)0x01000000;
static const void* _marriedDialoguesTextIndexSegmentRomStartTextSegmentRomEnd = (const void*)0x01000000;
static const void* _masterCarpenterTextIndexSegmentRomStartTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _masterCarpenterTextIndexSegmentRomStartTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _masterCarpenterTextIndexSegmentRomStartTextSegmentRomStart = (const void*)0x01000000;
static const void* _masterCarpenterTextIndexSegmentRomStartTextSegmentRomEnd = (const void*)0x01000000;
static const void* _mayorTextIndexSegmentRomStartTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _mayorTextIndexSegmentRomStartTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _mayorTextIndexSegmentRomStartTextSegmentRomStart = (const void*)0x01000000;
static const void* _mayorTextIndexSegmentRomStartTextSegmentRomEnd = (const void*)0x01000000;
static const void* _mayorWifeTextIndexSegmentRomStartTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _mayorWifeTextIndexSegmentRomStartTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _mayorWifeTextIndexSegmentRomStartTextSegmentRomStart = (const void*)0x01000000;
static const void* _mayorWifeTextIndexSegmentRomStartTextSegmentRomEnd = (const void*)0x01000000;
static const void* _mayTextIndexSegmentRomStartTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _mayTextIndexSegmentRomStartTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _mayTextIndexSegmentRomStartTextSegmentRomStart = (const void*)0x01000000;
static const void* _mayTextIndexSegmentRomStartTextSegmentRomEnd = (const void*)0x01000000;
static const void* _midwifeTextIndexSegmentRomStartTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _midwifeTextIndexSegmentRomStartTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _midwifeTextIndexSegmentRomStartTextSegmentRomStart = (const void*)0x01000000;
static const void* _midwifeTextIndexSegmentRomStartTextSegmentRomEnd = (const void*)0x01000000;
static const void* _mrsManaAndJohnTextIndexSegmentRomStartTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _mrsManaAndJohnTextIndexSegmentRomStartTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _mrsManaAndJohnTextIndexSegmentRomStartTextSegmentRomStart = (const void*)0x01000000;
static const void* _mrsManaAndJohnTextIndexSegmentRomStartTextSegmentRomEnd = (const void*)0x01000000;
static const void* _namingScreenTextIndexSegmentRomStartTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _namingScreenTextIndexSegmentRomStartTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _namingScreenTextIndexSegmentRomStartTextSegmentRomStart = (const void*)0x01000000;
static const void* _namingScreenTextIndexSegmentRomStartTextSegmentRomEnd = (const void*)0x01000000;
static const void* _newYearFestivalTextIndexSegmentRomStartTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _newYearFestivalTextIndexSegmentRomStartTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _newYearFestivalTextIndexSegmentRomStartTextSegmentRomStart = (const void*)0x01000000;
static const void* _newYearFestivalTextIndexSegmentRomStartTextSegmentRomEnd = (const void*)0x01000000;
static const void* _pastorTextIndexSegmentRomStartTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _pastorTextIndexSegmentRomStartTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _pastorTextIndexSegmentRomStartTextSegmentRomStart = (const void*)0x01000000;
static const void* _pastorTextIndexSegmentRomStartTextSegmentRomEnd = (const void*)0x01000000;
static const void* _popuriTextIndexSegmentRomStartTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _popuriTextIndexSegmentRomStartTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _popuriTextIndexSegmentRomStartTextSegmentRomStart = (const void*)0x01000000;
static const void* _popuriTextIndexSegmentRomStartTextSegmentRomEnd = (const void*)0x01000000;
static const void* _potionShopDealerTextIndexSegmentRomStartTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _potionShopDealerTextIndexSegmentRomStartTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _potionShopDealerTextIndexSegmentRomStartTextSegmentRomStart = (const void*)0x01000000;
static const void* _potionShopDealerTextIndexSegmentRomStartTextSegmentRomEnd = (const void*)0x01000000;
static const void* _recipesJapaneseTextIndexSegmentRomStartTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _recipesJapaneseTextIndexSegmentRomStartTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _recipesJapaneseTextIndexSegmentRomStartTextSegmentRomStart = (const void*)0x01000000;
static const void* _recipesJapaneseTextIndexSegmentRomStartTextSegmentRomEnd = (const void*)0x01000000;
static const void* _rickTextIndexSegmentRomStartTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _rickTextIndexSegmentRomStartTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _rickTextIndexSegmentRomStartTextSegmentRomStart = (const void*)0x01000000;
static const void* _rickTextIndexSegmentRomStartTextSegmentRomEnd = (const void*)0x01000000;
static const void* _saibaraTextIndexSegmentRomStartTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _saibaraTextIndexSegmentRomStartTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _saibaraTextIndexSegmentRomStartTextSegmentRomStart = (const void*)0x01000000;
static const void* _saibaraTextIndexSegmentRomStartTextSegmentRomEnd = (const void*)0x01000000;
static const void* _sashaTextIndexSegmentRomStartTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _sashaTextIndexSegmentRomStartTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _sashaTextIndexSegmentRomStartTextSegmentRomStart = (const void*)0x01000000;
static const void* _sashaTextIndexSegmentRomStartTextSegmentRomEnd = (const void*)0x01000000;
static const void* _shipperTextIndexSegmentRomStartTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _shipperTextIndexSegmentRomStartTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _shipperTextIndexSegmentRomStartTextSegmentRomStart = (const void*)0x01000000;
static const void* _shipperTextIndexSegmentRomStartTextSegmentRomEnd = (const void*)0x01000000;
static const void* _shopTextIndexSegmentRomStartTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _shopTextIndexSegmentRomStartTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _shopTextIndexSegmentRomStartTextSegmentRomStart = (const void*)0x01000000;
static const void* _shopTextIndexSegmentRomStartTextSegmentRomEnd = (const void*)0x01000000;
static const void* _spiritFestivalTextIndexSegmentRomStartTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _spiritFestivalTextIndexSegmentRomStartTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _spiritFestivalTextIndexSegmentRomStartTextSegmentRomStart = (const void*)0x01000000;
static const void* _spiritFestivalTextIndexSegmentRomStartTextSegmentRomEnd = (const void*)0x01000000;
static const void* _stuTextIndexSegmentRomStartTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _stuTextIndexSegmentRomStartTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _stuTextIndexSegmentRomStartTextSegmentRomStart = (const void*)0x01000000;
static const void* _stuTextIndexSegmentRomStartTextSegmentRomEnd = (const void*)0x01000000;
static const void* _sydneyTextIndexSegmentRomStartTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _sydneyTextIndexSegmentRomStartTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _sydneyTextIndexSegmentRomStartTextSegmentRomStart = (const void*)0x01000000;
static const void* _sydneyTextIndexSegmentRomStartTextSegmentRomEnd = (const void*)0x01000000;
static const void* _tvTextIndexSegmentRomStartTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _tvTextIndexSegmentRomStartTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _tvTextIndexSegmentRomStartTextSegmentRomStart = (const void*)0x01000000;
static const void* _tvTextIndexSegmentRomStartTextSegmentRomEnd = (const void*)0x01000000;
static const void* _vegetableFestivalTextIndexSegmentRomStartTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _vegetableFestivalTextIndexSegmentRomStartTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _vegetableFestivalTextIndexSegmentRomStartTextSegmentRomStart = (const void*)0x01000000;
static const void* _vegetableFestivalTextIndexSegmentRomStartTextSegmentRomEnd = (const void*)0x01000000;
static const void* _vineyardCutscenesTextIndexSegmentRomStartTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _vineyardCutscenesTextIndexSegmentRomStartTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _vineyardCutscenesTextIndexSegmentRomStartTextSegmentRomStart = (const void*)0x01000000;
static const void* _vineyardCutscenesTextIndexSegmentRomStartTextSegmentRomEnd = (const void*)0x01000000;
// Plural variants of text segments
static const void* _assistantCarpentersTextIndexSegmentRomStart = (const void*)0x01000000;
static const void* _assistantCarpentersTextIndexSegmentRomEnd = (const void*)0x01000000;
static const void* _assistantCarpentersTextSegmentRomStart = (const void*)0x01000000;
static const void* _assistantCarpentersTextSegmentRomEnd = (const void*)0x01000000;
