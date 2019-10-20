#include "FrameBuffer.h"

FrameBuffer::FrameBuffer() {
	glGenFramebuffers(1, &fboId);
}

void FrameBuffer::bind() {
	glBindFramebuffer(GL_FRAMEBUFFER, fboId);
}

void FrameBuffer::unBind() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::attachDepthTarget(Texture* texture, uint32_t mipLevel) {
	glBindTexture(GL_TEXTURE_2D, texture->textureId);
	bind();
//	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, texture->textureId, mipLevel);
}