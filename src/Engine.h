//
// Created by Pulkit Juneja on 02/08/18.
//

#ifndef ENGINE_H
#define ENGINE_H

#include "Globals.h"
#include "Renderer.h"
#include "DefferedRenderer.h"

class Engine {

protected:
    sf::Window* window;
    bool isEngineRunning = true;
	bool setupSFML();
	Renderer* renderer;
	DefferedRenderer* defferedRenderer;

public:
    static sf::Time deltaTime;
    static sf::Time timeSinceStart;
	void loadDefaultShaders();
    virtual bool init () = 0 ;
    virtual void update() = 0;
    void start ();
};


#endif //ENGINE_H
