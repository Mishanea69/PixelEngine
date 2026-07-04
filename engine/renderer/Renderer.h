#pragma once

#include <SDL3/SDL.h>
#include <renderer/Sprite.h>
#include <memory>

struct SdlRenderrerDestroyer {
    void operator()(SDL_Renderer* r) const { SDL_DestroyRenderer(r); }
};
typedef std::unique_ptr<SDL_Renderer, SdlRenderrerDestroyer> SdlRendererPtr;

class Renderer {
    SdlRendererPtr renderer;

public:
    Renderer() = default;
    ~Renderer() = default;

    bool Init(SDL_Window* window);
    SDL_Renderer* Get() const { return renderer.get(); }
    void Clear();
    void Present();
    void DrawSprite(const Sprite& sprite);
};