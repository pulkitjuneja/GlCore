#include "EntityManager.h"

void EntityManager::setCamera(Camera * camera)
{
	this->mainCamera = camera;
}

void EntityManager::addEntity(Entity* entity)
{
	this->entities.push_back(entity);
}

void EntityManager::updateAndRenderEntities()
{
	mainCamera->update();
	std::vector<Entity*>::iterator it = entities.begin();
	for (; it != entities.end(); it++) {
		(*it)->update();
		renderEntity((*it));
	}
}

void EntityManager::renderEntity(Entity* ent)
{
	glm::mat4 viewMatrix = mainCamera->getViewMatrix();
	glm::mat4 projectionMatrix = mainCamera->getProjectionMatrix();
	ent->renderable->shader->setMat4("viewMatrix", &viewMatrix[0][0]);
	ent->renderable->shader->setMat4("projectionMatrix", &projectionMatrix[0][0]);
	ent->renderable->render();
}
