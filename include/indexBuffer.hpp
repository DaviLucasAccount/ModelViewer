#ifndef INDEXBUFFER_HPP
#define INDEXBUFFER_HPP

#include <glad/glad.h>

class IndexBuffer {
  public:
    GLuint ID;

    IndexBuffer(const void *data, GLsizeiptr size);
    ~IndexBuffer();

    void Bind();
    void Unbind();
};

#endif
