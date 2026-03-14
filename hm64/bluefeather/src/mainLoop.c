#include "common.h"

#include "mainLoop.h"

#include "stdlib.h"

#include <libultraship/bridge/windowbridge.h>

#include "nualstl_n.h"
#include "system/audio.h"
#include "system/controller.h"
#include "system/cutscene.h"
#include "system/entity.h"
#include "system/flags.h"
#include "system/globalSprites.h"
#include "system/graphic.h"
#include "system/message.h"
#include "system/numberSprites.h"
#include "system/sprite.h"
#include "system/mapController.h"
#include "system/sceneGraph.h"
#include "system/spriteDMAManager.h"

#include "mainproc.h"

// bss
volatile u16 mainLoopCallbackCurrentIndex;
MainLoopCallback mainLoopCallbacksTable[MAIN_LOOP_CALLBACK_FUNCTION_TABLE_SIZE];

volatile u16 D_80182BA0;
volatile u16 D_8020564C;
void *currentGfxTaskPtr;
static bool sMainLoopStarted = FALSE;
static bool sMainLoopReady = FALSE;

// forward declarations
void func_80026284(void);
void handleGraphicsUpdate(int pendingGfx);
void updateMainLoopTimer(int pendingGfx);
static void HM64_FinishMainLoopBoot(void);
static void HM64_RunMainLoopIteration(void);

extern s32 __osSpSetPc(u32 pc);

  
//INCLUDE_ASM("asm/nonmatchings/mainLoop", mainLoop)

void HM64_BeginMainLoop(void) {
    stepMainLoop = FALSE;
    engineStateFlags = 1;
    sMainLoopStarted = TRUE;
    sMainLoopReady = FALSE;
}

static void HM64_FinishMainLoopBoot(void) {
    func_8004DEC8();
    D_80182BA0 = 1;
    D_8020564C = 0;
    sMainLoopReady = TRUE;
}

static void HM64_RunMainLoopIteration(void) {
    if (!D_8020564C) { 
      
      D_80182BA0 = 1;
      
      // handle specific logic depending on game mode/screen
      mainLoopCallbacksTable[mainLoopCallbackCurrentIndex](); 

      D_8020564C = D_80182BA0; 

    } 
    
    D_8020564C -= 1;    

    // dead code
    if (D_8020564C) {

    }
    
    resetBitmaps();
    updateAudio(); 
    resetSceneNodeCounter();
    updateCutsceneExecutors();
    updateEntities();
    updateMapController();
    updateMapGraphics();
    updateNumberSprites();
    updateSprites(); 
    dmaSprites(); 
    updateBitmaps(); 
    updateMessageBox(); 
    updateDialogues();

    // no op
    // shelved or debug code
    func_800293B8(); 

    stepMainLoop = FALSE; 

    // unused
    D_80237A04 = retraceCount;
      
    // update RNG seed
    rand();
}

bool HM64_MainLoopStep(void) {
    if (!sMainLoopStarted || !WindowIsRunning()) {
        return FALSE;
    }

    nuGfxDisplayOn();

    if (!(engineStateFlags & 1)) {
        nuGfxDisplayOff();
        return FALSE;
    }

    if (stepMainLoop == FALSE) {
        return FALSE;
    }

    if (!sMainLoopReady) {
        stepMainLoop = FALSE;

        if (engineStateFlags & 2) {
            HM64_FinishMainLoopBoot();
        }

        return TRUE;
    }

    HM64_RunMainLoopIteration();
    return TRUE;
}

bool HM64_HostAdvanceFrame(int pendingGfx) {
    if (!sMainLoopStarted || !WindowIsRunning()) {
        return FALSE;
    }

    gfxRetraceCallback(pendingGfx);
    const bool stepped = HM64_MainLoopStep();
    nuAuStlTick();
    return stepped;
}

bool HM64_HostPumpIdleFrame(int pendingGfx) {
    if (!sMainLoopStarted || !WindowIsRunning()) {
        return FALSE;
    }

    // Keep retrace, input, and drawing alive while the host has game logic paused.
    stepMainLoop = FALSE;
    gfxRetraceCallback(pendingGfx);
    stepMainLoop = FALSE;
    return TRUE;
}

void mainLoop(void) {
    HM64_BeginMainLoop();

    while (WindowIsRunning()) {
        while ((engineStateFlags & 1) && WindowIsRunning()) {
            HM64_HostAdvanceFrame(0);
        }

        nuGfxDisplayOff();
    }
}

//INCLUDE_ASM("asm/nonmatchings/mainLoop", registerMainLoopCallback);

bool registerMainLoopCallback(u16 index, MainLoopCallback func) {

    bool result = FALSE;

    if (index < MAIN_LOOP_CALLBACK_FUNCTION_TABLE_SIZE) {
        if (mainLoopCallbacksTable[index] == NULL) {
            mainLoopCallbacksTable[index] = func;
            result = TRUE;
        }
    }

    return result;

}

//INCLUDE_ASM("asm/nonmatchings/mainLoop", setMainLoopCallbackFunctionIndex);

u32 setMainLoopCallbackFunctionIndex(u16 index) {
    
    u32 result = FALSE;

    volatile int *temp;
    
    if (index < MAIN_LOOP_CALLBACK_FUNCTION_TABLE_SIZE) {

        temp = (volatile int*)mainLoopCallbacksTable;
      
        if (temp[index]) {
            mainLoopCallbackCurrentIndex = index;
            result = TRUE;
        }
    } 
    
    return result;

}

//INCLUDE_ASM("asm/nonmatchings/mainLoop", func_8002620C);

// unused
void func_8002620C(void) {
    D_80204B38 = 1;
}

//INCLUDE_ASM("asm/nonmatchings/mainLoop", func_80026220);

// unused
void func_80026220(void) {
    D_80204B38 = 0;
}

//INCLUDE_ASM("asm/nonmatchings/mainLoop", func_80026230);

// unused
void func_80026230(u16 num) {
    D_80182BA0 = num;
}

// noOpCallback - returns void* to match MainLoopCallback signature
void* noOpCallback(void) {
    return NULL;
}

//INCLUDE_ASM("asm/nonmatchings/mainLoop", func_80026248);

static inline void func_80026248(u16 count) {
    u16 counter;

    for (counter = 0; counter < count; counter++) {
        if (!WindowIsRunning()) {
            return;
        }

        HM64_HostAdvanceFrame(0);
    }

}

//INCLUDE_ASM("asm/nonmatchings/mainLoop", func_80026284);

// start up before main loop
void func_80026284(void) {

    goto loop_end;
    
    // first 60 frames
    while (!(engineStateFlags & 2) && WindowIsRunning()) {

        func_80026248(1);

loop_end:     
        ;
    }

}


// gfx retrace funcs

//INCLUDE_ASM("asm/nonmatchings/mainLoop", gfxRetraceCallback);

// NUGfxFunc
u8 gfxRetraceCallback(int pendingGfx) {
  
    u8 temp;
    
    pendingGfxNum = pendingGfx;

    engineStateFlags &= ~2;
    
    readControllerData();

    handleGraphicsUpdate(pendingGfx);
    updateMainLoopTimer(pendingGfx);
    
    if (frameCount > 59) {
        frameCount = 0;
        engineStateFlags |= 2;
    }
    
    // no op
    func_8004DF00();
    
    frameCount++;
    retraceCount++;

    // reset to 0 when pendingGfx < 3
    // FIXME: unnecessary assignment
    temp = framebufferCount++;
    
    return framebufferCount;
    
}

//INCLUDE_ASM("asm/nonmatchings/mainLoop", handleGraphicsUpdate);

void handleGraphicsUpdate(int pendingGfx) {

  u8 temp;
    
  if ((frameCount % frameRate) == 0) {
      
    if (frameCount > 59) {

      previousDrawnFrameCount = drawnFrameCount;
      drawnFrameCount = 0;

      // < hz
      if (previousDrawnFrameCount < (60 / frameRate)) {
        // unused
        D_80222730 = 2;
      }

    }
      
    if (pendingGfx < 3) { 

      temp = stepMainLoop;

      if (temp == FALSE) {
        
        drawFrame();

        drawnFrameCount += 1;
        // FIXME: unnecessary assignment, might be return value
        temp = drawnFrameCount;

        framebufferCount = 0;
        
      }
    }
  }

}

//INCLUDE_ASM("asm/nonmatchings/mainLoop", updateMainLoopTimer);

void updateMainLoopTimer(int pendingGfx) {
    
    if ((frameCount % mainLoopUpdateRate) == 0) {
        
        if (frameCount > 59) {

          previousLoopStepsPerCycle = loopStepsPerCycle;
          loopStepsPerCycle = 0;

          // < hz
          if (previousLoopStepsPerCycle < (60 / mainLoopUpdateRate)) {
            // unused
            D_80222730 = 1;
          }

        }
      
        if (stepMainLoop == FALSE) {

          stepMainLoop = TRUE;

          retraceCount = 0;
          loopStepsPerCycle += 1;
          // FIXME: ? might be return value
          loopStepsPerCycle;  

        }
    }
    
}

//INCLUDE_ASM("asm/nonmatchings/mainLoop", gfxBufferSwap);

void gfxBufferSwap(void *gfxTask) {
    
    currentGfxTaskPtr = gfxTask;
    nuGfxSwapCfb(gfxTask);
    
    // unused
    currentFramebufferIndex = framebufferCount;
    
}

// manual copy of library func
s32 osAfterPreNMI(void) {
    return __osSpSetPc(0);
}

//INCLUDE_ASM("asm/nonmatchings/mainLoop", gfxPreNMICallback);

void gfxPreNMICallback(void) {
    
    volatile int *callbackTablePtr;
    
    callbackTablePtr = (volatile int*)&mainLoopCallbacksTable;
    
    if (*callbackTablePtr) {
        mainLoopCallbackCurrentIndex = 0;
    }
    
    nuGfxFuncSet(NULL);
    nuGfxTaskAllEndWait();
    nuGfxDisplayOff();

    osStopThread(&nusched.graphicsThread);
    osStopThread(&nusched.audioThread);
    
    osViSetYScale(1.0f);
    
    while (__osSpSetPc(0));
    
    while (TRUE);

}
