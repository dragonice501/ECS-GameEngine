#include "SceneXWing.h"

SceneXWing::SceneXWing()
{
}

SceneXWing::~SceneXWing()
{
}

void SceneXWing::Setup(SDL_Renderer* renderer)
{
	mShip = Ship(Vec2(200.0f, 200.0f), Vec2(0.0f, -1.0f), 50.f);
}

void SceneXWing::Shutdown()
{
}

void SceneXWing::Input()
{
	if (InputManager::KeyPressedSpace()) mIsPaused = !mIsPaused;

	if (InputManager::MouseLeftClick())
	{
		if (mShip.rectangle.ContainsPoint(InputManager::GetMousePosition()))
		{
			mSelectedShip = &mShip;
		}
		else
		{
			mSelectedShip = nullptr;
		}
	}
}

void SceneXWing::Update(float dt)
{
	if (!mIsPaused)
		mShip.Rotate(30.0f * dt);
}

void SceneXWing::Render(SDL_Renderer* renderer, SDL_Rect& camera)
{
	GraphicsManager::DrawGrid(0xFF222222);

	mShip.Draw();

	if (mSelectedShip)
	{
		GraphicsManager::DrawRect(mShip.rectangle, 0xFF00FF00);
	}

	Vec2 mouse = InputManager::GetMousePosition();

	/*Vec2 edge = mShip.rectangle.p1 - mShip.rectangle.p0;
	Vec2 mouseV = mouse - mShip.rectangle.p0;
	GraphicsManager::DrawLine(mouse.x, mouse.y, mShip.rectangle.p0.x, mShip.rectangle.p0.y, Vec2::Cross(edge, mouseV) >= 0.0f ? 0xFF00FF00 : 0xFFFF0000);

	edge = mShip.rectangle.p2 - mShip.rectangle.p1;
	mouseV = mouse - mShip.rectangle.p1;
	GraphicsManager::DrawLine(mouse.x, mouse.y, mShip.rectangle.p1.x, mShip.rectangle.p1.y, Vec2::Cross(edge, mouseV) >= 0.0f ? 0xFF00FF00 : 0xFFFF0000);

	edge = mShip.rectangle.p3 - mShip.rectangle.p2;
	mouseV = mouse - mShip.rectangle.p2;
	GraphicsManager::DrawLine(mouse.x, mouse.y, mShip.rectangle.p2.x, mShip.rectangle.p2.y, Vec2::Cross(edge, mouseV) >= 0.0f ? 0xFF00FF00 : 0xFFFF0000);

	edge = mShip.rectangle.p0 - mShip.rectangle.p3;
	mouseV = mouse - mShip.rectangle.p3;
	GraphicsManager::DrawLine(mouse.x, mouse.y, mShip.rectangle.p3.x, mShip.rectangle.p3.y, Vec2::Cross(edge, mouseV) >= 0.0f ? 0xFF00FF00 : 0xFFFF0000);*/
}
