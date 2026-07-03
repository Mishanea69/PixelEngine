#include <core/Engine.h>
#include <core/states/States.h>

bool Engine::Init(const char* title, int width, int height) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL_Init error: %s", SDL_GetError());
        return false;
    }

    window = WindowPtr(SDL_CreateWindow(title, width, height, 0));
    if (!window) {
        SDL_Log("SDL_CreateWindow error: %s", SDL_GetError());
        SDL_Quit();
        return false;
    }

    renderer = RendererPtr(SDL_CreateRenderer(window.get(), nullptr));
    if (!renderer) {
        SDL_Log("SDL_CreateRenderer error: %s", SDL_GetError());
        SDL_Quit();
        return false;
    }

    running = true;
    return true;
}

void Engine::Run() {
    ChangeState(std::make_unique<BootState>());
    ChangeState(std::make_unique<RunningState>());

    // FPS counter
    double fpsTimer = 0.0;
    int fpsFrameCount = 0;

    double accumulator = 0.0;
    while(running){
        // Event handling
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_EVENT_QUIT){
                running = false;
            }
        }

        // Update and render
        double frameTime = time.Tick();
        if(frameTime > 0.25) frameTime = 0.25;
        accumulator += frameTime;

        fpsTimer += frameTime;
        fpsFrameCount++;
        if(fpsTimer >= 1.0){
            SDL_Log("FPS: %d", fpsFrameCount);
            fpsFrameCount = 0;
            fpsTimer -= 1.0;
        }

        while(accumulator >= targetFrameTime){
            accumulator -= targetFrameTime;
            Update(targetFrameTime);
        }

        double alpha = accumulator / targetFrameTime;
        Render(alpha);
    }

    ChangeState(std::make_unique<ShutDownState>());
}

void Engine::ChangeState(GameStatePtr newState) {
    if(currentState) currentState->OnExit();
    if(newState) newState->OnEnter();
    currentState = std::move(newState);
}

void Engine::Update(double dt) {
    currentState->Update(dt);
}

void Engine::Render(double alpha) {
    currentState->Render(renderer.get(), alpha);
}

Engine::~Engine() {
    SDL_Quit();
}