#include <glad/glad.h>

#include "vertexBuffer.hpp"

VertexBuffer::VertexBuffer() {
    glGenBuffers(1, &ID);
}
VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(1, &ID);
}

void VertexBuffer::SetBufferSize(GLsizeiptr size) {
    glBindBuffer(GL_ARRAY_BUFFER, ID);
    glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
}
void VertexBuffer::SetBufferData(GLintptr offset, GLsizeiptr size, const void *data) {
    glBindBuffer(GL_ARRAY_BUFFER, ID);
    glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
}

void VertexBuffer::Bind() {
    glBindBuffer(GL_ARRAY_BUFFER, ID);
}
void VertexBuffer::Unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
