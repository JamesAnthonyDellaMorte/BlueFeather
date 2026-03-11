// HM64 PC Port - Game Class Implementation

#include "hm64_game.h"
#include "hm64_ram.h"
#include "nugfx.h"

#include <ship/Context.h>

#include <ship/window/Window.h>
#include <ship/controller/controldeck/ControlDeck.h>
#include <ship/audio/Audio.h>
#include <libultraship/libultra.h>
#include <libultraship/bridge.h>
#include <fast/interpreter.h>
#include <iostream>
#include <cstdlib>

#include <thread>
#include <chrono>

extern "C" {
void mainproc(void* arg);
void HM64_InitCutsceneBytecodeAddresses(void);
extern volatile u16 engineStateFlags;
extern volatile u8 stepMainLoop;
}

// Drive the N64 retrace callback at 60 Hz.
constexpr float TARGET_FPS = 60.0f;
constexpr float TARGET_FRAME_TIME_MS = 1000.0f / TARGET_FPS;

HM64Game::HM64Game(std::shared_ptr<Ship::Context> context)
    : m_context(context)
    , m_running(false)
    , m_initialized(false)
    , m_gameThreadStarted(false)
    , m_hostFrameCounter(0) {
}

HM64Game::~HM64Game() {
    Shutdown();
}

bool HM64Game::Init() {
    if (m_initialized) {
        return true;
    }

    std::cout << "[INFO] Initializing HM64 Game..." << std::endl;

    if (!InitWindow()) {
        std::cerr << "[ERROR] Failed to initialize window!" << std::endl;
        return false;
    }

    if (!InitGraphics()) {
        std::cerr << "[ERROR] Failed to initialize graphics!" << std::endl;
        return false;
    }

    if (!InitAudio()) {
        std::cout << "[WARN] Failed to initialize audio (continuing without audio)" << std::endl;
    }

    if (!InitInput()) {
        std::cerr << "[ERROR] Failed to initialize input!" << std::endl;
        return false;
    }

    m_initialized = true;
    std::cout << "[INFO] HM64 Game initialization complete" << std::endl;

    return true;
}

bool HM64Game::InitWindow() {
    std::cout << "[INFO] Initializing window..." << std::endl;
    
    auto window = m_context->GetWindow();
    if (!window) {
        std::cerr << "[ERROR] Window not available from context!" << std::endl;
        return false;
    }

    std::cout << "[INFO] Window initialized" << std::endl;
    return true;
}

bool HM64Game::InitGraphics() {
    std::cout << "[INFO] Initializing graphics..." << std::endl;

    HM64Host_ClearRam();
    std::srand(0x486D3634);

    // Mirror the N64 framebuffer setup before booting imported HM64 code.
    if (gfx_create_framebuffer(320, 240, 320, 240, true) == 0) {
        std::cerr << "[ERROR] Failed to create host framebuffer!" << std::endl;
        return false;
    }

    return true;
}

bool HM64Game::InitAudio() {
    std::cout << "[INFO] Initializing audio..." << std::endl;
    
    auto audio = m_context->GetAudio();
    if (!audio) {
        std::cout << "[WARN] Audio not available from context" << std::endl;
        return false;
    }

    std::cout << "[INFO] Audio initialized" << std::endl;
    return true;
}

bool HM64Game::InitInput() {
    std::cout << "[INFO] Initializing input..." << std::endl;
    
    auto controlDeck = m_context->GetControlDeck();
    if (!controlDeck) {
        std::cerr << "[ERROR] Control deck not available from context!" << std::endl;
        return false;
    }

    // Set up controller mappings for N64-style controls
    // This will map keyboard/controller inputs to N64 buttons

    std::cout << "[INFO] Input initialized" << std::endl;
    return true;
}

void HM64Game::StartGameThread() {
    if (m_gameThreadStarted) {
        return;
    }

    HM64_InitCutsceneBytecodeAddresses();
    // Moonwright [Port] Keep the real game owner path on mainproc/mainLoop instead of
    // replacing it with a host-side runtime loop.
    m_gameThread = std::thread([]() {
        mainproc(nullptr);
    });
    m_gameThreadStarted = true;
    std::cout << "[INFO] Booting real HM64 mainproc/mainLoop" << std::endl;
}

void HM64Game::Run() {
    if (!m_initialized) {
        std::cerr << "[ERROR] Cannot run game - not initialized!" << std::endl;
        return;
    }

    m_running = true;
    std::cout << "[INFO] Starting game main loop" << std::endl;
    StartGameThread();

    auto window = m_context->GetWindow();
    
    using Clock = std::chrono::high_resolution_clock;
    using Duration = std::chrono::duration<float, std::milli>;
    
    while (m_running && window && window->IsRunning()) {
        auto frameStart = Clock::now();

        window->HandleEvents();
        while (nuGfxProcessPendingMainThread()) {
        }
        nuGfxCallFunc(nuGfxTaskNum());
        while (nuGfxProcessPendingMainThread()) {
        }
        m_hostFrameCounter++;

        auto frameEnd = Clock::now();
        Duration frameTime = frameEnd - frameStart;
        
        if (frameTime.count() < TARGET_FRAME_TIME_MS) {
            std::this_thread::sleep_for(
                std::chrono::milliseconds(static_cast<int>(TARGET_FRAME_TIME_MS - frameTime.count()))
            );
        }
    }

    m_running = false;
    engineStateFlags = 0;
    stepMainLoop = TRUE;

    if (m_gameThread.joinable()) {
        m_gameThread.join();
    }

    std::cout << "[INFO] Game main loop ended" << std::endl;
}

void HM64Game::Shutdown() {
    if (!m_initialized) {
        return;
    }

    std::cout << "[INFO] Shutting down HM64 Game..." << std::endl;

    m_running = false;

    if (m_gameThread.joinable()) {
        engineStateFlags = 0;
        stepMainLoop = TRUE;
        m_gameThread.join();
    }

    m_initialized = false;

    std::cout << "[INFO] HM64 Game shutdown complete" << std::endl;
}
