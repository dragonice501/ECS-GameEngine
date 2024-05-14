#pragma once

#include "Scene.h"

#include <SDL.h>
#include <map>
#include <string>

class Engine
{
public:
	static Engine& Instance();

	static void SetIsRunning(const bool running);

	bool Init();
	void Destroy();

	void Run();

	void Input();
	void Update();
	void Render();

	static bool mIsRunning;

private:
	Engine() {}
};