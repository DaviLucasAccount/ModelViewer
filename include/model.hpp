#ifndef MODEL_HPP
#define MODEL_HPP

#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>

struct Vertex {
    glm::vec3 position;
    glm::vec3 color;
    glm::vec2 texCoords;
};
typedef GLuint Index;
typedef GLuint Texture;
struct MeshInfo {
    std::size_t count;
    std::size_t offset;
    std::size_t texture;
};

class Model {
  public:
    std::vector<Vertex> vertices;
    std::vector<Index> indices;
    std::vector<Texture> textures;
    std::vector<MeshInfo> meshes;

    Model(const char *name);
    ~Model();
};

#endif
