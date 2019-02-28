#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 front) {
	this->transform.setPosition(position);
	this->front = front;
	this->up = glm::vec3(0, 1, 0);
	this->right = glm::normalize(glm::cross(position, -front));
	this->cameraUP = glm::normalize(glm::cross(-front, right));
	setintialRotation();
}

void Camera::getFrontFromRotation()
{
	glm::vec3 eulerAngles = transform.getEulerAngles();
	if (eulerAngles.x > 89) {
		eulerAngles.x = 89;
	}
	else if (eulerAngles.x < -89) {
		eulerAngles.x = -89;
	}

	glm::vec3 newFront;
	newFront.x = cos(glm::radians(eulerAngles.y)) * cos(glm::radians(eulerAngles.x));
	newFront.y = sin(glm::radians(eulerAngles.x));
	newFront.z = cos(glm::radians(eulerAngles.x))*sin(glm::radians(eulerAngles.y));
	front = glm::normalize(newFront);
}

glm::mat4 Camera::getViewMatrix()
{
	getFrontFromRotation();
	return glm::lookAt(this->transform.getPosition(), this->transform.getPosition() + front, this->up);
}

glm::mat4 Camera::getProjectionMatrix()
{
	return glm::perspective(glm::radians(30.0f), 4.0f / 3.0f, 0.1f, 3000.0f);
}

void Camera::setintialRotation()
{
	float yaw = std::atan(front.y/front.x) * (180/3.1412);
	float xz = sqrt(pow(front.x, 2) + pow(front.z, 2));
	float pitch = std::atan(front.y/xz)* (180 / 3.1412);
	this->transform.setRotation(glm::vec3(0.0f, 90.0f, 0));
}
