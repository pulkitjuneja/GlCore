//#include "ShadowMapRenderer.h"
//
//ShadowMapRenderer::ShadowMapRenderer()
//{
//	glGenTextures(1, &depthMap);
//	glBindTexture(GL_TEXTURE_2D, depthMap);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
//		SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//
//	glGenFramebuffers(1, &depthMapFBO);
//	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
//	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
//	glDrawBuffer(GL_NONE);
//	glReadBuffer(GL_NONE);
//	glBindFramebuffer(GL_FRAMEBUFFER, 0);
//}
//
//void ShadowMapRenderer::renderDepthMap(Scene * scene)
//{
//	glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
//	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
//	glClear(GL_DEPTH_BUFFER_BIT);
//	sceneRenderer.renderScene(scene);
//	glBindFramebuffer(GL_FRAMEBUFFER, 0);
//}
//
//glm::mat4 ShadowMapRenderer::calculateLightSpaceTransfrom(DirectionalLight * directionalLight)
//{
//	glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 1.0f, 3000.0f);
//	glm::mat4 lightView = glm::lookAt(directionalLight.)
//	return glm::mat4();
//}
