#include "Renderer.h"

Renderer::Renderer()
{
	ResourceManager::getInstance()->perFrameUbo = new UniformBuffer(sizeof(PerFrameUniforms), 0);
}

void Renderer::setScene(Scene* scene)
{
	this->scene = scene;
}

void Renderer::render()
{
	glClearColor(0.3f, 0.4f, 0.6f, 1.0f);

	// Render Shadow map pass
	glClear(GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, shadowMaprender.SHADOW_WIDTH, shadowMaprender.SHADOW_HEIGHT);
	shadowMaprender.updateLightSpaceMatrix(scene);

	//Update Global Uniform blocks
	sceneRenderer.setGlobalUniforms(perFrameUniforms, scene);
	void* mem = ResourceManager::getInstance()->perFrameUbo->mapToMemory(GL_WRITE_ONLY);

	if (mem) {
		memcpy(mem, &perFrameUniforms, sizeof(PerFrameUniforms));
		ResourceManager::getInstance()->perFrameUbo->unmapFromMemroy();
	}

	shadowMaprender.render(scene);

	//Render Scene normally
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	sceneRenderer.renderScene(scene);


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
	//quadMaterial->setShader(ResourceManager::getInstance()->getShader("defaultShader"));

	//vector<SubMesh> quadSubmeshes = {
	//	SubMesh(quadMaterial,0,6,0)
	//};

	//Entity* ent = scene->createEntity<Entity>("shadowMap", new Mesh(quadVertices, quadIndices, quadSubmeshes));

	//if (ent->mesh == nullptr) {
	//	return;
	//}

	//Mesh* currentMesh = ent->mesh;
	//glBindVertexArray(currentMesh->VAO);

	//Shader* currentShader = nullptr;

	//for (int i = 0; i < currentMesh->subMeshes.size(); i++) {

	//	SubMesh currentSubMesh = currentMesh->subMeshes[i];
	//	Shader* submeshShader = currentSubMesh.material->getShader();

	//	if (!currentShader) {
	//		currentShader = submeshShader;
	//		currentShader->use();
	//		sceneRenderer.setGlobalUniforms(currentShader);
	//	}

	//	currentShader->setMat4("modelMatrix", &ent->getTransform()->getTransformationMatrix()[0][0]);

	//	unsigned int diffuseNr = 0;
	//	unsigned int specularNr = 0;

	//	for (int j = 0; j < currentSubMesh.material->textures.size(); j++) {
	//		Texture* currentTexture = currentSubMesh.material->textures[j];
	//		string name, number;
	//		if (currentTexture->type == TextureType::DIFFUSE) {
	//			name = "texture_diffuse";
	//			number = std::to_string(diffuseNr++);
	//		}

	//		currentTexture->bind(GL_TEXTURE0 + j);
	//		currentShader->setInt("material." + name + "[" + number + "]", j);
	//	}

	//	currentShader->setInt("material.specularCount", specularNr);
	//	currentShader->setInt("material.diffuseCount", diffuseNr);
	//	glDrawElementsBaseVertex(GL_TRIANGLES, currentSubMesh.indexCount, GL_UNSIGNED_INT, (void*)(sizeof(unsigned int) * currentSubMesh.baseIndex), currentSubMesh.baseVertex);

	//}
}
