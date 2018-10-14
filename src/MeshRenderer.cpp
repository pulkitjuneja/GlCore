#include "MeshRenderer.h"

MeshRenderer::MeshRenderer(Mesh* mesh, Shader* shader, GLuint textureID) {
	this->mesh = mesh;
	this->shader = shader;
	this->textureID = textureID;
}

MeshRenderer::MeshRenderer(Mesh* mesh, Shader* shader) {
	this->mesh = mesh;
	this->shader = shader;
	textureID = 0;
}

void MeshRenderer::render() {
	if (textureID != 0) {
		// setup texture for rendering 
	}
	shader->use();
	glBindVertexArray(mesh->VAO);
	glDrawElements(GL_TRIANGLES, mesh->indices.size() * sizeof(int), GL_UNSIGNED_INT,0);
}