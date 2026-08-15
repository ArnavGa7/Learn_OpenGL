#version 330 core

out vec4 FragColor;
in vec3 FragPos;
in vec3 Normal;
in vec2 Texture;


void main(){

		

FragColor = vec4(Normal * 0.5 + 0.5, 1.0);
}