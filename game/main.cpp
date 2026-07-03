#include <SDL3/SDL_main.h>
#include <SDL3/SDL.h>
#include <memory>

bool running = true;

struct SDL_Destroyer {
    void operator()(SDL_Window* w) const { SDL_DestroyWindow(w); }
    void operator()(SDL_Renderer* r) const { SDL_DestroyRenderer(r); }
};
using WindowPtr = std::unique_ptr<SDL_Window, SDL_Destroyer>;
using RendererPtr = std::unique_ptr<SDL_Renderer, SDL_Destroyer>;

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    const char* title = "Pixel Engine";
    const int window_w = 800;
    const int window_h = 600;
    WindowPtr window = WindowPtr(SDL_CreateWindow(title, window_w, window_h, 0));
    RendererPtr renderer = RendererPtr(SDL_CreateRenderer(window.get(), nullptr));

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