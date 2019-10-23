//
// Created by Pulkit Juneja on 02/08/18.
//

#ifndef GLTESTBED_CAMERA_H
#define GLTESTBED_CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Transform.h"
#include "Globals.h"

class Camera  {
public:

	Transform transform;
	glm::vec3 up;
	glm::vec3 cameraUP;
	glm::vec3 right;
	glm::vec3 front;

	float nearPlane;
	float farPlane;
	float fov;
	float aspect;

	Camera(glm::vec3 position, glm::vec3 front, float fov, float aspect, float near, float far);
	void getFrontFromRotation();
	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix();
	void setintialRotation();
};

#endif