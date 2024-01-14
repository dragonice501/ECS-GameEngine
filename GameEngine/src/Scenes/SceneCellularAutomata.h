#pragma once

#include "Scene.h"

#include "../Utils/Vec2.h"

class SceneCellularAutomata : public Scene
{
public:
	void Setup(static SDL_Renderer* renderer) override;
	void Shutdown() override;

	void Input() override;
	void Update(float dt) override;
	void Render(static SDL_Renderer* renderer, SDL_Rect& camera) override;

	void Cycle();
	bool CheckNeighborIsAlive(int x, int y);

private:
	struct Automata
	{
		bool isAlive = false;
		bool isAliveOutcome = false;
		Vec2 position = Vec2(0.0f, 0.0f);
	};

	static const int AUTOMATA_COUNT_HORIZONTAL = 30;
	static const int AUTOMATA_COUNT_VERTICAL = 30;
	const float TICK_TIME = 0.1f;

	float mRunTime = 0.0f;

	bool mPaused = false;

	Automata mAutomata[AUTOMATA_COUNT_HORIZONTAL][AUTOMATA_COUNT_VERTICAL];
};