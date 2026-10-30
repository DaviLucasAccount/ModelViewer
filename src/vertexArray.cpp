#include <vector>

#include <glad/glad.h>

#include "vertexArray.hpp"

VertexArray::VertexArray() {
    glGenVertexArrays(1, &ID);
}
VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &ID);
}

void VertexArray::SetAttributes(std::vector<VertexArrayAttribute> attributes) {
    for (const VertexArrayAttribute attribute : attributes) {
        glVertexAttribPointer(
            attribute.index, attribute.size, attribute.type, attribute.normalized, attribute.stride, attribute.pointer
        );
        glEnableVertexAttribArray(attribute.index);
    }
}

void VertexArray::Bind() {
    glBindVertexArray(ID);
}
void VertexArray::Unbind() {
    glBindVertexArray(0);
}
