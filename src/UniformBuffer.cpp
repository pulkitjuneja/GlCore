#include "UniformBuffer.h"

UniformBuffer::UniformBuffer(GLsizeiptr bufferSize, GLuint bindIndex)
{
	glGenBuffers(1, &id);
	glBindBuffer(GL_UNIFORM_BUFFER, id);
	glBufferData(GL_UNIFORM_BUFFER, bufferSize, NULL, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	glBindBufferBase(GL_UNIFORM_BUFFER, bindIndex, id);
}

void UniformBuffer::setData(GLintptr offset, GLsizeiptr size, void * data)
{
	glBindBuffer(GL_UNIFORM_BUFFER, id);
	glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void* UniformBuffer::mapToMemory(GLenum access) {
	glBindBuffer(GL_UNIFORM_BUFFER, id);
	void* ptr = glMapBuffer(GL_UNIFORM_BUFFER, access);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	return ptr;
}

void UniformBuffer::unmapFromMemroy()
{
	glBindBuffer(GL_UNIFORM_BUFFER, id);
	glUnmapBuffer(GL_UNIFORM_BUFFER);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}
