#include <format>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include <SDL3/SDL.h>
#include <glad/glad.h>

#include "appContext.hpp"
#include "application.hpp"
#include "camera.hpp"
#include "indexBuffer.hpp"
#include "model.hpp"
#include "shader.hpp"
#include "vertexArray.hpp"
#include "vertexBuffer.hpp"

Application::Application(const char *name) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        constexpr std::string_view err = "SDL_Init failed: {}";
        throw std::runtime_error(std::format(err, SDL_GetError()));
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

    m_context.window = SDL_CreateWindow("ModelViewer", 640, 360, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if (!m_context.window) {
        constexpr std::string_view err = "SDL_CreateWindow failed: {}";
        throw std::runtime_error(std::format(err, SDL_GetError()));
    }

    SDL_SetWindowPosition(m_context.window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

    m_context.glcontext = SDL_GL_CreateContext(m_context.window);
    if (!m_context.glcontext) {
        constexpr std::string_view err = "SDL_GL_CreateContext failed: {}";
        throw std::runtime_error(std::format(err, SDL_GetError()));
    }

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
        throw std::runtime_error("gladLoadGLLoader failed");

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    // Model
    m_context.camera = std::make_unique<Camera>();
    m_context.camera->position.z += 10;

    const char *basepath = SDL_GetBasePath();
    if (!basepath) {
        constexpr std::string_view err = "SDL_GetBasePath failed: {}";
        throw std::runtime_error(std::format(err, SDL_GetError()));
    }

    std::string fullpath = std::format("{}resources/models/cube.obj", basepath);
    m_context.model = std::make_unique<Model>(name ? name : fullpath.c_str());

    // OpenGL
    m_context.shader = std::make_unique<Shader>("default.vert", "default.frag");

    m_context.VAO = std::make_unique<VertexArray>();
    m_context.VAO->Bind();

    GLsizeiptr vsize = m_context.model->vertices.size() * sizeof(Vertex);
    m_context.VBO = std::make_unique<VertexBuffer>();
    m_context.VBO->SetBufferSize(vsize);
    m_context.VBO->SetBufferData(0, vsize, m_context.model->vertices.data());

    GLsizeiptr isize = m_context.model->indices.size() * sizeof(Index);
    m_context.EBO = std::make_unique<IndexBuffer>();
    m_context.EBO->SetBufferSize(isize);
    m_context.EBO->SetBufferData(0, isize, m_context.model->indices.data());

    m_context.VAO->SetAttribute(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, position));
    m_context.VAO->SetAttribute(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, color));
    m_context.VAO->SetAttribute(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, texCoords));

    m_context.VAO->Unbind();
    m_context.VBO->Unbind();
    m_context.EBO->Unbind();
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
        m_context.camera->Input(&event);
        if (event.type == SDL_EVENT_QUIT) {
            running = false;
        } else if (event.type == SDL_EVENT_WINDOW_RESIZED) {
            int windowW = event.window.data1;
            int windowH = event.window.data2;
            glViewport(0, 0, windowW, windowH);

            if (windowH > 0) {
                float aspect = windowW / 1.0f / windowH;
                m_context.camera->aspect = aspect;
            }
        }
    }
}
void Application::Update() {
    Uint64 currTick = SDL_GetTicks();
    Uint64 deltaTime = currTick - m_context.lastTick;
    m_context.lastTick = currTick;

    m_context.camera->Update(deltaTime);
}
void Application::Render() {
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 mvp = m_context.camera->GetMVP(model);

    glClearColor(0.04f, 0.04f, 0.04f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_context.shader->Bind();
    m_context.shader->SetUniformMat4("uMVP", mvp);
    m_context.shader->SetUniform1i("uTex0", 0);

    m_context.VAO->Bind();

    for (const auto &mesh : m_context.model->meshes) {
        bool hasTexture = (mesh.texture < m_context.model->textures.size());
        m_context.shader->SetUniform1i("uHasTexture", hasTexture ? 1 : 0);

        if (hasTexture) {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, m_context.model->textures[mesh.texture]);
        }

        glDrawElements(GL_TRIANGLES, (GLsizei)mesh.count, GL_UNSIGNED_INT, (void *)(mesh.offset * sizeof(Index)));
    }

    SDL_GL_SwapWindow(m_context.window);
    SDL_Delay(16);
}
