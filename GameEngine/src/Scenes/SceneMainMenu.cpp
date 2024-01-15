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
	rectAA = AARectangle(20.0f, 20.0f, 20.0f, 20.0f);
	rect = Rectangle(Vec2(GraphicsManager::ScreenWidth() / 2.0f, GraphicsManager::ScreenHeight() / 2.0f), 100.0f, 100.0f, 0.0f);
}

void SceneMainMenu::Shutdown()
{
}

void SceneMainMenu::Input()
{
	
}

void SceneMainMenu::Update(float dt)
{
	rect.rotation += 90.0f * dt;
}

void SceneMainMenu::Render(static SDL_Renderer* renderer, SDL_Rect& camera)
{
	GraphicsManager::DrawRect(rect, 0xFF00FF00);
}