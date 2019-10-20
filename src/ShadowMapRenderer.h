#pragma once

#ifndef SHADOWMAPRENDERER_H
#define SHADOWMAPRENDERER_H

#include "Globals.h"
#include "SceneRenderer.h"

class ShadowMapRenderer {
	int depthMap;
	int depthMapFbo;
	int SHADOW_WIDTH = 1024;
	int SHADOW_HEIGHT = 1024;
	SceneRenderer sceneRenderer;
public:
	ShadowMapRenderer();
	void renderDepthMap(Scene* scene);
	glm::mat4 calculateLightSpaceTransfrom (DirectionalLight* directionalLight);
};

#endif // !SHADOWMAPRENDERER_H
