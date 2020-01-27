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
	CameraController* cameraController;
	Entity* crysisEntity;
	Entity * sponzaEntity;
public:
	TestWorld() {};
	bool init() {

		// Change this to load a different model
		string sponzaMeshLocation = "Assets/Meshes/Sponza/sponza.obj";
		string crysisMeshLocation = "Assets/Meshes/crysisM/nanosuit.obj";

		scene = new Scene();
		renderer->setScene(scene);
		sponzaEntity = scene->createEntity<Entity>("Model", ResourceManager::getInstance()->loadMesh(sponzaMeshLocation));
		crysisEntity = scene->createEntity<Entity>("CrysisModel", ResourceManager::getInstance()->loadMesh(crysisMeshLocation));

		sponzaEntity->transfrom.setScale(glm::vec3(0.3, 0.3, 0.3));
		crysisEntity->transfrom.setScale(glm::vec3(2, 2, 2));

		scene->setMainCamera(new Camera(glm::vec3(-50, 30, 0), glm::vec3(1, -0.04f, -0.06f), 90.0f, float(SCREEN_WIDTH)/float(SCREEN_HEIGHT), 8.0f, 1000.0f));
		scene->createPointLight(glm::vec3(-10, 10, 5), glm::vec3(0.01, 0.01, 0.01), glm::vec3(1, 1, 1), glm::vec3(1, 1, 1));
		scene->createPointLight(glm::vec3(-10, 150, 80), glm::vec3(0.01, 0.01, 0.01), glm::vec3(1, 1, 1), glm::vec3(1, 1, 1));
		scene->createPointLight(glm::vec3(-10, 150, -80), glm::vec3(0.01, 0.01, 0.01), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
		scene->createPointLight(glm::vec3(300, 10, 5), glm::vec3(0.01, 0.01, 0.01), glm::vec3(1, 0, 0), glm::vec3(1, 0, 0));
		scene->createPointLight(glm::vec3(-300, 10, 5), glm::vec3(0.01, 0.01, 0.01), glm::vec3(0, 0, 1), glm::vec3(05, 0, 1));
		scene->createDirectionalLight(glm::vec3(0, -1, 0), glm::vec3(0.08, 0.08, 0.08), glm::vec3(0.01, 0.01, 0.01), glm::vec3(0.01, 0.01, 0.01));
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