#pragma once

#include "Globals.h"
#include "Vertex.h"
#include "Texture.h"

#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

class FrameBuffer {
	unsigned int fboId;
public:
	FrameBuffer();
	void attachDepthTarget(Texture* texture, uint32_t mipLevel);
	void bind();
	void unBind();
};

#endif