#version 330 core

struct Material {
	int diffuseCount;
	int specularCount;
	sampler2D texture_diffuse[5];
	sampler2D texture_specular[5];
};

struct Light {
	vec3 position;
	vec3 color;
};

in vec3 vert_normal;
in vec2 vert_texCoords;
in vec3 fragPos;

uniform Light light;
uniform Material material;
uniform vec3 cameraPosition;

out vec4 FragColor;

void main()
{
	vec3 objectColor = vec3(texture(material.texture_diffuse[0],vert_texCoords));
	vec3 specularStrength  = vec3(texture(material.texture_specular[0], vert_texCoords));

	vec3 normal = normalize(vert_normal);
	vec3 lightDir = (light.position - fragPos);

	vec3 diffuseResult = light.color * objectColor * max(dot(lightDir, normal), 0.0) ;

	vec3 viewDir = normalize(cameraPosition - fragPos);
	vec3 reflectDir = reflect(-lightDir, normal);

	float spec = pow(max(dot(viewDir, reflectDir),0.0),32);
	vec3 specularResult = vec3(0.5,0.5,0.5) * spec * light.color;

	vec3 lightingResult = diffuseResult + specularResult;
	FragColor = vec4(lightingResult,1.0);
		
}