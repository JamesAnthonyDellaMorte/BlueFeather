// ROM segment symbols - defined using inline assembly with actual ROM addresses.
// Moonwright keeps these ROM offsets so the original HM64 code can reference the
// same startup ranges while the port resolves the bytes from archive blobs.

__asm__(
    // Title screen sprites - texture
    ".globl __titleSpritesTextureSegmentRomStart\n"
    ".set __titleSpritesTextureSegmentRomStart, 0x00DBA100\n"
    ".globl __titleSpritesTextureSegmentRomEnd\n"
    ".set __titleSpritesTextureSegmentRomEnd, 0x00DD38F0\n"
    // Title screen sprites - assets index
    ".globl __titleSpritesAssetsIndexSegmentRomStart\n"
    ".set __titleSpritesAssetsIndexSegmentRomStart, 0x00DD38F0\n"
    ".globl __titleSpritesAssetsIndexSegmentRomEnd\n"
    ".set __titleSpritesAssetsIndexSegmentRomEnd, 0x00DD3910\n"
    // Dialogue icons - texture
    ".globl __dialogueButtonIconsTextureSegmentRomStart\n"
    ".set __dialogueButtonIconsTextureSegmentRomStart, 0x00D47F00\n"
    ".globl __dialogueButtonIconsTextureSegmentRomEnd\n"
    ".set __dialogueButtonIconsTextureSegmentRomEnd, 0x00D49B80\n"
    // Dialogue icons - assets index
    ".globl __dialogueButtonIconsAssetsIndexSegmentRomStart\n"
    ".set __dialogueButtonIconsAssetsIndexSegmentRomStart, 0x00D49B80\n"
    ".globl __dialogueButtonIconsAssetsIndexSegmentRomEnd\n"
    ".set __dialogueButtonIconsAssetsIndexSegmentRomEnd, 0x00D49BA0\n"
    // Dog sprites - texture
    ".globl __dogTextureSegmentRomStart\n"
    ".set __dogTextureSegmentRomStart, 0x0060EC20\n"
    ".globl __dogTextureSegmentRomEnd\n"
    ".set __dogTextureSegmentRomEnd, 0x00630EC0\n"
    // Dog sprites - assets index
    ".globl __dogAssetsIndexSegmentRomStart\n"
    ".set __dogAssetsIndexSegmentRomStart, 0x00630EC0\n"
    ".globl __dogAssetsIndexSegmentRomEnd\n"
    ".set __dogAssetsIndexSegmentRomEnd, 0x00630EE0\n"
    // Dog sprites - spritesheet index
    ".globl __dogSpritesheetIndexSegmentRomStart\n"
    ".set __dogSpritesheetIndexSegmentRomStart, 0x00630EE0\n"
    ".globl __dogSpritesheetIndexSegmentRomEnd\n"
    ".set __dogSpritesheetIndexSegmentRomEnd, 0x00631400\n"
    // Cutscene segments - startup ranges exported into Moonwright.o2r
    ".globl __farmBusinessSegmentRomStart\n"
    ".set __farmBusinessSegmentRomStart, 0x100FF5C0\n"
    ".globl __farmBusinessSegmentRomEnd\n"
    ".set __farmBusinessSegmentRomEnd, 0x10100180\n"
    ".globl __funeralIntroSegmentRomStart\n"
    ".set __funeralIntroSegmentRomStart, 0x10149CC0\n"
    ".globl __funeralIntroSegmentRomEnd\n"
    ".set __funeralIntroSegmentRomEnd, 0x1014B8F0\n"
    ".globl __demosSegmentRomStart\n"
    ".set __demosSegmentRomStart, 0x1014B8F0\n"
    ".globl __demosSegmentRomEnd\n"
    ".set __demosSegmentRomEnd, 0x10150120\n"
    // More cutscene segments (need to add proper addresses)
    ".globl __farmVisitsSegmentRomStart\n"
    ".set __farmVisitsSegmentRomStart, 0x10030000\n"
    ".globl __farmVisitsSegmentRomEnd\n"
    ".set __farmVisitsSegmentRomEnd, 0x10040000\n"
    ".globl __familyCutscenesSegmentRomStart\n"
    ".set __familyCutscenesSegmentRomStart, 0x10050000\n"
    ".globl __familyCutscenesSegmentRomEnd\n"
    ".set __familyCutscenesSegmentRomEnd, 0x10060000\n"
    ".globl __roadCutscenesSegmentRomStart\n"
    ".set __roadCutscenesSegmentRomStart, 0x10070000\n"
    ".globl __roadCutscenesSegmentRomEnd\n"
    ".set __roadCutscenesSegmentRomEnd, 0x10080000\n"
);
