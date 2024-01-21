#pragma once

#include "../Managers/AssetManager.h"
#include "../Managers/GraphicsManager.h"

#include "../Utils/Vec2.h"

#include <string>
#include <SDL.h>

class UISprite
{
public:

	void Render()
	{
		SDL_Rect destRect =
		{
			mPosition.x + mOffset.x,
			mPosition.y + mOffset.y,
			mSize.x,
			mSize.y
		};

		GraphicsManager::DrawSpriteRect(AssetManager::GetAsset(mAssetID), mSrcRect, destRect);
	}

	SDL_Rect mSrcRect;
	Vec2 mPosition;
	Vec2 mOffset;
	Vec2 mSize;

	std::string mAssetID;
};