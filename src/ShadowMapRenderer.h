#pragma once

#ifndef SHADOWMAPRENDERER_H
#define SHADOWMAPRENDERER_H

#include "Globals.h"
#include "ResourceManager.hpp"
#include "SceneRenderer.h"
#include "FrameBuffer.h"
#include "Texture.h"

class ShadowMapRenderer {
	Texture* depthMap;
	FrameBuffer* depthMapFbo;
	int SHADOW_WIDTH = 1024;
	int SHADOW_HEIGHT = 1024;
	SceneRenderer sceneRenderer;
public:
	ShadowMapRenderer();
	void render(Scene* scene);
	glm::mat4 updateLightProjectionMatrix (DirectionalLight* directionalLight);
};

#endif // !SHADOWMAPRENDERER_H
