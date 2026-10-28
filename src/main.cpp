#include <cstdlib>
#include <stdexcept>

#include <SDL3/SDL.h>

#include "application.hpp"

int main(int argc, char *argv[]) {
    try {
        Application app;
        while (app.running)
            app.Tick();
    } catch (const std::exception &e) {
        SDL_Log(e.what());
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
