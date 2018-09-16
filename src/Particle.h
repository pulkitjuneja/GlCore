//
// Created by Pulkit Juneja on 05/08/18.
//

#ifndef GLTESTBED_PARTICLE_H
#define GLTESTBED_PARTICLE_H

#include <glm/glm.hpp>
#include "Globals.h"


class Particle {
public:
    glm::vec3 position;
    glm::vec3 velocity;
    glm::vec4 color;
    float life, size;

    Particle(const glm::vec4 &position, const glm::vec3 &velocity, const glm::vec4 &color, float life);

    Particle ();
};


#endif //GLTESTBED_PARTICLE_H
