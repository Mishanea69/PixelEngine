#include <core/states/BootState.h>
#include <SDL3/SDL.h>

void BootState::OnEnter() {
    // Initialization code for the boot state
    SDL_Log("Engine is booting up...");
}

void BootState::OnExit() {
    // Cleanup code for the boot state
    SDL_Log("Engine booted successfully.");
}

void BootState::Update(double dt) {
    // Update logic for the boot state
}

void BootState::Render(SDL_Renderer* renderer, double alpha) {
    // Render logic for the boot state
}