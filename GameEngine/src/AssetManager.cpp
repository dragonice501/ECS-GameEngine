#include "AssetManager.h"

#include "GraphicsManager.h"

#include <SDL_image.h>

std::map<std::string, SDL_Texture*> AssetManager::mTextures;
std::map<std::string, TTF_Font*> AssetManager::mFonts;

AssetManager::AssetManager()
{
}

AssetManager::~AssetManager()
{
}

void AssetManager::ClearAssets()
{
	for (auto texture : mTextures)
	{
		SDL_DestroyTexture(texture.second);
	}

	mTextures.clear();
}

void AssetManager::ClearFonts()
{
	for (auto font : mFonts)
	{
		TTF_CloseFont(font.second);
	}

	mFonts.clear();
}

void AssetManager::AddTexture(const std::string& assetId, const std::string& textureName)
{
	std::string path = SDL_GetBasePath();
	path += "assets\\images\\" + textureName;
	
	SDL_Surface* surface = IMG_Load(path.c_str());
	if (surface)
	{
		SDL_Texture* texture = SDL_CreateTextureFromSurface(GraphicsManager::GetRenderer(), surface);
		mTextures.emplace(assetId, texture);
	}

	SDL_FreeSurface(surface);
}

SDL_Texture* AssetManager::GetTexture(const std::string& assetId)
{
	return mTextures.at(assetId);
}

void AssetManager::AddFont(const std::string& assetId, const std::string& fontName, size_t fontSize)
{
	std::string path = SDL_GetBasePath();
	path += "assets\\fonts\\" + fontName;
	
	TTF_Font* font = TTF_OpenFont(path.c_str(), fontSize);
	if (font)
	{
		mFonts.emplace(assetId, font);
	}
}

TTF_Font* AssetManager::GetFont(const std::string& assetId)
{
	return mFonts.at(assetId);
}
