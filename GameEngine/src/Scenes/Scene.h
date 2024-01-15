#pragma once

#include "../Managers/InputManager.h"
#include "../Managers/GraphicsManager.h"

#include "../Utils/Constants.h"

#include <SDL.h>

class Scene
{
public:
	virtual ~Scene() {};

	virtual void Setup(static SDL_Renderer* renderer) = 0;
	virtual void Shutdown() = 0;

	virtual void Input() = 0;
	virtual void Update(float dt) = 0;
	virtual void Render(static SDL_Renderer* renderer, SDL_Rect& camera) = 0;
};