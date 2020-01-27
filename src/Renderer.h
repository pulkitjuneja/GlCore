#pragma once 

#ifndef RENDERER_H
#define RENDERER_H

#include "SceneRenderer.h"
#include "ShadowMapRenderer.h"

class Renderer {
	Scene* scene;
public:
	void setScene(Scene* scene);
	SceneRenderer sceneRenderer;
	ShadowMapRenderer shadowMaprender;
	void render();
};

#endif // !RENDERER_H

