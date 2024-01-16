#pragma once

#include "../../Utils/Vec2.h"

#include "../../Managers/GraphicsManager.h"

struct Rectangle
{
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

	bool ContainsPoint(const Vec2& point)
	{
		Vec2 vA = p1 - p0;
		Vec2 vB = point - p0;
		if (vA.Cross(vB) < 0) return false;

		vA = p2 - p1;
		vB = point - p1;
		if (vA.Cross(vB) < 0) return false;

		vA = p3 - p2;
		vB = point - p2;
		if (vA.Cross(vB) < 0) return false;

		vA = p0 - p3;
		vB = point - p3;
		if (vA.Cross(vB) < 0) return false;

		return true;
	}

	Vec2 center;
	Vec2 p0;
	Vec2 p1;
	Vec2 p2;
	Vec2 p3;

private:
	float rotation;
};