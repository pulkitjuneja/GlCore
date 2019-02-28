//
// Created by Pulkit Juneja on 02/08/18.
//

#ifndef GLTESTBED_ENGINE_H
#define GLTESTBED_ENGINE_H

#include "Globals.h"


class Engine {

private:
    sf::Window* window;
    bool isEngineRunning = true;
	bool setupSFML();

public:
    static sf::Time deltaTime;
    static sf::Time timeSinceStart;
	void loadDefaultShaders();
    virtual bool init () = 0 ;
    virtual void update() = 0;
    virtual void render () = 0;
    void start ();
};


#endif //GLTESTBED_ENGINE_H
