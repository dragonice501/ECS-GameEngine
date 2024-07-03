#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>
#include <map>
#include <string>

class AssetManager
{
private:
	static std::map<std::string, SDL_Texture*> mTextures;
	static std::map<std::string, TTF_Font*> mFonts;

private:
	AssetManager();
	~AssetManager();

public:
	static void ClearAssets();
	static void ClearFonts();
	static void AddTexture(const std::string& assetId, const std::string& textureName);
	static SDL_Texture* GetTexture(const std::string& assetId);
	static void AddFont(const std::string& assetId, const std::string& fontName, size_t fontSize);
	static TTF_Font* GetFont(const std::string& assetId);
};