#include <SDL3/SDL_main.h>
#include <core/Engine.h>

int main(int argc, char* argv[]) {

    Engine engine;
    if (!engine.Init("Pixel Engine", 960, 540)) {
        return 1;
    }

    engine.Run();
    
    return 0;
}