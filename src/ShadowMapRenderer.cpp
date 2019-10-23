#include "ShadowMapRenderer.h"

ShadowMapRenderer::ShadowMapRenderer()
{
	depthMap = ResourceManager::getInstance()->generateTexture("ShadowMap",
		TextureType::DEPTH, NULL, SHADOW_WIDTH, SHADOW_HEIGHT, GL_DEPTH_COMPONENT, GL_FLOAT);
	depthMapFbo = new FrameBuffer();
	depthMapFbo->attachDepthTarget(depthMap, 0);
}

void ShadowMapRenderer::render(Scene * scene)
{
	glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
	depthMapFbo->bind();
	glClear(GL_DEPTH_BUFFER_BIT);
	sceneRenderer.renderScene(scene);
	depthMapFbo->unBind();
}

//glm::mat4 ShadowMapRenderer::calculateLightSpaceTransfrom(DirectionalLight * directionalLight)
//{
//	glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 1.0f, 3000.0f);
//	glm::mat4 lightView = glm::lookAt(directionalLight.)
//	return glm::mat4();
//}
