// HM64 PC Port - Main Entry Point

#include <ship/Context.h>
#include <ship/window/Window.h>
#include <ship/controller/controldeck/ControlDeck.h>
#include <fast/Fast3dWindow.h>
#include <libultraship/libultra.h>
#include <libultraship/controller/controldeck/ControlDeck.h>
#include <libultraship/bridge/consolevariablebridge.h>
#include <spdlog/spdlog.h>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <filesystem>
#include <unordered_set>

#include "hm64_game.h"

int main(int argc, char* argv[]) {
    // On macOS, libultraship will look for the config in the app bundle's Resources folder
    // Just pass the filename and let libultraship handle the path resolution
    std::string configFileName = "bluefeather.json";
    
    // Mirror the golden-image model: locate port/base archives via the shared
    // app-dir -> bundle -> current-dir search, then load port first.
    std::vector<std::string> archivePaths;
    std::unordered_set<std::string> seenArchivePaths;

    auto addArchivePathIfExists = [&](const std::string& path) {
        const std::filesystem::path archivePath(path);
        if (!std::filesystem::exists(archivePath)) {
            return;
        }

        std::filesystem::path canonicalPath;
        try {
            canonicalPath = std::filesystem::weakly_canonical(archivePath);
        } catch (...) {
            canonicalPath = archivePath;
        }

        const std::string canonicalString = canonicalPath.string();
        if (seenArchivePaths.insert(canonicalString).second) {
            archivePaths.push_back(canonicalString);
        }
    };

    const std::string portArchivePath = Ship::Context::LocateFileAcrossAppDirs("BlueFeather.o2r", "bluefeather");
    const std::string baseArchivePath = Ship::Context::LocateFileAcrossAppDirs("hm64.o2r", "bluefeather");
    addArchivePathIfExists(portArchivePath);
    addArchivePathIfExists(baseArchivePath);

    if (!std::filesystem::exists(portArchivePath)) {
        std::cerr << "Missing BlueFeather.o2r. BlueFeather requires its port archive and will not fall back to in-exe assets." << std::endl;
        return 1;
    }

    if (!std::filesystem::exists(baseArchivePath)) {
        std::cerr << "Missing hm64.o2r. BlueFeather is archive-only and will not fall back to a raw ROM." << std::endl;
        return 1;
    }
    
    try {
        auto context = Ship::Context::CreateUninitializedInstance(
            "BlueFeather",           // Full app name
            "bluefeather",           // Short app name
            configFileName           // Config file (just the name)
        );

        if (!context) {
            std::cerr << "Failed to create libultraship bootstrap context." << std::endl;
            return 1;
        }

        if (!context->InitLogging(spdlog::level::warn, spdlog::level::warn)) {
            std::cerr << "Failed to initialize libultraship logging." << std::endl;
            return 1;
        }

        if (!context->InitConfiguration()) {
            SPDLOG_ERROR("Failed to initialize libultraship config.");
            SPDLOG_ERROR("Make sure bluefeather.json exists in the app bundle Resources folder.");
            return 1;
        }

        if (!context->InitConsoleVariables()) {
            SPDLOG_ERROR("Failed to initialize libultraship console variables.");
            return 1;
        }
        CVarRegisterInteger("gDeveloperTools.LogLevel", static_cast<int32_t>(spdlog::level::warn));
        context->GetLogger()->set_level(
            static_cast<spdlog::level::level_enum>(CVarGetInteger("gDeveloperTools.LogLevel", spdlog::level::warn)));

        // Create window and control deck in a nested scope so the local
        // shared_ptrs are released immediately after context->Init() takes
        // ownership.  This matches the golden-repo pattern and prevents the
        // locals from outliving the context (whose destructor calls
        // spdlog::shutdown() before these would otherwise destruct).
        {
            auto window = std::make_shared<Fast::Fast3dWindow>();
            auto controlDeck = std::make_shared<LUS::ControlDeck>();

            if (!context->Init(
                    archivePaths,            // Archive paths (assets folder)
                    {},                      // Valid hashes (empty = accept all)
                    1,                       // Reserved thread count
                    Ship::AudioSettings{},   // Default audio settings
                    window,
                    controlDeck)) {
                SPDLOG_ERROR("Failed to initialize libultraship context.");
                return 1;
            }
        }

        if (!context->GetWindow()) {
            SPDLOG_ERROR("Window initialization failed.");
            return 1;
        }

        if (!context->GetControlDeck()) {
            SPDLOG_ERROR("ControlDeck initialization failed.");
            return 1;
        }

        // Initialize and run the game
        HM64Game game(context);

        if (!game.Init()) {
            SPDLOG_ERROR("Failed to initialize HM64 game.");
            return 1;
        }

        game.Run();
        game.Shutdown();

        // Skip C++ destructors and let the OS reclaim all resources.
        _Exit(0);
    } catch (const std::exception& e) {
        SPDLOG_ERROR("Exception caught: {}", e.what());
        return 1;
    } catch (...) {
        SPDLOG_ERROR("Unknown exception caught.");
        return 1;
    }

    return 0;
}
