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

void FrameBuffer::attachDepthTarget(Texture* texture, uint32_t mipLevel, int layer) {
	texture->bind(GL_TEXTURE0);
	bind();

	if (texture->arraySize > 1) {
		glFramebufferTextureLayer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, texture->textureId, mipLevel, layer);
	}
	else {
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, texture->target, texture->textureId, mipLevel);
	}
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);

	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

	if (status != GL_FRAMEBUFFER_COMPLETE)
	{
		std::string error = "Framebuffer Incomplete: ";

		switch (status)
		{
		case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
		{
			error += "GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT";
			break;
		}
		case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:
		{
			error += "GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS";
			break;
		}
		case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
		{
			error += "GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER";
			break;
		}
		case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
		{
			error += "GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT";
			break;
		}
		case GL_FRAMEBUFFER_UNSUPPORTED:
		{
			error += "GL_FRAMEBUFFER_UNSUPPORTED";
			break;
		}
		default:
			break;
		}
		std::cout << error.c_str();
	}

	unBind();
	texture->Unbind();
}