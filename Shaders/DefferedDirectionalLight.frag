#version 330 core

out vec4 FragColor;

uniform sampler2D positionTexture;
uniform sampler2D normalTexture;
uniform sampler2D albedoTexture;

struct PointLight {
	vec4 position;
	vec4 diffuse;
	vec4 specular;
	vec4 ambient;
};

struct DirectionalLight {
	vec4 direction;
	vec4 diffuse;
	vec4 specular;
	vec4 ambient;
};

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

in vec2 fragTexcoords;
in vec4 fragPos;

void main()
{   
    FragColor = texture(albedoTexture, fragTexcoords);
}  