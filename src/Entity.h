#pragma once

#ifndef ENTITY_H
#define ENTITY_H

#include "Component.h"
#include "Globals.h"
#include "Renderable.h"

class Entity {
public:
	std::vector<Component*> components;
	Renderable* renderable;
	void addComponent(Component * component);
	void setRenderer(Renderable* renderable);
	void update();
};

#endif // !ENTITY_H
