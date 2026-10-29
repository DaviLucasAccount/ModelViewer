#include <format>
#include <memory>
#include <stdexcept>

#include <SDL3/SDL.h>
#include <glad/glad.h>

#include "appContext.hpp"
#include "application.hpp"
#include "shader.hpp"
#include "vertex.hpp"

constexpr Vertex vertices[] = {
    {{-0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}}, // A
    {{0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}},  // B
    {{0.0f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}}    // C
};
constexpr GLuint indices[] = {0, 1, 2};

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

    // OpenGL
    m_context.shader = std::make_unique<Shader>("default.vert", "default.frag");

    glGenVertexArrays(1, &m_context.VAO);
    glGenBuffers(1, &m_context.VBO);
    glGenBuffers(1, &m_context.EBO);

    glBindVertexArray(m_context.VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_context.VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_context.EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, color));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
Application::~Application() {
    glDeleteVertexArrays(1, &m_context.VAO);
    glDeleteBuffers(1, &m_context.VBO);
    glDeleteBuffers(1, &m_context.EBO);

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

    m_context.shader->Bind();
    glBindVertexArray(m_context.VAO);

    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

    SDL_GL_SwapWindow(m_context.window);
    SDL_Delay(16);
}
