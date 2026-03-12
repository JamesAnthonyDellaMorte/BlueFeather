#include "BlueFeatherUI.h"

#include <algorithm>
#include <memory>

#include <imgui.h>
#include <spdlog/spdlog.h>

#include <libultraship/bridge/consolevariablebridge.h>
#include <ship/Context.h>
#include <ship/window/Window.h>
#include <ship/window/gui/Gui.h>
#include <ship/window/gui/GuiMenuBar.h>
#include <ship/window/gui/GuiWindow.h>

namespace {
constexpr const char* CVAR_MENU_BAR_OPEN = "gOpenMenuBar";
constexpr const char* CVAR_GAME_SPEED = "gGameSpeed";
constexpr const char* CVAR_GAME_PAUSED = "gGamePaused";
constexpr const char* CVAR_GAME_STEP_FRAME = "gGameStepFrame";
constexpr const char* CVAR_LOG_LEVEL = "gDeveloperTools.LogLevel";
constexpr int32_t DEFAULT_GAME_SPEED = 100;
constexpr int32_t DEFAULT_LOG_LEVEL = static_cast<int32_t>(spdlog::level::warn);

int32_t ClampLogLevel(int32_t level) {
    return std::clamp(level, static_cast<int32_t>(spdlog::level::trace), static_cast<int32_t>(spdlog::level::off));
}

void SaveConsoleVariables() {
    auto context = Ship::Context::GetInstance();
    if (context == nullptr || context->GetWindow() == nullptr || context->GetWindow()->GetGui() == nullptr) {
        return;
    }

    context->GetWindow()->GetGui()->SaveConsoleVariablesNextFrame();
}

void ApplyConfiguredLogLevel() {
    auto context = Ship::Context::GetInstance();
    if (context == nullptr || context->GetLogger() == nullptr) {
        return;
    }

    const auto level = static_cast<spdlog::level::level_enum>(ClampLogLevel(CVarGetInteger(CVAR_LOG_LEVEL, DEFAULT_LOG_LEVEL)));
    context->GetLogger()->set_level(level);
}

void SetGameSpeed(int32_t speedPercent) {
    CVarSetInteger(CVAR_GAME_SPEED, std::clamp(speedPercent, 50, 400));
    SaveConsoleVariables();
}

void SetPaused(bool paused) {
    CVarSetInteger(CVAR_GAME_PAUSED, paused ? 1 : 0);
    SaveConsoleVariables();
}

void RequestSingleFrameAdvance() {
    CVarSetInteger(CVAR_GAME_STEP_FRAME, 1);
}

void SetLogLevel(int32_t level) {
    CVarSetInteger(CVAR_LOG_LEVEL, ClampLogLevel(level));
    ApplyConfiguredLogLevel();
    SaveConsoleVariables();
}

void DrawWindowToggle(const char* label, const char* windowName) {
    auto gui = Ship::Context::GetInstance()->GetWindow()->GetGui();
    auto guiWindow = gui != nullptr ? gui->GetGuiWindow(windowName) : nullptr;
    if (guiWindow == nullptr) {
        ImGui::BeginDisabled();
        ImGui::MenuItem(label, nullptr, false, false);
        ImGui::EndDisabled();
        return;
    }

    const bool isVisible = guiWindow->IsVisible();
    if (ImGui::MenuItem(label, nullptr, isVisible)) {
        guiWindow->ToggleVisibility();
        SaveConsoleVariables();
    }
}

void DrawSpeedMenu() {
    struct SpeedOption {
        const char* Label;
        int32_t Percent;
    };

    static constexpr SpeedOption kSpeedOptions[] = {
        { "0.5x", 50 },
        { "1x", 100 },
        { "1.5x", 150 },
        { "2x", 200 },
        { "3x", 300 },
        { "4x", 400 },
    };
    const int32_t currentSpeed = std::clamp(CVarGetInteger(CVAR_GAME_SPEED, DEFAULT_GAME_SPEED), 50, 400);

    for (const auto& speed : kSpeedOptions) {
        if (ImGui::MenuItem(speed.Label, nullptr, currentSpeed == speed.Percent)) {
            SetGameSpeed(speed.Percent);
        }
    }
}

void DrawLogLevelMenu() {
    struct LogLevelLabel {
        const char* Label;
        int32_t Level;
    };

    static constexpr LogLevelLabel kLogLevels[] = {
        { "Warn", static_cast<int32_t>(spdlog::level::warn) },
        { "Info", static_cast<int32_t>(spdlog::level::info) },
        { "Debug", static_cast<int32_t>(spdlog::level::debug) },
        { "Trace", static_cast<int32_t>(spdlog::level::trace) },
        { "Error", static_cast<int32_t>(spdlog::level::err) },
        { "Off", static_cast<int32_t>(spdlog::level::off) },
    };

    const int32_t currentLevel = ClampLogLevel(CVarGetInteger(CVAR_LOG_LEVEL, DEFAULT_LOG_LEVEL));
    for (const auto& option : kLogLevels) {
        if (ImGui::MenuItem(option.Label, nullptr, currentLevel == option.Level)) {
            SetLogLevel(option.Level);
        }
    }
}

class BlueFeatherMenuBar : public Ship::GuiMenuBar {
  public:
    using Ship::GuiMenuBar::GuiMenuBar;

  protected:
    void DrawElement() override {
        auto context = Ship::Context::GetInstance();
        auto window = context != nullptr ? context->GetWindow() : nullptr;

        if (!ImGui::BeginMenuBar()) {
            return;
        }

        if (ImGui::BeginMenu("Game")) {
            const bool isPaused = CVarGetInteger(CVAR_GAME_PAUSED, 0) != 0;
            if (ImGui::MenuItem("Pause", nullptr, isPaused)) {
                SetPaused(!isPaused);
            }

            if (ImGui::MenuItem("Step Frame", nullptr, false, isPaused)) {
                RequestSingleFrameAdvance();
            }

            if (ImGui::BeginMenu("Speed")) {
                DrawSpeedMenu();
                ImGui::EndMenu();
            }

            if (window != nullptr && ImGui::MenuItem("Fullscreen", nullptr, window->IsFullscreen())) {
                window->ToggleFullscreen();
            }

            ImGui::Separator();

            if (ImGui::MenuItem("Exit")) {
                window->Close();
            }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Tools")) {
            DrawWindowToggle("Stats", "Stats");
            DrawWindowToggle("Console", "Console");
            DrawWindowToggle("Input Editor", "Input Editor");
            DrawWindowToggle("Graphics Debugger", "GfxDebuggerWindow");
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Debug")) {
            if (ImGui::BeginMenu("Log Level")) {
                DrawLogLevelMenu();
                ImGui::EndMenu();
            }
            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
    }

    void InitElement() override {
    }

    void UpdateElement() override {
    }
};
} // namespace

void BlueFeatherSetupGuiElements() {
    auto context = Ship::Context::GetInstance();
    if (context == nullptr || context->GetWindow() == nullptr || context->GetWindow()->GetGui() == nullptr) {
        return;
    }

    CVarRegisterInteger(CVAR_GAME_SPEED, DEFAULT_GAME_SPEED);
    CVarRegisterInteger(CVAR_GAME_PAUSED, 0);
    CVarRegisterInteger(CVAR_GAME_STEP_FRAME, 0);
    CVarRegisterInteger(CVAR_LOG_LEVEL, DEFAULT_LOG_LEVEL);
    ApplyConfiguredLogLevel();

    auto gui = context->GetWindow()->GetGui();
    if (gui->GetMenuBar() == nullptr) {
        gui->SetMenuBar(std::make_shared<BlueFeatherMenuBar>(CVAR_MENU_BAR_OPEN, false));
    }
}
