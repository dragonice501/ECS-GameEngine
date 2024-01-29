#pragma once

#include "GraphicsManager.h"

#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <SDL.h>
#include <SDL_image.h>

class AssetManager
{
private:
	static SDL_Texture* mTileMapTexture;
	static SDL_Texture* mMenuIconsTexture;
	static SDL_Texture* mBattleBackgroundTexture;
	static SDL_Texture* mEnemiesTexture;
	static std::vector<SDL_Texture*> mCharacterTextures;

	static std::string mMenuIconsFilePath;
	static std::string mBattleBackgroundImageFilePath;

	static std::map<std::string, SDL_Texture*> mAssetMap;

public:
	static SDL_Texture* GetTileMapTexture() { return mTileMapTexture; }
	static SDL_Texture* GetMenuIconsTexture() { return mMenuIconsTexture; }
	static SDL_Texture* GetBattleBackgroundTexture() { return mBattleBackgroundTexture; }
	static SDL_Texture* GetEnemiesTexture() { return mEnemiesTexture; }
	static SDL_Texture* GetCharacterTexture(int index) { return mCharacterTextures[index]; }
	static SDL_Texture* GetAsset(const std::string& assetID) { return mAssetMap.find(assetID)->second; }

	static void CreateTileMapTexture(const std::string& textureName);
	static void CreateMenuIconsTexture();
	static void CreateBattleBackgroundTexture(const std::string& textureName);
	static void CreateEnemiesTexture(const std::string& textureName);
	static void CreateCharacterTexture(const std::string& textureName);
	static void CreateAsset(const std::string& assetID, const std::string& textureName);

	static void BuildMenuIconMap();

	static void DestroyTileMapTexture() { SDL_DestroyTexture(mTileMapTexture); mTileMapTexture = nullptr; }
	static void DestroyMenuIconsTexture() { SDL_DestroyTexture(mMenuIconsTexture); mMenuIconsTexture = nullptr; }
	static void DestroyBattleBackgroundTexture() { SDL_DestroyTexture(mBattleBackgroundTexture); mBattleBackgroundTexture = nullptr; }
	static void DestroyEnemiesTexture() { SDL_DestroyTexture(mEnemiesTexture); mEnemiesTexture = nullptr; }
	static void DestroyCharacterTextures()
	{
		for (int i = 0; i < 4; i++)
		{
			SDL_DestroyTexture(mCharacterTextures[i]);
			mCharacterTextures[i] = nullptr;
		}
	}
	static void DestroyAssetMap()
	{
		for (auto i : mAssetMap)
		{
			SDL_DestroyTexture(i.second);	
		}

		mAssetMap.clear();
	}

private:
	AssetManager() {}
	~AssetManager() {}
};