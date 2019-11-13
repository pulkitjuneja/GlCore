#include "ShadowMapRenderer.h"

ShadowMapRenderer::ShadowMapRenderer()
{
	depthMap = ResourceManager::getInstance()->generateTexture(SHADOW_MAP,
		TextureType::DEPTH, NULL, SHADOW_WIDTH, SHADOW_HEIGHT, GL_DEPTH_COMPONENT, GL_FLOAT);
	depthMapMaterial = new Material();
	depthMapMaterial->setShader(ResourceManager::getInstance()->getShader("depthMap"));
	depthMapFbo = new FrameBuffer();
	depthMapFbo->attachDepthTarget(depthMap, 0);
}

void ShadowMapRenderer::render(Scene * scene)
{
	glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
	depthMapFbo->bind();
	glClear(GL_DEPTH_BUFFER_BIT);
	updateLightSpaceMatrix(scene);
	sceneRenderer.renderScene(scene, depthMapMaterial);
	depthMapFbo->unBind();
}

void ShadowMapRenderer::updateLightSpaceMatrix(Scene* scene)
{
	Camera* camera = scene->getMainCamera();
	glm::vec3 directionalLightDirection = scene->getDirectionalLight()->direction;

	//glm::vec3 center = camera->transform.getPosition() + camera->front * 50.0f;
	//glm::vec3 temporaryLightPos = center - directionalLightDirection * ((camera->farPlane - camera->nearPlane) / 2.0f);

	//glm::mat4 lightView = glm::lookAt(temporaryLightPos, center, camera->cameraUP);

	glm::vec3 * frustumCorners = camera->getFrustumCorners();
	glm::vec3 frustumCenter = glm::vec3(0.0f, 0.0f, 0.0f);

	for (int i = 0; i < 8; i++)
		frustumCenter += frustumCorners[i];

	frustumCenter /= 8.0f;

	float radius = 0.0f;

	for (int i = 0; i < 8; i++)
	{
		float length = glm::length(frustumCorners[i] - frustumCenter);
		radius = glm::max(radius, length);
	}

	radius = ceil(radius * 16.0f) / 16.0f;

	// Find bounding box that fits the sphere
	glm::vec3 radius3(radius, radius, radius);

	glm::vec3 max = radius3;
	glm::vec3 min = -radius3;

	glm::vec3 frustumExtents = max - min;

	float nearOffset = 300.0f; // need to figure out how to calculate this;

	// Push the light position back along the light direction by an offset (not sure how to calculate this)
	glm::vec3 shadowCameraPos = frustumCenter - directionalLightDirection * nearOffset;

	glm::mat4 ortho = glm::ortho(min.x, max.x, min.y, max.y, -nearOffset, nearOffset + frustumExtents.z);
	glm::mat4 view = glm::lookAt(shadowCameraPos, frustumCenter, camera->cameraUP);

	scene->directionalLightSpaceMatrix = ortho * view;
}
