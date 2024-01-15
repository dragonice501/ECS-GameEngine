#pragma once

#include "../../Utils/Vec2.h"

#include "../../Managers/GraphicsManager.h"

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

	bool ContainsPoint(const Vec2& point)
	{
		Vec2 p0 = position + Vec2(-width * 0.5f, -height * 0.5f);
		Vec2 p1 = position + Vec2(width * 0.5f, -height * 0.5f);
		Vec2 p2 = position + Vec2(width * 0.5f, height * 0.5f);
		Vec2 p3 = position + Vec2(-width * 0.5f, height * 0.5f);

		p0.RotateAroundPoint(position, rotation);
		p1.RotateAroundPoint(position, rotation);
		p2.RotateAroundPoint(position, rotation);
		p3.RotateAroundPoint(position, rotation);

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

	Vec2 position;
	float width;
	float height;
	float rotation;
};