// HM64 PC Port - Game Class Implementation

#include "hm64_game.h"
#include "hm64_ram.h"
#include "nugfx.h"
#include "ui/BlueFeatherUI.h"

#include <ship/Context.h>

#include <fast/Fast3dWindow.h>
#include <ship/window/Window.h>
#include <ship/controller/controldeck/ControlDeck.h>
#include <ship/audio/Audio.h>
#include <libultraship/bridge/consolevariablebridge.h>
#include <libultraship/libultra.h>
#include <libultraship/bridge.h>
#include <fast/interpreter.h>
#include <spdlog/spdlog.h>
#include <cstdlib>

#include <algorithm>
#include <chrono>
#include <thread>

extern "C" {
void HM64_BootGame(void);
void HM64_BeginMainLoop(void);
bool HM64_HostAdvanceFrame(int pendingGfx);
bool HM64_HostPumpIdleFrame(int pendingGfx);
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
constexpr const char* CVAR_GAME_SPEED = "gGameSpeed";
constexpr const char* CVAR_GAME_PAUSED = "gGamePaused";
constexpr const char* CVAR_GAME_STEP_FRAME = "gGameStepFrame";

static double GetGameSpeedScale() {
    const int32_t speedPercent = std::clamp(CVarGetInteger(CVAR_GAME_SPEED, 100), 50, 400);
    return static_cast<double>(speedPercent) / 100.0;
}

static bool IsGamePaused() {
    return CVarGetInteger(CVAR_GAME_PAUSED, 0) != 0;
}

static bool ConsumeStepFrameRequest() {
    if (CVarGetInteger(CVAR_GAME_STEP_FRAME, 0) == 0) {
        return false;
    }

    CVarSetInteger(CVAR_GAME_STEP_FRAME, 0);
    return true;
}

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

    if (!InitWindow()) {
        SPDLOG_ERROR("Failed to initialize window.");
        return false;
    }

    if (!InitGraphics()) {
        SPDLOG_ERROR("Failed to initialize graphics.");
        return false;
    }

    if (!InitAudio()) {
        SPDLOG_WARN("Failed to initialize audio, continuing without audio.");
    }

    if (!InitInput()) {
        SPDLOG_ERROR("Failed to initialize input.");
        return false;
    }

    m_initialized = true;

    return true;
}

bool HM64Game::InitWindow() {
    auto window = m_context->GetWindow();
    if (!window) {
        SPDLOG_ERROR("Window not available from context.");
        return false;
    }

    BlueFeatherSetupGuiElements();
    return true;
}

bool HM64Game::InitGraphics() {
    HM64Host_ClearRam();
    std::srand(0x486D3634);

    // Mirror the N64 framebuffer setup before booting imported HM64 code.
    if (gfx_create_framebuffer(320, 240, 320, 240, true) == 0) {
        SPDLOG_ERROR("Failed to create host framebuffer.");
        return false;
    }

    return true;
}

bool HM64Game::InitAudio() {
    auto audio = m_context->GetAudio();
    if (!audio) {
        SPDLOG_WARN("Audio not available from context.");
        return false;
    }

    return true;
}

bool HM64Game::InitInput() {
    auto controlDeck = m_context->GetControlDeck();
    if (!controlDeck) {
        SPDLOG_ERROR("Control deck not available from context.");
        return false;
    }

    // Set up controller mappings for N64-style controls
    // This will map keyboard/controller inputs to N64 buttons

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
}

void HM64Game::Run() {
    if (!m_initialized) {
        SPDLOG_ERROR("Cannot run game before initialization.");
        return;
    }

    m_running = true;
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

        window->HandleEvents();
        while (nuGfxProcessPendingMainThread()) {
        }

        const bool isPaused = IsGamePaused();
        const bool stepSingleFrame = isPaused && ConsumeStepFrameRequest();
        if (!isPaused) {
            accumulatedSeconds += frameDeltaSeconds * GetGameSpeedScale();
        } else {
            accumulatedSeconds = 0.0;
        }

        int retraceSteps = 0;
        if (stepSingleFrame && m_running && window->IsRunning()) {
            HM64_HostAdvanceFrame(nuGfxTaskNum());

            while (nuGfxProcessPendingMainThread()) {
            }

            retraceSteps = 1;
            m_hostFrameCounter++;
        }

        if (isPaused && !stepSingleFrame && m_running && window->IsRunning()) {
            HM64_HostPumpIdleFrame(nuGfxTaskNum());

            while (nuGfxProcessPendingMainThread()) {
            }
        }

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

    nuGfxShutdown();
}

void HM64Game::Shutdown() {
    if (!m_initialized) {
        return;
    }

    m_running = false;
    engineStateFlags = 0;
    nuGfxShutdown();

    m_initialized = false;
}
