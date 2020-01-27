#pragma once

#ifndef PARTICLEMANAGER_H
#define PARTICLEMANAGER_H

#include "Globals.h"
#include "Particle.h"
#include "Shader.h"
#include "ParticleUpdater.h"
#include <glm/gtc/matrix_transform.hpp>

enum ParticleType {billboard, mesh};

class ParticleManager {

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

	// TODO use proper material
	Shader* shader;

public:
    ParticleManager(const std::string& shaderName, ParticleUpdater *particleUpdater);
    virtual void update ();
    virtual void spawnInitial ();
    void render ();
    void updateBuffers ();
};

#endif //PARTICLEMANAGER_H
