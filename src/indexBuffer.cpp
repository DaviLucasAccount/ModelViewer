#include <glad/glad.h>

#include "indexBuffer.hpp"

IndexBuffer::IndexBuffer() {
    glGenBuffers(1, &ID);
}
IndexBuffer::~IndexBuffer() {
    glDeleteBuffers(1, &ID);
}

void IndexBuffer::SetBufferSize(GLsizeiptr size) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
}
void IndexBuffer::SetBufferData(GLintptr offset, GLsizeiptr size, const void *data) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, data);
}

void IndexBuffer::Bind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}
void IndexBuffer::Unbind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
