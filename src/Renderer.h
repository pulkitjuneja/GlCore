#pragma once

#ifndef RENDERER_H
#define RENDERER_H

#include "Scene.h"
#include "Globals.h"

class Renderer {
	Scene* scene;;
public:
	void setGlobalUniforms(Shader* shader);
	void setScene(Scene* scene);
	void renderScene();
	void render();
};

#endif // !RENDERER_H
