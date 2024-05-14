#pragma once

#include "Scene.h"

class SceneTest : public Scene
{
public:
	float mScreenZoom;

public:
	virtual void Setup();
	virtual void Shutdown();

	virtual void Input();
	virtual void Update(float dt);
	virtual void Render();
};