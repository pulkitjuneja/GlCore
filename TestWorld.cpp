#pragma once 

#ifndef TEST_WORLD
#define TEST_WORLD

#include "src/Engine.h"
#include "src/Mesh.h"
#include "src/Globals.h"
#include "src/ResourceManager.hpp"
#include "Entity.h"
#include "Scene.h"

class TestWorld : public Engine {

	Scene* scene;
	Entity* crysisEntity;
public:
	TestWorld() {};
	bool init() {
		scene = new Scene();

		crysisEntity = scene->createEntity<Entity>("CrysisEntity", ResourceManager::getInstance()->loadMesh("F:/Projects/libraries/crysisM/nanosuit.obj"));
		scene->setMainCamera(new Camera(glm::vec3(0, 0, -15), glm::vec3(0, 0, 1)));
		scene->createLight<Light>(glm::vec3(10, -10, 0), glm::vec3(1,1, 1), glm::vec3(1,1,1), glm::vec3(0.2,0.2,0.2));
		crysisEntity->transfrom.setPosition(glm::vec3(0,-4, 0));
		crysisEntity->transfrom.setScale(glm::vec3(0.4, 0.4, 0.4));
		return true;
	}

	void update() {
		crysisEntity->transfrom.rotate(glm::vec3(0, 0.0005, 0));
		scene->update();
	}

	void render() {
		scene->RenderEntities();
	}
};

#endif // !TEST_WORLD