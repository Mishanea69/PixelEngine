#pragma once

#include <SDL3/SDL.h>

class Time{
    Uint64 frequency;
    Uint64 lastCounter;

public:
    Time();
    ~Time() = default;

    double Tick();
};