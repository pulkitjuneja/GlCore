#pragma once

#ifndef Mesh_h
#define Mesh_h

#include "Globals.h"
#include <glm/glm.hpp>
#include "Vertex.h"
#include "Texture.h"
#include "Material.h"

struct SubMesh {
	Material* material;
	uint32_t baseIndex;
	uint32_t indexCount;
	uint32_t baseVertex;

public:
	SubMesh() {}

	SubMesh(Material* material, uint32_t baseIndex, uint32_t indexCount, uint32_t baseVertex) {
		this->material = material;
		this->baseIndex = baseIndex;
		this->indexCount = indexCount;
		this->baseVertex = baseVertex;
	}
};

class Mesh {
public:
	Mesh(std::vector<Vertex> &vertices,
		std::vector<unsigned int> &indices,
		std::vector<SubMesh> &subMeshes,
		bool hasNormals,
		bool hasTextCoords
	);
	
	GLuint VBO, VAO, EBO;
	std::vector<unsigned int> indices;
	std::vector<Vertex> vertices;
	std::vector<SubMesh> subMeshes;
	bool hasNormals;
	bool hasTexCoords;

    void setupMesh();
	void updateBuffers(std::vector<Vertex>& vertices, glm::vec3* indices);
};


#endif /* Mesh_h */
