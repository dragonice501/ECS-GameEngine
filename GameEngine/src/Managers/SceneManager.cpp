#include "SceneManager.h"

std::unique_ptr<Scene> SceneManager::mCurrentScene = nullptr;

void SceneManager::LoadScene()
{
	if (mCurrentScene)
	{
		mCurrentScene->Shutdown();
		mCurrentScene.reset();
	}

	mCurrentScene = std::make_unique<SceneMainMenu>();

	if (mCurrentScene) mCurrentScene->Setup(GraphicsManager::Renderer());
}

void SceneManager::CurrentSceneInput()
{
	mCurrentScene->Input();
}

void SceneManager::CurrentSceneUpdate(const float dt)
{
	mCurrentScene->Update(dt);
}

void SceneManager::CurrentSceneRender()
{
	mCurrentScene->Render(GraphicsManager::Renderer(), GraphicsManager::Camera());
}

void SceneManager::CurrentSceneShutdown()
{
	mCurrentScene->Shutdown();
}