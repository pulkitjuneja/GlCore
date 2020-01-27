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
	texture->bind(GL_TEXTURE0);
	bind();
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, texture->target, texture->textureId, mipLevel);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	unBind();
}