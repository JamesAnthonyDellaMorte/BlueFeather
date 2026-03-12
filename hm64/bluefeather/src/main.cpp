// HM64 PC Port - Main Entry Point

#include <ship/Context.h>
#include <ship/window/Window.h>
#include <ship/controller/controldeck/ControlDeck.h>
#include <fast/Fast3dWindow.h>
#include <libultraship/libultra.h>
#include <libultraship/controller/controldeck/ControlDeck.h>
#include <iostream>
#include <memory>
#include <filesystem>
#include <unordered_set>

#include "hm64_game.h"

int main(int argc, char* argv[]) {
    std::cout << "[INFO] BlueFeather starting..." << std::endl;
    
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
            std::cout << "[INFO] Added asset source: " << canonicalPath << std::endl;
        }
    };

    const std::string portArchivePath = Ship::Context::LocateFileAcrossAppDirs("BlueFeather.o2r", "bluefeather");
    const std::string baseArchivePath = Ship::Context::LocateFileAcrossAppDirs("hm64.o2r", "bluefeather");
    addArchivePathIfExists(portArchivePath);
    addArchivePathIfExists(baseArchivePath);

    if (!std::filesystem::exists(portArchivePath)) {
        std::cerr << "[ERROR] Missing BlueFeather.o2r. BlueFeather requires its port archive and will not fall back to in-exe assets." << std::endl;
        return 1;
    }

    if (!std::filesystem::exists(baseArchivePath)) {
        std::cerr << "[ERROR] Missing hm64.o2r. BlueFeather is archive-only and will not fall back to a raw ROM." << std::endl;
        return 1;
    }

    std::cout << "[INFO] Total asset sources: " << archivePaths.size() << std::endl;
    
    try {
        std::cout << "[DEBUG] Creating libultraship bootstrap context..." << std::endl;

        auto context = Ship::Context::CreateUninitializedInstance(
            "BlueFeather",           // Full app name
            "bluefeather",           // Short app name
            configFileName           // Config file (just the name)
        );

        if (!context) {
            std::cerr << "[ERROR] Failed to create libultraship bootstrap context!" << std::endl;
            return 1;
        }

        if (!context->InitLogging()) {
            std::cerr << "[ERROR] Failed to initialize libultraship logging!" << std::endl;
            return 1;
        }

        if (!context->InitConfiguration()) {
            std::cerr << "[ERROR] Failed to initialize libultraship config!" << std::endl;
            std::cerr << "[HINT] Make sure bluefeather.json exists in the app bundle's Resources folder" << std::endl;
            return 1;
        }

        if (!context->InitConsoleVariables()) {
            std::cerr << "[ERROR] Failed to initialize libultraship console variables!" << std::endl;
            return 1;
        }

        std::cout << "[DEBUG] Creating window and control deck..." << std::endl;

        auto window = std::make_shared<Fast::Fast3dWindow>();
        auto controlDeck = std::make_shared<LUS::ControlDeck>();

        std::cout << "[DEBUG] Initializing libultraship context..." << std::endl;

        if (!context->Init(
                archivePaths,            // Archive paths (assets folder)
                {},                      // Valid hashes (empty = accept all)
                1,                       // Reserved thread count
                Ship::AudioSettings{},   // Default audio settings
                window,
                controlDeck)) {
            std::cerr << "[ERROR] Failed to initialize libultraship context!" << std::endl;
            return 1;
        }

        std::cout << "[DEBUG] Context initialized, checking window..." << std::endl;

        // Verify critical components were initialized
        if (!context->GetWindow()) {
            std::cerr << "[ERROR] Window initialization failed!" << std::endl;
            return 1;
        }
        
        std::cout << "[DEBUG] Window OK, checking ControlDeck..." << std::endl;
        
        if (!context->GetControlDeck()) {
            std::cerr << "[ERROR] ControlDeck initialization failed!" << std::endl;
            return 1;
        }

        std::cout << "[INFO] Libultraship context created successfully" << std::endl;

        std::cout << "[DEBUG] About to create HM64Game..." << std::endl;

        // Initialize and run the game
        HM64Game game(context);
        
        std::cout << "[DEBUG] About to call game.Init()..." << std::endl;
        
        if (!game.Init()) {
            std::cerr << "[ERROR] Failed to initialize HM64 game!" << std::endl;
            return 1;
        }

        std::cout << "[DEBUG] About to call game.Run()..." << std::endl;
        game.Run();

        std::cout << "[INFO] BlueFeather shutting down" << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "[ERROR] Exception caught: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "[ERROR] Unknown exception caught!" << std::endl;
        return 1;
    }

    return 0;
}
