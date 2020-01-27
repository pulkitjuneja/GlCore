#pragma once

#ifndef SCENERENDERER_H
#define SCENERENDERER_H

#include "Scene.h"
#include "Globals.h"
#include "ResourceManager.hpp"

class SceneRenderer {
	Scene* scene;
public:
	void setGlobalUniforms(Shader* shader);
	void bindGlobalMaps();
	void renderScene(Scene* scene, Material* overrideMaterial = nullptr);
};

#endif // !SCENERENDERER_H
