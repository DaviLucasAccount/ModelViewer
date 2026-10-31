#ifndef APPCONTEXT_HPP
#define APPCONTEXT_HPP

#include <memory>

#include <SDL3/SDL.h>
#include <glad/glad.h>

#include "camera.hpp"
#include "indexBuffer.hpp"
#include "model.hpp"
#include "shader.hpp"
#include "vertexArray.hpp"
#include "vertexBuffer.hpp"

struct AppContext {
    SDL_Window *window = nullptr;
    SDL_GLContext glcontext = nullptr;

    std::unique_ptr<Shader> shader = nullptr;
    std::unique_ptr<VertexArray> VAO = nullptr;
    std::unique_ptr<VertexBuffer> VBO = nullptr;
    std::unique_ptr<IndexBuffer> EBO = nullptr;

    std::unique_ptr<Camera> camera = nullptr;
    std::unique_ptr<Model> model = nullptr;
};

#endif
