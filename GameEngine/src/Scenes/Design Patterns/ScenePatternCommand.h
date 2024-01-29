#pragma once

#include "../Scene.h"

#include "../../Objects/GameObject.h"
#include "../../Commands/Command.h"
#include "../../Utils/Vec2.h"

#include "../../Objects/Shapes/AARectangle.h"

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

		Vec2 position;
		AARectangle rect;
	};

	class CommandMove : public Command
	{
	public:
		CommandMove(const int x, const int y)
		{
			xMovement = x;
			yMovement = y;
		}

		void Execute(GameObject& object) override
		{
			Player* player = static_cast<Player*>(&object);
			if (player)
			{
				MovePlayer(player);
			}
		}

		void Undo(GameObject& object) override
		{

		}

		void MovePlayer(Player* player)
		{
			player->Move(xMovement, yMovement);
		}

		int xMovement;
		int yMovement;
	};

	Player mPlayer;

	CommandMove mUpCommand = CommandMove(0, -50);
	CommandMove mDownCommand = CommandMove(0, 50);
	CommandMove mLeftCommand = CommandMove(-50, 0);
	CommandMove mRightCommand = CommandMove(50, 0);
};