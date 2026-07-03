#include <SDL3/SDL_main.h>
#include <SDL3/SDL.h>
#include <memory>

void LogSDLError(const char* msg) {
    SDL_Log("%s error: %s", msg, SDL_GetError());
}


struct SdlDestroyer {
    void operator()(SDL_Window* w) const { SDL_DestroyWindow(w); }
    void operator()(SDL_Renderer* r) const { SDL_DestroyRenderer(r); }
};
using WindowPtr = std::unique_ptr<SDL_Window, SdlDestroyer>;
using RendererPtr = std::unique_ptr<SDL_Renderer, SdlDestroyer>;

int main(int argc, char* argv[]) {
    bool initialized = SDL_Init(SDL_INIT_VIDEO);
    if (!initialized) {
        LogSDLError("SDL_Init");
        return 1;
    }

    const char* title = "Pixel Engine";
    const int window_w = 800;
    const int window_h = 600;
    WindowPtr window = WindowPtr(SDL_CreateWindow(title, window_w, window_h, 0));
    if (!window) {
        LogSDLError("SDL_CreateWindow");
        SDL_Quit();
        return 1;
    }
    RendererPtr renderer = RendererPtr(SDL_CreateRenderer(window.get(), nullptr));
    if (!renderer) {
        LogSDLError("SDL_CreateRenderer");
        SDL_Quit();
        return 1;
    }

    bool running = true;
    while(running){
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_EVENT_QUIT){
                running = false;
            }
        }

        // Rendering code:
        SDL_SetRenderDrawColor(renderer.get(), 100, 0, 255, 255);
        SDL_RenderClear(renderer.get());
        SDL_RenderPresent(renderer.get());

    }

    SDL_Quit();

    return 0;
}