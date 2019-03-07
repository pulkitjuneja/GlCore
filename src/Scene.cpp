#pragma once

#include "Scene.h"

PointLight * Scene::createPointLight(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
{
	PointLight* light = new PointLight();
	light->position = position;
	light->ambient = ambient;
	light->diffuse = diffuse;
	light->specular = specular;

	pointLights.push_back(light);
	return light;
}

DirectionalLight * Scene::createDirectionalLight(glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
{
	DirectionalLight* light = new DirectionalLight();

	light->ambient = ambient;
	light->diffuse = diffuse;
	light->specular = specular;
	light->direction = direction;

	this->directionalLight = light;
	return light;

}

std::vector<Entity*>& Scene::getEntities()
{
	return Entities;
}

std::vector<PointLight*>& Scene::getPointLIghts()
{
	return pointLights;
}

DirectionalLight * Scene::getDirectionalLight()
{
	return directionalLight;
}

Camera * Scene::getMainCamera()
{
	return mainCamera;
}

void  Scene::setMainCamera(Camera * camera)
{
	this->mainCamera = camera;
}

void Scene::update()
{
	std::vector<Entity*>::iterator it = Entities.begin();
	for (; it != Entities.end(); it++) {
		(*it)->update();
	}
}
