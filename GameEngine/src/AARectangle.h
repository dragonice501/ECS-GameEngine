#pragma once

#include "Vec2.h"

struct AARectangle
{
public:
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

	bool ContainsPoint(const Vec2& point)
	{
		if (point.x < topLeft.x) return false;
		else if (point.x > bottomRight.x) return false;
		else if (point.y < topLeft.y) return false;
		else if (point.y > bottomRight.y) return false;

		return true;
	}

	Vec2 topLeft;
	Vec2 bottomRight;
};