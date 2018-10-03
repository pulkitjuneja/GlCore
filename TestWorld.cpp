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

class TestWorld : public Engine {

	Entity meshEntity;
	EntityManager rootManager;
public:
	TestWorld() {};
	bool init() {
		vector<float> vertices = {
		  0.5f,  0.5f, 0.0f,
		  0.5f, -0.5f, 0.0f, 
		 -0.5f, -0.5f, 0.0f, 
		 -0.5f,  0.5f, 0.0f  };

		vector<unsigned int> indices = { 0,1,2,2,3,0 };
		Mesh* mesh = new Mesh(vertices, indices);
		MeshRenderer*  meshRenderer = new MeshRenderer(mesh, ResourceManager::getInstance()->getShader("defaultShader"));
		Camera* camera = new Camera(glm::vec3(0, 0, 10), glm::vec3(0, 0, 1));
		rootManager.setCamera(camera);
		meshEntity.setRenderer(meshRenderer);
		rootManager.addEntity(&meshEntity);
		return true;
	}

	void update() {
	}

	void render() {
		cout << "updated code running";
		rootManager.updateAndRenderEntities();
	}
};

#endif // !TEST_WORLD
