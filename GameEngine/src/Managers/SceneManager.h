#pragma once

#include "../Scenes/Scene.h"
#include "../Scenes/SceneMainMenu.h"
#include "../Scenes/SceneCellularAutomata.h"
#include "../Scenes/X-Wing/SceneXWing.h"

#include "../Managers/GameManager.h"
#include "../Managers/GraphicsManager.h"

#include <memory>

class SceneManager
{
public:
	static void LoadScene();

	static void CurrentSceneInput();
	static void CurrentSceneUpdate(const float dt);
	static void CurrentSceneRender();

	static void CurrentSceneShutdown();

private:
	SceneManager() {};
	~SceneManager() {};

	static std::unique_ptr<Scene> mCurrentScene;
};