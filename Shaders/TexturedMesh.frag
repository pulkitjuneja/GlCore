#version 330 core

struct Material {
	int diffuseCount;
	int specularCount;
	sampler2D texture_diffuse[5];
	sampler2D texture_specular[5];
};

struct PointLight {
	vec3 position;
	vec3 diffuse;
	vec3 specular;
	vec3 ambient;
};

struct DirectionalLight {
	vec3 direction;
	vec3 diffuse;
	vec3 specular;
	vec3 ambient;
};

in vec3 vert_normal;
in vec2 vert_texCoords;
in vec3 fragPos;

uniform PointLight pointLights[10];
uniform int pointLightCount;
uniform DirectionalLight directionalLight;

uniform Material material;
uniform vec3 cameraPosition;

out vec4 FragColor;

vec3 calculatePointLight (PointLight pointLight, vec3 normal, vec3 viewDir) {
	
	vec3 diffuseColor = vec3(texture(material.texture_diffuse[0],vert_texCoords));
	vec3 specularStrength  = vec3(texture(material.texture_specular[0], vert_texCoords));

	vec3 lightDir = normalize(pointLight.position - fragPos);
	float diff = max(dot(normal, lightDir), 0.0);
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	float distance = length(pointLight.position - fragPos);

	vec3 ambient  = pointLight.ambient  * diffuseColor;
	vec3 diffuse  = pointLight.diffuse  * diff * diffuseColor;
	vec3 specular = pointLight.specular * spec * specularStrength;

	return (ambient + diffuse + specular);
}

vec3 calculateDirectionalLight (vec3 normal, vec3 viewDir) {
	vec3 diffuseColor = vec3(texture(material.texture_diffuse[0],vert_texCoords));
	vec3 specularStrength  = vec3(texture(material.texture_specular[0], vert_texCoords));

	vec3 lightDir = normalize(-directionalLight.direction);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0),32);

	vec3 ambient  = directionalLight.ambient  * diffuseColor;
	vec3 diffuse  = directionalLight.diffuse  * diff * diffuseColor;
	vec3 specular = directionalLight.specular * spec * specularStrength;

		
	return (ambient + diffuse + specular);
}

void main()
{
	vec3 normal = normalize(vert_normal);
	vec3 viewDir = normalize(cameraPosition - fragPos);
	vec3 result = vec3(0,0,0);

	for(int i = 0; i < pointLightCount; i++) {
		result += calculatePointLight(pointLights[i], normal, viewDir);
	}

	FragColor = vec4(result,1.0);
		
}