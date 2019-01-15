#pragma once

#ifndef SCENE_H
#define SCENE_H

#include <unordered_map>
#include <Entity.h>
#include <Camera.h>
#include "Light.h"

class Scene {
protected:
	std::vector<Entity*> Entities;
	std::vector<Light*> Lights;
	Camera* mainCamera;
public:

	template <class T >
	T* createEntity(string name, Mesh* mesh = nullptr, Material* overrideMat = nullptr);

	template <class T>
	T* createLight(glm::vec3 position, glm::vec3 color);

	std::vector<Entity*>& getEntities();

	Camera* getMainCamera();
	void setMainCamera(Camera* camera);

	virtual void update();

	// temporary function to be moved to renderer class;
	void setGlobalUniforms(Shader* shader);
	void RenderEntities();
};

template<class T>
inline T * Scene::createEntity(string name, Mesh* mesh, Material* overrideMat)
{
	T* ent = new T(name);
	// this is to make sure T is always an entity
	static_cast<Entity*>(ent);
	if (mesh != nullptr) {
		ent->mesh = mesh;
	}
	if (overrideMat != nullptr) {
		ent->overrideMaterial = overrideMat;
	}

	Entities.push_back(ent);
	return ent;
}

template<class T>
inline T * Scene::createLight(glm::vec3 position, glm::vec3 color)
{
	T* light = new T();
	static_cast<Light*>(light);
	light->position = position;
	light->color = color;

	Lights.push_back(light);
	return light;
}

#endif

