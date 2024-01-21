#pragma once

#include "../Managers/GraphicsManager.h"

#include "../Utils/Vec2.h"

#include<string>

class UIText
{
public:
	UIText(const std::string& text = "", const Vec2& position = Vec2(0.0f, 0.0f))
	{
		this->mText = text;
		this->mPosition = position;
		this->mReference = nullptr;
	}

	void Render()
	{
		if (mReference)
		{
			int* intRef = static_cast<int*>(mReference);
			if (intRef)
			{
				GraphicsManager::DrawString(mPosition.x, mPosition.y, (std::to_string(*intRef) + mText).c_str());
				return;
			}

			std::string* stringRef = static_cast<std::string*>(mReference);
			if (stringRef)
			{
				GraphicsManager::DrawString(mPosition.x, mPosition.y, stringRef->c_str());
				return;
			}
		}
		else
		{
			GraphicsManager::DrawString(mPosition.x, mPosition.y, mText.c_str());
		}
	}

	std::string mText;
	Vec2 mPosition;
	void* mReference;
};