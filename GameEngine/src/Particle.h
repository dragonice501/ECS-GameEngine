#pragma once

#include "GraphicsManager.h"

#include "Vec2.h"

class Particle
{
public:
	Particle() {}

	void Update(const float dt);

	void Render();

public:
	Vec2 mPosition = { GraphicsManager::ScreenWidth() / 2.0f, 10.0f};
	Vec2 mVelocity;
};