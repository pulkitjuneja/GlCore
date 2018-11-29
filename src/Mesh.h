#pragma once

#ifndef Mesh_h
#define Mesh_h

#include <Material.h>
#include "Globals.h"
#include <glm/glm.hpp>

struct Vertex {
	glm::vec3 position;
	glm::vec3 normals;
	glm::vec2 texCoords;
public:
	Vertex(glm::vec3 position, glm::vec3 normals, glm::vec2 texCoords) {
		this->position = position;
		this->normals = normals;
		this->texCoords = texCoords;
	}

	Vertex () {}
};

struct Texture {
	unsigned int id;
	string type;
	string name;
	string path;
};

class Mesh {
public:
	std::vector<unsigned int> indices;
	std::vector<Vertex> vertices;
	vector<Texture> textures;
    Mesh (std::vector<Vertex> &vertices, std::vector<unsigned int> &indices, vector<Texture> textures);
	void Draw(Shader* shader);
	GLuint VBO, VAO, EBO;
private:
    void setupMesh();
};


#endif /* Mesh_h */
