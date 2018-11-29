#pragma once 

#ifndef MODEL_H
#define MODEL_H

#include "Globals.h"
#include "Shader.h"
#include "Mesh.h"
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "ResourceManager.hpp"
#include "Renderable.h"

class Model: public Renderable {
	
public:
	Model(std::string &path);
	Model(vector<Vertex>& vertices, vector<unsigned int>& indices, string texturepath, string directory);
	Model(vector<Vertex>& vertices, vector<unsigned int>& indices);
	void render();
private:
	string directory;
	std::vector<Mesh> meshes;
	void loadModel(string path, unsigned int loaderFlags);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type,string typeName);
};

#endif