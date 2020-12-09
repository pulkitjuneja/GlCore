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
#include <windows.h>
#include "Uniforms.h"

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
		defferedRenderer->setScene(scene);
		sponzaEntity = scene->createEntity<Entity>("Model", ResourceManager::getInstance()->loadMesh(sponzaMeshLocation));
		crysisEntity = scene->createEntity<Entity>("CrysisModel", ResourceManager::getInstance()->loadMesh(crysisMeshLocation));

		sponzaEntity->transfrom.setScale(glm::vec3(0.3, 0.3, 0.3));
		crysisEntity->transfrom.setScale(glm::vec3(2, 2, 2));

		scene->setMainCamera(new Camera(glm::vec3(-4.31142f, 55.923f, 191.538f), glm::vec3(-16.8f, -89.1506f, 0), 90.0f, float(SCREEN_WIDTH)/float(SCREEN_HEIGHT), 8.0f, 1000.0f));
		scene->createPointLight(glm::vec4(-40, 30, 5, 1.0), glm::vec4(0.3f, 0.01, 0.01, 1.0), glm::vec4(1, 0, 0, 1.0), glm::vec4(1, 0, 0, 1.0));
		//scene->createPointLight(glm::vec4(-10, 150, 80, 1.0), glm::vec4(0.01, 0.5f, 0.01, 1.0), glm::vec4(1, 1, 1, 1.0), glm::vec4(0.1, 0.1, 0.1, 1.0));
		//scene->createPointLight(glm::vec4(-10, 150, -80, 1.0), glm::vec4(0.01, 0.01, 0.5, 1.0), glm::vec4(0, 1, 0, 1.0), glm::vec4(0.1, 0.1, 0.1, 1.0));
		scene->createPointLight(glm::vec4(300, 10, 5, 1.0), glm::vec4(0.01, 0.01, 0.3f, 1.0), glm::vec4(0, 1, 0, 1.0), glm::vec4(0, 1, 0, 1.0));
		//scene->createPointLight(glm::vec3(-300, 10, 5), glm::vec3(0.01, 0.01, 0.01), glm::vec3(0, 0, 1), glm::vec3(05, 0, 1));
		scene->createDirectionalLight(glm::vec4(0.5f, -1.0f, 0, 1.0), glm::vec4(0.2f, 0.2f, 0.2f, 1.0f), glm::vec4(0.6f, 0.6f, 0.6f, 1.0f), glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));
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