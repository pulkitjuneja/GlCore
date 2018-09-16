//
// Created by Pulkit Juneja on 05/08/18.
//

#include "Particle.h"

Particle::Particle(const glm::vec4 &position, const glm::vec3 &velocity, const glm::vec4 &color, float life) : position(
        position), velocity(velocity), color(color), life(life) {
}

Particle::Particle() {

}