#include "ScenePatternObserver.h"

ScenePatternObserver::ScenePatternObserver()
{
}

ScenePatternObserver::~ScenePatternObserver()
{
}

void ScenePatternObserver::Setup()
{
}

void ScenePatternObserver::Shutdown()
{
}

void ScenePatternObserver::Input()
{
	mPlayer.Input();
}

void ScenePatternObserver::Update(float dt)
{
	mPlayer.Update(dt);
}

void ScenePatternObserver::Render()
{
	GraphicsManager::DrawGrid(25, 25, 0xFF555555);
	mPlayer.Render();
}
