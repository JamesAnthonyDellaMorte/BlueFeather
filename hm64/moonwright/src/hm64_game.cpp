// HM64 PC Port - Game Class Implementation

#include "hm64_game.h"
#include "hm64_title_runtime.h"

#include <ship/Context.h>

#include <ship/window/Window.h>
#include <ship/controller/controldeck/ControlDeck.h>
#include <ship/audio/Audio.h>
#include <libultraship/libultra.h>
#include <libultraship/bridge.h>
#include <iostream>

#include <thread>
#include <chrono>

// Target 20 FPS (N64 NTSC games typically ran at 20 or 30 FPS)
constexpr float TARGET_FPS = 20.0f;
constexpr float TARGET_FRAME_TIME_MS = 1000.0f / TARGET_FPS;

HM64Game::HM64Game(std::shared_ptr<Ship::Context> context)
    : m_context(context)
    , m_running(false)
    , m_initialized(false)
    , m_titleRuntimeActive(false) {
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

    m_titleRuntime = std::make_unique<HM64TitleRuntime>();
    if (m_titleRuntime->Init(m_context)) {
        m_titleRuntimeActive = true;
        std::cout << "[INFO] Booting real HM64 title runtime" << std::endl;
        return true;
    }

    m_titleRuntime.reset();
    std::cerr << "[ERROR] Moonwright must boot through the N64 intro/runtime path. "
              << "Title runtime initialization failed." << std::endl;
    return false;
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

void HM64Game::Run() {
    if (!m_initialized) {
        std::cerr << "[ERROR] Cannot run game - not initialized!" << std::endl;
        return;
    }

    m_running = true;
    std::cout << "[INFO] Starting game main loop" << std::endl;

    auto window = m_context->GetWindow();
    
    using Clock = std::chrono::high_resolution_clock;
    using Duration = std::chrono::duration<float, std::milli>;
    
    while (m_running && window && window->IsRunning()) {
        auto frameStart = Clock::now();

        // Process window events
        window->HandleEvents();

        // Update game state
        Update();
        
        // Render frame
        Render();

        // Frame rate limiting
        auto frameEnd = Clock::now();
        Duration frameTime = frameEnd - frameStart;
        
        if (frameTime.count() < TARGET_FRAME_TIME_MS) {
            std::this_thread::sleep_for(
                std::chrono::milliseconds(static_cast<int>(TARGET_FRAME_TIME_MS - frameTime.count()))
            );
        }
    }

    m_running = false;
    std::cout << "[INFO] Game main loop ended" << std::endl;
}

void HM64Game::Update() {
    if (m_titleRuntimeActive && m_titleRuntime) {
        m_titleRuntime->Tick();
    }
}

void HM64Game::Render() {
    (void)m_context;
}

void HM64Game::Shutdown() {
    if (!m_initialized) {
        return;
    }

    std::cout << "[INFO] Shutting down HM64 Game..." << std::endl;

    m_running = false;
    m_initialized = false;

    std::cout << "[INFO] HM64 Game shutdown complete" << std::endl;
}
