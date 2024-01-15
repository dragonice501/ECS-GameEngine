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
	if (InputManager::KeyPressedSpace()) mIsPaused = !mIsPaused;
}

void SceneMainMenu::Update(float dt)
{
	if(!mIsPaused)
		rect.rotation += 90.0f * dt;
}

void SceneMainMenu::Render(static SDL_Renderer* renderer, SDL_Rect& camera)
{
	Vec2 p0 = rect.position + Vec2(-rect.width * 0.5f, -rect.height * 0.5f);
	Vec2 p1 = rect.position + Vec2(rect.width * 0.5f, -rect.height * 0.5f);
	Vec2 p2 = rect.position + Vec2(rect.width * 0.5f, rect.height * 0.5f);
	Vec2 p3 = rect.position + Vec2(-rect.width * 0.5f, rect.height * 0.5f);

	Vec2 mousePos = InputManager::MousePosition() * SCREEN_SCALE;

	GraphicsManager::DrawRect(rect, rect.ContainsPoint(mousePos) ? 0xFF00FF00 : 0xFFFF0000);
}