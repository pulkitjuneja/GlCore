#pragma once

#ifndef TEXTURE_H
#define TEXTURE_H

#include "Globals.h"

enum class TextureType {
	DIFFUSE,
	SPECULAR,
	DEPTH
};

class Texture {
public:

	GLuint textureId;
	TextureType type;
	GLenum target;

	Texture(TextureType type);
	void bind();
	void unBind();
	void setData(unsigned char* data, uint32_t w, uint32_t h, GLenum format, GLenum dataType);
	void setMinMagFilter(GLenum minFilter, GLenum magFilter);
	void setWrapping(GLenum s, GLenum t);

};

#endif