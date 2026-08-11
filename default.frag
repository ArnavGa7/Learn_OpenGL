#version 330 core

out vec4 FragColor;
in vec3 FragPos;
in vec3 Normal;
in vec2 Texture;



uniform vec3 view_Position;


struct Material{

	sampler2D diffuse;
	sampler2D  specular;
	float shininess;
};

struct PointLight{
	vec3 Position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	
    float constant;
    float linear;
    float quadratic;
	
	
};

struct DirLight{
	vec3 Direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};


#define NR_POINT_LIGHTS 1
uniform PointLight point_light[NR_POINT_LIGHTS];
uniform Material material;
uniform DirLight dirlight;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 ViewDir){
	vec3 LightDir = normalize(-light.Direction);
	float diff = max(dot(normal, LightDir), 0.0);

	vec3 reflectDir = reflect(-LightDir, normal);
	float specStrenght = pow(max(dot(reflectDir, ViewDir), 0.0), material.shininess);

	vec3 ambient = light.ambient * vec3(texture(material.diffuse, Texture));
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, Texture));
	vec3 specular = light.specular * specStrenght * vec3(texture(material.specular, Texture));

	return (ambient + diffuse + specular);
}


vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 ViewDir){
	vec3 LightDir = normalize(light.Position - fragPos);
	float diff = max(dot(normal, LightDir), 0.0);
	
	vec3 reflectDir = reflect(-LightDir, normal);
	float specStrength = pow(max(dot(reflectDir, ViewDir), 0.0), material.shininess);

	float distances = length(light.Position - fragPos);
	float Attenuation = 1.0/(light.constant + light.linear * distances + light.quadratic * (distances * distances));

	vec3 ambient = light.ambient * vec3(texture(material.diffuse, Texture));
	vec3 diffuse = light.diffuse * vec3(texture(material.diffuse, Texture)) * diff;
	vec3 specular = light.specular * specStrength * vec3(texture(material.specular, Texture));

	ambient *= Attenuation;
	diffuse *= Attenuation;
	specular *= Attenuation;
	return(ambient + diffuse + specular);
}


void main()
{

	vec3 normal = normalize(Normal);
	vec3 ViewDir = normalize(view_Position - FragPos);

	vec3 result = CalcDirLight(dirlight, normal, ViewDir);

	for(int i = 0; i < NR_POINT_LIGHTS; i++){
		result += CalcPointLight(point_light[i], normal, FragPos, ViewDir);
	}
	FragColor = vec4(result, 1.0);
}