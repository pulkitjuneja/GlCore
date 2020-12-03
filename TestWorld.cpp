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
	//Entity* quadEntity;
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

		//vector<Vertex> quadVertices = {
		//	 Vertex(glm::vec3(0.5f,  0.5f, 0.0f), glm::vec3(0,0,-1), glm::vec2(1.0f, 1.0f)),
		//	 Vertex(glm::vec3(0.5f, -0.5f, 0.0f), glm::vec3(0,0,-1), glm::vec2(1.0f, 0.0f)),
		//	 Vertex(glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(0,0,-1), glm::vec2(0.0f, 0.0f)),
		//	 Vertex(glm::vec3(-0.5f,  0.5f, 0.0f), glm::vec3(0,0,-1), glm::vec2(0.0f, 1.0f))
		//};

		//vector<unsigned int> quadIndices = {
		//	0, 1, 3, // first triangle
		//	1, 2, 3  // second triangle
		//};

		//Material* quadMaterial = new Material();
		//quadMaterial->setShader(ResourceManager::getInstance()->getShader("texturedMeshShader"));
		//quadMaterial->textures.push_back(ResourceManager::getInstance()->loadTexture("spnza_bricks_a_diff.tga", "Assets/Meshes/Sponza/textures", TextureType::DIFFUSE));

		//vector<SubMesh> quadSubmeshes = {
		//	SubMesh(quadMaterial,0,6,0)
		//};

		//quadEntity = scene->createEntity<Entity>("shadowMap", new Mesh(quadVertices, quadIndices, quadSubmeshes));

		sponzaEntity->transfrom.setScale(glm::vec3(0.3, 0.3, 0.3));
		crysisEntity->transfrom.setScale(glm::vec3(2, 2, 2));
		/*quadEntity->transfrom.setScale(glm::vec3(100, 100, 100));
		quadEntity->transfrom.rotate(glm::vec3(90, 0, 0));*/

		scene->setMainCamera(new Camera(glm::vec3(-4.31142f, 55.923f, 191.538f), glm::vec3(-16.8f, -89.1506f, 0), 90.0f, float(SCREEN_WIDTH)/float(SCREEN_HEIGHT), 8.0f, 1000.0f));
		scene->createPointLight(glm::vec4(-10, 50, 5, 1.0), glm::vec4(0.5f, 0.01, 0.01, 1.0), glm::vec4(1, 0, 0, 1.0), glm::vec4(1, 1, 1, 1.0));
		scene->createPointLight(glm::vec4(-10, 150, 80, 1.0), glm::vec4(0.01, 0.5f, 0.01, 1.0), glm::vec4(1, 1, 1, 1.0), glm::vec4(0.1, 0.1, 0.1, 1.0));
		scene->createPointLight(glm::vec4(-10, 150, -80, 1.0), glm::vec4(0.01, 0.01, 0.5, 1.0), glm::vec4(0, 1, 0, 1.0), glm::vec4(0.1, 0.1, 0.1, 1.0));
		scene->createPointLight(glm::vec4(300, 10, 5, 1.0), glm::vec4(0.01, 0.01, 0.5, 1.0), glm::vec4(1, 0, 0, 1.0), glm::vec4(0.1, 0.1, 0.1, 1.0));
		//scene->createPointLight(glm::vec3(-300, 10, 5), glm::vec3(0.01, 0.01, 0.01), glm::vec3(0, 0, 1), glm::vec3(05, 0, 1));
		scene->createDirectionalLight(glm::vec4(0.5f, -1.0f, 0, 1.0), glm::vec4(0.2f, 0.2f, 0.2f, 1.0f), glm::vec4(0.6f, 0.6f, 0.6f, 1.0f), glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));
		cameraController = new CameraController(scene->getMainCamera());
		return true;
	}

	void update() {
		crysisEntity->transfrom.rotate(glm::vec3(0, 0.005, 0));
		//quadEntity->transfrom.rotate(glm::vec3(0.005f, 0, 0));
		cameraController->update();
		scene->update();
	}
};

#endif // !TEST_WORLD