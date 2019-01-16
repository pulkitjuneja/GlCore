#pragma once

#include "Scene.h"

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

	// set light(s) into shader
	for (int i = 0; i < Lights.size(); i++) {
		shader->setFloat3("light.position", Lights[i]->position.x, Lights[i]->position.y, Lights[i]->position.z);
		shader->setFloat3("light.diffuse", Lights[i]->diffuse.r, Lights[i]->diffuse.g, Lights[i]->diffuse.b);
		shader->setFloat3("light.specular", Lights[i]->specular.r, Lights[i]->specular.g, Lights[i]->specular.b);
		shader->setFloat3("light.ambient", Lights[i]->ambient.r, Lights[i]->ambient.g, Lights[i]->ambient.b);
	}

	shader->setFloat3("cameraPosition", mainCamera->position.x, mainCamera->position.y, mainCamera->position.z);
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

			unsigned int diffuseNr = 0;
			unsigned int specularNr = 0;

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
