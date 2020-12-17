#pragma once
#ifndef MATERIAL_H
#define MATERIAL_H

#include "Vertex.h"
#include "Texture.h"
#include "Shader.h"

class Material {

public:
	string name;
	Shader* getShader() { return shader; };
	void setShader(Shader* shader) { this->shader = shader; };
	std::vector<Texture*> textures;
	Texture* normalMap;
private:
	Shader* shader;
};


#endif //MATERIAL_H
