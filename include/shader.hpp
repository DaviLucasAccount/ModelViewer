#ifndef SHADER_HPP
#define SHADER_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>

class Shader {
  private:
    char *GetSource(const char *name);
    void CompileShader(GLuint shaderID);
    void LinkProgram(GLuint programID);

  public:
    GLuint ID;

    Shader(const char *vertexName, const char *fragmentName);
    ~Shader();

    GLint GetUniformLocation(const char *name);
    void SetUniformMat4(const char *name, glm::mat4 value);
    void SetUniform1i(const char *name, GLint value);

    void Bind();
    void Unbind();
};

#endif
