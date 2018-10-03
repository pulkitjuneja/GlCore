#pragma once

#ifndef MESH_RENDERER_H
#define MESH_RENDERER_H

#include "Renderable.h"
#include "Mesh.h"
#include "Shader.h"

class MeshRenderer : public Renderable {
public:
	Mesh* mesh;
	GLuint textureID;

	MeshRenderer(Mesh* mesh, Shader* shader, GLuint textureID);
	MeshRenderer(Mesh* mesh, Shader* shader);
	void render();
};

#endif // !MESH_RENDERER_H
