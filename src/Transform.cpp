#pragma once

#include "Transform.h"

glm::mat4 Transform::getTransformationMatrix() {
	glm::quat rotationQuat = glm::quat(eulerAngles);
	glm::mat4 rotationMatrix = glm::toMat4(rotationQuat);
	glm::mat4 transformationMAtrix(1.0f);
	// translate to centerglm::translate(glm::mat4(1.0f), -position)
	transformationMAtrix = glm::translate(glm::mat4(1.0f), -position) * transformationMAtrix;
	transformationMAtrix = glm::scale(glm::mat4(1.0f), scale) * transformationMAtrix;
	transformationMAtrix = rotationMatrix * transformationMAtrix;
	transformationMAtrix = glm::translate(glm::mat4(1.0f), position) * transformationMAtrix;
	return transformationMAtrix;
}

void Transform::translate(glm::vec3 & movement)
{
	position += movement;
}

void Transform::increaseScale(glm::vec3 & scale)
{
	this->scale += scale;
}

void Transform::rotate(glm::vec3 & rotation)
{
	this->eulerAngles += rotation;
}

Transform::Transform()
{
	this->position = glm::vec3(0, 0, 0);
	this->eulerAngles = glm::vec3(0, 0, 0);
	this->scale = glm::vec3(1, 1, 1);
}

void Transform::setScale(glm::vec3& scale) 
{
	this->scale = scale;
}
