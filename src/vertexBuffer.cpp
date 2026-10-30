#include <glad/glad.h>

#include "vertexBuffer.hpp"

VertexBuffer::VertexBuffer(const void *data, GLsizeiptr size) {
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ARRAY_BUFFER, ID);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}
VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(1, &ID);
}

void VertexBuffer::Bind() {
    glBindBuffer(GL_ARRAY_BUFFER, ID);
}
void VertexBuffer::Unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
