#include "Engine.h"

#include "../Utils/Constants.h"

#include "../Managers/GraphicsManager.h"
#include "../Managers/InputManager.h"
#include "../Managers/SceneManager.h"

#include <SDL.h>
#include <random>

bool Engine::mIsRunning = true;

Engine& Engine::Instance()
{
	static Engine* engine = new Engine();
	return *engine;
}

void Engine::SetIsRunning(const bool running)
{
	mIsRunning = running;
}

bool Engine::Init()
{
	return GraphicsManager::OpenWindow();
}

void Engine::Destroy()
{
	GraphicsManager::CloseWindow();
}

void Engine::Run()
{
	srand(time(NULL));

	SceneManager::LoadScene();

	while (mIsRunning)
	{
		// Delta Time
		static int timePreviousFrame;
		int timeToWait = MILLISECONDS_PER_FRAME - (SDL_GetTicks() - timePreviousFrame);
		if (timeToWait > 0)
		{
			SDL_Delay(timeToWait);
		}

		static float deltaTime = (SDL_GetTicks() - timePreviousFrame) / 1000.0f;
		if (deltaTime > 0.016f) deltaTime = 0.016f;

		timePreviousFrame = SDL_GetTicks();

		GraphicsManager::ClearScreen(0xFF000011);

		InputManager::Update(deltaTime);

		SceneManager::CurrentSceneInput();
		SceneManager::CurrentSceneUpdate(deltaTime);
		SceneManager::CurrentSceneRender();

		GraphicsManager::PresentRender();
	}

	Destroy();
}

void Engine::Input()
{
}

void Engine::Update()
{
}

void Engine::Render()
{
}
