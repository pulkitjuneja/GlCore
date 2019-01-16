#pragma once 

#ifndef LIGHT_H
#define LIGHT_H

#include <glm/glm.hpp>

class Light {
public:
	glm::vec3 diffuse;
	glm::vec3 specular;
	glm::vec3 ambient;
	glm::vec3 position;
};

#endif