#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;

uniform mat4 modelMatrix;

struct PointLight {
	vec4 position;
	vec4 diffuse;
	vec4 specular;
	vec4 ambient;
	float radius;
};

struct DirectionalLight {
	vec4 direction;
	vec4 diffuse;
	vec4 specular;
	vec4 ambient;
};

// TODO: create a different uniform structured for deffered
layout (std140) uniform perFrameUniforms
{
	mat4 projectionMatrix;
	mat4 viewMatrix;
	mat4 lightSpaceMatrix;
	DirectionalLight directionalLight;
	PointLight pointLights[10];
	vec4 cameraPosition;
	int pointLightCount;
};

out VS_OUT {
    vec3 worldPos;
    vec3 vertNormal;
    vec2 texCoords;
} vsOut;

out vec3 FragPos;

void main() {
	vec4 homogenousVertexPosition = vec4(position, 1.0);
	vsOut.vertNormal = mat3(inverse(transpose(modelMatrix)))*normal;
	vsOut.texCoords = texCoords;
	vsOut.worldPos = vec3(modelMatrix* homogenousVertexPosition);
	FragPos = (modelMatrix*homogenousVertexPosition).xyz;
	// vsOut.fragPosLightSpace = lightSpaceMatrix* vec4(vsOut.fragPos, 1.0);
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * homogenousVertexPosition;
}