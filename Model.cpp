#include "Model.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <iostream>

void Model::loadModel(const char* path)
{
    Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile(
        path,
        aiProcess_Triangulate | aiProcess_FlipUVs
    );

    if (!scene ||
        scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE ||
        !scene->mRootNode)
    {
        std::cout << "ASSIMP ERROR: "
            << importer.GetErrorString()
            << std::endl;

        return;
    }

    // Get the folder containing the model
    std::string fullPath = path;

    directory = fullPath.substr(
        0,
        fullPath.find_last_of('/')
    );

    processNode(scene->mRootNode, scene);
}


Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
    std::vector<Vertex> meshvertices;
    std::vector<unsigned int> meshindices;
    std::vector<Texture> meshtextures;

    // Vertices
    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;

        vertex.Position = glm::vec3(
            mesh->mVertices[i].x,
            mesh->mVertices[i].y,
            mesh->mVertices[i].z
        );

        vertex.Normal = glm::vec3(
            mesh->mNormals[i].x,
            mesh->mNormals[i].y,
            mesh->mNormals[i].z
        );

        if (mesh->mTextureCoords[0])
        {
            vertex.Texture = glm::vec2(
                mesh->mTextureCoords[0][i].x,
                mesh->mTextureCoords[0][i].y
            );
        }
        else
        {
            vertex.Texture = glm::vec2(0.0f, 0.0f);
        }

        meshvertices.push_back(vertex);
    }

    // Indices
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];

        for (unsigned int j = 0; j < face.mNumIndices; j++)
        {
            meshindices.push_back(face.mIndices[j]);
        }
    }

    // Materials / textures
    if (mesh->mMaterialIndex < scene->mNumMaterials)
    {
        aiMaterial* material =
            scene->mMaterials[mesh->mMaterialIndex];

        std::vector<Texture> diffuseMaps =
            loadMaterialTextures(
                material,
                aiTextureType_DIFFUSE,
                "texture_diffuse"
            );

        meshtextures.insert(
            meshtextures.end(),
            diffuseMaps.begin(),
            diffuseMaps.end()
        );

        std::vector<Texture> specularMaps =
            loadMaterialTextures(
                material,
                aiTextureType_SPECULAR,
                "texture_specular"
            );

        meshtextures.insert(
            meshtextures.end(),
            specularMaps.begin(),
            specularMaps.end()
        );
    }

    return Mesh(
        meshvertices,
        meshindices,
        meshtextures
    );
}


std::vector<Texture> Model::loadMaterialTextures(
    aiMaterial* material,
    aiTextureType type,
    std::string typeName)
{
    std::vector<Texture> textures;

    for (unsigned int i = 0;
        i < material->GetTextureCount(type);
        i++)
    {
        aiString str;

        material->GetTexture(
            type,
            i,
            &str
        );

        // Build the full texture path
        std::string filename =
            directory + "/" + str.C_Str();

        // Create your Texture object
        Texture texture(filename.c_str());

    
        texture.type = typeName;

  
        textures.push_back(texture);
    }

    return textures;
}


void Model::processNode(
    aiNode* node,
    const aiScene* scene)
{
    // Process all meshes in this node
    for (unsigned int i = 0;
        i < node->mNumMeshes;
        i++)
    {
        unsigned int meshIndex =
            node->mMeshes[i];

        aiMesh* mesh =
            scene->mMeshes[meshIndex];

        Mesh newMesh =
            processMesh(mesh, scene);

        meshes.push_back(newMesh);
    }

    // Process children
    for (unsigned int i = 0;
        i < node->mNumChildren;
        i++)
    {
        processNode(
            node->mChildren[i],
            scene
        );
    }
}


void Model::Draw(
    Shader& shader,
    glm::mat4 view,
    glm::mat4 projection)
{
    glm::mat4 model =
        glm::mat4(1.0f);

    model = glm::translate(
        model,
        glm::vec3(0.0f, 0.0f, -5.0f)
    );

    shader.Active();

    glUniformMatrix4fv(
        glGetUniformLocation(
            shader.ID,
            "Meshmodel"
        ),
        1,
        GL_FALSE,
        glm::value_ptr(model)
    );

    glUniformMatrix4fv(
        glGetUniformLocation(
            shader.ID,
            "Meshview"
        ),
        1,
        GL_FALSE,
        glm::value_ptr(view)
    );

    glUniformMatrix4fv(
        glGetUniformLocation(
            shader.ID,
            "Meshprojection"
        ),
        1,
        GL_FALSE,
        glm::value_ptr(projection)
    );

    for (Mesh& mesh : meshes)
    {
        mesh.Draw(shader);
    }
}