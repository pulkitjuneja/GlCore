//
//  Resources.hpp
//  src
//
//  Created by Pulkit Juneja on 22/07/18.
//  Copyright © 2018 Pulkit Juneja. All rights reserved.
//

#ifndef Resources_hpp
#define Resources_hpp

#include <stdio.h>
#include <unordered_map> 
#include "Shader.h"
#include "Mesh.h"
#include "Globals.h"
#include "Vertex.h"


class ResourceManager {
private:

	// Resource Maps
    std::unordered_map <string, Shader> loadedShaders;
	std::unordered_map <string, Texture> textures;
	std::unordered_map<string, Material> materials;
	std::unordered_map<string, Mesh> loadedMeshes;

	std::unordered_map <aiTextureType, TextureType> textureTypeMap = {
	{aiTextureType_DIFFUSE, TextureType::DIFFUSE},
	{aiTextureType_SPECULAR, TextureType::SPECULAR}
	};

    ResourceManager ();
    static ResourceManager* instance;

	void readFromFile(const string &fileName, char* & shaderContent);
	std::vector<Texture *> loadMaterialTextures(aiMaterial* aiMaterial, aiTextureType textureType, string directory);

public:
    static ResourceManager* getInstance ();

	//Resource Loaders
	void loadShader(const string &vertexShaderPath, const string &fragmentShaderPath, const string& shaderName);
    Texture* loadTexture (const string& texturePath, const string& directory, TextureType textureType);
	Mesh* loadMesh(string path, int loaderFlags = aiProcess_Triangulate | aiProcess_FlipUVs);

	//Getters
	Shader* getShader(string shaderName);
};


#endif /* Resources_hpp */
