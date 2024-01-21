#include "AssetManager.h"

SDL_Texture* AssetManager::mTileMapTexture = nullptr;
SDL_Texture* AssetManager::mMenuIconsTexture = nullptr;
SDL_Texture* AssetManager::mBattleBackgroundTexture = nullptr;
SDL_Texture* AssetManager::mEnemiesTexture = nullptr;
std::vector<SDL_Texture*> AssetManager::mCharacterTextures;

std::string AssetManager::mMenuIconsFilePath;
std::string AssetManager::mBattleBackgroundImageFilePath;

std::map<std::string, SDL_Texture*> AssetManager::mAssetMap;

void AssetManager::CreateTileMapTexture(const std::string& textureName)
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

void AssetManager::CreateMenuIconsTexture()
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

void AssetManager::CreateBattleBackgroundTexture(const std::string& textureName)
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

void AssetManager::CreateEnemiesTexture(const std::string& textureName)
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

void AssetManager::CreateCharacterTexture(const std::string& textureName)
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

void AssetManager::CreateAsset(const std::string& assetID, const std::string& textureName)
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