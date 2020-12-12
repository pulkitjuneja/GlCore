#pragma once

#ifndef SCENERENDERER_H
#define SCENERENDERER_H

#include "Scene.h"
#include "Globals.h"
#include "ResourceManager.hpp"

class SceneRenderer {
public:
	void setGlobalUniforms(PerFrameUniforms &perFrameUniforms, Scene* scene);
	void bindGlobalMaps();
	void renderScene(Scene* scene, Material* overrideMaterial = nullptr, bool passBaseMaterialProperties = false);
};

#endif // !SCENERENDERER_H
