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

void Texture::bind() {
	glBindTexture(target, textureId);
}

void Texture::unBind() {
	glBindTexture(target, 0);
}

void Texture::setData(unsigned char* data, uint32_t w, uint32_t h, GLenum format, GLenum dataType) {
	bind();
	glTexImage2D(target, 0, format, w, h, 0, format, dataType, data);
	glGenerateMipmap(target);
	unBind();
}

void Texture::setMinMagFilter(GLenum minFilter, GLenum magFilter) {
	bind();
	glTexParameteri(target, GL_TEXTURE_MIN_FILTER, minFilter);
	glTexParameteri(target, GL_TEXTURE_MAG_FILTER, magFilter);
	unBind();
}

void Texture::setWrapping(GLenum s, GLenum t) {
	bind();
	glTexParameteri(target, GL_TEXTURE_WRAP_S, s);
	glTexParameteri(target, GL_TEXTURE_WRAP_T, t);
	unBind();
}
