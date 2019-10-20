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
	std::vector<PointLight*> pointLights;
	DirectionalLight* directionalLight;
	Camera* mainCamera;
public:

	template <class T >
	T* createEntity(string name, Mesh* mesh = nullptr, Material* overrideMat = nullptr);
	PointLight* createPointLight(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);
	DirectionalLight* createDirectionalLight(glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);
	void setMainCamera(Camera* camera);

	std::vector<Entity*>& getEntities();
	std::vector<PointLight*>& getPointLIghts();
	DirectionalLight* getDirectionalLight();
	Camera* getMainCamera();

	virtual void update();
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

#endif
