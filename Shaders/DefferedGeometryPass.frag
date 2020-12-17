#version 330 core
layout (location = 0) out vec3 gPosition;
layout (location = 1) out vec3 gNormal;
layout (location = 2) out vec4 gAlbedoSpec;

struct Material {
	int diffuseCount;
	int specularCount;
	sampler2D texture_diffuse[5];
	sampler2D texture_specular[5];
	sampler2D texture_normal;
	int hasNormalMap;
};

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

in VS_OUT {
    vec3 worldPos;
    vec3 vertNormal;
    vec2 texCoords;
	mat3 TBN;
} vsOut;

in vec3 FragPos;

uniform Material material;

void main()
{    
    // store the fragment position vector in the first gbuffer texture
    gPosition = FragPos;
    // also store the per-fragment normals into the gbuffer
	vec3 normal = normalize(texture(material.texture_normal, vsOut.texCoords).rgb);
	normal = normal * 2.0 - 1.0;   
	normal = normalize(vsOut.TBN * normal); 
    gNormal = mix(vsOut.vertNormal, normal, step(1.0f, material.hasNormalMap));
    // and the diffuse per-fragment color
    gAlbedoSpec.rgb = texture(material.texture_diffuse[0], vsOut.texCoords).rgb;
    // store specular intensity in gAlbedoSpec's alpha component
    gAlbedoSpec.a = mix(0.1f, texture(material.texture_specular[0], vsOut.texCoords).r, step(1.0f, material.specularCount));
}