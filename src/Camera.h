//
// Created by Pulkit Juneja on 02/08/18.
//

#ifndef GLTESTBED_CAMERA_H
#define GLTESTBED_CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "WorldObject.h"

class Camera  {
public:
	glm::vec3 position;
	glm::vec3 up;
	glm::vec3 cameraUP;
	glm::vec3 right;
	glm::vec3 direction;
	Camera(glm::vec3 position, glm::vec3 direction);
	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix();
};

#endif
