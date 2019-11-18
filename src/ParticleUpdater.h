#pragma once

#ifndef PARTICLEUPDATER_H
#define PARTICLEUPDATER_H

#include "Globals.h"
#include "Particle.h"

class ParticleUpdater {
public:
    virtual void update (std::vector<Particle*> &particleContainer) = 0;
    virtual void spawnInitial (std::vector<Particle*> &emptyContainer) = 0;
};

#endif //PARTICLEUPDATER_H


