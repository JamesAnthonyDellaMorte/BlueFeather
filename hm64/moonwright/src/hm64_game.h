// HM64 PC Port - Game Class

#ifndef HM64_GAME_H
#define HM64_GAME_H

#include <ship/Context.h>
#include <memory>
#include <atomic>
#include <thread>

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
    bool m_gameThreadStarted;
    uint32_t m_hostFrameCounter;
    std::thread m_gameThread;

    bool InitWindow();
    bool InitGraphics();
    bool InitAudio();
    bool InitInput();
    void StartGameThread();
};

#endif // HM64_GAME_H
