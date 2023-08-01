#include <stdbool.h>
#include <SDL.h>

#include "Utils/Constants.h"

#include "Graphics/Graphics.h"
#include "Graphics/Font.h"

#include "Managers/SceneManager.h"
#include "Scenes/Scene.h"
#include "Scenes/SceneMainMenu.h"

bool Init()
{
	return Graphics::OpenWindow();
}

void Setup()
{
	SceneManager::Instance()->CreateScene(MainMenu);
}

void Destroy()
{
	SceneManager::Instance()->DeleteCurrentScene();
	Graphics::CloseWindow();
}

int main(int argv, char* argc[])
{
	Init();
	Setup();

	while (SceneManager::Instance()->GetCurrentScene()->IsRunning())
	{
		static int timePreviousFrame;
		int timeToWait = MILLISECONDS_PER_FRAME - (SDL_GetTicks() - timePreviousFrame);
		if (timeToWait > 0)
		{
			SDL_Delay(timeToWait);
		}

		static float deltaTime = (SDL_GetTicks() - timePreviousFrame) / 1000.0f;
		if (deltaTime > 0.016f) deltaTime = 0.016f;

		timePreviousFrame = SDL_GetTicks();

		Input::Instance()->Update();
		Graphics::ClearScreen(0xFF111122);

		SceneManager::Instance()->GetCurrentScene()->Input();
		SceneManager::Instance()->GetCurrentScene()->Update(deltaTime);
		SceneManager::Instance()->GetCurrentScene()->Render();

		Graphics::RenderFrame();
	}

	Destroy();

	return 0;
}