#pragma once

#include <SDL3/SDL.h>
#include <renderer/Sprite.h>
#include <renderer/Camera.h>
#include <memory>

struct SdlRenderrerDestroyer {
    void operator()(SDL_Renderer* r) const { SDL_DestroyRenderer(r); }
};
typedef std::unique_ptr<SDL_Renderer, SdlRenderrerDestroyer> SdlRendererPtr;

class Renderer {
    SdlRendererPtr renderer;
    Camera camera;
    static constexpr int LogicalWidth = 320;
    static constexpr int LogicalHeight = 180;

public:
    Renderer() = default;
    ~Renderer() = default;

    bool Init(SDL_Window* window);
    SDL_Renderer* Get() const { return renderer.get(); }
    Camera& GetCamera() { return camera;}
    
    void Clear();
    void Present();
    void SetBackgroundColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    void DrawSprite(const Sprite& sprite);
};