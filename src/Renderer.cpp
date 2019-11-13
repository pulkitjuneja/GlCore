#include "Renderer.h"

void Renderer::setScene(Scene * scene)
{
	this->scene = scene;
}

void Renderer::render()
{
	glClearColor(0.3f, 0.4f, 0.6f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	shadowMaprender.render(scene);
	sceneRenderer.renderScene(scene);
}
