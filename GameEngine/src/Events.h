#pragma once

#include "ECS.h"
#include "Event.h"

#include <SDL.h>

class CollisionEvent : public Event
{
public:
	Entity a;
	Entity b;

	CollisionEvent(Entity a, Entity b)
	{
		this->a = a;
		this->b = b;
	}
};

class KeyPressedEvent : public Event
{
public:
	SDL_KeyCode key;
	
	KeyPressedEvent(SDL_KeyCode key)
	{
		this->key = key;
	}
};