#pragma once 

#ifndef TEST_WORLD
#define TEST_WORLD

#include "src/Engine.h"
#include "src/Mesh.h"
#include "src/Globals.h"
#include "src/ResourceManager.hpp"
#include "Entity.h"
#include "Scene.h"
#include "utils/CameraController.h"

class TestWorld : public Engine {

	Scene* scene;
	Entity* crysisEntity;
	CameraController* cameraController;
public:
	TestWorld() {};
	bool init() {
		scene = new Scene();
		renderer->setScene(scene);
		crysisEntity = scene->createEntity<Entity>("CrysisEntity", ResourceManager::getInstance()->loadMesh("F:/Projects/libraries/crysisM/nanosuit.obj"));
		Entity* sponzaEntity = scene->createEntity<Entity>("SponzaEntity", ResourceManager::getInstance()->loadMesh("Assets/Meshes/Sponza/sponza.obj"));
		sponzaEntity->transfrom.setScale(glm::vec3(0.3, 0.3, 0.3));

		scene->setMainCamera(new Camera(glm::vec3(-50, 30, 0), glm::vec3(1, -0.04f, -0.06f), 90.0f, float(screenWidth)/float(screenHeight), 8.0f, 1000.0f));
		scene->createPointLight(glm::vec3(-10, 10, 5), glm::vec3(0.01, 0.01, 0.01), glm::vec3(1, 1, 1), glm::vec3(1, 1, 1));
		scene->createPointLight(glm::vec3(300, 10, 5), glm::vec3(0.01, 0.01, 0.01), glm::vec3(1, 1, 1), glm::vec3(1, 1, 1));
		scene->createDirectionalLight(glm::vec3(0, -1, 0), glm::vec3(0.01, 0.01, 0.01), glm::vec3(1, 1, 0.8), glm::vec3(1, 1, 0.8));
		crysisEntity->transfrom.setScale(glm::vec3(2, 2, 2));
		cameraController = new CameraController(scene->getMainCamera());
		return true;
	}

	void update() {
		crysisEntity->transfrom.rotate(glm::vec3(0, 0.005, 0));
		cameraController->update();
		scene->update();
	}
};

#endif // !TEST_WORLD