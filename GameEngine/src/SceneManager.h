#pragma once

#include "Scene.h"
#include "SceneTest.h"
#include "ScenePatternCommand.h"
#include "ScenePatternObserver.h"
#include "SceneMainMenu.h"
#include "SceneCellularAutomata.h"

#include "GameManager.h"
#include "GraphicsManager.h"

#include <memory>

class SceneManager
{
private:
	static std::unique_ptr<Scene> mCurrentScene;

private:
	SceneManager() {};
	~SceneManager() {};

public:
	static void LoadScene();

	static void CurrentSceneInput();
	static void CurrentSceneUpdate(const float dt);
	static void CurrentSceneRender();

	static void CurrentSceneShutdown();
};