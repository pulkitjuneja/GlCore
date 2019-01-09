#pragma once

#include "Scene.h"

Entity * Scene::createEntity(string name, Mesh* mesh, Material* overrideMat)
{
	Entity* ent = new Entity(name);
	if (mesh != nullptr) {
		ent->mesh = mesh;
	}
	if (overrideMat != nullptr) {
		ent->overrideMaterial = overrideMat;
	}

	Entities.push_back(ent);
	return ent;
}

Entity * Scene::lookupEntity(string name)
{
	return nullptr;
}

std::vector<Entity*>& Scene::getEntities()
{
	return Entities;
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

void Scene::setGlobalUniforms(Shader * shader)
{
	glm::mat4 viewMatrix = mainCamera->getViewMatrix();
	glm::mat4 projectionMatrix = mainCamera->getProjectionMatrix();
	shader->setMat4("viewMatrix", &viewMatrix[0][0]);
	shader->setMat4("projectionMatrix", &projectionMatrix[0][0]);
}

void Scene::RenderEntities()
{
	std::vector<Entity*>::iterator it = Entities.begin();
	for (; it != Entities.end(); it++) {
		Entity* ent = (*it);

		if (ent->mesh == nullptr) {
			return;
		}

		Mesh* currentMesh = ent->mesh;
		glBindVertexArray(currentMesh->VAO);

		for (int i = 0; i < currentMesh->subMeshes.size(); i++) {

			SubMesh currentSubMesh = currentMesh->subMeshes[i];
			Shader* shader = currentSubMesh.material->getShader();

			setGlobalUniforms(shader);
			shader->setMat4("modelMatrix", &ent->getTransform()->getTransformationMatrix()[0][0]);

			unsigned int diffuseNr = 1;
			unsigned int specularNr = 1;

			for (int j = 0; j < currentSubMesh.material->textures.size(); j++) {
				Texture* currentTexture = currentSubMesh.material->textures[j];
				glActiveTexture(GL_TEXTURE0 + j);
				string name, number;
				if (currentTexture->type == TextureType::DIFFUSE) {
					name = "texture_diffuse";
					number = std::to_string(diffuseNr++);
				}
				else if (currentTexture->type == TextureType::SPECULAR) {
					name = "texture_specular";
					number = std::to_string(specularNr++);
				}

				shader->setInt("material." + name + "[" + number + "]", j);
				glBindTexture(GL_TEXTURE_2D, currentTexture->id);
			}

			shader->use();
			glDrawElementsBaseVertex(GL_TRIANGLES, currentSubMesh.indexCount, GL_UNSIGNED_INT, (void*)(sizeof(unsigned int) * currentSubMesh.baseIndex), currentSubMesh.baseVertex);

		}
		glBindVertexArray(0);
	}
}
