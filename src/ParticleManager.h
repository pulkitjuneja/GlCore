//
// Created by Pulkit Juneja on 08/08/18.
//

#ifndef GLPARTICLES_PARTICLEMANAGER_H
#define GLPARTICLES_PARTICLEMANAGER_H

#include <string>
#include "Particle.h"
#include "Shader.h"
#include "ParticleUpdater.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Renderable.h"
#include "Component.h"

enum ParticleType {billboard, mesh};

class ParticleManager: public Renderable, Component {

    const int maxParticles = 100000;
    std::vector<Particle*> particleContainer;
    GLuint VAO ;// VAO to encapsulate the vertex attribs of the particles

    ParticleType particleType;
    ParticleUpdater *particleUpdater;

    // arrays to store the data to be streamed to the GPU
    std::vector<GLfloat> particlePositionData, particleColorData;

    // OpenGL IDS for the buffers (Abstract out of this class ?)
    GLuint vertexBuffer; // TODO: move this into the particle class
    GLuint vertexPositionBuffer;
    GLuint vertexColorBuffer;

    // TODO: To replace this with actual camera matrix
    glm::mat4 viewMatrix, projectionMatrix;
    void calculateViewProjectionMatrix();

public:
    ParticleManager(const std::string& shaderName, ParticleUpdater *particleUpdater);
    virtual void update ();
    virtual void spawnInitial ();
    void render ();
    void updateBuffers ();
};

#endif //GLPARTICLES_PARTICLEMANAGER_H
