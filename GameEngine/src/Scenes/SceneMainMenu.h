#pragma once

#include "Scene.h"

class SceneMainMenu : public Scene
{
public:
	SceneMainMenu();
	virtual ~SceneMainMenu();

	void Input() override;
	void Update(float dt) override;
	void Render() override;
};