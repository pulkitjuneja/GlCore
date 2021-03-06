#include "ShadowMapRenderer.h"

ShadowMapRenderer::ShadowMapRenderer()
{
	depthMap = ResourceManager::getInstance()->generateTexture(SHADOW_MAP,
		TextureType::DEPTH, SHADOW_WIDTH, SHADOW_HEIGHT, GL_DEPTH_COMPONENT, GL_DEPTH_COMPONENT, GL_FLOAT, 1);
	depthMap->bind();
	depthMap->setMinMagFilter(GL_NEAREST, GL_NEAREST);
	depthMap->setWrapping(GL_CLAMP_TO_BORDER, GL_CLAMP_TO_BORDER);
	depthMap->Unbind();
	depthMapMaterial = new Material();
	depthMapMaterial->setShader(ResourceManager::getInstance()->getShader("depthMap"));
	depthMapFbo = new FrameBuffer();
	depthMapFbo->attachDepthTarget(depthMap,0,0);

	GLenum Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

	if (Status != GL_FRAMEBUFFER_COMPLETE) {
		printf("Shadow frame buffer error, status: 0x%x\n", Status);
	}
}

void ShadowMapRenderer::render(Scene * scene)
{
	depthMapFbo->bind();
	sceneRenderer.renderScene(scene, depthMapMaterial);
	depthMapFbo->unBind();
}

void ShadowMapRenderer::updateLightSpaceMatrix(Scene* scene)
{
	Camera* camera = scene->getMainCamera();
	glm::vec3 directionalLightDirection = scene->getDirectionalLight()->direction;

	glm::vec3 * frustumCorners = camera->getFrustumCorners();
	glm::vec3 frustumCenter = glm::vec3(0.0f, 0.0f, 0.0f);

	for (int i = 0; i < 8; i++)
		frustumCenter += frustumCorners[i];

	frustumCenter /= 8.0f;
	float frustumExtents = 100;
	glm::vec3 temporaryLightPos = frustumCenter - (directionalLightDirection * frustumExtents); //
	glm::mat4 lightView = glm::lookAt(temporaryLightPos, frustumCenter, camera->cameraUP);

	float minY = FLT_MAX;
	float minX = FLT_MAX;
	float maxY = FLT_MIN;
	float maxX = FLT_MIN;

	frustumCorners = camera->getFrustumCorners();

	for (int i = 0; i < 8; i++) {
		glm::vec3 transformedCorner = lightView * glm::vec4(frustumCorners[i], 1.0f);
		minY = std::min(minY, transformedCorner.y);
		maxY = std::max(maxY, transformedCorner.y);
		minX = std::min(minX, transformedCorner.x);
		maxX = std::max(maxX, transformedCorner.x);
	}

	glm::mat4 ortho = glm::ortho(minX, maxX, minY, maxY, 2.0f, frustumExtents + 500);
	scene->directionalLightSpaceMatrix = ortho * lightView;
}
