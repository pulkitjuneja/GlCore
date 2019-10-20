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
	glBindTexture(GL_TEXTURE_2D, textureId);
}

void Texture::unBind() {
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::setData(unsigned char* data, uint32_t w, uint32_t h, GLenum format) {
	bind();
	glTexImage2D(GL_TEXTURE_2D, 0, format, w, h, 0, format, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	unBind();
}

void Texture::setMinMagFilter(GLenum minFilter, GLenum magFilter) {
	bind();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
	unBind();
}

void Texture::setWrapping(GLenum s, GLenum t) {
	bind();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, s);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, t);
	unBind();
}
