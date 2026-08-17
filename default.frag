#version 330 core

out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D texture_diffuse;
uniform vec3 Color;
void main()
{
    FragColor = vec4(Color, 1.0) * texture(texture_diffuse, TexCoord);
}