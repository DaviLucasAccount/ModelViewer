#ifndef VERTEXARRAY_HPP
#define VERTEXARRAY_HPP

#include <glad/glad.h>

class VertexArray {
  public:
    GLuint ID;

    VertexArray();
    ~VertexArray();

    void SetAttribute(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer);

    void Bind();
    void Unbind();
};

#endif
