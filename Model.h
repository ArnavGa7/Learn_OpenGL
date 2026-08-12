#pragma once
#include "Mesh.h"
#include <string>
#include <assimp/scene.h>

class Model {
public:

	std::vector<Mesh> meshes;

	Model(const char* path) {
		loadModel(path);
	}

	void Draw(Shader& shader);

private:
	void loadModel(const char* path);
	Mesh processMesh(aiMesh* mesh);
	void processNode(aiNode* node, const aiScene* scene);
};