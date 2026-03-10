#include "common.h"

#include <stdio.h>

#include "game/gameAudio.h"
#include "game/title.h"
#include "mainLoop.h"
#include "mainproc.h"
#include "system/audio.h"

#include <string.h>

volatile u8 previousLoopStepsPerCycle;
volatile u16 engineStateFlags;
volatile u8 drawnFrameCount;
volatile u8 retraceCount;
volatile u8 loopStepsPerCycle;
volatile u8 framebufferCount;
volatile u8 previousDrawnFrameCount;
volatile u8 currentFramebufferIndex;
u16 gMainMapIndex;
volatile u8 D_80204B38;
volatile u8 stepMainLoop;
volatile u32 pendingGfxNum;
volatile u8 mainLoopUpdateRate;
volatile u8 D_80222730;
volatile u8 frameRate;
volatile u8 D_80237A04;
volatile u8 frameCount;
volatile u32 gGraphicsBufferIndex;
volatile u8 gfxTaskNo;

volatile u16 mainLoopCallbackCurrentIndex;
MainLoopCallback mainLoopCallbacksTable[MAIN_LOOP_CALLBACK_FUNCTION_TABLE_SIZE];

u16 gCurrentAudioSequenceIndex;
s32 gAudioSequenceVolume;
Sfx gSfx[4];
SequenceInfo gAudioSequences[4];

long long int gspF3DEX2_fifoTextStart[1];
long long int gspF3DEX2_fifoDataStart[1];

void HM64Host_ResetShimState(void) {
    previousLoopStepsPerCycle = 0;
    engineStateFlags = 0;
    drawnFrameCount = 0;
    retraceCount = 0;
    loopStepsPerCycle = 0;
    framebufferCount = 0;
    previousDrawnFrameCount = 0;
    currentFramebufferIndex = 0;
    gMainMapIndex = 0;
    D_80204B38 = 0;
    stepMainLoop = FALSE;
    pendingGfxNum = 0;
    mainLoopUpdateRate = 1;
    D_80222730 = 0;
    frameRate = 1;
    D_80237A04 = 0;
    frameCount = 0;
    gGraphicsBufferIndex = 0;
    gfxTaskNo = 0;

    mainLoopCallbackCurrentIndex = NO_OP;
    memset(mainLoopCallbacksTable, 0, sizeof(mainLoopCallbacksTable));

    gCurrentAudioSequenceIndex = 0xFFFF;
    gAudioSequenceVolume = SEQUENCE_VOLUME;
    memset(gSfx, 0, sizeof(gSfx));
    memset(gAudioSequences, 0, sizeof(gAudioSequences));
}

bool registerMainLoopCallback(u16 index, MainLoopCallback func) {
    if (index >= MAIN_LOOP_CALLBACK_FUNCTION_TABLE_SIZE || mainLoopCallbacksTable[index] != NULL) {
        return FALSE;
    }

    mainLoopCallbacksTable[index] = func;
    return TRUE;
}

u32 setMainLoopCallbackFunctionIndex(u16 index) {
    if (index >= MAIN_LOOP_CALLBACK_FUNCTION_TABLE_SIZE || mainLoopCallbacksTable[index] == NULL) {
        return FALSE;
    }

    mainLoopCallbackCurrentIndex = index;
    return TRUE;
}

// noOpCallback - matches MainLoopCallback signature (returns void*)
void* noOpCallback(void) {
    return NULL;
}

void setCurrentAudioSequence(u16 sequenceIndex) {
    gCurrentAudioSequenceIndex = sequenceIndex;
}

void stopCurrentAudioSequence(u16 sequenceIndex) {
    (void)sequenceIndex;
}

void stopAudioSequenceWithDefaultFadeOut(u16 sequenceIndex) {
    (void)sequenceIndex;
}

u8 checkDefaultSequenceChannelOpen(u16 sequenceIndex) {
    (void)sequenceIndex;
    return TRUE;
}

void setAudioSequenceVolume(u16 sequenceIndex, u32 volume) {
    (void)sequenceIndex;
    gAudioSequenceVolume = (s32)volume;
}

void func_800ACC1C(u16 sequenceIndex) {
    (void)sequenceIndex;
}

void playSfx(u16 index) {
    (void)index;
}

u8 checkAllSfxInactive(void) {
    return TRUE;
}

// Note: These are now implemented in the real game code or intro runtime
// The shims are removed to allow the real flow to work

// Forward declarations for functions that may be called before real implementation is linked
extern void initializeLoadGameScreen_real(bool controllerPakEnabled);
extern void launchIntroCutscene_real(u16 cutsceneIndex, u16 spawnPoint, u8 arg2);

// These shim functions will be replaced by real implementations when hm64_decomp_host_core is linked
void initializeLoadGameScreen(bool controllerPakEnabled) {
    (void)controllerPakEnabled;
    // For now, go directly to title - real implementation will handle game loading
    initializeTitleScreen(0);
}

// Forward declarations for cutscene functions
extern void deactivateSprites(void);
extern void deactivateGlobalSprites(void);
extern void initializeMessageBoxes(void);
extern void initializeCutsceneExecutors(void);
extern void initializeMainMessageBoxes(void);
extern void resetGlobalLighting(void);
extern void setEntitiesRGBA(u8 r, u8 g, u8 b, u8 a);
extern void setMapControllerRGBA(u8 mapIndex, u8 r, u8 g, u8 b, u8 a);
extern void initializeEntityInstances(void);
extern void setSpawnPoint(u8 index);
extern void loadCutscene(bool morningVisit);
extern void loadMapAtSpawnPoint(void);
extern void setupPlayerEntity(void);
extern void handlePlayerAnimation(u8 animation);
extern u32 setMainLoopCallbackFunctionIndex(u16 index);

// Cutscene state
extern u16 gCutsceneIndex;
extern u16 gSpawnPointIndex;
extern u8 gHour;

void launchIntroCutscene(u16 cutsceneIndex, u16 spawnPoint, u8 arg2) {
    // This is called by the title screen to start cutscenes
    printf("[SHIM] launchIntroCutscene called: cutsceneIndex=%u, spawnPoint=%u, arg2=%u\n", 
           cutsceneIndex, spawnPoint, arg2);
    
    // Try to load the cutscene properly
    printf("[SHIM] Deactivating sprites...\n");
    deactivateSprites();
    deactivateGlobalSprites();
    
    printf("[SHIM] Initializing message boxes...\n");
    initializeMessageBoxes();
    initializeCutsceneExecutors();
    initializeMainMessageBoxes();
    
    printf("[SHIM] Resetting lighting...\n");
    resetGlobalLighting();
    
    setEntitiesRGBA(0, 0, 0, 0);
    setMapControllerRGBA(0, 0, 0, 0, 0);
    
    gHour = 12;
    
    printf("[SHIM] Initializing entity instances...\n");
    initializeEntityInstances();
    
    setSpawnPoint((u8)spawnPoint);
    gCutsceneIndex = cutsceneIndex;
    
    printf("[SHIM] Loading cutscene...\n");
    loadCutscene(0);  // FALSE
    
    printf("[SHIM] Loading map at spawn point...\n");
    loadMapAtSpawnPoint();
    
    printf("[SHIM] Setting up player...\n");
    setupPlayerEntity();
    handlePlayerAnimation(0);
    
    printf("[SHIM] Setting main loop callback to SET_AUDIO_AND_LIGHTING...\n");
    setMainLoopCallbackFunctionIndex(3);  // SET_AUDIO_AND_LIGHTING
    
    printf("[SHIM] Cutscene setup complete!\n");
}
