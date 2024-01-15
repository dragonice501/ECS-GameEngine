#include "InputManager.h"

#include "../Engine/Engine.h"

#include <SDL.h>
#include <iostream>

Vec2 InputManager::mMousePosition = Vec2();

bool InputManager::mKeyPressedW = false;
bool InputManager::mKeyHeldW = false;
bool InputManager::mKeyReleasedW = false;
float InputManager::mKeyHeldTimeW = 0.0f;

bool InputManager::mKeyPressedS = false;
bool InputManager::mKeyHeldS = false;
bool InputManager::mKeyReleasedS = false;
float InputManager::mKeyHeldTimeS = 0.0f;

bool InputManager::mKeyPressedA = false;
bool InputManager::mKeyHeldA = false;
bool InputManager::mKeyReleasedA = false;
float InputManager::mKeyHeldTimeA = 0.0f;

bool InputManager::mKeyPressedD = false;
bool InputManager::mKeyHeldD = false;
bool InputManager::mKeyReleasedD = false;
float InputManager::mKeyHeldTimeD = 0.0f;

bool InputManager::mKeyPressedE = false;
bool InputManager::mKeyPressedO = false;
bool InputManager::mKeyPressedSpace = false;

void InputManager::Update(const float dt)
{
    if (mKeyPressedW || mKeyHeldW)
    {
        mKeyPressedW = false;
        mKeyHeldW = true;
        mKeyHeldTimeW += dt;
    }
    else if (mKeyReleasedW)
    {
        mKeyReleasedW = false;
        mKeyHeldTimeW = 0.0f;
    }

    if (mKeyPressedS || mKeyHeldS)
    {
        mKeyPressedS = false;
        mKeyHeldS = true;
        mKeyHeldTimeS += dt;
    }
    else if (mKeyReleasedS)
    {
        mKeyReleasedS = false;
        mKeyHeldTimeS = 0.0f;
    }

    if (mKeyPressedA || mKeyHeldA)
    {
        mKeyPressedA = false;
        mKeyHeldA = true;
        mKeyHeldTimeA += dt;
    }
    else if (mKeyReleasedA)
    {
        mKeyReleasedA = false;
        mKeyHeldTimeA = 0.0f;
    }

    if (mKeyPressedD || mKeyHeldD)
    {
        mKeyPressedD = false;
        mKeyHeldD = true;
        mKeyHeldTimeD += dt;
    }
    else if (mKeyReleasedD)
    {
        mKeyReleasedD = false;
        mKeyHeldTimeD = 0.0f;
    }

    if (mKeyPressedE) mKeyPressedE = false;
    if (mKeyPressedO) mKeyPressedO = false;
    if (mKeyPressedSpace) mKeyPressedSpace = false;

    SDL_Event sdlEvent;
    while (SDL_PollEvent(&sdlEvent))
    {
        switch (sdlEvent.type)
        {
        case SDL_KEYDOWN:
        {
            switch (sdlEvent.key.keysym.sym)
            {
            case SDLK_a:
            {
                if (!mKeyPressedA && !mKeyHeldA)
                {
                    mKeyPressedA = true;
                    mKeyHeldTimeA = 0.0f;
                }
                break;
            }
            case SDLK_d:
            {
                if (!mKeyPressedD && !mKeyHeldD)
                {
                    mKeyPressedD = true;
                    mKeyHeldTimeD = 0.0f;
                }
                break;
            }
            case SDLK_e:
            {
                if (!mKeyPressedE)
                {
                    mKeyPressedE = true;
                }
                break;
            }
            case SDLK_o:
            {
                if (!mKeyPressedO)
                {
                    mKeyPressedO = true;
                }
                break;
            }
            case SDLK_s:
            {
                if (!mKeyPressedS && !mKeyHeldS)
                {
                    mKeyPressedS = true;
                    mKeyHeldTimeS = 0.0f;
                }
                break;
            }
            case SDLK_w:
            {
                if (!mKeyPressedW && !mKeyHeldW)
                {
                    mKeyPressedW = true;
                    mKeyHeldTimeW = 0.0f;
                }
                break;
            }
            case SDLK_SPACE:
            {
                mKeyPressedSpace = true;
                break;
            }
            case SDLK_ESCAPE:
            {
                Engine::Instance().SetIsRunning(false);
                break;
            }
            }
            break;
        }
        case SDL_KEYUP:
        {
            switch (sdlEvent.key.keysym.sym)
            {
            case SDLK_a:
            {
                mKeyReleasedW = true;
                mKeyPressedW = false;
                mKeyHeldW = false;
                break;
            }
            case SDLK_d:
            {
                mKeyReleasedD = true;
                mKeyPressedD = false;
                mKeyHeldD = false;
                break;
            }
            case SDLK_s:
            {
                mKeyReleasedS = true;
                mKeyPressedS = false;
                mKeyHeldS = false;
                break;
            }
            case SDLK_w:
            {
                mKeyReleasedW = true;
                mKeyPressedW = false;
                mKeyHeldW = false;
                break;
            }
            }
            break;
        }
        case SDL_MOUSEMOTION:
        {
            mMousePosition.x = sdlEvent.motion.x;
            mMousePosition.y = sdlEvent.motion.y;
            break;
        }
        }
    }
}