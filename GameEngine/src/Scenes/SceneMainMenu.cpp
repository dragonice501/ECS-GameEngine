#include "SceneMainMenu.h"
#include "../Managers/SceneManager.h"

SceneMainMenu::SceneMainMenu()
{
	
}

SceneMainMenu::~SceneMainMenu()
{
}

void SceneMainMenu::Setup(SDL_Renderer* renderer)
{
	rect = Rectangle(Vec2(GraphicsManager::ScreenWidth() / 2.0f, GraphicsManager::ScreenHeight() / 2.0f), 100.0f, 100.0f, 0.0f);
}

void SceneMainMenu::Shutdown()
{
}

void SceneMainMenu::Input()
{
	if (InputManager::KeyPressedSpace()) mIsPaused = !mIsPaused;
}

void SceneMainMenu::Update(float dt)
{
	if(!mIsPaused)
		rect.Rotate(30.0f * dt);
}

void SceneMainMenu::Render(static SDL_Renderer* renderer, SDL_Rect& camera)
{
	Vec2 mousePos = InputManager::MousePosition();
	GraphicsManager::DrawRect(rect, rect.ContainsPoint(mousePos) ? 0xFF00FF00 : 0xFFFF0000);
}