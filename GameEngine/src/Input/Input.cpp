#include "Input.h"

Input* Input::Instance()
{
    static Input* inputObject = new Input();
    return inputObject;
}

Input::Input()
{
    m_keyUp = 0;
    m_keyDown = 0;

    m_isXClicked = false;
    m_isKeyPressed = false;

    m_isLeftButtonClicked = false;
    m_isRightButtonClicked = false;
    m_isMiddleButtonCliked = false;

    m_mouseMotionX = 0;
    m_mouseMotionY = 0;

    m_mousePositionX = 0;
    m_mousePositionY = 0;
}

bool Input::IsXClicked()
{
    return m_isXClicked;
}

bool Input::IsKeyPressed()
{
    return m_isKeyPressed;
}

char Input::GetKeyUp()
{
    return m_keyUp;
}

char Input::GetKeyDown()
{
    return m_keyDown;
}

bool Input::IsLeftButtonClicked()
{
    return m_isLeftButtonClicked;
}

bool Input::IsRightButtonClicked()
{
    return m_isRightButtonClicked;
}

bool Input::IsMiddleButtonClicked()
{
    return m_isMiddleButtonCliked;
}

int Input::GetMousePositionX()
{
    return m_mousePositionX;
}

int Input::GetMousePositionY()
{
    return m_mousePositionY;
}

int Input::GetMouseMotionX()
{
    return m_mouseMotionX;
}

int Input::GetMouseMotionY()
{
    return m_mouseMotionY;
}

void Input::Update()
{
    m_mouseMotionX = 0;
    m_mouseMotionY = 0;

    m_mousePositionX = 0;
    m_mousePositionY = 0;

    SDL_Event sdlEvents;
    while (SDL_PollEvent(&sdlEvents))
    {
        switch (sdlEvents.type)
        {
            case SDL_QUIT:
            {
                m_isXClicked = true;
            }
            case SDL_KEYDOWN:
            {
                m_isKeyPressed = true;
                m_keyDown = sdlEvents.key.keysym.sym;
                break;
            }
            case SDL_KEYUP:
            {
                m_isKeyPressed = false;
                m_keyUp = sdlEvents.key.keysym.sym;
                break;
            }
            case SDL_MOUSEBUTTONDOWN:
            {
                switch (sdlEvents.button.button)
                {
                    case SDL_BUTTON_LEFT:
                    {
                        m_isLeftButtonClicked = true;
                        break;
                    }
                    case SDL_BUTTON_MIDDLE:
                    {
                        m_isMiddleButtonCliked = true;
                        break;
                    }
                    case SDL_BUTTON_RIGHT:
                    {
                        m_isRightButtonClicked = false;
                    }
                }
                break;
            }
            case SDL_MOUSEBUTTONUP:
            {
                switch (sdlEvents.button.button)
                {
                    case SDL_BUTTON_LEFT:
                    {
                        m_isLeftButtonClicked = false;
                        break;
                    }
                    case SDL_BUTTON_MIDDLE:
                    {
                        m_isMiddleButtonCliked = false;
                        break;
                    }
                    case SDL_BUTTON_RIGHT:
                    {
                        m_isRightButtonClicked = false;
                    }
                }
                break;
            }
            case SDL_MOUSEMOTION:
            {
                m_mouseMotionX = sdlEvents.motion.xrel;
                m_mouseMotionY = sdlEvents.motion.yrel;

                m_mousePositionX = sdlEvents.motion.x;
                m_mousePositionY = sdlEvents.motion.y;
                break;
            }
        }
    }
}
