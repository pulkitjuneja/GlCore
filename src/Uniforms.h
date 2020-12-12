#pragma once 

#include "Globals.h"
#include <glm/glm.hpp>

#ifndef UNIFORMS_H
#define UNIFORMS_H 

#define MAX_POINT_LIGHTS 10

class Light {};

class DirectionalLight : public Light {
public:
	ALIGNED(16) glm::vec4 direction;
	ALIGNED(16) glm::vec4 diffuse;
	ALIGNED(16) glm::vec4 specular;
	ALIGNED(16) glm::vec4 ambient;
};

class PointLight : public Light {
public:
	ALIGNED(16) glm::vec4 position;
	ALIGNED(16) glm::vec4 diffuse;
	ALIGNED(16) glm::vec4 specular;
	ALIGNED(16) glm::vec4 ambient;
	ALIGNED(16) float radius;
	PointLight() {
		float constant = 1.0;
		float linear = 0.0025f;
		float quadratic = 0.00007f;
		float lightMax = std::fmaxf(std::fmaxf(diffuse.r, diffuse.g), diffuse.b);
		radius = 150;
	}
};

struct PerFrameUniforms {
	ALIGNED(16) glm::mat4 projectionMatrix;
	ALIGNED(16) glm::mat4 viewMatrix;
	ALIGNED(16) glm::mat4 lightSpaceMatrix;
	ALIGNED(16) DirectionalLight directionalLight;
	ALIGNED(16) PointLight pointLights[MAX_POINT_LIGHTS];
	ALIGNED(16) glm::vec4 cameraPosition;
	int pointLightCount;
};

struct FarBound {
	ALIGNED(16) float farBound;
};

struct CSMUniforms {
	//ALIGNED(16) glm::mat4 cropMatrices[MAX_FRUSTUM_SPLITS];
    int splitCount;
	ALIGNED(16) glm::mat4 textureMatrices[CSM_MAX_SPLIT_COUNT];
	ALIGNED(16) FarBound farBounds[CSM_MAX_SPLIT_COUNT];

};

#endif