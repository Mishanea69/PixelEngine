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

    ctx.inputManager.BindKey("move_right", SDL_SCANCODE_RIGHT);
    ctx.inputManager.BindKey("move_left", SDL_SCANCODE_LEFT);
    ctx.inputManager.BindKey("move_up", SDL_SCANCODE_UP);
    ctx.inputManager.BindKey("move_down", SDL_SCANCODE_DOWN);
    // Check double binding
    ctx.inputManager.BindKey("move_right", "D");
    ctx.inputManager.BindKey("move_left", "A");
    ctx.inputManager.BindKey("move_up", "W");
    ctx.inputManager.BindKey("move_down", "s"); // lower case
    // check same key binded
    ctx.inputManager.BindKey("move_down", "S");
    
}

void RunningState::OnExit(EngineContext& ctx) {
    // Cleanup code for the running state
    SDL_Log("Engine has stopped running.");
}

void RunningState::Update(EngineContext& ctx, double dt) {
    // Update logic for the running state

    if (ctx.inputManager.IsActionHeld("move_right")) {
        ctx.renderer.GetCamera().x += 20.0f * dt; // Move camera to the right at 5 units per second
    }
    if (ctx.inputManager.IsActionHeld("move_left")) {
        ctx.renderer.GetCamera().x -= 20.0f * dt; // Move camera to the left at 5 units per second
    }
    if (ctx.inputManager.IsActionHeld("move_up")) {
        ctx.renderer.GetCamera().y -= 20.0f * dt; // Move camera up at 5 units per second
    }
    if (ctx.inputManager.IsActionHeld("move_down")) {
        ctx.renderer.GetCamera().y += 20.0f * dt; // Move camera down at 5 units per second
    }
}

void RunningState::Render(EngineContext& ctx, double alpha) {
    // Render logic for the running state
    ctx.renderer.DrawSprite(heartSprite);
}