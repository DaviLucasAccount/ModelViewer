#include <filesystem>
#include <format>
#include <stdexcept>
#include <vector>

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <glad/glad.h>
#include <glm/glm.hpp>

#include "model.hpp"

Model::Model(const char *name) {
    Assimp::Importer importer;

    const aiScene *scene =
        importer.ReadFile(name, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_FlipUVs);
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
    meshes.resize(scene->mNumMeshes);

    std::filesystem::path modelDir = std::filesystem::path(name).parent_path();
    for (std::size_t i = 0; i < scene->mNumMaterials; i++) {
        aiMaterial *material = scene->mMaterials[i];
        if (material->GetTextureCount(aiTextureType_DIFFUSE) <= 0)
            continue;

        aiString fullpath;
        if (material->GetTexture(aiTextureType_DIFFUSE, 0, &fullpath) == AI_FAILURE)
            continue;

        std::string texturePath = (modelDir / fullpath.C_Str()).string();
        SDL_Surface *surface = IMG_Load(texturePath.c_str());
        if (!surface) {
            constexpr std::string_view err = "IMG_Load failed: {}";
            throw std::runtime_error(std::format(err, SDL_GetError()));
        }

        SDL_Surface *formattedSurface = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_RGBA32);
        SDL_DestroySurface(surface);
        if (!formattedSurface) {
            constexpr std::string_view err = "SDL_ConvertSurface failed: {}";
            throw std::runtime_error(std::format(err, SDL_GetError()));
        }

        GLuint textureID;
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);

        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RGBA,
            formattedSurface->w,
            formattedSurface->h,
            0,
            GL_RGBA,
            GL_UNSIGNED_BYTE,
            formattedSurface->pixels
        );
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        SDL_DestroySurface(formattedSurface);
        textures.push_back(textureID);
    }

    unsigned int vertexOffset = 0;
    for (std::size_t i = 0; i < scene->mNumMeshes; i++) {
        aiMesh *mesh = scene->mMeshes[i];

        meshes[i].offset = indices.size();
        meshes[i].count = mesh->mNumFaces * 3;
        meshes[i].texture = mesh->mMaterialIndex < textures.size() ? mesh->mMaterialIndex : 0;

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

            if (mesh->HasTextureCoords(0)) {
                vertex.texCoords.s = mesh->mTextureCoords[0][j].x;
                vertex.texCoords.t = mesh->mTextureCoords[0][j].y;
            } else {
                vertex.texCoords.s = 0.0f;
                vertex.texCoords.t = 0.0f;
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
Model::~Model() {
    glDeleteTextures((GLsizei)textures.size(), textures.data());
}
