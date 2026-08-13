#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexture;


out vec3 FragPos;
out vec3 Normal;
out vec2 Texture;

uniform mat4 Meshmodel;
uniform mat4 Meshview;
uniform mat4 Meshprojection;

void main(){

		FragPos = vec3(Meshmodel * vec4(aPos, 1.0));
	    Normal = normalize(mat3(transpose(inverse(Meshmodel))) * aNormal);
		gl_Position = Meshprojection * Meshview * vec4(FragPos, 1.0);
		Texture = aTexture;
}

	
