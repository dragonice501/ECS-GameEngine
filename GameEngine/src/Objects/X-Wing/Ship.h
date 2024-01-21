#pragma once

#include "../../Managers/GraphicsManager.h"

#include "../Curves/Curve.h"
#include "../Shapes/Rectangle.h"
#include "../../Utils/Vec2.h"

#include "../../Objects/X-Wing/ShipManuever.h"

#include <vector>

struct Ship
{

	Ship() : Ship(Vec2(0.0f, 0.0f), Vec2(0.0f, 0.0f), 0.0f) {}
	Ship(const Vec2& position, const Vec2& direction, const float size)
	{
		this->position = position;
		this->direction = direction;
		this->size = size;
		rectangle = Rectangle(position, size, size, 0.0f);
	}

	void Draw()
	{
		GraphicsManager::DrawRect(rectangle, 0xFFFFFF00);

		Curve curve = Curve(position + direction * size * 0.5f, direction, 100.0f, 45.0f);
		GraphicsManager::DrawCruve(curve, 0xFFFFFFFF);
	}

	void Rotate(const float degrees)
	{
		direction.Rotate(degrees);
		direction.Normalize();

		rectangle.Rotate(degrees);
	}

	Vec2 position;
	Vec2 direction;
	Rectangle rectangle;
	float size;

	std::vector<ShipManuever> mManuevers =
	{
		ShipManuever(MD_STRAIGHT, 1)
	};
};