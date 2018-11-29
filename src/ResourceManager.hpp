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
#include "Mesh.h"

using namespace std;

class ResourceManager {
private:
    map <string,Shader*> loadedShaders;
    void readFromFile(const string &fileName, char* & shaderContent);
    ResourceManager ();
    static ResourceManager* instance;
public:
    Shader* currentShader;
    static ResourceManager* getInstance ();
    void loadShader(const string &vertexShaderPath, const string &fragmentShaderPath, const string& shaderName);
    Shader* getShader (const string &shaderName);
    unsigned int loadTexture (const string& texturePath, const string& directory);
};


#endif /* Resources_hpp */
