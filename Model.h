#pragma once
#include "Mesh.h"
#include <string>
#include <assimp/scene.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class Model {
public:

	std::vector<Mesh> meshes;

	Model(const char* path) {
		loadModel(path);
	}

	void Draw(Shader& shader, glm::mat4 view, glm::mat4 projection);

private:
	void loadModel(const char* path);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	void processNode(aiNode* node, const aiScene* scene);
};