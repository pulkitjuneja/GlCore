#pragma once

#ifndef SCENE_H
#define SCENE_H

#include <unordered_map>
#include <Entity.h>
#include <Camera.h>

class Scene {
protected:
	std::vector<Entity*> Entities;
	// std::vector<Light> Lights;
	Camera* mainCamera;
public:
	Entity* createEntity(string name, Mesh* mesh=nullptr, Material* overrideMat=nullptr);
	Entity* lookupEntity(string name);
	std::vector<Entity*>& getEntities();

	Camera* getMainCamera();
	void setMainCamera(Camera* camera);

	virtual void update();

	// temporary function to be moved to renderer class;
	void setGlobalUniforms(Shader* shader);
	void RenderEntities();
};

#endif