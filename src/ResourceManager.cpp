#include "Globals.h"
#include "ResourceManager.hpp"

using namespace std;

ResourceManager *ResourceManager::instance;

void ResourceManager::readFromFile(const std::string &fileName, char *&shaderContent)
{
	string fullPath = fileName;
	ifstream shaderFile(fullPath);
	stringstream buffer;
	buffer << shaderFile.rdbuf();
	shaderContent = new char[buffer.str().length()];
	strcpy(shaderContent, &buffer.str()[0]);
}

ResourceManager::ResourceManager() {

}

ResourceManager *ResourceManager::getInstance()
{
	if (instance == nullptr)
	{
		instance = new ResourceManager();
	}
	return instance;
}

void ResourceManager::loadShader(const std::string &vertexShaderPath, const std::string &fragmentShaderPath, const std::string &shaderName)
{

	if (loadedShaders.find(shaderName) != loadedShaders.end())
	{
		cout << "Shader already loaded, to get the shader use the getShader function";
		return;
	}
	unsigned int vertexShader, fragmentShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	char *vertexShaderSource;
	readFromFile(vertexShaderPath, vertexShaderSource);
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	glCompileShader(vertexShader);
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
		std::cout << "ERROR " << shaderName << "::VERTEX::COMPILATION_FAILED\n"
							<< infoLog << std::endl;
	}

	char *fragmentShaderSource;
	readFromFile(fragmentShaderPath, fragmentShaderSource);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
		std::cout << "ERROR " << shaderName << "::FRAGMENT::COMPILATION_FAILED\n"
							<< infoLog << std::endl;
	}
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
		std::cout << "ERROR" << shaderName << "::PROGRAM::LINKING_FAILED\n"
							<< infoLog << std::endl;
	}

	int uniformCount = 0;
	glGetProgramiv(shaderProgram, GL_ACTIVE_UNIFORMS, &uniformCount);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	Shader* newShader = new Shader(shaderProgram, shaderName, uniformCount);
	newShader->setUniformBlockBinding("perFrameUniforms", 0);
	newShader->setUniformBlockBinding("csmUniforms", 1);

	cout << "Shader loaded : " << shaderName << " id : " << std::to_string(newShader->getShaderID()) << "\n";
	loadedShaders.insert(make_pair(shaderName, newShader));
}

Texture *ResourceManager::loadTexture(const string &texturePath, const string &directory, TextureType type)
{

	string filename = string(texturePath);
	filename = directory + '/' + filename;

	if (textures.find(texturePath) != textures.end())
	{
		return textures.find(texturePath)->second;
	}

	int width, height, nrComponents;
	unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);

	Texture* tex;

	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;
		tex = new Texture(type, 1, width, height, format, GL_UNSIGNED_BYTE, format);
		tex->bind();
		tex->setData(data, 0);
		tex->generateMipMaps();
		tex->setWrapping(GL_REPEAT, GL_REPEAT);
		tex->setMinMagFilter(GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
		tex->Unbind();
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
	textures.emplace(make_pair(texturePath, tex));
	std::cout << "Texture Loaded: " << texturePath << std::endl;
	return textures.find(texturePath)->second;
}

Texture* ResourceManager::generateTexture(const string& identifier, TextureType textureType, const uint32_t& w,
	const uint32_t& h, GLenum format, GLenum internalFormat, GLenum dataType, int arraySize) {
	if (textures.find(identifier) != textures.end())
	{
		return textures.find(identifier)->second;
	}
	Texture* tex = new Texture(textureType, arraySize, w, h, format, dataType, internalFormat);
	textures.emplace(make_pair(identifier, tex));
	return tex;
}

Mesh *ResourceManager::loadMesh(string path, int loaderFlags)
{
	if (loadedMeshes.find(path) != loadedMeshes.end())
	{
		return loadedMeshes.find(path)->second;
	}

	Assimp::Importer import;
	const aiScene *scene = import.ReadFile(path, loaderFlags);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		cout << "ERROR::ASSIMP::" << import.GetErrorString() << endl;
		return nullptr;
	}
	string directory = path.substr(0, path.find_last_of('/'));

	// Sort scene meshes based on material
	struct {
		bool operator () (aiMesh* a, aiMesh* b) {
			return a->mMaterialIndex < b->mMaterialIndex;
		}
	} meshMaterialSort;
	std::sort(scene->mMeshes, scene->mMeshes + scene->mNumMeshes, meshMaterialSort);

	int vertexCount = 0;
	int runningBaseIndexSum=0;
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<SubMesh> submeshes;

	bool hasNormals = true;
	bool hasTexCoords = true;
	bool hasTangents = true;
	bool hasBiTangents = true;

	submeshes.resize(scene->mNumMaterials-1);

	int currentSubmeshIndex = -1;
	int currentRunningMaterialIndex = -1;
	int indexOffset = 0;

	for (int i = 0; i < scene->mNumMeshes; i++)
	{
		aiMesh *currentMesh = scene->mMeshes[i];

		if (currentMesh->mMaterialIndex != currentRunningMaterialIndex) {
			currentRunningMaterialIndex = currentMesh->mMaterialIndex;
			if (currentSubmeshIndex > -1) {
				runningBaseIndexSum += submeshes[currentSubmeshIndex].indexCount;
			}
			currentSubmeshIndex++;
			submeshes[currentSubmeshIndex].material = getAiSceneMaterial(scene, currentRunningMaterialIndex, directory);
			submeshes[currentSubmeshIndex].baseVertex = vertexCount;
			submeshes[currentSubmeshIndex].baseIndex = runningBaseIndexSum;
			indexOffset = 0;
		}
		submeshes[currentSubmeshIndex].indexCount += currentMesh->mNumFaces * 3;

		vertexCount += currentMesh->mNumVertices;

		// extract vertex data from current mesh
		for (int j = 0; j < currentMesh->mNumVertices; j++)
		{
			Vertex vertex;
			glm::vec3 tangent;
			glm::vec3 biTangent;
			vertex.position = glm::vec3(currentMesh->mVertices[j].x, currentMesh->mVertices[j].y, currentMesh->mVertices[j].z);
			if (hasNormals && currentMesh->mNormals != nullptr) {
				vertex.normals = glm::vec3(currentMesh->mNormals[j].x, currentMesh->mNormals[j].y, currentMesh->mNormals[j].z);
			}
			if (hasTexCoords && currentMesh->mTextureCoords[0]) {
				vertex.texCoords = glm::vec2(currentMesh->mTextureCoords[0][j].x, currentMesh->mTextureCoords[0][j].y);
			}
			if (hasTangents && currentMesh->mTangents != nullptr) {
				tangent = glm::vec3(currentMesh->mTangents[j].x, currentMesh->mTangents[j].y, currentMesh->mTangents[j].z);
			}
			if (hasBiTangents && currentMesh->mBitangents != nullptr) {
				biTangent = glm::vec3(currentMesh->mBitangents[j].x, currentMesh->mBitangents[j].y, currentMesh->mBitangents[j].z);
			}
			float handedness = glm::dot(glm::cross(tangent, biTangent), vertex.normals);
			vertex.tangent = glm::vec4(tangent.x, tangent.y, tangent.z, handedness < 0 ? -1: 1);

			vertices.push_back(vertex);
		}

		for (unsigned int j = 0; j < currentMesh->mNumFaces; j++)
		{
			aiFace face = currentMesh->mFaces[j];
			for (unsigned int k = 0; k < face.mNumIndices; k++)
				indices.push_back(face.mIndices[k] + indexOffset);
		}

		indexOffset += currentMesh->mNumFaces * 3;
	}

	Mesh *newMesh = new Mesh(vertices, indices, submeshes, hasNormals, hasTexCoords, hasTangents);
	newMesh->hasNormals = hasNormals;
	newMesh->hasTexCoords = hasTexCoords;
	loadedMeshes.insert(make_pair(path, newMesh));
	std::cout << "Mesh Loaded: " << path << std::endl;
	return loadedMeshes.find(path)->second;
}

Material * ResourceManager::getAiSceneMaterial(const aiScene * scene, int materialIndex, string directory)
{
	Material *material = new Material();
	material->name = string(directory);
	material->name += "_";
	material->name += std::to_string(materialIndex);

	if (materialIndex >= 0)
	{
		material->setShader(getShader("texturedMeshShader"));
		aiMaterial *aiMaterial = scene->mMaterials[materialIndex];
		material->diffuseMap = loadMaterialTexture(aiMaterial, aiTextureType_DIFFUSE, directory);
		material->specularMap = loadMaterialTexture(aiMaterial, aiTextureType_SPECULAR, directory);
		material->normalMap = loadMaterialTexture(aiMaterial, aiTextureType_HEIGHT, directory);
	}

	else
	{
		material->setShader(getShader("defaultShader"));
	}

	return material;
}


Texture * ResourceManager::getTexture(const string & textureName)
{
	if (textures.find(textureName) != textures.end())
	{
		return textures.find(textureName)->second;
	}
	else
	{
		cout << "Shader " << textureName << " does not exist";
		return nullptr;
	}
}

Shader *ResourceManager::getShader(const string& shaderName)
{
	if (loadedShaders.find(shaderName) != loadedShaders.end())
	{
		return loadedShaders.find(shaderName)->second;
	}
	else
	{
		cout << "Shader " << shaderName << " is not loaded";
		return nullptr;
	}
}

std::vector<Texture *> ResourceManager::loadMaterialTextures(aiMaterial *aiMaterial, aiTextureType aiTextureType, string directory)
{
	vector<Texture *> textures;

	for (int i = 0; i < aiMaterial->GetTextureCount(aiTextureType); i++)
	{
		aiString texturePath;
		aiMaterial->GetTexture(aiTextureType, i, &texturePath);
		TextureType textureType = textureTypeMap[aiTextureType];
		Texture *tex = loadTexture(texturePath.C_Str(), directory, textureType);
		textures.push_back(tex);
	}

	return textures;
}

Texture * ResourceManager::loadMaterialTexture(aiMaterial * aiMaterial, aiTextureType aiTextureType, string directory)
{
	aiString texturePath;
	if (aiMaterial->GetTextureCount(aiTextureType) > 0) {
		aiMaterial->GetTexture(aiTextureType, 0, &texturePath);
		TextureType textureType = textureTypeMap[aiTextureType];
		Texture *tex = loadTexture(texturePath.C_Str(), directory, textureType);
		return tex;
	}
	else {
		return NULL;
	}
}
