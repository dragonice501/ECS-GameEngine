#include "ScenePatternCommand.h"

ScenePatternCommand::ScenePatternCommand()
{
}

ScenePatternCommand::~ScenePatternCommand()
{
}

void ScenePatternCommand::Setup()
{
	mPlayer.position = Vec2(100.0f, 100.0f);
	mPlayer.rect = AARectangle(mPlayer.position.x, mPlayer.position.y, 50.0f, 50.0f);

	InputManager::SetCommandA(mLeftCommand);
	InputManager::SetCommandD(mRightCommand);
	InputManager::SetCommandS(mDownCommand);
	InputManager::SetCommandW(mUpCommand);
}

void ScenePatternCommand::Shutdown()
{
	InputManager::ClearCommands();
}

void ScenePatternCommand::Input()
{
	Command* command = InputManager::GetCommand();
	if (command)
	{
		command->Execute(mPlayer);
	}
}

void ScenePatternCommand::Update(float dt)
{
}

void ScenePatternCommand::Render()
{
	GraphicsManager::DrawGrid(50, 50, 0xFF555555);
	mPlayer.Render();
}
