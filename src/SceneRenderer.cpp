#include "Renderer.h"

void SceneRenderer::setGlobalUniforms(PerFrameUniforms &perFrameUniforms, Scene* scene)
{
	Camera* mainCamera = scene->getMainCamera();
	perFrameUniforms.viewMatrix = mainCamera->getViewMatrix();
	perFrameUniforms.projectionMatrix = mainCamera->getProjectionMatrix();

	// set directional light
	perFrameUniforms.directionalLight = *scene->getDirectionalLight();

	// set pointlight(s) into shader
	auto pointLights = scene->getPointLIghts();
	for (int i = 0; i < pointLights.size(); i++) {
		perFrameUniforms.pointLights[i] = *pointLights[i];
		//string prefixString = "pointLights[" + std::to_string(i) + "].";
		//shader->setFloat3(prefixString + "position", pointLights[i]->position.x, pointLights[i]->position.y, pointLights[i]->position.z);
		//shader->setFloat3(prefixString + "diffuse", pointLights[i]->diffuse.r, pointLights[i]->diffuse.g, pointLights[i]->diffuse.b);
		//shader->setFloat3(prefixString + "specular", pointLights[i]->specular.r, pointLights[i]->specular.g, pointLights[i]->specular.b);
		//shader->setFloat3(prefixString + "ambient", pointLights[i]->ambient.r, pointLights[i]->ambient.g, pointLights[i]->ambient.b);
		//shader->setFloat(prefixString + "linearAttenuation", 0.0025);
		//shader->setFloat(prefixString + "quadraticAttenuation", 0.00007);
	}
	perFrameUniforms.pointLightCount = pointLights.size();
	perFrameUniforms.lightSpaceMatrix = scene->directionalLightSpaceMatrix;
	//shader->setInt("pointLightCount", pointLights.size());
	//shader->setFloat3("cameraPosition", mainCamera->transform.getPosition().x, mainCamera->transform.getPosition().y, mainCamera->transform.getPosition().z);

	//// Uniforms for shadow mapping
	//shader->setMat4("lightSpaceMatrix", &scene->directionalLightSpaceMatrix[0][0]);
	//shader->setInt("shadowMap", 10);
}

void SceneRenderer::bindGlobalMaps()
{
	Texture* depthMapTexture = ResourceManager::getInstance()->getTexture(SHADOW_MAP);
	if (depthMapTexture) {
		depthMapTexture->bind(GL_TEXTURE0 + 10);
	}
}

void SceneRenderer::renderScene(Scene * scene, Material* overrideMaterial)
{
	std::vector<Entity*> entities = scene->getEntities();;
	std::vector<Entity*>::iterator it = entities.begin();

	bindGlobalMaps();

	for (; it != entities.end(); it++) {
		Entity* ent = (*it);

		if (ent->mesh == nullptr) {
			return;
		}

		Mesh* currentMesh = ent->mesh;
		glBindVertexArray(currentMesh->VAO);

		Shader* currentShader = nullptr;
		if(overrideMaterial) {
			currentShader = overrideMaterial->getShader();
			currentShader->use();
		}

		for (int i = 0; i < currentMesh->subMeshes.size(); i++) {

			SubMesh currentSubMesh = currentMesh->subMeshes[i];
			Shader* submeshShader = currentSubMesh.material->getShader();

			if (!currentShader) {
				currentShader = submeshShader;
				currentShader->use();
			}

			if (!overrideMaterial && submeshShader->shaderName.compare(currentShader->shaderName)) {
				currentShader = submeshShader;
				currentShader->use();
			}

			currentShader->setMat4("modelMatrix", &ent->getTransform()->getTransformationMatrix()[0][0]);

			unsigned int diffuseNr = 0;
			unsigned int specularNr = 0;

			for (int j = 0; j < currentSubMesh.material->textures.size(); j++) {
				Texture* currentTexture = currentSubMesh.material->textures[j];
				string name, number;
				if (currentTexture->type == TextureType::DIFFUSE) {
					name = "texture_diffuse";
					number = std::to_string(diffuseNr++);
				}
				else if (currentTexture->type == TextureType::SPECULAR) {
					name = "texture_specular";
					number = std::to_string(specularNr++);
				}

				currentTexture->bind(GL_TEXTURE0 + j);
				currentShader->setInt("material." + name + "[" + number + "]", j);
			}

			currentShader->setInt("material.specularCount", specularNr);
			currentShader->setInt("material.diffuseCount", diffuseNr);
			glDrawElementsBaseVertex(GL_TRIANGLES, currentSubMesh.indexCount, GL_UNSIGNED_INT, (void*)(sizeof(unsigned int) * currentSubMesh.baseIndex), currentSubMesh.baseVertex);

		}
	}
	glBindVertexArray(0);
}
