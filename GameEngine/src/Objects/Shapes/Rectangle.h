#pragma once

#include "../../Utils/Vec2.h"

struct Rectangle
{
	Rectangle() : Rectangle(Vec2(), 0, 0, 0.0f) {}
	Rectangle(const Vec2& center, int width, int height, float rotation)
	{
		this->position = center;
		this->width = width;
		this->height = height;
		this->rotation = rotation;
	}

	Vec2 position;
	float width;
	float height;
	float rotation;
};