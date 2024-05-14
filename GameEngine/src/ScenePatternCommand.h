#pragma once

#include "Scene.h"

#include "AARectangle.h"
#include "Command.h"
#include "GameObject.h"
#include "Vec2.h"

#include <stack>
#include <vector>

class ScenePatternCommand : public Scene
{
public:
	ScenePatternCommand();
	~ScenePatternCommand();

	void Setup() override;
	void Shutdown() override;

	void Input() override;
	void Update(float dt) override;
	void Render() override;

private:
	class Player : public GameObject
	{
	public:
		Vec2 position;
		AARectangle rect;

	public:
		Player() {}
		void Input() override
		{

		}

		void Update(const float dt) override
		{

		}

		void Render() override
		{
			GraphicsManager::DrawFillAARect(rect, 0xFFFF0000);
		}

		void Move(int x, int y)
		{
			Vec2 movement = Vec2(x, y);
			position += movement;
			rect.topLeft += movement;
			rect.bottomRight += movement;
		}
	};

	class CommandMove : public Command
	{
	private:
		int xMovement, yMovement;
		int xUndoMovement, yUndoMovement;

	public:
		CommandMove() {}
		CommandMove(const int x, const int y)
		{
			xMovement = x;
			yMovement = y;

			xUndoMovement = -x;
			yUndoMovement = y;
		}
		CommandMove(const CommandMove* command)
		{
			this->xMovement = command->xMovement;
			this->yMovement = command->yMovement;

			this->xUndoMovement = -xMovement;
			this->yUndoMovement = -yMovement;
		}

		void Execute(GameObject& object) override
		{
			Player* player = static_cast<Player*>(&object);
			if (player)
			{
				player->Move(xMovement, yMovement);
			}
		}

		void Undo(GameObject& object) override
		{
			Player* player = static_cast<Player*>(&object);
			if (player)
			{
				player->Move(xUndoMovement, yUndoMovement);
			}
		}
	};

	Player mPlayer;

	CommandMove mUpCommand = CommandMove(0, -50);
	CommandMove mDownCommand = CommandMove(0, 50);
	CommandMove mLeftCommand = CommandMove(-50, 0);
	CommandMove mRightCommand = CommandMove(50, 0);

	std::vector<CommandMove> mCommands;
	size_t mCommandsIndex = 0;
};