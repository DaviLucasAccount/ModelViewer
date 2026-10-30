#ifndef MODEL_HPP
#define MODEL_HPP

#include <vector>

#include <glad/glad.h>

#include "vertex.hpp"

class Model {
  public:
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;

    Model(const char *name);
};

#endif
