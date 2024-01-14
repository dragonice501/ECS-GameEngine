#include "SceneMainMenu.h"
#include "../Managers/SceneManager.h"

SceneMainMenu::SceneMainMenu()
{
	Vec2 screenCenter = Vec2(GraphicsManager::ScreenWidth() / 2, GraphicsManager::ScreenHeight() / 2);

	p0 = screenCenter - Vec2(0, 50);
	p1 = screenCenter + Vec2(100, 0);
	p2 = screenCenter + Vec2(0, 50);
	p3 = screenCenter - Vec2(100, 0);
}

SceneMainMenu::~SceneMainMenu()
{
}

void SceneMainMenu::Setup(SDL_Renderer* renderer)
{
}

void SceneMainMenu::Shutdown()
{
}

void SceneMainMenu::Input()
{
	
}

void SceneMainMenu::Update(float dt)
{
	
}

void SceneMainMenu::Render(static SDL_Renderer* renderer, SDL_Rect& camera)
{
	/*GraphicsManager::DrawLine(p0.x, p0.y, p1.x, p1.y, 0xFFFFFF00);
	GraphicsManager::DrawLine(p1.x, p1.y, p2.x, p2.y, 0xFFFFFF00);
	GraphicsManager::DrawLine(p2.x, p2.y, p3.x, p3.y, 0xFFFFFF00);
	GraphicsManager::DrawLine(p3.x, p3.y, p0.x, p0.y, 0xFFFFFF00);

	GraphicsManager::DrawPixel(p0.x, p0.y, 0xFFFF0000);
	GraphicsManager::DrawPixel(p1.x, p1.y, 0xFFFF0000);
	GraphicsManager::DrawPixel(p2.x, p2.y, 0xFFFF0000);
	GraphicsManager::DrawPixel(p3.x, p3.y, 0xFFFF0000);*/
}