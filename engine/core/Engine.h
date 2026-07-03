#pragma once

#include <SDL3/SDL.h>
#include <core/Time.h>
#include <core/GameState.h>
#include <memory>


struct SdlDestroyer {
    void operator()(SDL_Window* w) const { SDL_DestroyWindow(w); }
    void operator()(SDL_Renderer* r) const { SDL_DestroyRenderer(r); }
};
using WindowPtr = std::unique_ptr<SDL_Window, SdlDestroyer>;
using RendererPtr = std::unique_ptr<SDL_Renderer, SdlDestroyer>;
using GameStatePtr = std::unique_ptr<GameState>;


class Engine {
    bool running = false;
    WindowPtr window;
    RendererPtr renderer;
    GameStatePtr currentState;
    Time time;
    static constexpr double targetFrameTime = 1.0 / 60.0; // Target frame time for 60 FPS

    void Update(double dt);
    void Render(double alpha = 1.0);
    void ChangeState(GameStatePtr newState);

public:
    Engine() = default;
    ~Engine();

    bool Init(const char* title, int width, int height);
    void Run();
};