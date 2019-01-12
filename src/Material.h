#pragma once
#ifndef GLTESTBED_MATERIAL_H
#define GLTESTBED_MATERIAL_H

#include <Shader.h>
#include "Vertex.h"
#include "Shader.h"

class Material {

public:
	string name;
	Shader* getShader() { return shader; };
	void setShader(Shader* shader) { this->shader = shader; };
	std::vector<Texture*> textures;
private:
	Shader* shader;
};


#endif //GLTESTBED_MATERIAL_H
