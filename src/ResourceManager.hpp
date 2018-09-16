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
#include <map>
#include "Shader.h"

using namespace std;

class ResourceManager {
private:
    map <string,Shader*> loadedShaders;
    map <string, GLuint&> textures;
    void readFromFile(const string &fileName, char* & shaderContent);
    ResourceManager ();
    static ResourceManager* instance;
public:
    Shader* currentShader;
    static ResourceManager* getInstance ();
    void loadShader(const string &vertexShaderPath, const string &fragmentShaderPath, const string& shaderName);
    Shader* getShader (const string &shaderName);
    void loadTexture (const string& texturePath, int &width, int &height, int &nrChannels, const string &textureName);
};


#endif /* Resources_hpp */
