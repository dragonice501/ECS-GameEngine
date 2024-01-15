#pragma once

#include "Scene.h"

#include "../Utils/Vec2.h"
#include "../Objects/Shapes/AARectangle.h"
#include "../Objects/Shapes/Rectangle.h"

class SceneMainMenu : public Scene
{
public:
	SceneMainMenu();
	virtual ~SceneMainMenu();

	void Setup(static SDL_Renderer* renderer);
	void Shutdown() override;

	void Input() override;
	void Update(float dt) override;
	void Render(static SDL_Renderer* renderer, SDL_Rect& camera) override;

	AARectangle rectAA;
	Rectangle rect;

	bool mIsPaused = false;
};