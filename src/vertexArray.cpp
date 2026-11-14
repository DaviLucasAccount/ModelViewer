#include <glad/glad.h>

#include "vertexArray.hpp"

VertexArray::VertexArray() {
    glGenVertexArrays(1, &ID);
}
VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &ID);
}

void VertexArray::SetAttribute(
    GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer
) {
    glVertexAttribPointer(index, size, type, normalized, stride, pointer);
    glEnableVertexAttribArray(index);
}

void VertexArray::Bind() {
    glBindVertexArray(ID);
}
void VertexArray::Unbind() {
    glBindVertexArray(0);
}
