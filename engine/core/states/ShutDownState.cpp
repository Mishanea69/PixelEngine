#include <core/states/ShutDownState.h>
#include <SDL3/SDL.h>   

void ShutDownState::OnEnter() {
    // Initialization code for the shutdown state
    SDL_Log("Engine is shutting down...");
}

void ShutDownState::OnExit() {
    // Cleanup code for the shutdown state
    SDL_Log("Engine has shut down.");
}

void ShutDownState::Update(double dt) {
    // Update logic for the shutdown state
}

void ShutDownState::Render(SDL_Renderer* renderer, double alpha) {
    // Render logic for the shutdown state
}