#include "ResourceManager.h"

SDL_Texture* ResourceManager::mTileMapTexture = nullptr;
SDL_Texture* ResourceManager::mMenuIconsTexture = nullptr;
SDL_Texture* ResourceManager::mBattleBackgroundTexture = nullptr;
SDL_Texture* ResourceManager::mEnemiesTexture = nullptr;
std::vector<SDL_Texture*> ResourceManager::mCharacterTextures;

std::string ResourceManager::mMenuIconsFilePath;
std::string ResourceManager::mBattleBackgroundImageFilePath;

std::map<std::string, SDL_Texture*> ResourceManager::mAssetMap;

void ResourceManager::CreateTileMapTexture(const std::string& textureName)
{
	SDL_Surface* surface = nullptr;

    std::string basePath = SDL_GetBasePath();
    std::string surfacePath = "assets\\images\\" + textureName + ".png";
    std::string fullPath = basePath + surfacePath;
    surface = IMG_Load(fullPath.c_str());
    if (surface)
    {
        mTileMapTexture = SDL_CreateTextureFromSurface(GraphicsManager::GetRenderer(), surface);
    }

    SDL_FreeSurface(surface);
}

void ResourceManager::CreateMenuIconsTexture()
{
    SDL_Surface* surface = nullptr;

    std::string basePath = SDL_GetBasePath();
    std::string surfacePath = "assets\\images\\MenuIcons.png";
    std::string fullPath = basePath + surfacePath;
    surface = IMG_Load(fullPath.c_str());
    if (surface)
    {
        mMenuIconsTexture = SDL_CreateTextureFromSurface(GraphicsManager::GetRenderer(), surface);
    }

    SDL_FreeSurface(surface);
}

void ResourceManager::CreateBattleBackgroundTexture(const std::string& textureName)
{
    SDL_Surface* surface = nullptr;

    std::string basePath = SDL_GetBasePath();
    std::string surfacePath = "assets\\images\\" + textureName + ".png";
    std::string fullPath = basePath + surfacePath;
    surface = IMG_Load(fullPath.c_str());
    if (surface)
    {
        mBattleBackgroundTexture = SDL_CreateTextureFromSurface(GraphicsManager::GetRenderer(), surface);
    }

    SDL_FreeSurface(surface);
}

void ResourceManager::CreateEnemiesTexture(const std::string& textureName)
{
    SDL_Surface* surface = nullptr;

    std::string surfacePath = "./assets/images/" + textureName + ".png";
    surface = IMG_Load(surfacePath.c_str());
    if (surface)
    {
        mEnemiesTexture = SDL_CreateTextureFromSurface(GraphicsManager::GetRenderer(), surface);
    }

    SDL_FreeSurface(surface);
}

void ResourceManager::CreateCharacterTexture(const std::string& textureName)
{
    if (mAssetMap.find(textureName) != mAssetMap.end()) return;

    SDL_Surface* surface = nullptr;

    std::string basePath = SDL_GetBasePath();
    std::string surfacePath = "assets\\images\\" + textureName + ".png";
    std::string fullPath = basePath + surfacePath;
    surface = IMG_Load(fullPath.c_str());
    if (surface)
    {
        mAssetMap.emplace(textureName, SDL_CreateTextureFromSurface(GraphicsManager::GetRenderer(), surface));
    }

    SDL_FreeSurface(surface);
}

void ResourceManager::CreateAsset(const std::string& assetID, const std::string& textureName)
{
    if (mAssetMap.find(assetID) != mAssetMap.end()) return;

    SDL_Surface* surface = nullptr;

    std::string basePath = SDL_GetBasePath();
    std::string surfacePath = "\\assets\\images\\" + textureName + ".png";
    std::string fullPath = basePath + surfacePath;
    surface = IMG_Load(fullPath.c_str());
    if (surface)
    {
        mAssetMap.emplace(assetID, SDL_CreateTextureFromSurface(GraphicsManager::GetRenderer(), surface));
    }

    SDL_FreeSurface(surface);
}