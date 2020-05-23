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
};

struct PerFrameUniforms {
	ALIGNED(16) glm::mat4 projectionMatrix;
	ALIGNED(16) glm::mat4 viewMatrix;
	ALIGNED(16) glm::mat4 lightSpaceMatrix;
	ALIGNED(16) DirectionalLight directionalLight;
	ALIGNED(16) PointLight pointLights[MAX_POINT_LIGHTS];
	int pointLightCount;
};

#endif