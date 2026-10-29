#ifndef SHADER_HPP
#define SHADER_HPP

#include <glad/glad.h>

class Shader {
  private:
    char *GetSource(const char *name);
    void CompileShader(GLuint shaderID);
    void LinkProgram(GLuint programID);

  public:
    GLuint ID;

    Shader(const char *vertexName, const char *fragmentName);
    ~Shader();

    void Bind();
    void Unbind();
};

#endif
