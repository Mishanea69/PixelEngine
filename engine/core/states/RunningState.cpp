#include <core/states/RunningState.h>
#include <core/EngineContext.h>
#include <SDL3/SDL.h>

void RunningState::OnEnter(EngineContext& ctx) {
    // Initialization code for the running state
    SDL_Log("Engine is running.");
    ctx.renderer.SetBackgroundColor(100, 100, 100, 255); // Set background color to gray

    heartSprite.texture = ctx.textureManager.LoadTexture("textures/heart.png");
    heartSprite.x = 0.0f;
    heartSprite.y = 0.0f;
}

void RunningState::OnExit(EngineContext& ctx) {
    // Cleanup code for the running state
    SDL_Log("Engine has stopped running.");
}

void RunningState::Update(EngineContext& ctx, double dt) {
    // Update logic for the running state
    ctx.inputManager.BindKey("move_right", SDL_SCANCODE_RIGHT);
    ctx.inputManager.BindKey("move_left", "A");

    if (ctx.inputManager.IsActionHeld("move_right")) {
        ctx.renderer.GetCamera().x += 20.0f * dt; // Move camera to the right at 5 units per second
    }
    if (ctx.inputManager.IsActionHeld("move_left")) {
        ctx.renderer.GetCamera().x -= 20.0f * dt; // Move camera to the left at 5 units per second
    }
}

void RunningState::Render(EngineContext& ctx, double alpha) {
    // Render logic for the running state
    ctx.renderer.DrawSprite(heartSprite);
}