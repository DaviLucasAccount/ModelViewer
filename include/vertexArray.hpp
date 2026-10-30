#ifndef VERTEXARRAY_HPP
#define VERTEXARRAY_HPP

#include <vector>

#include <glad/glad.h>

struct VertexArrayAttribute {
    GLuint index;
    GLint size;
    GLenum type;
    GLboolean normalized;
    GLsizei stride;
    void *pointer;
};

class VertexArray {
  public:
    GLuint ID;

    VertexArray();
    ~VertexArray();

    void SetAttributes(std::vector<VertexArrayAttribute> attributes);

    void Bind();
    void Unbind();
};

#endif
