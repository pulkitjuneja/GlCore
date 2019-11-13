#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 front, float fov, float aspect, float near, float far): front(front),
	fov(fov),
	nearPlane(near),
	farPlane(far),
	aspect(aspect){

	this->transform.setPosition(position);
	this->up = glm::vec3(0, 1, 0);
	this->right = glm::normalize(glm::cross(front, up));
	this->cameraUP = glm::normalize(glm::cross(right, front));
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
	return glm::perspective(glm::radians(30.0f), aspect, nearPlane, farPlane);
}

glm::vec3 * Camera::getFrustumCorners()
{
	glm::vec3 center = this->transform.getPosition();

	glm::vec3 fc = center + front * farPlane;
	glm::vec3 nc = center + front * nearPlane;

	float nearHeight = tan(fov / 2.0f) * nearPlane;
	float nearWidth = nearHeight * aspect;
	float farHeight = tan(fov / 2.0f) * farPlane;
	float farWidth = farHeight * aspect;

	glm::vec3* corners = new glm::vec3[8];

	corners[0] = nc - up * nearHeight - right * nearWidth; // near-bottom-left
	corners[1] = nc + up * nearHeight - right * nearWidth; // near-top-left
	corners[2] = nc + up * nearHeight + right * nearWidth; // near-top-right
	corners[3] = nc - up * nearHeight + right * nearWidth; // near-bottom-right

	corners[4] = fc - up * farHeight - right * farWidth; // far-bottom-left
	corners[5] = fc + up * farHeight - right * farWidth; // far-top-left
	corners[6] = fc + up * farHeight + right * farWidth; // far-top-right
	corners[7] = fc - up * farHeight + right * farWidth; // far-bottom-right

	return corners;
}

void Camera::setintialRotation()
{
	float yaw = std::atan(front.y/front.x) * (180/3.1412);
	float xz = sqrt(pow(front.x, 2) + pow(front.z, 2));
	float pitch = std::atan(front.y/xz)* (180 / 3.1412);
	this->transform.setRotation(glm::vec3(0.0f, 90.0f, 0));
}
