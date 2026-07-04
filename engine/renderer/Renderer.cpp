#include <renderer/Renderer.h>

bool Renderer::Init(SDL_Window* window) {
    renderer = SdlRendererPtr(SDL_CreateRenderer(window, nullptr));
    if (!renderer) {
        SDL_Log("SDL_CreateRenderer error: %s", SDL_GetError());
        SDL_Quit();
        return false;
    }
    return true;
}

void Renderer::Clear() {
    SDL_RenderClear(renderer.get());
}

void Renderer::Present() {
    SDL_RenderPresent(renderer.get());
}

void Renderer::DrawSprite(const Sprite& sprite) {
    if (!sprite.texture) return;

    SDL_FRect dest{
        sprite.x,
        sprite.y,
        static_cast<float>(sprite.texture->w),
        static_cast<float>(sprite.texture->h)
    };
    
    SDL_RenderTexture(renderer.get(), sprite.texture, nullptr, &dest);
}