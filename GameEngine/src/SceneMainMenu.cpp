#include "SceneMainMenu.h"

#include "SceneManager.h"

SceneMainMenu::SceneMainMenu()
{
	
}

SceneMainMenu::~SceneMainMenu()
{
}

void SceneMainMenu::Setup()
{
	
}

void SceneMainMenu::Shutdown()
{
}

void SceneMainMenu::Input()
{
	if (InputManager::MouseWheel())
	{
		mMouseWheelValue += InputManager::MouseWheelValue();
		std::cout << mMouseWheelValue << std::endl;
	}
}

void SceneMainMenu::Update(float dt)
{
	
}

void SceneMainMenu::Render()
{
	
}