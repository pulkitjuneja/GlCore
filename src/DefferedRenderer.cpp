#include "DefferedRenderer.h"


DefferedRenderer::DefferedRenderer()
{
	gBuffer = new FrameBuffer();
	gBuffer->bind();

	gBufferPositionTexture = ResourceManager::getInstance()->generateTexture(G_BUFFER_POSITION_TEXTURE_NAME, TextureType::DIFFUSE,
		SCREEN_WIDTH, SCREEN_HEIGHT, GL_RGBA, GL_RGBA16F, GL_FLOAT, 1);
	gBufferPositionTexture->bind();
	gBufferPositionTexture->setMinMagFilter(GL_NEAREST, GL_NEAREST);
	gBuffer->attachRenderTarget(gBufferPositionTexture, 0, 0);

	gBufferNormalTexture = ResourceManager::getInstance()->generateTexture(G_BUFFER_NORMAL_TEXTURE_NAME, TextureType::DIFFUSE,
		SCREEN_WIDTH, SCREEN_HEIGHT, GL_RGBA, GL_RGBA16F, GL_FLOAT, 1);
	gBufferNormalTexture->bind();
	gBufferNormalTexture->setMinMagFilter(GL_NEAREST, GL_NEAREST);
	gBuffer->attachRenderTarget(gBufferNormalTexture, 0, 1);

	gBufferColorTexture = ResourceManager::getInstance()->generateTexture(G_BUFFER_COLOR_TEXTURE_NAME, TextureType::DIFFUSE,
		SCREEN_WIDTH, SCREEN_HEIGHT, GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE, 1);
	gBufferColorTexture->bind();
	gBufferColorTexture->setMinMagFilter(GL_NEAREST, GL_NEAREST);
	gBuffer->attachRenderTarget(gBufferColorTexture, 0, 2);


	// TODO: use this buffer to reconstruct world position 
	gBUfferDepthTexture = ResourceManager::getInstance()->generateTexture(G_BUFFER_DEPTH_TEXTURE_NAME, TextureType::DEPTH,
		SCREEN_WIDTH, SCREEN_HEIGHT, GL_DEPTH_COMPONENT, GL_DEPTH_COMPONENT, GL_FLOAT, 1);
	gBUfferDepthTexture->bind();
	gBUfferDepthTexture->setMinMagFilter(GL_LINEAR, GL_LINEAR);
	gBUfferDepthTexture->setWrapping(GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);
	gBuffer->attachDepthTarget(gBUfferDepthTexture, 0);

	unsigned int attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
	glDrawBuffers(3, attachments);

	gBuffer->attachRenderBuffer(GL_DEPTH_COMPONENT, GL_DEPTH_ATTACHMENT, SCREEN_WIDTH, SCREEN_HEIGHT);
	gBuffer->checkStatus();
	gBuffer->unBind();

	perFrameUbo = new UniformBuffer(sizeof(PerFrameUniforms), 0);
	std::cout << glGetError() << std::endl;
}

void DefferedRenderer::setScene(Scene* scene)
{
	this->scene = scene;
}

void DefferedRenderer::runGeometryPass()
{
	sceneRenderer.setGlobalUniforms(perFrameUniforms, scene);

	void* mem = perFrameUbo->mapToMemory(GL_WRITE_ONLY);

	if (mem) {
		memcpy(mem, &perFrameUniforms, sizeof(PerFrameUniforms));
		perFrameUbo->unmapFromMemroy();
	}

	gBuffer->bind();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Material* gBufferMaterial = new Material();
	gBufferMaterial->setShader(ResourceManager::getInstance()->getShader("defferedGeometryPass"));
	sceneRenderer.renderScene(scene, gBufferMaterial, true);
	gBuffer->unBind();
}

void DefferedRenderer::render()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	runGeometryPass();

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// render scene normall for testing
	sceneRenderer.renderScene(scene);
}
