#pragma once

#include "../Scenes/Scene.h"
#include "../Scenes/Design Patterns/ScenePatternCommand.h"
#include "../Scenes/Games and Stuff/SceneMainMenu.h"
#include "../Scenes/Games and Stuff/SceneCellularAutomata.h"
#include "../Scenes/X-Wing/SceneXWing.h"

#include "../Managers/GameManager.h"
#include "../Managers/GraphicsManager.h"

#include <memory>

class SceneManager
{
private:
	static std::unique_ptr<Scene> mCurrentScene;

public:
	static void LoadScene();

	static void CurrentSceneInput();
	static void CurrentSceneUpdate(const float dt);
	static void CurrentSceneRender();

	static void CurrentSceneShutdown();

private:
	SceneManager() {};
	~SceneManager() {};
};