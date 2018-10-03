#include "Entity.h"

void Entity::update()
{
	for (std::vector<Component*>::iterator it = components.begin(); it != components.end(); it++) {
		(*it)->update();
	}
}

void Entity::addComponent(Component * component)
{
	components.push_back(component);
}

void Entity::setRenderer(Renderable * renderable)
{
	this->renderable = renderable;
}
