#pragma once
#include "Mesh.h"
#include <string>

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
	void processNode(aiNode* node, aiScene* scene);
};