// HM64 PC Port - Game Class

#ifndef HM64_GAME_H
#define HM64_GAME_H

#include <ship/Context.h>
#include <memory>
#include <atomic>

class HM64TitleRuntime;

class HM64Game {
public:
    HM64Game(std::shared_ptr<Ship::Context> context);
    ~HM64Game();

    bool Init();
    void Run();
    void Shutdown();

    bool IsRunning() const { return m_running; }

private:
    std::shared_ptr<Ship::Context> m_context;
    std::atomic<bool> m_running;
    bool m_initialized;
    std::unique_ptr<HM64TitleRuntime> m_titleRuntime;
    bool m_titleRuntimeActive;

    bool InitWindow();
    bool InitGraphics();
    bool InitAudio();
    bool InitInput();

    void Update();
    void Render();
};

#endif // HM64_GAME_H
