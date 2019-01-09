#pragma once 

#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "Entity.h"
#include "Camera.h"
#include "Globals.h"

class EntityManager {
	std::vector<Entity*> entities;

	void setGlobalUniforms(Shader* shader);

public:
	Camera* mainCamera;
	void addEntity(Entity* entity);
	void setCamera(Camera* camera);
	void updateAndRenderEntities();
	void renderEntity(Entity* ent);
};

#endif // !ENTITY_MANAGER_H
