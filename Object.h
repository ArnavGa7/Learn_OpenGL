#pragma once

#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "ShaderClass.h"
#include "glm/glm.hpp"
#include "glad/glad.h"

class Object {
public:
	VAO vao;
	VBO* vbo;
	EBO* ebo;
	Shader shader;
	glm::vec3 Position;
	glm::vec3 Rotation;
	glm::vec3 Scale;
	GLsizei  IndexCount;
	glm::vec3 Color;
	float angle;
	Object(GLfloat* vertices, GLsizeiptr verticesSize,GLuint* indices, GLsizeiptr indicesSize, const char* VertexShader, const char* FragmentSize);
	
	void Draw(glm::mat4 view, glm::mat4 projection,glm::vec3 light_Color,glm::vec3 Light_Position ,glm::vec3 camera_Position);
};
