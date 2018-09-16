#include "Globals.h"
#include "Shader.h"
#include "ResourceManager.hpp"

using namespace std;

Shader::Shader(const GLuint shaderProgram, const string &shaderName) {
    this->shaderProgram = shaderProgram;
    this->shaderName = shaderName;
}

void Shader::readFromFile(const string &fileName, char* & shaderContent) {
    ifstream shaderFile(fileName);
    stringstream buffer;
    buffer << shaderFile.rdbuf();
    shaderContent = new char[buffer.str().length()];
    strcpy(shaderContent, &buffer.str()[0]);
}

void Shader::use() {
    if(!(ResourceManager::getInstance()->currentShader == this)) {
        glUseProgram(shaderProgram);
        ResourceManager::getInstance()->currentShader = this;
    }
}

void Shader::setBool(const string &name, bool value) const {
    glUniform1i (glGetUniformLocation(shaderProgram, name.c_str()), (int)value);
}

void Shader::setInt(const string &name, int value) const {
    glUniform1i (glGetUniformLocation(shaderProgram, name.c_str()), value);
}

void Shader::setFloat(const string &name, float value) const {
    glUniform1f (glGetUniformLocation(shaderProgram, name.c_str()), value);
}

void Shader::setFloat3(const string &name, float value1, float value2, float value3) {
    glUniform3f(glGetUniformLocation(shaderProgram, name.c_str()), value1, value2, value3);
}

void Shader::setMat4(const string &name, GLfloat *matrix) {
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram,name.c_str()),1,GL_FALSE,matrix);
}
