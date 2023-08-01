#include <stdbool.h>
#include <SDL.h>

#include "Graphics/Graphics.h"
#include "Graphics/Font.h"

#include "Scenes/SceneMainMenu.h"

bool isRunning = false;

SceneMainMenu mainMenu;

bool Init()
{
	return Graphics::OpenWindow();
}

void Setup()
{

}

void Destroy()
{
	Graphics::CloseWindow();
}

int main(int argv, char* argc[])
{
	isRunning = Init();
	Setup();

	while (mainMenu.IsRunning())
	{
		Input::Instance()->Update();

		mainMenu.Input();
		mainMenu.Update(0.0f);
		mainMenu.Render();
	}

	Destroy();

	return 0;
}