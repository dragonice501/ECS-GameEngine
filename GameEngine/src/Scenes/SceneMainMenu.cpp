#include "SceneMainMenu.h"
#include "../Managers/SceneManager.h"

SceneMainMenu::SceneMainMenu()
{
	
}

SceneMainMenu::~SceneMainMenu()
{
}

void SceneMainMenu::Setup(SDL_Renderer* renderer)
{
}

void SceneMainMenu::Shutdown()
{
}

void SceneMainMenu::Input()
{
	
}

void SceneMainMenu::Update(float dt)
{
	mParticle.Update(dt);
}

void SceneMainMenu::Render(static SDL_Renderer* renderer, SDL_Rect& camera)
{
	mParticle.Render();
}