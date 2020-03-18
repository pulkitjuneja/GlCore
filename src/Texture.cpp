
#include "Texture.h"

Texture::Texture(TextureType type) {
	glGenTextures(1, &textureId);

	// keeping this constant for now,, need to make it parameterized when introducing cubemaps
	target = GL_TEXTURE_2D;
	this->type = type;
}

//Texture::~Texture() {
//	std::cout << "Destructor called";
//	glDeleteTextures(1, &textureId);
//}

void Texture::bind(int textureUnit) {
	glActiveTexture(textureUnit);
	glBindTexture(target, textureId);
}

void Texture::setData(unsigned char* data, uint32_t w, uint32_t h, GLenum format, GLenum dataType) {
	glBindTexture(target, textureId);
	glTexImage2D(target, 0, format, w, h, 0, format, dataType, data);
	if (data) {
		glGenerateMipmap(target);
	}
	glBindTexture(target, 0);
}

void Texture::setMinMagFilter(GLenum minFilter, GLenum magFilter) {
	glBindTexture(target, textureId);
	glTexParameteri(target, GL_TEXTURE_MIN_FILTER, minFilter);
	glTexParameteri(target, GL_TEXTURE_MAG_FILTER, magFilter);
	glBindTexture(target, 0);
}

void Texture::setWrapping(GLenum s, GLenum t) {
	glBindTexture(target, textureId);
	glTexParameteri(target, GL_TEXTURE_WRAP_S, s);
	glTexParameteri(target, GL_TEXTURE_WRAP_T, t);
	float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	glBindTexture(target, 0);
}
