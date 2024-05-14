#pragma once

#include "InputManager.h"
#include "GraphicsManager.h"

#include "Constants.h"

#include <SDL.h>
#include <iostream>

class Scene
{
public:
	virtual ~Scene() {};

	virtual void Setup() = 0;
	virtual void Shutdown() = 0;

	virtual void Input() = 0;
	virtual void Update(float dt) = 0;
	virtual void Render() = 0;
};