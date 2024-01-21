#pragma once

#include "../Managers/GraphicsManager.h"

#include "../Utils/Vec2.h"

#include <iostream>
#include <string>
#include <functional>
#include <SDL.h>

class UIButton
{
public:
	UIButton(const std::string& text = "", const Vec2& position = Vec2(0.0f, 0.0f), const bool active = true)
	{
		this->mIsActive = active;
		this->mText = text;
		this->mPosition = position;
	}

	void Render()
	{
		GraphicsManager::DrawString(mPosition.x, mPosition.y, mText.c_str());
	}

	bool mIsActive;
	std::string mText;
	Vec2 mPosition;

	using ButtonAction = std::function<void()>;

	ButtonAction OnSelected;
	ButtonAction OnUpAction;
	ButtonAction OnDownAction;
	ButtonAction OnRightAction;
	ButtonAction OnLeftAction;
	ButtonAction OnAcceptAction;
	ButtonAction OnCancelAction;
};