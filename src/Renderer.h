#pragma once 

#ifndef RENDERER_H
#define RENDERER_H

#include "SceneRenderer.h"
#include "ShadowMapRenderer.h"
#include "Uniforms.h"
#include "UniformBuffer.h"

class Renderer {
	Scene* scene;

	//Uniforms
	PerFrameUniforms perFrameUniforms;
public:
	Renderer();
	void setScene(Scene* scene);
	SceneRenderer sceneRenderer;
	ShadowMapRenderer shadowMaprender;
	void render();
};

#endif // !RENDERER_H

