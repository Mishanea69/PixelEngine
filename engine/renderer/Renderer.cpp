#include <renderer/Renderer.h>

bool Renderer::Init(SDL_Window* window) {
    renderer = SdlRendererPtr(SDL_CreateRenderer(window, nullptr));
    if (!renderer) {
        SDL_Log("SDL_CreateRenderer error: %s", SDL_GetError());
        SDL_Quit();
        return false;
    }
    SDL_SetRenderLogicalPresentation(renderer.get(), LogicalWidth, LogicalHeight, SDL_LOGICAL_PRESENTATION_INTEGER_SCALE);


    return true;
}

void Renderer::Clear() {
    SDL_RenderClear(renderer.get());
}

void Renderer::Present() {
    SDL_RenderPresent(renderer.get());
}

void Renderer::SetBackgroundColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    SDL_SetRenderDrawColor(renderer.get(), r, g, b, a);
}

void Renderer::DrawSprite(const Sprite& sprite) {
    if (!sprite.texture) return;

    SDL_FRect dest{
        sprite.x - camera.x,
        sprite.y - camera.y,
        static_cast<float>(sprite.texture->w),
        static_cast<float>(sprite.texture->h)
    };
    
    SDL_RenderTexture(renderer.get(), sprite.texture, nullptr, &dest);
}