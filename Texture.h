#pragma once
#include <glad/glad.h>
#include <string>
class Texture {
public:
	GLuint ID;
	std::string type;
	Texture(const char* imgPath);
	void Bind(GLenum TextureUnit);
	void Unbind();
	void Delete();

};
