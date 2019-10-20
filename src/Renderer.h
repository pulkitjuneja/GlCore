#pragma once 

#ifndef RENDERER_H
#define RENDERER_H

#include "SceneRenderer.h"

class Renderer {
	Scene* scene;
public:
	void setScene(Scene* scene);
	SceneRenderer sceneRenderer;
	void render();
};

#endif // !RENDERER_H

