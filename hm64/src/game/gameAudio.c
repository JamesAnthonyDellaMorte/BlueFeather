#include "common.h"

#include "system/audio.h"

#include "game/gameAudio.h"

#include "assetIndices/sequences.h"
#include "ld_symbols.h"

#ifdef HM64_PC_PORT
#define MW_ROM_U32(symbol) MW_ROM_VALUE_##symbol
#else
#define MW_ROM_U32(symbol) ((u32)(uintptr_t)&(symbol))
#endif

typedef struct {
    u32 pbk_addr;
    u32 pbk_end;
    u32 wbk_addr;
} WaveTableRomInfo;

// data
static const WaveTableRomInfo waveTableAddresses[1] = {
    { MW_ROM_U32(_waveTablePointerSegmentRomStart), MW_ROM_U32(_waveTablePointerSegmentRomEnd), MW_ROM_U32(_waveTableDataSegmentRomStart) },
};

Addresses sequenceRomAddresses[] = {
    { MW_ROM_U32(_openingSegmentRomStart), MW_ROM_U32(_openingSegmentRomEnd) },
    { MW_ROM_U32(_titleSegmentRomStart), MW_ROM_U32(_titleSegmentRomEnd) },
    { MW_ROM_U32(_sportsFestival1SegmentRomStart), MW_ROM_U32(_sportsFestival1SegmentRomEnd) },
    { MW_ROM_U32(_goodbyeSegmentRomStart), MW_ROM_U32(_goodbyeSegmentRomEnd) },
    { MW_ROM_U32(_springSegmentRomStart), MW_ROM_U32(_springSegmentRomEnd) },
    { MW_ROM_U32(_summerSegmentRomStart), MW_ROM_U32(_summerSegmentRomEnd) },
    { MW_ROM_U32(_autumnSegmentRomStart), MW_ROM_U32(_autumnSegmentRomEnd) },
    { MW_ROM_U32(_winterSegmentRomStart), MW_ROM_U32(_winterSegmentRomEnd) },
    { MW_ROM_U32(_namingScreenSegmentRomStart), MW_ROM_U32(_namingScreenSegmentRomEnd) },
    { MW_ROM_U32(_festivalThemeSegmentRomStart), MW_ROM_U32(_festivalThemeSegmentRomEnd) },
    { MW_ROM_U32(_sportsFestival2SegmentRomStart), MW_ROM_U32(_sportsFestival2SegmentRomEnd) },
    { MW_ROM_U32(_spiritFestivalThemeSegmentRomStart), MW_ROM_U32(_spiritFestivalThemeSegmentRomEnd) },
    { MW_ROM_U32(_dogRaceThemeSegmentRomStart), MW_ROM_U32(_dogRaceThemeSegmentRomEnd) },
    { MW_ROM_U32(_racingFestivalSegmentRomStart), MW_ROM_U32(_racingFestivalSegmentRomEnd) },
    { MW_ROM_U32(_festivalDanceSegmentRomStart), MW_ROM_U32(_festivalDanceSegmentRomEnd) },
    { MW_ROM_U32(_mountainSegmentRomStart), MW_ROM_U32(_mountainSegmentRomEnd) },
    { MW_ROM_U32(_villageSegmentRomStart), MW_ROM_U32(_villageSegmentRomEnd) },
    { MW_ROM_U32(_pondSegmentRomStart), MW_ROM_U32(_pondSegmentRomEnd) },
    { MW_ROM_U32(_churchSegmentRomStart), MW_ROM_U32(_churchSegmentRomEnd) },
    { MW_ROM_U32(_tavernSegmentRomStart), MW_ROM_U32(_tavernSegmentRomEnd) },
    { MW_ROM_U32(_weddingSegmentRomStart), MW_ROM_U32(_weddingSegmentRomEnd) },
    { MW_ROM_U32(_newYearSunriseSegmentRomStart), MW_ROM_U32(_newYearSunriseSegmentRomEnd) },
    { MW_ROM_U32(_creditsSegmentRomStart), MW_ROM_U32(_creditsSegmentRomEnd) },
    { MW_ROM_U32(_brokenMusicBoxSegmentRomStart), MW_ROM_U32(_brokenMusicBoxSegmentRomEnd) },
    { MW_ROM_U32(_musicBoxSegmentRomStart), MW_ROM_U32(_musicBoxSegmentRomEnd) },
    { MW_ROM_U32(_flutePerformanceSegmentRomStart), MW_ROM_U32(_flutePerformanceSegmentRomEnd) },
    { MW_ROM_U32(_organPerformanceSegmentRomStart), MW_ROM_U32(_organPerformanceSegmentRomEnd) },
    { MW_ROM_U32(_ocarinaPerformanceSegmentRomStart), MW_ROM_U32(_ocarinaPerformanceSegmentRomEnd) },
    { MW_ROM_U32(_sleighBellsSegmentRomStart), MW_ROM_U32(_sleighBellsSegmentRomEnd) },
    { MW_ROM_U32(_badEndingSegmentRomStart), MW_ROM_U32(_badEndingSegmentRomEnd) },
    { MW_ROM_U32(_vocalPerformanceSegmentRomStart), MW_ROM_U32(_vocalPerformanceSegmentRomEnd) },
    { MW_ROM_U32(_ensemblePerformanceSegmentRomStart), MW_ROM_U32(_ensemblePerformanceSegmentRomEnd) },
    { MW_ROM_U32(_drumPerformanceSegmentRomStart), MW_ROM_U32(_drumPerformanceSegmentRomEnd) },
    { MW_ROM_U32(_typhoonAmbience1SegmentRomStart), MW_ROM_U32(_typhoonAmbience1SegmentRomEnd) },
    { MW_ROM_U32(_typhoonAmbience2SegmentRomStart), MW_ROM_U32(_typhoonAmbience2SegmentRomEnd) },
    { MW_ROM_U32(_nightAmbienceSpringSegmentRomStart), MW_ROM_U32(_nightAmbienceSpringSegmentRomEnd) },
    { MW_ROM_U32(_nightAmbienceSummerSegmentRomStart), MW_ROM_U32(_nightAmbienceSummerSegmentRomEnd) },
    { MW_ROM_U32(_nightAmbienceAutumnSegmentRomStart), MW_ROM_U32(_nightAmbienceAutumnSegmentRomEnd) },
    { MW_ROM_U32(_starryNightFestivalSegmentRomStart), MW_ROM_U32(_starryNightFestivalSegmentRomEnd) },
    { MW_ROM_U32(_beachAmbience1SegmentRomStart), MW_ROM_U32(_beachAmbience1SegmentRomEnd) },
    { MW_ROM_U32(_beachAmbience2SegmentRomStart), MW_ROM_U32(_beachAmbience2SegmentRomEnd) },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
};

Addresses sfxRomAddresses[] = {
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { MW_ROM_U32(_horseGallop2SegmentRomStart), MW_ROM_U32(_horseGallop2SegmentRomEnd) },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { MW_ROM_U32(_sickleSegmentRomStart), MW_ROM_U32(_sickleSegmentRomEnd) },
    { 0, 0 },
    { 0, 0 },
    { MW_ROM_U32(_hoeSegmentRomStart), MW_ROM_U32(_hoeSegmentRomEnd) },
    { 0, 0 },
    { 0, 0 },
    { MW_ROM_U32(_seq59SegmentRomStart), MW_ROM_U32(_seq59SegmentRomEnd) },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { MW_ROM_U32(_horseGallop3SegmentRomStart), MW_ROM_U32(_horseGallop3SegmentRomEnd) },
    { MW_ROM_U32(_water1SegmentRomStart), MW_ROM_U32(_water1SegmentRomEnd) },
    { MW_ROM_U32(_water2SegmentRomStart), MW_ROM_U32(_water2SegmentRomEnd) },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { MW_ROM_U32(_seedsSegmentRomStart), MW_ROM_U32(_seedsSegmentRomEnd) },
    { 0, 0 },
    { 0, 0 },
    { MW_ROM_U32(_cowBellSegmentRomStart), MW_ROM_U32(_cowBellSegmentRomEnd) },
    { 0, 0 },
    { 0, 0 },
    { MW_ROM_U32(_shimmerSegmentRomStart), MW_ROM_U32(_shimmerSegmentRomEnd) },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { MW_ROM_U32(_seq60SegmentRomStart), MW_ROM_U32(_seq60SegmentRomEnd) },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { MW_ROM_U32(_bird1SegmentRomStart), MW_ROM_U32(_bird1SegmentRomEnd) },
    { MW_ROM_U32(_bird2SegmentRomStart), MW_ROM_U32(_bird2SegmentRomEnd) },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { MW_ROM_U32(_cicadaSegmentRomStart), MW_ROM_U32(_cicadaSegmentRomEnd) },
    { 0, 0 },
    { 0, 0 },
    { MW_ROM_U32(_seq47SegmentRomStart), MW_ROM_U32(_seq47SegmentRomEnd) },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { MW_ROM_U32(_fanfareSegmentRomStart), MW_ROM_U32(_fanfareSegmentRomEnd) },
    { MW_ROM_U32(_fireworksSfxSegmentRomStart), MW_ROM_U32(_fireworksSfxSegmentRomEnd) },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { MW_ROM_U32(_horseGallopFastSegmentRomStart), MW_ROM_U32(_horseGallopFastSegmentRomEnd) },
    { 0, 0 },
    { MW_ROM_U32(_seq64SegmentRomStart), MW_ROM_U32(_seq64SegmentRomEnd) },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
};

// for sfx; sfx can either be raw audio data from `/data/audio/sfx.c` or sequences that use the game's wavetable
u8 audioTypeTable[] = {
    SFX_TYPE, SFX_TYPE, SFX_TYPE, SFX_TYPE, SFX_TYPE, SFX_TYPE, 
    SFX_TYPE, SFX_TYPE, SFX_TYPE, SEQUENCE_TYPE,SFX_TYPE, SFX_TYPE, 
    SFX_TYPE, SEQUENCE_TYPE,SFX_TYPE, SFX_TYPE, SEQUENCE_TYPE,SFX_TYPE, 
    SFX_TYPE, SEQUENCE_TYPE,SFX_TYPE, SFX_TYPE, SFX_TYPE, SEQUENCE_TYPE,
    SEQUENCE_TYPE, SEQUENCE_TYPE,SFX_TYPE, SFX_TYPE, SFX_TYPE, SEQUENCE_TYPE,
    SFX_TYPE, SFX_TYPE, SEQUENCE_TYPE,SFX_TYPE, SFX_TYPE, SEQUENCE_TYPE,
    SFX_TYPE, SFX_TYPE, SFX_TYPE, SFX_TYPE, SFX_TYPE, SFX_TYPE, 
    SFX_TYPE, SFX_TYPE, SFX_TYPE, SFX_TYPE, SEQUENCE_TYPE, SFX_TYPE, 
    SFX_TYPE, SFX_TYPE, SFX_TYPE, SFX_TYPE, SFX_TYPE, SFX_TYPE, 
    SFX_TYPE, SFX_TYPE, SFX_TYPE, SFX_TYPE, SFX_TYPE, SFX_TYPE, 
    SFX_TYPE, SFX_TYPE, SFX_TYPE, SFX_TYPE, SFX_TYPE, SFX_TYPE, 
    SFX_TYPE, SFX_TYPE, SFX_TYPE, SFX_TYPE, SFX_TYPE, SFX_TYPE, 
    SEQUENCE_TYPE, SEQUENCE_TYPE, SFX_TYPE, SFX_TYPE, SFX_TYPE, SFX_TYPE, 
    SEQUENCE_TYPE, SFX_TYPE, SFX_TYPE, SEQUENCE_TYPE,SFX_TYPE, SFX_TYPE, 
    SFX_TYPE, SFX_TYPE, SFX_TYPE, SFX_TYPE, SFX_TYPE, SFX_TYPE, 
    0x03, SEQUENCE_TYPE,SFX_TYPE, SFX_TYPE, SFX_TYPE, SFX_TYPE, 
    SEQUENCE_TYPE, SFX_TYPE, SEQUENCE_TYPE, 0x00, 0x00, 0x00, 0x00, 
    
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    // this is probably separate unused array 
    0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 
    0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 
    0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 
    0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 
    0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 
    0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 
    0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 
    0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 
    0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 
    0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 
    0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

s32 volumesTable[] = {
    128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
    128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
    128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
    128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
    128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
    128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
    128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
    128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
    128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
    128, 128, 128, 128, 128, 128, 128, 128, 128, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0,
};


//INCLUDE_ASM("asm/nonmatchings/game/gameAudio", initializeWaveTable);

void initializeWaveTable(u16 waveTableIndex) {
    setAudioSequenceBank(waveTableAddresses[waveTableIndex].pbk_addr, waveTableAddresses[waveTableIndex].pbk_end, waveTableAddresses[waveTableIndex].wbk_addr);
}

//INCLUDE_ASM("asm/nonmatchings/game/gameAudio", setCurrentAudioSequence);

void setCurrentAudioSequence(u16 sequenceIndex) {

    if (sequenceIndex < TOTAL_SEQUENCES) {
        setAudioSequence(0, (u8*)(uintptr_t)sequenceRomAddresses[sequenceIndex].romAddrStart,
                         (u8*)(uintptr_t)sequenceRomAddresses[sequenceIndex].romAddrEnd);
    }
    
    setAudioSequenceVolumes(0, 0, 0);

}

//INCLUDE_ASM("asm/nonmatchings/game/gameAudio", stopAudioSequenceWithDefaultFadeOut);

void stopAudioSequenceWithDefaultFadeOut(u16 sequenceIndex) {
    if (sequenceIndex < TOTAL_SEQUENCES) {
        stopAudioSequenceWithFadeOut(0, 32);
    }
}

//INCLUDE_ASM("asm/nonmatchings/game/gameAudio", stopCurrentAudioSequence);

void stopCurrentAudioSequence(u16 sequenceIndex) {
    if (sequenceIndex  < TOTAL_SEQUENCES) {
        stopAudioSequence(0);
    }
}

//INCLUDE_ASM("asm/nonmatchings/game/gameAudio", checkDefaultSequenceChannelOpen);

// check if first sequence slot is open/not set
bool checkDefaultSequenceChannelOpen(u16 sequenceIndex) {
    
    u8 result = FALSE;
    
    if (sequenceIndex < TOTAL_SEQUENCES) {
        result = gAudioSequences[0].flags == 0;
    }

    if (sequenceIndex == 0xFF) {
        result = TRUE;
    }
    
    return result;

}

//INCLUDE_ASM("asm/nonmatchings/game/gameAudio", setAudioSequenceVolume);

void setAudioSequenceVolume(u16 sequenceIndex, u32 targetVolume) {
    if (sequenceIndex < TOTAL_SEQUENCES) {
        setAudioSequenceVolumes(0, targetVolume, 32);
    }
}

//INCLUDE_ASM("asm/nonmatchings/game/gameAudio", func_800ACC1C);

// unused
void func_800ACC1C(u16 sequenceIndex) {
    if (sequenceIndex < TOTAL_SEQUENCES) {
        setAudioSequenceVolumes(0, 0, 32);
    }
}

//INCLUDE_ASM("asm/nonmatchings/game/gameAudio", setSfx);

void playSfx(u16 index) {
    
  if (index < TOTAL_SFX) {
      
    if (audioTypeTable[index] == SFX_TYPE) {
      
      setSfx(index + 1);
      setSfxVolume(index + 1, volumesTable[index]);

    } else {

        setAudioSequence(audioTypeTable[index], (u8*)(uintptr_t)sfxRomAddresses[index].romAddrStart,
                         (u8*)(uintptr_t)sfxRomAddresses[index].romAddrEnd);
        setAudioSequenceVolumes(audioTypeTable[index], volumesTable[index], volumesTable[index]);
    
    }
    
  }
  
}

//INCLUDE_ASM("asm/nonmatchings/game/gameAudio", checkAllSfxInactive);

u8 checkAllSfxInactive(void) {

    u8 i;
    u8 count;

    count = 0;

    for (i = 0; i < MAX_ACTIVE_SFX; i++) {
        if (!gSfx[i].flags) {
            count++;
        }
    }
    
    return count == 4;

}
