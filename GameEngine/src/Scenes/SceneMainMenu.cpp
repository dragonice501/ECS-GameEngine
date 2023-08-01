#include "SceneMainMenu.h"

SceneMainMenu::SceneMainMenu()
{
	mIsRunning = true;
}

SceneMainMenu::~SceneMainMenu()
{
}

void SceneMainMenu::Input()
{
	if (Input::Instance()->IsKeyPressed())
	{
		if (Input::Instance()->GetKeyDown() == SDLK_ESCAPE)
		{
			mIsRunning = false;
		}
	}
}

void SceneMainMenu::Update(float dt)
{
}

void SceneMainMenu::Render()
{
	Graphics::DrawString(
		Graphics::ScreenWidth() * 0.5f,
		Graphics::ScreenHeight() * 0.5f,
		"Hello World",
		Center,
		Middle,
		0xFFFF0000
	);
}