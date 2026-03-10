#include "hm64_title_runtime.h"

#include "hm64_host_rom.h"
#include "hm64_ram.h"

#include <cstdlib>
#include <iostream>

#include <ship/Context.h>
#include <ship/window/Window.h>
#include <fast/interpreter.h>

extern "C" {
#include "game/title.h"
#include "game/transition.h"
#include "mainLoop.h"
#include "mainproc.h"
#include "system/controller.h"
#include "system/globalSprites.h"
#include "system/graphic.h"
#include "system/sceneGraph.h"
#include "system/sprite.h"
#include "system/spriteDMAManager.h"

void HM64Host_ResetShimState(void);

// Game callback functions needed for intro cutscenes
void mainGameLoopCallback(void);
void setMapAudioAndLighting(void);
void mapLoadCallback(void);

// Cutscene system
void updateCutsceneExecutors(void);

// Cutscene initialization
void HM64_InitCutsceneBytecodeAddresses(void);
}

HM64TitleRuntime::HM64TitleRuntime() : m_initialized(false) {
}

bool HM64TitleRuntime::Init(const std::shared_ptr<Ship::Context>& context) {
    m_context = context;

    HM64Host_ClearRam();
    HM64Host_ResetShimState();
    std::srand(0x486D3634);

    if (!HM64Host_LoadTitleRomSegments()) {
        std::cerr << "[HM64] Title runtime could not load ROM-backed title assets" << std::endl;
        return false;
    }

    auto window = m_context ? m_context->GetWindow() : nullptr;
    if (window) {
        window->HandleEvents();
    }

    controllerInit();
    initializeSceneNodes();
    initializeBitmaps();
    initializeGlobalSprites();
    initializeSpriteAssetDescriptorFlags();
    graphicsInit();
    
    // Create framebuffers for PC rendering (matches Shipwright pattern)
    gfx_create_framebuffer(320, 240, 320, 240, true);

    registerMainLoopCallback(NO_OP, (MainLoopCallback)noOpCallback);
    registerMainLoopCallback(TITLE_SCREEN, (MainLoopCallback)titleScreenMainLoopCallback);
    // Game callbacks needed for intro cutscenes
    registerMainLoopCallback(MAIN_GAME, (MainLoopCallback)mainGameLoopCallback);
    registerMainLoopCallback(SET_AUDIO_AND_LIGHTING, (MainLoopCallback)setMapAudioAndLighting);
    registerMainLoopCallback(MAP_LOAD, (MainLoopCallback)mapLoadCallback);

    // Initialize cutscene bytecode addresses (PC port requirement)
    HM64_InitCutsceneBytecodeAddresses();
    
    // Start with opening logos instead of going straight to title screen
    // This matches the original game's boot sequence
    extern void launchIntroCutscene(u16 cutsceneIndex, u16 spawnPoint, u8 arg2);
    launchIntroCutscene(1456, 0x61, 1);  // OPENING_LOGOS = 1456
    m_initialized = true;

    std::cout << "[HM64] Title runtime initialized" << std::endl;
    return true;
}

void HM64TitleRuntime::Tick() {
    if (!m_initialized) {
        return;
    }

    readControllerData();

    if (mainLoopCallbackCurrentIndex < MAIN_LOOP_CALLBACK_FUNCTION_TABLE_SIZE &&
        mainLoopCallbacksTable[mainLoopCallbackCurrentIndex] != nullptr) {
        mainLoopCallbacksTable[mainLoopCallbackCurrentIndex]();
    }

    // Keep the intro logo path aligned with the real main-loop ordering.
    resetBitmaps();
    resetSceneNodeCounter();
    updateCutsceneExecutors();
    updateSprites();
    dmaSprites();
    updateBitmaps();
    drawFrame();

    frameCount = (frameCount + 1) % 60;
    retraceCount++;
}

bool HM64TitleRuntime::IsInitialized() const {
    return m_initialized;
}
