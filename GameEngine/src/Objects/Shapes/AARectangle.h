#pragma once

#include "../../Utils/Vec2.h"

struct AARectangle
{
	AARectangle()
	{
		topLeft = Vec2();
		bottomRight = Vec2();
	}
	AARectangle(float topLeftX, float topRightY, float width, float height)
	{
		topLeft = Vec2(topLeftX, topRightY);
		bottomRight = topLeft + Vec2(width, height);
	}

	Vec2 topLeft;
	Vec2 bottomRight;
};