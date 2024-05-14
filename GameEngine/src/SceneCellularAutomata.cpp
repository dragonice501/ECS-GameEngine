#include "SceneCellularAutomata.h"

void SceneCellularAutomata::Setup()
{
	Vec2 screenCenterPosition = Vec2(GraphicsManager::ScreenWidth() / 2, GraphicsManager::ScreenHeight() / 2);

	for (size_t x = 0; x < AUTOMATA_COUNT_HORIZONTAL; x++)
	{
		for (size_t y = 0; y < AUTOMATA_COUNT_VERTICAL; y++)
		{
			Automata& automata = mAutomata[x][y];

			automata.position =
				screenCenterPosition +
				Vec2(11, 0) * x + Vec2(0, 11) * y -
				Vec2(11, 11) * AUTOMATA_COUNT_HORIZONTAL * 0.5f;

			automata.isAlive = rand() % 2 == 0 ? false : true;
		}
	}
}

void SceneCellularAutomata::Shutdown()
{
}

void SceneCellularAutomata::Input()
{
	if (InputManager::KeyPressedSpace())
	{
		mPaused = !mPaused;
	}
}

void SceneCellularAutomata::Update(float dt)
{
	mRunTime += dt;

	if (mRunTime >= TICK_TIME)
	{
		mRunTime = 0.0f;

		if (!mPaused)
			Cycle();
	}
}

void SceneCellularAutomata::Render()
{
	for (size_t x = 0; x < AUTOMATA_COUNT_HORIZONTAL; x++)
	{
		for (size_t y = 0; y < AUTOMATA_COUNT_VERTICAL; y++)
		{
			const Automata& automata = mAutomata[x][y];

			GraphicsManager::DrawFillAARect(automata.position.x, automata.position.y, 10, 10, automata.isAlive ? 0xFFFFFFFF : 0xFF000000);
		}
	}
}

void SceneCellularAutomata::Cycle()
{
	int liveNeighborCount = 0;

	for (size_t x = 0; x < AUTOMATA_COUNT_HORIZONTAL; x++)
	{
		for (size_t y = 0; y < AUTOMATA_COUNT_VERTICAL; y++)
		{
			liveNeighborCount = 0;

			Automata& automata = mAutomata[x][y];

			automata.isAliveOutcome = false;

			if (CheckNeighborIsAlive(x - 1, y)) liveNeighborCount++;
			if (CheckNeighborIsAlive(x + 1, y)) liveNeighborCount++;
			if (CheckNeighborIsAlive(x, y - 1)) liveNeighborCount++;
			if (CheckNeighborIsAlive(x, y + 1)) liveNeighborCount++;
			if (CheckNeighborIsAlive(x - 1, y - 1)) liveNeighborCount++;
			if (CheckNeighborIsAlive(x + 1, y - 1)) liveNeighborCount++;
			if (CheckNeighborIsAlive(x - 1, y + 1)) liveNeighborCount++;
			if (CheckNeighborIsAlive(x + 1, y + 1)) liveNeighborCount++;

			if (automata.isAlive == false && liveNeighborCount == 3) automata.isAliveOutcome = true;
			else if (liveNeighborCount < 2) automata.isAliveOutcome = false;
			else if (
				automata.isAlive && liveNeighborCount == 2 ||
				automata.isAlive && liveNeighborCount == 3) automata.isAliveOutcome = true;
		}
	}

	for (size_t x = 0; x < AUTOMATA_COUNT_HORIZONTAL; x++)
	{
		for (size_t y = 0; y < AUTOMATA_COUNT_VERTICAL; y++)
		{
			Automata& automata = mAutomata[x][y];
			automata.isAlive = automata.isAliveOutcome;
		}
	}
}

bool SceneCellularAutomata::CheckNeighborIsAlive(int x, int y)
{
	if (x < 0) return false;
	else if (x >= AUTOMATA_COUNT_HORIZONTAL) return false;

	if (y < 0) return false;
	else if (y >= AUTOMATA_COUNT_VERTICAL) return false;

	return mAutomata[x][y].isAlive;
}
