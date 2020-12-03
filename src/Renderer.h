#pragma once 

#ifndef RENDERER_H
#define RENDERER_H

#include "SceneRenderer.h"
#include "ShadowMapRenderer.h"
#include "Uniforms.h"
#include "UniformBuffer.h"
#include "Csm.h"
#include "Scene.h"

class Renderer {
	Scene* scene;

	//Uniforms
	PerFrameUniforms perFrameUniforms;
	CSMUniforms csmUniforms;

	//UniformBUffers
	UniformBuffer* perFrameUbo;
	UniformBuffer* CsmUbo;

public:
	Renderer();
	void setScene(Scene* scene);
	SceneRenderer sceneRenderer;
	ShadowMapRenderer shadowMaprender;
	Csm* csm;
	void render();
};

#endif // !RENDERER_H

