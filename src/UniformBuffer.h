#pragma once

#include "Globals.h"

#ifndef UNIFORM_BUFFER_H
#define UNIFORM_BUFFER_H

class UniformBuffer {
	GLuint id;
public:
	UniformBuffer(GLsizeiptr bufferSize, GLuint bindIndex);
	void setData(GLintptr offset, GLsizeiptr size, void* data);
	void* mapToMemory(GLenum access);
	void unmapFromMemroy();
};

#endif // !UNIFORM_BUFFER_H
