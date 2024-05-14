#pragma once

#include "GraphicsManager.h"
#include "Vec2.h"

struct Rectangle
{
private:
	float rotation;

public:
	Vec2 center;
	Vec2 p0;
	Vec2 p1;
	Vec2 p2;
	Vec2 p3;

	Rectangle() : Rectangle(Vec2(), 0, 0, 0.0f) {}
	Rectangle(const Vec2& center, int width, int height, float rotation)
	{
		this->center = center;
		p0 = center + Vec2(-width * 0.5f, -height * 0.5f);
		p1 = center + Vec2(width * 0.5f, -height * 0.5f);
		p2 = center + Vec2(width * 0.5f, height * 0.5f);
		p3 = center + Vec2(-width * 0.5f, height * 0.5f);
		this->rotation = rotation;
	}

	inline const float GetRotation() const { return rotation; }

	void Rotate(float degrees)
	{
		p0.RotateAroundPoint(center, degrees);
		p1.RotateAroundPoint(center, degrees);
		p2.RotateAroundPoint(center, degrees);
		p3.RotateAroundPoint(center, degrees);
	}

	bool ContainsPoint(const Vec2& point) const
	{
		Vec2 edge = p1 - p0;
		Vec2 pointV = point - p0;
		if (Vec2::Cross(edge, pointV) < 0.0f) return false;

		edge = p2 - p1;
		pointV = point - p1;
		if (Vec2::Cross(edge, pointV) < 0.0f) return false;

		edge = p3 - p2;
		pointV = point - p2;
		if (Vec2::Cross(edge, pointV) < 0.0f) return false;

		edge = p0 - p3;
		pointV = point - p3;
		if (Vec2::Cross(edge, pointV) < 0.0f) return false;

		return true;
	}
};