#pragma once

#include "Mesh.h"
#include <assimp/scene.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <vector>

class Model
{
public:

    std::vector<Mesh> meshes;

    Model(const char* path)
    {
        loadModel(path);
    }

    void Draw(
        Shader& shader,
        glm::mat4 view,
        glm::mat4 projection
    );

private:

    // Folder containing the model and its textures
    std::string directory;

    void loadModel(const char* path);

    Mesh processMesh(
        aiMesh* mesh,
        const aiScene* scene
    );

    void processNode(
        aiNode* node,
        const aiScene* scene
    );

    std::vector<Texture> loadMaterialTextures(
        aiMaterial* material,
        aiTextureType type,
        std::string typeName
    );
};