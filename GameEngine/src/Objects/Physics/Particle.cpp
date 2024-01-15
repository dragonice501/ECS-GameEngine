#include "Particle.h"

void Particle::Update(const float dt)
{
	mVelocity += Vec2(0.0f, 9.87f) * dt;
	mPosition += mVelocity * dt;

	if (mPosition.y >= GraphicsManager::ScreenHeight()) mPosition.y = 0.0f;
}

void Particle::Render()
{
	GraphicsManager::DrawPixel(mPosition.x, mPosition.y, 0xFFFF0000);
}