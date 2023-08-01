#include "SceneManager.h"

SceneManager* SceneManager::Instance()
{
    static SceneManager* sceneManager = new SceneManager();
    return sceneManager;
}

SceneManager::SceneManager()
{

}

void SceneManager::CreateScene(const SceneName& sceneName)
{
    if (currentScene)
    {
        delete currentScene;
    }

    switch (sceneName)
    {
        case MainMenu:
        {
            currentScene = new SceneMainMenu();
            break;
        }

        return;
    }
}