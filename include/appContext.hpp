#ifndef APPCONTEXT_HPP
#define APPCONTEXT_HPP

#include <memory>

#include <SDL3/SDL.h>
#include <glad/glad.h>

#include "shader.hpp"

struct AppContext {
    SDL_Window *window = nullptr;
    SDL_GLContext glcontext = nullptr;

    std::unique_ptr<Shader> shader = nullptr;
    GLuint VAO = 0;
    GLuint VBO = 0;
    GLuint EBO = 0;
};

#endif
