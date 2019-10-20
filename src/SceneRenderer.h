#pragma once

#ifndef SCENERENDERER_H
#define SCENERENDERER_H

#include "Scene.h"
#include "Globals.h"

class SceneRenderer {
	Scene* scene;
public:
	void setGlobalUniforms(Shader* shader);
	void renderScene(Scene* scene);
};

#endif // !SCENERENDERER_H
