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
	}

	void DrawManuevers()
	{
		Curve curve;
		curve.start = position + direction * size * 0.5f;

		uint32_t color;

		for (const ShipManuever manuever : mManuevers)
		{
			switch (manuever.manueverStress)
			{
			case EManueverStress::MS_NONE:
			{
				color = 0xFFFFFFFF;
				break;
			}
			case EManueverStress::MS_DESTRESS:
			{
				color = 0xFF5555FF;
				break;
			}
			case EManueverStress::MS_STRESS:
			{
				color = 0xFFFF0000;
				break;
			}
			}

			switch (manuever.manueverDirection)
			{
			case EManueverDirection::MD_STRAIGHT:
			{
				curve.degree = 0.0f;
				curve.length = manuever.manueverLength * 50.0f;
				curve.normal = direction;
				GraphicsManager::DrawCruve(curve, color);
				break;
			}
			case EManueverDirection::MD_BANK_RIGHT:
			{
				curve.degree = -45.0f;
				curve.length = manuever.manueverLength * 50.0f;
				curve.normal = direction;
				GraphicsManager::DrawCruve(curve, color);
				break;
			}
			case EManueverDirection::MD_HARD_RIGHT:
			{
				curve.degree = -90.0f;
				curve.length = manuever.manueverLength * 50.0f;
				curve.normal = direction;
				GraphicsManager::DrawCruve(curve, color);
				break;
			}
			case EManueverDirection::MD_BANK_LEFT:
			{
				curve.degree = 45.0f;
				curve.length = manuever.manueverLength * 50.0f;
				curve.normal = direction;
				GraphicsManager::DrawCruve(curve, color);
				break;
			}
			case EManueverDirection::MD_HARD_LEFT:
			{
				curve.degree = 90.0f;
				curve.length = manuever.manueverLength * 50.0f;
				curve.normal = direction;
				GraphicsManager::DrawCruve(curve, color);
				break;
			}
			}
		}
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
		ShipManuever(MD_STRAIGHT, MS_DESTRESS, 1),
		ShipManuever(MD_BANK_RIGHT, MS_DESTRESS, 1),
		ShipManuever(MD_BANK_RIGHT, MS_NONE, 2),
		ShipManuever(MD_BANK_RIGHT, MS_STRESS, 3),
		ShipManuever(MD_HARD_RIGHT, MS_DESTRESS, 1),
		ShipManuever(MD_HARD_RIGHT, MS_NONE, 2),
		ShipManuever(MD_HARD_RIGHT, MS_STRESS, 3),
		ShipManuever(MD_BANK_LEFT, MS_DESTRESS, 1),
		ShipManuever(MD_BANK_LEFT, MS_NONE, 2),
		ShipManuever(MD_BANK_LEFT, MS_STRESS, 3),
		ShipManuever(MD_HARD_LEFT, MS_DESTRESS, 1),
		ShipManuever(MD_HARD_LEFT, MS_NONE, 2),
		ShipManuever(MD_HARD_LEFT, MS_STRESS, 3)
	};
};