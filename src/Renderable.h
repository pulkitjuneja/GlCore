#pragma once

#ifndef RENDERABLE_H
#define RENDERABLE_H

#include "Shader.h"

class Renderable {
public:
	Shader* shader;
	virtual void render() = 0;
};

#endif

