#include <core/states/RunningState.h>
#include <core/EngineContext.h>
#include <renderer/Renderer.h>
#include <renderer/TextureManager.h>
#include <SDL3/SDL.h>

void RunningState::OnEnter(EngineContext& ctx) {
    // Initialization code for the running state
    SDL_Log("Engine is running.");

    heartSprite.texture = ctx.textureManager.LoadTexture("textures/heart.png");
    heartSprite.x = 100.0f;
    heartSprite.y = 100.0f;
}

void RunningState::OnExit(EngineContext& ctx) {
    // Cleanup code for the running state
    SDL_Log("Engine has stopped running.");
}

void RunningState::Update(EngineContext& ctx, double dt) {
    // Update logic for the running state
}

void RunningState::Render(EngineContext& ctx, double alpha) {
    // Render logic for the running state
    ctx.renderer.DrawSprite(heartSprite);
}