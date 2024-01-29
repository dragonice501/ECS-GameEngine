#pragma once

#include "../Managers/GraphicsManager.h"

#include "../Objects/Shapes/AARectangle.h"
#include "../Utils/Vec2.h"

#include <iostream>
#include <string>
#include <functional>
#include <SDL.h>

class UIButton
{
public:
	UIButton(
		const std::string& text = "",
		const Vec2& position = Vec2(0.0f, 0.0f),
		const int width = 0, const int height = 0,
		const uint32_t colorMain = 0x55555555, const uint32_t colorHovered = 0xAAAAAAAA, const uint32_t coloredPressed = 0xFFFFFFFF,
		const bool active = true)
	{
		this->mIsActive = active;
		this->mText = text;
		this->mPosition = position;
		this->mRectangle = AARectangle(position.x - width / 2, position.y - height / 2, width, height);

		this->colorMain = colorMain;
		this->colorHovered = colorHovered;
		this->colorPressed = coloredPressed;
		this->renderColor = colorMain;
	}

	void Render()
	{
		GraphicsManager::DrawAARect(mRectangle, renderColor);
		GraphicsManager::DrawString(mPosition.x, mPosition.y, mText.c_str());
	}

	bool mIsActive;

	std::string mText;
	Vec2 mPosition;
	AARectangle mRectangle;

	uint32_t colorMain;
	uint32_t colorHovered;
	uint32_t colorPressed;
	uint32_t renderColor;

	using ButtonAction = std::function<void()>;

	ButtonAction OnSelectedAction;
	ButtonAction OnHoveredAction;

	ButtonAction OnUpAction;
	ButtonAction OnDownAction;
	ButtonAction OnRightAction;
	ButtonAction OnLeftAction;

	ButtonAction OnAcceptAction;
	ButtonAction OnCancelAction;
};