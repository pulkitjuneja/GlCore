#pragma once 

#ifndef LIGHT_H
#define LIGHT_H

#include <glm/glm.hpp>

class Light {};

class DirectionalLight: public Light {
public:
	glm::vec3 diffuse;
	glm::vec3 specular;
	glm::vec3 ambient;
	glm::vec3 direction;
};

class PointLight : public Light {
public:
	glm::vec3 position;
	glm::vec3 diffuse;
	glm::vec3 specular;
	glm::vec3 ambient;
};

#endif