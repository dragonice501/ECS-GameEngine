#pragma once

#include "../Scenes/Scene.h"
#include "../Scenes/SceneMainMenu.h"

#include <vector>
#include <string>

enum SceneName
{
	MainMenu
};

class SceneManager
{
public:
	static SceneManager* Instance();

	void CreateScene(const SceneName& sceneName);

	inline void DeleteCurrentScene() { delete currentScene; }

	inline Scene* GetCurrentScene() { return currentScene; }

	inline void SetCurrentScene(Scene* newScene) { currentScene = newScene; }

private:
	SceneManager();
	SceneManager(const SceneManager&);
	SceneManager& operator=(SceneManager&);

	Scene* currentScene = nullptr;
	std::vector<Scene*> sceneStack;
};