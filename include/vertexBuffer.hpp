#ifndef VERTEXBUFFER_HPP
#define VERTEXBUFFER_HPP

#include <glad/glad.h>

class VertexBuffer {
  public:
    GLuint ID;

    VertexBuffer(const void *data, GLsizeiptr size);
    ~VertexBuffer();

    void Bind();
    void Unbind();
};

#endif
