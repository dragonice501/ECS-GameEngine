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

		if (mCommands.size() != 0 && mCommandsIndex < mCommands.size() - 1)
		{
			mCommands.resize(mCommandsIndex);
		}
		
		CommandMove* moveCommand = static_cast<CommandMove*>(command);
		if (moveCommand)
		{
			CommandMove newCommand = CommandMove(moveCommand);
			mCommands.push_back(newCommand);
			mCommandsIndex++;
		}
	}
	else if (InputManager::KeyPressedZ())
	{
		if (!mCommands.empty() && mCommandsIndex > 0)
		{
			mCommands.at(mCommandsIndex - 1).Undo(mPlayer);
			mCommandsIndex--;
		}
	}
	else if (InputManager::KeyPressedR())
	{
		if (!mCommands.empty() && mCommandsIndex != mCommands.size())
		{
			mCommands.at(mCommandsIndex).Execute(mPlayer);
			mCommandsIndex++;
		}
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
