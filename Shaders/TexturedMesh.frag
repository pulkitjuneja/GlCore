#version 330 core

struct Material {
	sampler2D texture_diffuse;
	sampler2D texture_specular;
	sampler2D texture_normal;
	int hasSpecularMap;
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

layout (std140) uniform csmUniforms 
{
	int splitCount;
	mat4 textureMatrices[8];
	float farBounds[8];
};

in VS_OUT {
    vec3 worldPos;
    vec3 vertNormal;
    vec2 texCoords;
	mat3 TBN;
} vsOut;


uniform sampler2DArrayShadow shadowMap;

uniform Material material;

out vec4 FragColor;

vec3 calculatePointLight (PointLight pointLight, vec3 normal, vec3 viewDir, vec3 diffuseColor, float specularIntensity) {

	float specularStrength = mix(0.1, specularIntensity, step(1.0f, material.hasSpecularMap));

	vec3 lightDir = normalize(pointLight.position.xyz - vsOut.worldPos);
	float diff = max(dot(normal, lightDir), 0.0);
	vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(halfwayDir, normal), 0.0),32);
	float distance = length(pointLight.position.xyz - vsOut.worldPos);

	float attenuation = 1.0/(1.0 + 0.0025f *distance + 0.00007f * (distance*distance));

	vec3 ambient  = pointLight.ambient.xyz  * diffuseColor * attenuation;
	vec3 diffuse  = pointLight.diffuse.xyz  * diff * diffuseColor * attenuation;
	vec3 specular = pointLight.specular.xyz * spec * specularStrength * attenuation;

	return (ambient + diffuse + specular);
}


float ShadowCalculation(float fragDepth, vec3 normal, vec3 lightDirection)
{
	int index = 0 ;
	float blend = 0.0f;

	for (int i = 0; i < splitCount - 1; i++) {
		if(fragDepth > farBounds[i])
			index = i + 1;
	}

	blend = clamp((fragDepth - farBounds[index]*0.995)*200.0,0.0,1.0); // what is this doing exactly ??
	vec4 lightSpacePos = textureMatrices[index] * vec4(vsOut.worldPos, 1.0f);
	float currentDepth = lightSpacePos.z;
	float bias = max(0.0005 * (1.0 - dot(normal, lightDirection)), 0.0005);

	float shadow = 0.0;
	vec2 texelSize = 1.0 / textureSize(shadowMap, 0).xy;

	for(int x = -1; x <= 1; ++x)
	{
	    for(int y = -1; y <= 1; ++y)
	    {
	        float pcfDepth = texture(shadowMap, vec4(lightSpacePos.xy + vec2(x, y) * texelSize, float(index), currentDepth - 0.0005)); 
	        shadow += pcfDepth;         
	    }    
	}
	shadow /= 9.0;

	return shadow;
}

//vec3 debug_color(float fragDepth)
//{
//	int index = 0;
//
//	// Find shadow cascade.
//	for (int i = 0; i < splitCount - 1; i++)
//	{
//		if (fragDepth > farBounds[i])
//			index = i + 1;
//	}
//
//	if (index == 0)
//		return vec3(0.5, 0.0, 0.0);
//	else if (index == 1)
//		return vec3(0.0, 0.5, 0.0);
//	else if (index == 2)
//		return vec3(0.0, 0.0, 0.5);
//	else
//		return vec3(2.0, 1.0, 1.0);
//}

vec3 calculateDirectionalLight (vec3 normal, vec3 viewDir, vec3 diffuseColor, float specularIntensity) {
	vec4 clipPos = projectionMatrix * viewMatrix * vec4(vsOut.worldPos, 1.0);
	float fragDepth = (clipPos.z/ clipPos.w) * 0.5 + 0.5;
	//vec3 diffuseColor = debug_color(fragDepth);
	float specularStrength = mix(0.1, specularIntensity, step(1.0f, material.hasSpecularMap));

	vec3 lightDir = normalize(-directionalLight.direction.xyz);
    float diff = max(dot(normal, lightDir), 0.0);
	vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(halfwayDir, normal), 0.0),32);

	float shadow = ShadowCalculation(fragDepth, normal, lightDir);

	vec3 ambient  = directionalLight.ambient.xyz  * diffuseColor;
	vec3 diffuse  = (1.0 - shadow)*(directionalLight.diffuse.xyz  * diff) * diffuseColor;
	vec3 specular = (1.0 - shadow)*(directionalLight.specular.xyz * spec) * specularStrength;

	return (ambient + diffuse + specular);
}

void main()
{
	vec4 diffuseColor = texture(material.texture_diffuse, vsOut.texCoords);
	float specularIntensity = texture(material.texture_specular, vsOut.texCoords).r;
	if(diffuseColor.a == 0 && (material.hasSpecularMap ==0 || specularIntensity < 0)) {
		discard;
	}
	vec3 normal = texture(material.texture_normal, vsOut.texCoords).rgb;
	normal = normal * 2.0 - 1.0f;
	normal = normalize(vsOut.TBN * normal);
	normal = mix(vsOut.vertNormal, normal, step(1.0f, material.hasNormalMap));
	vec3 viewDir = normalize(vec3(cameraPosition) - vsOut.worldPos);
	vec3 result = vec3(0,0,0);

	result += calculateDirectionalLight(normal, viewDir, diffuseColor.xyz, specularIntensity);

	for(int i = 0; i < pointLightCount; i++) {
		result += calculatePointLight(pointLights[i], normal, viewDir,  diffuseColor.xyz, specularIntensity);
	}

	FragColor = vec4(result,1.0);
		
}