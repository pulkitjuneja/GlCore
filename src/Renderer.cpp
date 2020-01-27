#include "Renderer.h"

void Renderer::setScene(Scene* scene)
{
	this->scene = scene;
}

void Renderer::render()
{
	glClearColor(0.3f, 0.4f, 0.6f, 1.0f);

	// Render Shadow map pass
	glViewport(0, 0, shadowMaprender.SHADOW_WIDTH, shadowMaprender.SHADOW_HEIGHT);
	shadowMaprender.render(scene);

	//Render Scene normally
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	sceneRenderer.renderScene(scene);
}
