#include "InputManager.h"

#include "../Engine/Engine.h"

#include <SDL.h>
#include <iostream>

bool InputManager::mUpPressed = false;
bool InputManager::mUpHeld = false;
bool InputManager::mUpReleased = false;
float InputManager::mUpHeldTime = 0.0f;

bool InputManager::mDownPressed = false;
bool InputManager::mDownHeld = false;
bool InputManager::mDownReleased = false;
float InputManager::mDownHeldTime = 0.0f;

bool InputManager::mLeftPressed = false;
bool InputManager::mLeftHeld = false;
bool InputManager::mLeftReleased = false;
float InputManager::mLeftHeldTime = 0.0f;

bool InputManager::mRightPressed = false;
bool InputManager::mRightHeld = false;
bool InputManager::mRightReleased = false;
float InputManager::mRightHeldTime = 0.0f;

bool InputManager::mEPressed = false;
bool InputManager::mOPressed = false;
bool InputManager::mSpacebarPressed = false;

void InputManager::Update(const float dt)
{
    if (mUpPressed || mUpHeld)
    {
        mUpPressed = false;
        mUpHeld = true;
        mUpHeldTime += dt;
    }
    else if (mUpReleased)
    {
        mUpReleased = false;
        mUpHeldTime = 0.0f;
    }

    if (mDownPressed || mDownHeld)
    {
        mDownPressed = false;
        mDownHeld = true;
        mDownHeldTime += dt;
    }
    else if (mDownReleased)
    {
        mDownReleased = false;
        mDownHeldTime = 0.0f;
    }

    if (mLeftPressed || mLeftHeld)
    {
        mLeftPressed = false;
        mLeftHeld = true;
        mLeftHeldTime += dt;
    }
    else if (mLeftReleased)
    {
        mLeftReleased = false;
        mLeftHeldTime = 0.0f;
    }

    if (mRightPressed || mRightHeld)
    {
        mRightPressed = false;
        mRightHeld = true;
        mRightHeldTime += dt;
    }
    else if (mRightReleased)
    {
        mRightReleased = false;
        mRightHeldTime = 0.0f;
    }

    if (mEPressed) mEPressed = false;
    if (mOPressed) mOPressed = false;
    if (mSpacebarPressed) mSpacebarPressed = false;

    SDL_Event sdlEvent;
    while (SDL_PollEvent(&sdlEvent))
    {
        switch (sdlEvent.type)
        {
        case SDL_KEYDOWN:
        {
            switch (sdlEvent.key.keysym.sym)
            {
                case SDLK_w:
                {
                    if (!mUpPressed && !mUpHeld)
                    {
                        mUpPressed = true;
                        mUpHeldTime = 0.0f;
                    }
                    break;
                }
                case SDLK_SPACE:
                {
                    mSpacebarPressed = true;
                    break;
                }
            }

            if (sdlEvent.key.keysym.sym == SDLK_ESCAPE)
            {
                Engine::Instance().SetIsRunning(false);
            }

            if (sdlEvent.key.keysym.sym == SDLK_w)
            {
                if (!mUpPressed && !mUpHeld)
                {
                    mUpPressed = true;
                    mUpHeldTime = 0.0f;
                }
                break;
            }
            else if (sdlEvent.key.keysym.sym == SDLK_s)
            {
                if (!mDownPressed && !mDownHeld)
                {
                    mDownPressed = true;
                    mDownHeldTime = 0.0f;
                }
                break;
            }
            else if (sdlEvent.key.keysym.sym == SDLK_a)
            {
                if (!mLeftPressed && !mLeftHeld)
                {
                    mLeftPressed = true;
                    mLeftHeldTime = 0.0f;
                }
                break;
            }
            else if (sdlEvent.key.keysym.sym == SDLK_d)
            {
                if (!mRightPressed && !mRightHeld)
                {
                    mRightPressed = true;
                    mRightHeldTime = 0.0f;
                }
                break;
            }

            if (sdlEvent.key.keysym.sym == SDLK_e)
            {
                mEPressed = true;
                break;
            }

            if (sdlEvent.key.keysym.sym == SDLK_o)
            {
                mOPressed = true;
                break;
            }

            /*if(sdlEvent.key.keysym.sym == SDLK_SPACE)
            {
                mSpacebarPressed = true;
                break;
            }*/

            break;
        }
        case SDL_KEYUP:
        {
            if (sdlEvent.key.keysym.sym == SDLK_w)
            {
                mUpReleased = true;
                mUpPressed = false;
                mUpHeld = false;
                break;
            }
            else if (sdlEvent.key.keysym.sym == SDLK_s)
            {
                mDownReleased = true;
                mDownPressed = false;
                mDownHeld = false;
                break;
            }
            else if (sdlEvent.key.keysym.sym == SDLK_a)
            {
                mLeftReleased = true;
                mLeftPressed = false;
                mLeftHeld = false;
                break;
            }
            else if (sdlEvent.key.keysym.sym == SDLK_d)
            {
                mRightReleased = true;
                mRightPressed = false;
                mRightHeld = false;
                break;
            }
            break;
        }
        }
    }
}