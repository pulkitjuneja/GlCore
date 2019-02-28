#include "Globals.h"
#include "ResourceManager.hpp"

using namespace std;

ResourceManager* ResourceManager::instance;


void ResourceManager::readFromFile(const std::string &fileName, char *&shaderContent) {
	string fullPath = fileName;
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

	if (loadedShaders.find(shaderName) != loadedShaders.end()) {
		cout << "Shader already loaded, to get the shader use the getShader function";
		return;
	}
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

    loadedShaders.insert(make_pair(shaderName, Shader(shaderProgram, shaderName)));
}

Texture* ResourceManager::loadTexture(const string& texturePath, const string& directory, TextureType type) {

		string filename = string(texturePath);
		filename = directory + '/' + filename;

		if (textures.find(texturePath) != textures.end()) {
			return &textures.find(filename)->second;
		}

        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
// set the texture wrapping/filtering options (on the currently bound texture object)

		int width, height, nrComponents;

        unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);

        if (data) {
			GLenum format;
			if (nrComponents == 1)
				format = GL_RED;
			else if (nrComponents == 3)
				format = GL_RGB;
			else if (nrComponents == 4)
				format = GL_RGBA;

            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
		stbi_image_free(data);
		textures.insert(make_pair(filename, Texture(texture, texturePath, type)));

		return &textures.find(filename)->second;
}

Mesh * ResourceManager::loadMesh(string path, int loaderFlags)
{
	if (loadedMeshes.find(path) != loadedMeshes.end()) {
		return &loadedMeshes.find(path)->second;
	}

	Assimp::Importer import;
	const aiScene *scene = import.ReadFile(path, loaderFlags);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		cout << "ERROR::ASSIMP::" << import.GetErrorString() << endl;
		return nullptr;
	}
	string directory = path.substr(0, path.find_last_of('/'));

	int vertexCount = 0;
	int indexCount = 0;
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<SubMesh> submeshes;

	bool hasNormals = true;
	bool hasTexCoords = true;

	submeshes.resize(scene->mNumMeshes);

	for (int i = 0; i < scene->mNumMeshes; i++) {
		aiMesh* currentMesh = scene->mMeshes[i];

		submeshes[i].indexCount = currentMesh->mNumFaces * 3;
		submeshes[i].baseVertex = vertexCount;
		submeshes[i].baseIndex = indexCount;

		vertexCount += currentMesh->mNumVertices;
		indexCount += submeshes[i].indexCount;

		// extract vertex data from current mesh
		for (int j = 0; j < currentMesh->mNumVertices; j++) {
			Vertex vertex;
			vertex.position = glm::vec3(currentMesh->mVertices[j].x, currentMesh->mVertices[j].y, currentMesh->mVertices[j].z);
			if (hasNormals && currentMesh->mNormals != nullptr) {
				vertex.normals = glm::vec3(currentMesh->mNormals[j].x, currentMesh->mNormals[j].y, currentMesh->mNormals[j].z);

			}
			if (hasTexCoords && currentMesh->mTextureCoords[0]) {
				vertex.texCoords = glm::vec2(currentMesh->mTextureCoords[0][j].x, currentMesh->mTextureCoords[0][j].y);
			}

			vertices.push_back(vertex);
		}

		for (unsigned int j = 0; j < currentMesh->mNumFaces; j++)
		{
			aiFace face = currentMesh->mFaces[j];
			for (unsigned int k = 0; k < face.mNumIndices; k++)
				indices.push_back(face.mIndices[k]);
		}

		Material material;
		material.name = string(&path[path.find_last_of('/') + 1], &path[path.find_last_of('.')]);
		material.name += "_";
		material.name += currentMesh->mName.C_Str() + std::to_string(i);

		if (currentMesh->mMaterialIndex >= 0) {
			material.setShader(getShader("texturedMeshShader"));
			aiMaterial *aiMaterial = scene->mMaterials[currentMesh->mMaterialIndex];
			//material.

			std::vector<Texture* > diffuseMaps = loadMaterialTextures(aiMaterial,
				aiTextureType_DIFFUSE, directory);
			material.textures.insert(material.textures.end(), diffuseMaps.begin(), diffuseMaps.end());
			vector<Texture* > specularMaps = loadMaterialTextures(aiMaterial,
				aiTextureType_SPECULAR, directory);
			material.textures.insert(material.textures.end(), specularMaps.begin(), specularMaps.end());
		}

		else {
			material.setShader(getShader("defaultShader"));
		}

		// load a default shader to the material
		materials.insert(make_pair(material.name, material));
		submeshes[i].material = &materials[material.name];
	}

	Mesh newMesh(vertices, indices, submeshes);
	newMesh.hasNormals = hasNormals;
	newMesh.hasTexCoords = hasTexCoords;
	loadedMeshes.insert(make_pair(path, newMesh));
	return &loadedMeshes.find(path)->second;
}

Shader * ResourceManager::getShader(string shaderName)
{
	if (loadedShaders.find(shaderName) != loadedShaders.end()) {
		return &loadedShaders.find(shaderName)->second;
	}
	else {
		cout << "Shader " << shaderName << " is not loaded";
		return nullptr;
	}
}

std::vector<Texture*> ResourceManager::loadMaterialTextures(aiMaterial * aiMaterial,
	aiTextureType aiTextureType, string directory)
{
	vector<Texture* > textures;

	for (int i = 0; i < aiMaterial->GetTextureCount(aiTextureType); i++) {
		aiString texturePath;
		aiMaterial->GetTexture(aiTextureType, i, &texturePath);
		TextureType textureType = textureTypeMap[aiTextureType];
		Texture* tex = loadTexture(texturePath.C_Str(), directory, textureType);
		textures.push_back(tex);
	}

	return textures;
}
