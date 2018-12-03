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
	EntityManager rootManager;
public:
	TestWorld() {};
	bool init() {

		ResourceManager::getInstance()->loadShader("Shaders/TexturedMesh.vert", "Shaders/TexturedMesh.frag", "texturedMeshShader");

		vector<Vertex> vertices = {
			Vertex(glm::vec3(0.5f,0.5f,0),glm::vec3(0,0,-1),glm::vec2(0.5,0.5)),
			Vertex(glm::vec3(0.5f,-0.5f,0),glm::vec3(0,0,-1),glm::vec2(0.5,0.5)),
			Vertex(glm::vec3(-0.5f,-0.5f,0),glm::vec3(0,0,-1),glm::vec2(0.5,0.5)),
			Vertex(glm::vec3(-0.5f,0.5f,0),glm::vec3(0,0,-1),glm::vec2(0.5,0.5)),
		};

		vector<unsigned int> indices = { 0,1,3,1,2,3 };
		Model* model = new Model(string("F:/Projects/libraries/crysisM/nanosuit.obj"));
		model->shader = ResourceManager::getInstance()->getShader("texturedMeshShader");
		crysisEntity.setRenderer(model);
		Camera* camera = new Camera(glm::vec3(0, 0, 15), glm::vec3(0, 0, -1));
		rootManager.setCamera(camera);
		rootManager.addEntity(&crysisEntity);
		crysisEntity.transfrom.setPosition(glm::vec3(0,-4, 0));
		crysisEntity.transfrom.setScale(glm::vec3(0.4, 0.4, 0.4));
		return true;
	}

	void update() {
		crysisEntity.transfrom.rotate(glm::vec3(0, 0.0005, 0));
	}

	void render() {
		rootManager.updateAndRenderEntities();
	}
};

#endif // !TEST_WORLD