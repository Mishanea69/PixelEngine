#include <core/Time.h>

Time::Time() {
    frequency = SDL_GetPerformanceFrequency();
    lastCounter = SDL_GetPerformanceCounter();
}

double Time::Tick() {
    Uint64 now = SDL_GetPerformanceCounter();
    Uint64 deltaCounter = now - lastCounter;
    lastCounter = now;

    return static_cast<double>(deltaCounter) / static_cast<double>(frequency);
}