#ifndef _MODEL_H
#define _MODEL_H

// STL
#include <string>
#include <vector>
#include <iostream>

// glad, glfw, glm
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// assimp
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

// stbi
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

// custom headers
#include "shaders.h"

namespace Model {
  struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
  };

  struct Texture {
    unsigned int id;
    std::string type;
    aiString path;
  };

  class Mesh {
    public:
      std::vector<Vertex> vertices;
      std::vector<unsigned int> indices;
      std::vector<Texture> textures;

      Mesh(
        std::vector<Vertex> vertices,
        std::vector<unsigned int> indices,
        std::vector<Texture> textures
      );
      void Draw(Shader& shader);

    private:
      unsigned int VAO, VBO, EBO;
      void setupMesh();
  };

  class Model {
    public:
      Model(const char* path);

      void Draw(Shader& shader);

    private:
      std::vector<Mesh> meshes;
      std::string directory;

      void loadModel(std::string path);
      void processNode(aiNode* node, const aiScene* scene);
      Mesh processMesh(aiMesh* mesh, const aiScene* scene);
      std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
      std::vector<Texture> textures_loaded;
  };

  unsigned int TextureFromFile(const char* path, const std::string& directory);
};

#endif
