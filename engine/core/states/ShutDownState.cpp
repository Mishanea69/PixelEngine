#include <core/states/ShutDownState.h>
#include <SDL3/SDL.h>   

void ShutDownState::OnEnter(EngineContext& ctx) {
    // Initialization code for the shutdown state
    SDL_Log("Engine is shutting down...");
}

void ShutDownState::OnExit(EngineContext& ctx) {
    // Cleanup code for the shutdown state
    SDL_Log("Engine has shut down.");
}

void ShutDownState::Update(EngineContext& ctx, double dt) {
    // Update logic for the shutdown state
}

void ShutDownState::FixedUpdate(EngineContext& ctx, double dt) {
    // Fixed update logic for the shutdown state
}

void ShutDownState::Render(EngineContext& ctx, double alpha) {
    // Render logic for the shutdown state
}