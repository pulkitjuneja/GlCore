#version 330 core

struct Material {
	int diffuseCount;
	int specularCount;
	sampler2D texture_diffuse[5];
	sampler2D texture_specular[5];
};

struct PointLight {
	vec4 position;
	vec4 diffuse;
	vec4 specular;
	vec4 ambient;
	// TODO add back linear and quadratic attenuation to this class
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
	int pointLightCount;
};



in VS_OUT {
    vec3 fragPos;
    vec3 vertNormal;
    vec2 texCoords;
    vec4 fragPosLightSpace;
} vsOut;


//uniform PointLight pointLights[10];
//uniform int pointLightCount;
//uniform DirectionalLight directionalLight;
uniform sampler2D shadowMap;

uniform Material material;
uniform vec3 cameraPosition;

out vec4 FragColor;

vec3 calculatePointLight (PointLight pointLight, vec3 normal, vec3 viewDir) {

	vec3 diffuseColor = vec3(texture(material.texture_diffuse[0],vsOut.texCoords));
	vec3 specularStrength;

	if(material.specularCount > 0) {
		specularStrength  = vec3(texture(material.texture_specular[0], vsOut.texCoords));
	} else {
		specularStrength = vec3(0.1,0.1,0.1);
	}

	vec3 lightDir = normalize(pointLight.position.xyz - vsOut.fragPos);
	float diff = max(dot(normal, lightDir), 0.0);
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	float distance = length(pointLight.position.xyz - vsOut.fragPos);

	float attenuation = 1.0/(1.0 + 0.0025f *distance + 0.00007f * (distance*distance));

	vec3 ambient  = pointLight.ambient.xyz  * diffuseColor * attenuation;
	vec3 diffuse  = pointLight.diffuse.xyz  * diff * diffuseColor * attenuation;
	vec3 specular = pointLight.specular.xyz * spec * specularStrength * attenuation;

	return (ambient + diffuse + specular);
}

float ShadowCalculation(vec4 fragPosLightSpace)
{
	vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
	projCoords = projCoords * 0.5 + 0.5; 
	float closestDepth = texture(shadowMap, projCoords.xy).r;
	float bias = 0.05;
	vec2 inc = 1.0 / textureSize(shadowMap, 0);
	float shadowFactor = 0.0;
	for(int row = -1; row <= 1; ++row)
	{
		for(int col = -1; col <= 1; ++col)
			{
				float textDepth = texture(shadowMap, projCoords.xy + vec2(row, col) * inc).r; 
				shadowFactor += projCoords.z - bias > textDepth ? 1.0 : 0.0;        
			}    
	}
	shadowFactor /= 9.0;
	 return shadowFactor;
}

vec3 calculateDirectionalLight (vec3 normal, vec3 viewDir) {
	vec3 diffuseColor = vec3(texture(material.texture_diffuse[0],vsOut.texCoords));
	vec3 specularStrength;

	if(material.specularCount > 0) {
		specularStrength  = vec3(texture(material.texture_specular[0], vsOut.texCoords));
	} else {
		specularStrength = vec3(0.1,0.1,0.1);
	}

	vec3 lightDir = normalize(-directionalLight.direction.xyz);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0),32);

	float shadow = ShadowCalculation(vsOut.fragPosLightSpace);

	vec3 ambient  = directionalLight.ambient.xyz  * diffuseColor;
	vec3 diffuse  = (1.0 - shadow)*(directionalLight.diffuse.xyz  * diff) * diffuseColor;
	vec3 specular = (1.0 - shadow)*(directionalLight.specular.xyz * spec) * specularStrength;

		
	return (ambient + diffuse + specular);
}

void main()
{
	vec3 normal = normalize(vsOut.vertNormal);
	vec3 viewDir = normalize(cameraPosition - vsOut.fragPos);
	vec3 result = vec3(0,0,0);

	result += calculateDirectionalLight(normal, viewDir);

	for(int i = 0; i < pointLightCount; i++) {
		result += calculatePointLight(pointLights[i], normal, viewDir);
	}

	FragColor = vec4(result,1.0);
		
}