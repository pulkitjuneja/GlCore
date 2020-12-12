#include "Renderer.h"

Renderer::Renderer()
{
	csm = new Csm(0.3, 350.0f, 4, 4096);
	perFrameUbo = new UniformBuffer(sizeof(PerFrameUniforms), 0);
	CsmUbo = new UniformBuffer(sizeof(CSMUniforms), 1);
}

void Renderer::setScene(Scene* scene)
{
	this->scene = scene;
}

void Renderer::render()
{
	glClearColor(0.3f, 0.4f, 0.6f, 1.0f);
	// Render Shadow map pass
    csm->update(scene->getMainCamera(), scene->getDirectionalLight()->direction);

	//Update Global Uniform blocks
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


	//Render Scene normally
	
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	sceneRenderer.renderScene(scene);
}
