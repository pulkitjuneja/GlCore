#include "Globals.h"
#include "ResourceManager.hpp"

using namespace std;

ResourceManager* ResourceManager::instance;


void ResourceManager::readFromFile(const std::string &fileName, char *&shaderContent) {
	string fullPath = dpath + fileName;
    cout<<fullPath<<"\n";
    ifstream shaderFile(fullPath);
    stringstream buffer;
    buffer << shaderFile.rdbuf();
    shaderContent = new char[buffer.str().length()];
    strcpy(shaderContent, &buffer.str()[0]);
}

ResourceManager::ResourceManager() {}

 ResourceManager* ResourceManager::getInstance() {
    if (instance == nullptr) {
        instance = new ResourceManager();
    }
    return instance;
}

void ResourceManager::loadShader(const std::string &vertexShaderPath, const std::string &fragmentShaderPath, const std::string &shaderName) {
    unsigned int vertexShader, fragmentShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    
    char* vertexShaderSource;
    readFromFile(vertexShaderPath, vertexShaderSource);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cout << "ERROR " << shaderName <<"::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    
    char* fragmentShaderSource;
    readFromFile(fragmentShaderPath, fragmentShaderSource);
    glShaderSource(fragmentShader,1,&fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cout << "ERROR " << shaderName <<"::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cout << "ERROR"<< shaderName <<"::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    loadedShaders.insert(pair<string, Shader*>(shaderName, new Shader(shaderProgram, shaderName)));
    
}

Shader* ResourceManager::getShader(const std::string &shaderName) {
    if (loadedShaders.count(shaderName) == 0) {
        string debugShaderName = "defaultShader";
        return loadedShaders [debugShaderName];
    }
    return loadedShaders [shaderName];
}

void ResourceManager::loadTexture(const string &texturePath, int &width, int &height, int &nrChannels, const string &textureName) {
    {
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
// set the texture wrapping/filtering options (on the currently bound texture object)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        unsigned char* data = stbi_load(texturePath.c_str(), &width, &height, &nrChannels, 0);

        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
            textures.insert(pair<string,GLuint&>(textureName, texture));
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);

    }
}
