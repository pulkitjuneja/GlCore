#include "Renderer.h"

void SceneRenderer::setGlobalUniforms(Shader* shader)
{
	Camera* mainCamera = scene->getMainCamera();
	glm::mat4 viewMatrix = mainCamera->getViewMatrix();
	glm::mat4 projectionMatrix = mainCamera->getProjectionMatrix();
	shader->setMat4("viewMatrix", &viewMatrix[0][0]);
	shader->setMat4("projectionMatrix", &projectionMatrix[0][0]);

	// set directional light
	DirectionalLight* directionalLight = scene->getDirectionalLight();
	if (directionalLight != nullptr) {
		shader->setFloat3("directionalLight.direction", directionalLight->direction.x, directionalLight->direction.y, directionalLight->direction.z);
		shader->setFloat3("directionalLight.diffuse", directionalLight->diffuse.r, directionalLight->diffuse.g, directionalLight->diffuse.b);
		shader->setFloat3("directionalLight.specular", directionalLight->specular.r, directionalLight->specular.g, directionalLight->specular.b);
		shader->setFloat3("directionalLight.ambient", directionalLight->ambient.r, directionalLight->ambient.g, directionalLight->ambient.b);
	}

	// set pointlight(s) into shader
	auto pointLights = scene->getPointLIghts();
	for (int i = 0; i < pointLights.size(); i++) {
		string prefixString = "pointLights[" + std::to_string(i) + "].";
		shader->setFloat3(prefixString + "position", pointLights[i]->position.x, pointLights[i]->position.y, pointLights[i]->position.z);
		shader->setFloat3(prefixString + "diffuse", pointLights[i]->diffuse.r, pointLights[i]->diffuse.g, pointLights[i]->diffuse.b);
		shader->setFloat3(prefixString + "specular", pointLights[i]->specular.r, pointLights[i]->specular.g, pointLights[i]->specular.b);
		shader->setFloat3(prefixString + "ambient", pointLights[i]->ambient.r, pointLights[i]->ambient.g, pointLights[i]->ambient.b);
		shader->setFloat(prefixString + "linearAttenuation", 0.0025);
		shader->setFloat(prefixString + "quadraticAttenuation", 0.00007);
	}
	shader->setInt("pointLightCount", pointLights.size());

	shader->setFloat3("cameraPosition", mainCamera->transform.getPosition().x, mainCamera->transform.getPosition().y, mainCamera->transform.getPosition().z);
}

void SceneRenderer::renderScene(Scene * scene)
{
	this->scene = scene;
	std::vector<Entity*> entities = scene->getEntities();;
	std::vector<Entity*>::iterator it = entities.begin();
	for (; it != entities.end(); it++) {
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
				glBindTexture(GL_TEXTURE_2D, currentTexture->textureId);
			}

			shader->setInt("material.specularCount", specularNr);
			shader->setInt("material.diffuseCount", diffuseNr);
			shader->use();
			glDrawElementsBaseVertex(GL_TRIANGLES, currentSubMesh.indexCount, GL_UNSIGNED_INT, (void*)(sizeof(unsigned int) * currentSubMesh.baseIndex), currentSubMesh.baseVertex);

		}
		glBindVertexArray(0);
	}
}
