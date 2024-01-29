#include "SceneMainMenu.h"
#include "../../Managers/SceneManager.h"

SceneMainMenu::SceneMainMenu()
{
	
}

SceneMainMenu::~SceneMainMenu()
{
}

void SceneMainMenu::Setup()
{
	mMainButton = UIButton("Main", Vec2(GraphicsManager::ScreenWidth() * 0.5f, GraphicsManager::ScreenHeight() * 0.5f), 50, 25);
}

void SceneMainMenu::Shutdown()
{
}

void SceneMainMenu::Input()
{
	
}

void SceneMainMenu::Update(float dt)
{
	if (mMainButton.mRectangle.ContainsPoint(InputManager::GetMousePosition()))
	{
		if (InputManager::MouseLeftClick())
			mMainButton.renderColor = mMainButton.colorPressed;
		else
			mMainButton.renderColor = mMainButton.colorHovered;
	}
	else
	{
		mMainButton.renderColor = mMainButton.colorMain;
	}
}

void SceneMainMenu::Render()
{
	mMainButton.Render();
}