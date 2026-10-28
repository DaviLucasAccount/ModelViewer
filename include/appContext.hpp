#ifndef APPCONTEXT_HPP
#define APPCONTEXT_HPP

#include <SDL3/SDL.h>

struct AppContext {
    SDL_Window *window = nullptr;
    SDL_GLContext glcontext = nullptr;
};

#endif
