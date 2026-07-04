#include <core/Engine.h>
#include <core/states/States.h>

bool Engine::Init(const char* title, int width, int height) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL_Init error: %s", SDL_GetError());
        return false;
    }

    window = WindowPtr(SDL_CreateWindow(title, width, height, SDL_WINDOW_RESIZABLE));
    if (!window) {
        SDL_Log("SDL_CreateWindow error: %s", SDL_GetError());
        SDL_Quit();
        return false;
    }

    if (!renderer.Init(window.get())) {
        SDL_Log("Renderer initialization failed");
        SDL_Quit();
        return false;
    }

    if (!assetManager.Init()) {
        SDL_Log("AssetManager initialization failed");
        SDL_Quit();
        return false;
    }
    textureManager.Init(renderer.Get(), &assetManager);

    // Bind the fullscreen toggle action to F11
    inputManager.BindKey("toggle_fullscreen", SDL_SCANCODE_F11);

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
        //Check for input events
        inputManager.Update();

        // Update and render
        double frameTime = time.Tick();
        if(frameTime > 0.25) frameTime = 0.25;
        accumulator += frameTime;

        fpsTimer += frameTime;
        fpsFrameCount++;
        if(fpsTimer >= 1.0){
            // SDL_Log("FPS: %d", fpsFrameCount);
            fpsFrameCount = 0;
            fpsTimer -= 1.0;
        }

        Update(frameTime);
        while(accumulator >= targetFrameTime){
            accumulator -= targetFrameTime;
            FixedUpdate(targetFrameTime);
        }

        double alpha = accumulator / targetFrameTime;
        Render(alpha);
    }

    ChangeState(std::make_unique<ShutDownState>());
}

void Engine::ChangeState(GameStatePtr newState) {
    if(currentState) currentState->OnExit(ctx);
    if(newState) newState->OnEnter(ctx);
    currentState = std::move(newState);
}

void Engine::Update(double dt) {
    currentState->Update(ctx, dt);
    
    if (inputManager.IsActionPressed("toggle_fullscreen")) {
        ToggleFullscreen();
    }
}

void Engine::FixedUpdate(double dt) {
    currentState->FixedUpdate(ctx, dt);
}

void Engine::Render(double alpha) {
    renderer.Clear();
    currentState->Render(ctx, alpha);
    renderer.Present();
}

void Engine::ToggleFullscreen() {
    isFullscreen = !isFullscreen;
    if (!SDL_SetWindowFullscreen(window.get(), isFullscreen)) {
        SDL_Log("SDL_SetWindowFullscreen error: %s", SDL_GetError());
    }
}

Engine::~Engine() {
    SDL_Quit();
}