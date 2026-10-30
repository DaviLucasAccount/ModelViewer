#include <format>
#include <stdexcept>
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <glad/glad.h>

#include "model.hpp"
#include "vertex.hpp"

Model::Model(const char *name) {
    Assimp::Importer importer;

    const aiScene *scene = importer.ReadFile(name, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);

    if (!scene) {
        constexpr std::string_view err = "Assimp::Importer::ReadFile failed: {}";
        throw std::runtime_error(std::format(err, importer.GetErrorString()));
    }

    std::size_t numVertices = 0;
    std::size_t numIndices = 0;
    for (std::size_t i = 0; i < scene->mNumMeshes; i++) {
        numVertices += scene->mMeshes[i]->mNumVertices;
        numIndices += scene->mMeshes[i]->mNumFaces * 3;
    }

    vertices.reserve(numVertices);
    indices.reserve(numIndices);

    unsigned int vertexOffset = 0;

    for (std::size_t i = 0; i < scene->mNumMeshes; i++) {
        aiMesh *mesh = scene->mMeshes[i];
        for (std::size_t j = 0; j < mesh->mNumVertices; j++) {
            Vertex vertex;

            vertex.position.x = mesh->mVertices[j].x;
            vertex.position.y = mesh->mVertices[j].y;
            vertex.position.z = mesh->mVertices[j].z;

            if (mesh->HasVertexColors(0)) {
                vertex.color.r = mesh->mColors[0][j].r;
                vertex.color.g = mesh->mColors[0][j].g;
                vertex.color.b = mesh->mColors[0][j].b;
            } else {
                vertex.color.r = 1.0f;
                vertex.color.g = 1.0f;
                vertex.color.b = 1.0f;
            }

            vertices.push_back(vertex);
        }

        for (std::size_t j = 0; j < mesh->mNumFaces; j++) {
            aiFace face = mesh->mFaces[j];
            for (std::size_t k = 0; k < face.mNumIndices; k++) {
                indices.push_back(face.mIndices[k] + vertexOffset);
            }
        }

        vertexOffset += mesh->mNumVertices;
    }
}
