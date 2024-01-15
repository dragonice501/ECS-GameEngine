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
	screenCenter = Vec2(GraphicsManager::ScreenWidth() / 2, GraphicsManager::ScreenHeight() / 2);

	rayPosition = screenCenter;
	r0 = Vec2(-0.707f, -0.707f) * 100.0f;
	r1 = Vec2(0.707f, -0.707f) * 100.0f;
	r2 = Vec2(0.707f, 0.707f) * 100.0f;
	r3 = Vec2(-0.707f, 0.707f) * 100.0f;

	rectAA = AARectangle(20.0f, 20.0f, 20.0f, 20.0f);
	rect = Rectangle(Vec2(200.0f, 200.0f), 40.0f, 40.0f, 0.0f);
}

void SceneMainMenu::Shutdown()
{
}

void SceneMainMenu::Input()
{
	
}

void SceneMainMenu::Update(float dt)
{
	r0.Rotate(90 * dt);
	r1.Rotate(90 * dt);
	r2.Rotate(90 * dt);
	r3.Rotate(90 * dt);

	rect.rotation += 90.0f * dt;
}

void SceneMainMenu::Render(static SDL_Renderer* renderer, SDL_Rect& camera)
{
	//GraphicsManager::DrawCircle(screenCenter.x, screenCenter.y, 100, 0.0f, 0xFF00FF00);
	GraphicsManager::DrawPixel(screenCenter.x + r0.x, screenCenter.y + r0.y, 0xFFFF0000);
	GraphicsManager::DrawLine(rayPosition.x, rayPosition.y, rayPosition.x + r1.x, rayPosition.y + r1.y, 0xFFFFFF00);
	GraphicsManager::DrawLine(rayPosition.x, rayPosition.y, rayPosition.x + r2.x, rayPosition.y + r2.y, 0xFFFF0000);
	GraphicsManager::DrawLine(rayPosition.x, rayPosition.y, rayPosition.x + r3.x, rayPosition.y + r3.y, 0xFFFFFF00);

	GraphicsManager::DrawRect(rect, 0xFF00FF00);
}