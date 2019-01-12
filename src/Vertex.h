#pragma once

#include <unordered_map>
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

	Vertex() {}
};

enum class TextureType {
	DIFFUSE,
	SPECULAR
};

struct Texture {

	unsigned int id;
	string path;
	TextureType type;

	Texture(int id, string path, TextureType type) {
		this->id = id;
		this->path = path;
		this->type = type;
	}
};