#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 direction) {
	this->direction = glm::normalize(direction);
	this->position = position;
	this->up = glm::vec3(0, 1, 0);
	this->right = glm::normalize(glm::cross(position, -direction));
	this->cameraUP = glm::normalize(glm::cross(-direction, right));
}

glm::mat4 Camera::getViewMatrix()
{
	return glm::lookAt(this->position, this->direction, this->up);
}

glm::mat4 Camera::getProjectionMatrix()
{
	return glm::perspective(glm::radians(30.0f), 4.0f / 3.0f, 0.1f, 100.0f);
}