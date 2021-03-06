#include "DefferedRenderer.h"


void DefferedRenderer::createUVSphere()
{
	int stacks = 10;
	int slices = 10;
	const float PI = 3.14f;

	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

	// loop through stacks.
	for (int i = 0; i <= stacks; ++i) {

		float V = (float)i / (float)stacks;
		float phi = V * PI;

		// loop through the slices.
		for (int j = 0; j <= slices; ++j) {

			float U = (float)j / (float)slices;
			float theta = U * (PI * 2);

			// use spherical coordinates to calculate the positions.
			float x = cos(theta) * sin(phi);
			float y = cos(phi);
			float z = sin(theta) * sin(phi);
			Vertex vertex;
			vertex.position = glm::vec3(x, y, z);
			vertices.push_back(vertex);
		}
	}

	// Calc The Index Positions
	for (int i = 0; i < slices * stacks + slices; ++i) {
		indices.push_back(GLuint(i));
		indices.push_back(GLuint(i + slices + 1));
		indices.push_back(GLuint(i + slices));

		indices.push_back(GLuint(i + slices + 1));
		indices.push_back(GLuint(i));
		indices.push_back(GLuint(i + 1));
	}
	std::vector<SubMesh> submeshes;
	submeshes.resize(1);
	submeshes[0].indexCount = indices.size();
	pointVolumeMesh = new Mesh(vertices, indices, submeshes, false, false, false);
}

void DefferedRenderer::setupGBuffer()
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

	gBuffer->attachRenderBuffer(GL_DEPTH_COMPONENT, GL_DEPTH_ATTACHMENT, SCREEN_WIDTH, SCREEN_HEIGHT);
	gBuffer->checkStatus();
	gBuffer->unBind();
}

void DefferedRenderer::setupHDRBuffer()
{
	HDRBBuffer = new FrameBuffer();
	HDRBBuffer->bind();

	HDRBUfferTexture = ResourceManager::getInstance()->generateTexture(HDR_BUFFER_TEXTURE_NAME, TextureType::DIFFUSE,
		SCREEN_WIDTH, SCREEN_HEIGHT, GL_RGBA, GL_RGBA16F, GL_FLOAT, 1);
	HDRBUfferTexture->bind();
	HDRBUfferTexture->setMinMagFilter(GL_NEAREST, GL_NEAREST);
	HDRBBuffer->attachRenderTarget(HDRBUfferTexture, 0, 0);
	HDRBBuffer->checkStatus();
	HDRBBuffer->unBind();
}

DefferedRenderer::DefferedRenderer()
{	
	setupGBuffer();
	setupHDRBuffer();
	csm = new Csm(0.3, 150.0f, 3, 4096);
	perFrameUbo = new UniformBuffer(sizeof(PerFrameUniforms), 0);
	CsmUbo = new UniformBuffer(sizeof(CSMUniforms), 1);

	directionalLightShader = ResourceManager::getInstance()->getShader("defferedDirectionalLightPass");
	pointLightShader = ResourceManager::getInstance()->getShader("defferedPointLightPass");
	basicToneMappingShader = ResourceManager::getInstance()->getShader("basicToneMapping");

	directionalLightShader->setInt("positionTexture", 11);
	directionalLightShader->setInt("normalTexture", 12);
	directionalLightShader->setInt("albedoTexture", 13);
	directionalLightShader->setInt("shadowMap", 10);

	pointLightShader->setInt("positionTexture", 11);
	pointLightShader->setInt("normalTexture", 12);
	pointLightShader->setInt("albedoTexture", 13);


	// Create an empoty VAO to be bound when rendering screen quad
	glGenVertexArrays(1, &screenQuadVAO);
	createUVSphere();

	std::cout << glGetError() << std::endl;
}

void DefferedRenderer::setScene(Scene* scene)
{
	this->scene = scene;
}

void DefferedRenderer::runGeometryPass()
{
	gBuffer->bind();

	unsigned int attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
	glDrawBuffers(3, attachments);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Material* gBufferMaterial = new Material();
	gBufferMaterial->setShader(ResourceManager::getInstance()->getShader("defferedGeometryPass"));
	sceneRenderer.renderScene(scene, gBufferMaterial, true);
	gBuffer->unBind();

	gBufferPositionTexture->bind(GL_TEXTURE0 + 11);
	gBufferNormalTexture->bind(GL_TEXTURE0 + 12);
	gBufferColorTexture->bind(GL_TEXTURE0 + 13);
}

void DefferedRenderer::runDirectionalLightPass()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	directionalLightShader->use();

	//render simple quad
	glBindVertexArray(screenQuadVAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void DefferedRenderer::runPointLightPass()
{
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);
	glFrontFace(GL_CW);
	pointLightShader->use();

	glBindVertexArray(pointVolumeMesh->VAO);

	glDrawElementsInstanced(GL_TRIANGLES, pointVolumeMesh->subMeshes[0].indexCount, GL_UNSIGNED_INT, 0, scene->getPointLIghts().size());

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	glFrontFace(GL_CCW);
}

void DefferedRenderer::render()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	csm->update(scene->getMainCamera(), scene->getDirectionalLight()->direction);
	sceneRenderer.setGlobalUniforms(perFrameUniforms, scene);
	csm->updateUniforms(csmUniforms);

	perFrameUbo->bind();
	void* mem = perFrameUbo->mapToMemory(GL_WRITE_ONLY);

	if (mem) {
		memcpy(mem, &perFrameUniforms, sizeof(PerFrameUniforms));
		perFrameUbo->unmapFromMemroy();
	}

	CsmUbo->bind();
	auto siz = sizeof(int);
	void* mem2 = CsmUbo->mapToMemory(GL_WRITE_ONLY);
	if (mem2) {
		memcpy(mem2, &csmUniforms, sizeof(CSMUniforms));
		CsmUbo->unmapFromMemroy();
	}

	csm->render(scene);
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	runGeometryPass();

	HDRBBuffer->bind();
	unsigned int attachments[1] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, attachments);
	runDirectionalLightPass();
	runPointLightPass();
	HDRBBuffer->unBind();
	toneMappingPass();
}

void DefferedRenderer::toneMappingPass()
{
	basicToneMappingShader->setInt("hdrBuffer", 14);
	basicToneMappingShader->setFloat("exposure", 0.7f);
	HDRBUfferTexture->bind(GL_TEXTURE0 + 14);
	basicToneMappingShader->use();
	glBindVertexArray(screenQuadVAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

