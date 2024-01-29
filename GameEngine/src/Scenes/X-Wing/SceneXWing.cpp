#include "SceneXWing.h"

SceneXWing::SceneXWing()
{
}

SceneXWing::~SceneXWing()
{
}

void SceneXWing::Setup()
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

void SceneXWing::Render()
{
	GraphicsManager::DrawGrid(10, 10, 0xFF222222);

	mShip.Draw();

	if (mSelectedShip)
	{
		mSelectedShip->DrawManuevers();
	}
}
