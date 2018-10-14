#pragma once

#ifndef Mesh_h
#define Mesh_h

#include <Material.h>
#include "Globals.h"

class Mesh {
    std::vector<float> vertices;
public:
	std::vector<unsigned int> indices;
	GLuint VBO, VAO, EBO;
    Mesh (std::vector<float> &vertices, std::vector<unsigned int> &indices);
    void setupMesh();
};


#endif /* Mesh_h */
