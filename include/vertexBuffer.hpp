#ifndef VERTEXBUFFER_HPP
#define VERTEXBUFFER_HPP

#include <glad/glad.h>

class VertexBuffer {
  public:
    GLuint ID;

    VertexBuffer();
    ~VertexBuffer();

    void SetBufferSize(GLsizeiptr size);
    void SetBufferData(GLintptr offset, GLsizeiptr size, const void *data);

    void Bind();
    void Unbind();
};

#endif
