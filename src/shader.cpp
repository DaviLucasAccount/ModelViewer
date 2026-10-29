#include <format>
#include <stdexcept>
#include <string>

#include <SDL3/SDL.h>
#include <glad/glad.h>

#include "shader.hpp"

char *Shader::GetSource(const char *name) {
    const char *basepath = SDL_GetBasePath();
    if (!basepath) {
        constexpr std::string_view err = "SDL_GetBasePath failed: {}";
        throw std::runtime_error(std::format(err, SDL_GetError()));
    }

    std::string fullpath = std::format("{}resources/shaders/{}", basepath, name);
    void *source = SDL_LoadFile(fullpath.c_str(), nullptr);
    if (!source) {
        constexpr std::string_view err = "SDL_LoadFile failed: {}";
        throw std::runtime_error(std::format(err, SDL_GetError()));
    }

    return (char *)source;
}
void Shader::CompileShader(GLuint shaderID) {
    glCompileShader(shaderID);

    GLint success;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLint logLength = 0;
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logLength);

        std::string infoLog(logLength, '\0');
        glGetShaderInfoLog(shaderID, logLength, nullptr, infoLog.data());

        constexpr std::string_view err = "glCompileShader failed: {}";
        throw std::runtime_error(std::format(err, infoLog));
    }
}
void Shader::LinkProgram(GLuint programID) {
    glLinkProgram(programID);

    GLint success;
    glGetProgramiv(programID, GL_LINK_STATUS, &success);
    if (!success) {
        GLint logLength = 0;
        glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &logLength);

        std::string infoLog(logLength, '\0');
        glGetProgramInfoLog(programID, logLength, nullptr, infoLog.data());

        constexpr std::string_view err = "glLinkProgram failed: {}";
        throw std::runtime_error(std::format(err, infoLog));
    }
}

Shader::Shader(const char *vertexName, const char *fragmentName) {
    char *vertexSource = GetSource(vertexName);
    char *fragmentSource = GetSource(fragmentName);

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, nullptr);
    CompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
    CompileShader(fragmentShader);

    SDL_free(vertexSource);
    SDL_free(fragmentSource);

    ID = glCreateProgram();

    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    LinkProgram(ID);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}
Shader::~Shader() {
    glDeleteProgram(ID);
}

void Shader::Bind() {
    glUseProgram(ID);
}
void Shader::Unbind() {
    glUseProgram(0);
}
