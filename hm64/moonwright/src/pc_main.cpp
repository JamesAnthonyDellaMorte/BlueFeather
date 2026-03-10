// HM64 PC Port - Main Entry Point
// This file initializes libultraship and hooks into the game code

#include <ship/Context.h>
#include <libultraship/libultra.h>
#include <spdlog/spdlog.h>

#include <iostream>
#include <string>
#include <vector>

#include "hm64_game.h"

// Forward declarations from game code
extern "C" {
    void mainproc(void* arg);
}

// Libultraship Context
static std::shared_ptr<Ship::Context> g_context = nullptr;

// Window and rendering settings
constexpr int WINDOW_WIDTH = 640;
constexpr int WINDOW_HEIGHT = 480;
constexpr const char* WINDOW_TITLE = "Harvest Moon 64 - PC Port";

void InitializeLogging() {
    try {
        spdlog::set_level(spdlog::level::debug);
        spdlog::set_pattern("[%H:%M:%S] [%l] %v");
        spdlog::info("HM64 PC Port starting...");
    } catch (const spdlog::spdlog_ex& ex) {
        std::cerr << "Log initialization failed: " << ex.what() << std::endl;
    }
}

int main(int argc, char* argv[]) {
    InitializeLogging();

    spdlog::info("Initializing Harvest Moon 64 PC Port");

    try {
        // Create libultraship context
        g_context = Ship::Context::CreateInstance(
            "Harvest Moon 64",           // Full game name
            "HM64",                       // Short name
            "hm64.json",                  // Config file
            {},                           // Archive paths (will be set up later)
            {},                           // Valid hashes
            1,                            // Reserved thread count
            Ship::AudioSettings{}         // Default audio settings
        );

        if (!g_context) {
            spdlog::error("Failed to create libultraship context!");
            return 1;
        }

        spdlog::info("Libultraship context created successfully");

        // Initialize HM64 game
        HM64Game* game = new HM64Game(g_context);
        
        if (!game->Init()) {
            spdlog::error("Failed to initialize HM64 game!");
            delete game;
            return 1;
        }

        spdlog::info("HM64 game initialized, starting main loop");

        // Main game loop
        game->Run();

        // Cleanup
        delete game;
        g_context.reset();

        spdlog::info("HM64 PC Port shutting down");

    } catch (const std::exception& e) {
        spdlog::error("Exception caught: {}", e.what());
        return 1;
    }

    return 0;
}
