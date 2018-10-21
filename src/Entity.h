#pragma once

#ifndef ENTITY_H
#define ENTITY_H

#include "Component.h"
#include "Globals.h"
#include "Renderable.h"
#include "Transform.h"

class Entity {
public:
	Transform transfrom;
	std::vector<Component*> components;
	Renderable* renderable;
	void addComponent(Component * component);
	void setRenderer(Renderable* renderable);
	void update();
};

#endif // !ENTITY_H
