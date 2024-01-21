#pragma once

#include "../../Utils/Vec2.h"

struct Curve
{
	Curve() : Curve(Vec2(0.0f, 0.0f), Vec2(0.0f, 0.0f), 0.0f, 0.0f) {}
	Curve(const Vec2& start, const Vec2& normal, const float length, const float degree)
	{
		this->start = start;
		this->normal = normal;
		this->length = length;
		this->degree = degree;
	}

	Vec2 start;
	Vec2 normal;
	float length;
	float degree;
};