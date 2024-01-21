#pragma once

#include "UIButton.h"
#include "UIText.h"

#include "../Managers/GraphicsManager.h"

#include "../Utils/Vec2.h"

#include <vector>

class UIPanel
{
public:
	UIPanel() {}

	void SetButtons(const std::vector<UIButton*>& buttons) { mButtons = buttons; }

	void Render()
	{
		for (UIButton* button : mButtons)
		{
			if(button->mIsActive)
				button->Render();
		}

		for (UIText* text : mText)
		{
			text->Render();
		}
	}

	bool mIsActive = false;
	Vec2 mPosition;
	Vec2 mSize;

	std::vector<UIButton*> mButtons;
	std::vector<UIText*> mText;
};