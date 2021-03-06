#include "Renderer.h"

void SceneRenderer::setGlobalUniforms(PerFrameUniforms &perFrameUniforms, Scene* scene)
{
	Camera* mainCamera = scene->getMainCamera();
	perFrameUniforms.viewMatrix = mainCamera->getViewMatrix();
	perFrameUniforms.projectionMatrix = mainCamera->getProjectionMatrix();
	glm::vec3 cameraPosition = mainCamera->transform.getPosition();
	perFrameUniforms.cameraPosition = glm::vec4(cameraPosition.x, cameraPosition.y, cameraPosition.z, 1.0f);

	// set directional light
	perFrameUniforms.directionalLight = *scene->getDirectionalLight();

	// set pointlight(s) into shader
	auto pointLights = scene->getPointLIghts();
	for (int i = 0; i < pointLights.size(); i++) {
		perFrameUniforms.pointLights[i] = *pointLights[i];
	}
	perFrameUniforms.pointLightCount = pointLights.size();
	perFrameUniforms.lightSpaceMatrix = scene->directionalLightSpaceMatrix;
}

void SceneRenderer::bindGlobalMaps()
{
	Texture* depthMapTexture = ResourceManager::getInstance()->getTexture(CSM_SHADOW_MAPS);
	if (depthMapTexture) {
		depthMapTexture->bind(GL_TEXTURE0 + 10);
	}
}

void SceneRenderer::renderScene(Scene * scene, Material* overrideMaterial, bool passBaseMaterialProperties)
{
	std::vector<Entity*> entities = scene->getEntities();
	std::vector<Entity*>::iterator it = entities.begin();

	for (; it != entities.end(); it++) {
		Entity* ent = (*it);

		if (ent->mesh == nullptr) {
			return;
		}

		Mesh* currentMesh = ent->mesh;
		glBindVertexArray(currentMesh->VAO);

		glm::mat4 modelMatrix = ent->getTransform()->getTransformationMatrix();

		Shader* currentShader = nullptr;

		for (int i = 0; i < currentMesh->subMeshes.size(); i++) {

			SubMesh currentSubMesh = currentMesh->subMeshes[i];
			Shader* submeshShader = currentSubMesh.material->getShader();

			if (overrideMaterial) {
				currentShader = overrideMaterial->getShader();
			}
			else {
				currentShader = submeshShader;
			}

			currentShader->use();
			currentShader->setMat4("modelMatrix", modelMatrix);
			//currentShader->setMat4("normalMatrix", glm::transpose(glm::inverse(modelMatrix)));

			unsigned int hasSpecularMap = 0;
			unsigned int hasNormalMap = 0;
			int j = 0;
			if (!overrideMaterial || (overrideMaterial && passBaseMaterialProperties)) {
				//for (j= 0; j < currentSubMesh.material->textures.size(); j++) {
				//	Texture* currentTexture = currentSubMesh.material->textures[j];
				//	string name, number;
				//	if (currentTexture->type == TextureType::DIFFUSE) {
				//		name = "texture_diffuse";
				//		number = std::to_string(diffuseNr++);
				//	}
				//	else if (currentTexture->type == TextureType::SPECULAR) {
				//		name = "texture_specular";
				//		number = std::to_string(specularNr++);
				//	}

				//	currentTexture->bind(GL_TEXTURE0 + j);
				//	currentShader->setInt("material." + name + "[" + number + "]", j);
				//}
				if (currentSubMesh.material->diffuseMap != NULL) {
					currentSubMesh.material->diffuseMap->bind(GL_TEXTURE0 + 1);
					currentShader->setInt("material.texture_diffuse", 1);
				}
				if (currentSubMesh.material->specularMap != NULL) {
					currentSubMesh.material->specularMap->bind(GL_TEXTURE0 + 2);
					currentShader->setInt("material.texture_specular", 2);
					hasSpecularMap = 1;
				}
				if (currentSubMesh.material->normalMap != NULL) {
					currentSubMesh.material->normalMap->bind(GL_TEXTURE0 + 3);
					currentShader->setInt("material.texture_normal", 3);
					hasNormalMap = 1;
				}
				currentShader->setInt("material.hasNormalMap", hasNormalMap);
				currentShader->setInt("material.hasSpecularMap", hasSpecularMap);
			}
			currentShader->setInt("shadowMap", 10);
			glDrawElementsBaseVertex(GL_TRIANGLES, currentSubMesh.indexCount, GL_UNSIGNED_INT, (void*)(sizeof(unsigned int) * currentSubMesh.baseIndex), currentSubMesh.baseVertex);
			
		}
	}
	glBindVertexArray(0);
}
