#include <format>
#include <stdexcept>

#include <SDL3/SDL.h>
#include <glad/glad.h>

#include "appContext.hpp"
#include "application.hpp"
#include "shader.hpp"

Application::Application() {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        constexpr std::string_view err = "SDL_Init failed: {}";
        throw std::runtime_error(std::format(err, SDL_GetError()));
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    m_context.window = SDL_CreateWindow("ModelViewer", 640, 360, SDL_WINDOW_OPENGL);
    if (!m_context.window) {
        constexpr std::string_view err = "SDL_CreateWindow failed: {}";
        throw std::runtime_error(std::format(err, SDL_GetError()));
    }

    m_context.glcontext = SDL_GL_CreateContext(m_context.window);
    if (!m_context.glcontext) {
        constexpr std::string_view err = "SDL_GL_CreateContext failed: {}";
        throw std::runtime_error(std::format(err, SDL_GetError()));
    }

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
        throw std::runtime_error("gladLoadGLLoader failed");

    SDL_SetWindowPosition(m_context.window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

    // Shaders
    Shader shader("default.vert", "default.frag");
    SDL_Log("%u", shader.ID);
}
Application::~Application() {
    SDL_GL_DestroyContext(m_context.glcontext);
    SDL_DestroyWindow(m_context.window);

    SDL_Quit();
}

void Application::Tick() {
    Input();
    Update();
    Render();
}
void Application::Input() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT)
            running = false;
    }
}
void Application::Update() {}
void Application::Render() {
    glClearColor(0.04f, 0.04f, 0.04f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    SDL_GL_SwapWindow(m_context.window);
    SDL_Delay(16);
}
