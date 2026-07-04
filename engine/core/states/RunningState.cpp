#include <core/states/RunningState.h>
#include <core/EngineContext.h>
#include <SDL3/SDL.h>

void RunningState::OnEnter(EngineContext& ctx) {
    // Initialization code for the running state
    SDL_Log("Engine is running.");
    ctx.renderer.SetBackgroundColor(100, 100, 100, 255); // Set background color to gray

    heart.sprite = Sprite{ ctx.textureManager.LoadTexture("textures/heart.png")};
    heart.transform.x = 400.0f;
    heart.transform.y = 300.0f;

    // Bind keys for movement actions
    ctx.inputManager.BindKey("move_right", SDL_SCANCODE_RIGHT);
    ctx.inputManager.BindKey("move_left", SDL_SCANCODE_LEFT);
    ctx.inputManager.BindKey("move_up", SDL_SCANCODE_UP);
    ctx.inputManager.BindKey("move_down", SDL_SCANCODE_DOWN);
    ctx.inputManager.BindKey("move_right", "D");
    ctx.inputManager.BindKey("move_left", "A");
    ctx.inputManager.BindKey("move_up", "W");
    ctx.inputManager.BindKey("move_down", "S"); 

    ctx.inputManager.BindKey("zoom_in", SDL_SCANCODE_EQUALS);
    ctx.inputManager.BindKey("zoom_out", SDL_SCANCODE_MINUS);

    tileMap.Load(ctx.assetManager, ctx.textureManager, ctx.renderer, "tilemaps/testmap/test-tilemap.tmj");
}

void RunningState::OnExit(EngineContext& ctx) {
    // Cleanup code for the running state
    SDL_Log("Engine has stopped running.");
}

void RunningState::Update(EngineContext& ctx, double dt) {
    // Update logic for the running state

    if (ctx.inputManager.IsActionPressed("zoom_in")) {
        ctx.renderer.GetCamera().SetZoom(ctx.renderer.GetCamera().zoom + 1.0f);
    }
    if (ctx.inputManager.IsActionPressed("zoom_out")) {
        ctx.renderer.GetCamera().SetZoom(ctx.renderer.GetCamera().zoom - 1.0f);
    }
}

void RunningState::FixedUpdate(EngineContext& ctx, double dt) {
    // Fixed update logic for the running state

    float moveSpeed = 50.0f;
    if (ctx.inputManager.IsActionHeld("move_right")) {
        heart.transform.x += moveSpeed * dt; 
    }
    if (ctx.inputManager.IsActionHeld("move_left")) {
        heart.transform.x -= moveSpeed * dt;
    }
    if (ctx.inputManager.IsActionHeld("move_up")) {
        heart.transform.y -= moveSpeed * dt;
    }
    if (ctx.inputManager.IsActionHeld("move_down")) {
        heart.transform.y += moveSpeed * dt;
    }

    ctx.renderer.GetCamera().Follow(heart.transform.x, heart.transform.y, dt, 5.0f);
}

void RunningState::Render(EngineContext& ctx, double alpha) {
    // Render logic for the running state
    tileMap.Render(ctx.renderer);

    if(heart.sprite)
        ctx.renderer.DrawSprite(*heart.sprite, heart.transform);
}