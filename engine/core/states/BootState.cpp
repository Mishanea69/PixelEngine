#include <core/states/BootState.h>
#include <SDL3/SDL.h>

void BootState::OnEnter(EngineContext& ctx) {
    // Initialization code for the boot state
    SDL_Log("Engine is booting up...");
}

void BootState::OnExit(EngineContext& ctx) {
    // Cleanup code for the boot state
    SDL_Log("Engine booted successfully.");
}

void BootState::Update(EngineContext& ctx, double dt) {
    // Update logic for the boot state
}

void BootState::Render(EngineContext& ctx, double alpha) {
    // Render logic for the boot state
}