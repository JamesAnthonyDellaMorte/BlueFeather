// HM64 PC Port - Game Class Implementation

#include "hm64_game.h"
#include "hm64_ram.h"
#include "nugfx.h"

#include <ship/Context.h>

#include <fast/Fast3dWindow.h>
#include <ship/window/Window.h>
#include <ship/controller/controldeck/ControlDeck.h>
#include <ship/audio/Audio.h>
#include <libultraship/libultra.h>
#include <libultraship/bridge.h>
#include <fast/interpreter.h>
#include <iostream>
#include <cstdlib>

#include <chrono>
#include <thread>

extern "C" {
void HM64_BootGame(void);
void HM64_BeginMainLoop(void);
bool HM64_HostAdvanceFrame(int pendingGfx);
void HM64_InitCutsceneBytecodeAddresses(void);
extern volatile u16 engineStateFlags;
extern volatile u8 frameRate;
extern volatile u8 mainLoopUpdateRate;
}

// Drive imported HM64 timing from a fixed 60 Hz host retrace.
constexpr double TARGET_RETRACE_HZ = 60.0;
constexpr double TARGET_RETRACE_SECONDS = 1.0 / TARGET_RETRACE_HZ;
constexpr double MAX_ACCUMULATED_SECONDS = TARGET_RETRACE_SECONDS * 5.0;
constexpr int MAX_RETRACE_STEPS_PER_HOST_FRAME = 5;

HM64Game::HM64Game(std::shared_ptr<Ship::Context> context)
    : m_context(context)
    , m_running(false)
    , m_initialized(false)
    , m_gameBooted(false)
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

void HM64Game::BootGame() {
    if (m_gameBooted) {
        return;
    }

    HM64_InitCutsceneBytecodeAddresses();
    HM64_BootGame();
    HM64_BeginMainLoop();

    // HM64 initializes both rates to 1, which runs logic and drawing every VI.
    // On original hardware the engine regularly missed those deadlines; on host
    // it does not, so the intro and title flow end up effectively doubled.
    frameRate = 2;
    mainLoopUpdateRate = 2;

    m_gameBooted = true;
    std::cout << "[INFO] Booted HM64 and entered host-driven main loop" << std::endl;
}

void HM64Game::Run() {
    if (!m_initialized) {
        std::cerr << "[ERROR] Cannot run game - not initialized!" << std::endl;
        return;
    }

    m_running = true;
    std::cout << "[INFO] Starting game main loop" << std::endl;
    BootGame();

    auto window = m_context->GetWindow();
    auto fastWindow = std::dynamic_pointer_cast<Fast::Fast3dWindow>(window);
    if (fastWindow != nullptr) {
        fastWindow->SetTargetFps(static_cast<int32_t>(TARGET_RETRACE_HZ));
        fastWindow->SetMaximumFrameLatency(1);
    }
    
    using Clock = std::chrono::steady_clock;
    using Seconds = std::chrono::duration<double>;
    auto previousTick = Clock::now();
    double accumulatedSeconds = 0.0;
    
    while (m_running && window && window->IsRunning()) {
        auto now = Clock::now();
        double frameDeltaSeconds = std::chrono::duration_cast<Seconds>(now - previousTick).count();
        previousTick = now;

        if (frameDeltaSeconds > MAX_ACCUMULATED_SECONDS) {
            frameDeltaSeconds = MAX_ACCUMULATED_SECONDS;
        }

        accumulatedSeconds += frameDeltaSeconds;

        window->HandleEvents();
        while (nuGfxProcessPendingMainThread()) {
        }

        int retraceSteps = 0;
        while (accumulatedSeconds >= TARGET_RETRACE_SECONDS && retraceSteps < MAX_RETRACE_STEPS_PER_HOST_FRAME &&
               m_running && window->IsRunning()) {
            HM64_HostAdvanceFrame(nuGfxTaskNum());

            while (nuGfxProcessPendingMainThread()) {
            }

            accumulatedSeconds -= TARGET_RETRACE_SECONDS;
            retraceSteps++;
            m_hostFrameCounter++;
        }

        if (accumulatedSeconds > MAX_ACCUMULATED_SECONDS) {
            accumulatedSeconds = MAX_ACCUMULATED_SECONDS;
        }

        if (accumulatedSeconds < TARGET_RETRACE_SECONDS) {
            std::this_thread::sleep_for(Seconds(TARGET_RETRACE_SECONDS - accumulatedSeconds));
        }
    }

    m_running = false;
    engineStateFlags = 0;

    std::cout << "[INFO] Game main loop ended" << std::endl;
}

void HM64Game::Shutdown() {
    if (!m_initialized) {
        return;
    }

    std::cout << "[INFO] Shutting down HM64 Game..." << std::endl;

    m_running = false;
    engineStateFlags = 0;

    m_initialized = false;

    std::cout << "[INFO] HM64 Game shutdown complete" << std::endl;
}
