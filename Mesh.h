#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <glad/glad.h>
#include "ShaderClass.h"


struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 Texture;
};

struct Textures {

	GLuint ID;
	std::string Type;
	std::string path;
};
class Mesh {
public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Textures> textures;
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

	Mesh(std::vector<Vertex> meshvertices, std::vector<unsigned int> meshindices,  std::vector<Textures> meshtextures);

	void Draw(Shader& shader);
};

