#pragma once

#include <SDL3/SDL.h>
#include <core/Time.h>
#include <core/GameState.h>
#include <core/EngineContext.h>
#include <renderer/Renderer.h>
#include <renderer/TextureManager.h>
#include <assets/AssetManager.h>
#include <memory>


struct SdlDestroyer {
    void operator()(SDL_Window* w) const { SDL_DestroyWindow(w); }
};
using WindowPtr = std::unique_ptr<SDL_Window, SdlDestroyer>;
using GameStatePtr = std::unique_ptr<GameState>;


class Engine {
    bool running = false;
    GameStatePtr currentState;
    WindowPtr window;
    Time time;
    static constexpr double targetFrameTime = 1.0 / 60.0; // Target frame time for 60 FPS
    
    Renderer renderer;
    TextureManager textureManager;
    AssetManager assetManager;
    EngineContext ctx;

    void Update(double dt);
    void Render(double alpha = 1.0);
    void ChangeState(GameStatePtr newState);

public:
    Engine() : ctx{renderer, textureManager, assetManager} {}
    ~Engine();

    bool Init(const char* title, int width, int height);
    void Run();
};