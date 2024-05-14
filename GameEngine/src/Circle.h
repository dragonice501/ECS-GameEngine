#pragma once

#include "Vec2.h"

struct Circle
{
private:
	Vec2 mCenter;
	float mRadius;

public:
	Circle(const Vec2& center, const float radius)
	{
		mCenter = center;
		mRadius = radius;
	}
};