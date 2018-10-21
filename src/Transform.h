#pragma once

#ifndef TRANSFORM_H
#define TRANSFORM_
#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/quaternion.hpp>

class Transform {
	glm::vec3 position;
	glm::vec3 scale;
	glm::vec3 eulerAngles;
public:

	Transform();
	glm::mat4 getTransformationMatrix();
	void translate(glm::vec3& movement);
	void increaseScale(glm::vec3& scale);
	void rotate(glm::vec3& rotation);
};


#endif // !TRANSFORM_H
