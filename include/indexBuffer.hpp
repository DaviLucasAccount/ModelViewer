#ifndef INDEXBUFFER_HPP
#define INDEXBUFFER_HPP

#include <glad/glad.h>

class IndexBuffer {
  public:
    GLuint ID;

    IndexBuffer();
    ~IndexBuffer();

    void SetBufferSize(GLsizeiptr size);
    void SetBufferData(GLintptr offset, GLsizeiptr size, const void *data);

    void Bind();
    void Unbind();
};

#endif
