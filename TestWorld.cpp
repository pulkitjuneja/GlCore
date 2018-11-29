#pragma once 

#ifndef TEST_WORLD
#define TEST_WORLD

#include "src/Engine.h"
#include "src/Mesh.h"
#include "src/Globals.h"
#include "src/MeshRenderer.h"
#include "src/ResourceManager.hpp"
#include "Entity.h"
#include "EntityManager.h"
#include "Model.h"

class TestWorld : public Engine {

	Entity crysisEntity;
	Entity planeEntity;
	EntityManager rootManager;
public:
	TestWorld() {};
	bool init() {
		vector<Vertex> vertices = {
			Vertex(glm::vec3(0.5f,0.5f,0),glm::vec3(0,0,-1),glm::vec2(0.5,0.5)),
			Vertex(glm::vec3(0.5f,-0.5f,0),glm::vec3(0,0,-1),glm::vec2(0.5,0.5)),
			Vertex(glm::vec3(-0.5f,-0.5f,0),glm::vec3(0,0,-1),glm::vec2(0.5,0.5)),
			Vertex(glm::vec3(-0.5f,0.5f,0),glm::vec3(0,0,-1),glm::vec2(0.5,0.5)),
		};

		vector<unsigned int> indices = { 0,1,3,1,2,3 };
		Model* model = new Model(string("F:/Projects/libraries/crysisM/nanosuit.obj"));
		model->shader = ResourceManager::getInstance()->getShader("defaultShader");
		Model* planeModel = new Model(vertices, indices);
		planeModel->shader = ResourceManager::getInstance()->getShader("defaultShader");
		planeEntity.setRenderer(planeModel);
		crysisEntity.setRenderer(model);
		Camera* camera = new Camera(glm::vec3(0, 0, 10), glm::vec3(0, 0, 1));
		rootManager.setCamera(camera);
		rootManager.addEntity(&crysisEntity);
		rootManager.addEntity(&planeEntity);
		crysisEntity.transfrom.setScale(glm::vec3(0.2, 0.2, 0.2));
		planeEntity.transfrom.setScale(glm::vec3(2, 2, 2));
		planeEntity.transfrom.translate(glm::vec3(0, 1, 0));
		return true;
	}

	void update() {
		crysisEntity.transfrom.rotate(glm::vec3(0, 0.0005, 0));
	}

	void render() {
		cout << "updated code running";
		rootManager.updateAndRenderEntities();
	}
};

#endif // !TEST_WORLD