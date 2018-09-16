#pragma once
#ifndef GLTESTBED_MATERIAL_H
#define GLTESTBED_MATERIAL_H

#include <Shader.h>

class Material {

public:
    Shader* shader;
    GLuint texture;
    Material (Shader* shader, GLuint texture);
    Material (Shader* shader);

};

inline Material::Material(Shader *shader, GLuint texture): texture(texture) {
    this->shader = shader;
}

inline Material::Material(Shader *shader): texture(0) {
    this->shader = shader;
}

#endif //GLTESTBED_MATERIAL_H
