#ifndef MODEL_HPP
#define MODEL_HPP

#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>

struct Vertex {
    glm::vec3 position;
    glm::vec3 color;
};
typedef GLuint Index;

class Model {
  public:
    std::vector<Vertex> vertices;
    std::vector<Index> indices;

    Model(const char *name);
};

#endif
