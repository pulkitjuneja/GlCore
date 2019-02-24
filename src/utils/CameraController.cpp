#include "CameraController.h"

CameraController::CameraController(Camera * camera)
{
	this->camera = camera;
}

void CameraController::update()
{
	handleRotation();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		camera->transform.translate(camera->front * CAMERA_SPEED);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		camera->transform.translate(-camera->front * CAMERA_SPEED);
	}
}

void CameraController::handleRotation()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
		sf::Vector2i position = sf::Mouse::getPosition();
		glm::vec2 currentMousePosition(position.x, position.y);
		glm::vec2 mouseDelta = currentMousePosition - lastFrameMousePosition;
		glm::vec3 eulerAngleDelta(0);
		eulerAngleDelta.x = mouseDelta.y; // vertical rotation describes angle around the x axis
		eulerAngleDelta.y = mouseDelta.x; // horizontal rotation describes angle around the y axis
		eulerAngleDelta *= 0.05;
		camera->transform.rotate(eulerAngleDelta);
		lastFrameMousePosition = currentMousePosition;
	}
}
