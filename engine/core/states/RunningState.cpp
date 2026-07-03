#include <core/states/RunningState.h>
#include <SDL3/SDL.h>

void RunningState::OnEnter() {
    // Initialization code for the running state
    SDL_Log("Engine is running.");
}

void RunningState::OnExit() {
    // Cleanup code for the running state
    SDL_Log("Engine has stopped running.");
}

void RunningState::Update(double dt) {
    // Update logic for the running state
}

void RunningState::Render(SDL_Renderer* renderer, double alpha) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}