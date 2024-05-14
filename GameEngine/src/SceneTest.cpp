#include "SceneTest.h"

void SceneTest::Setup()
{
}

void SceneTest::Shutdown()
{
}

void SceneTest::Input()
{
	if (InputManager::MouseWheel())
	{
		mScreenZoom += InputManager::MouseWheelValue();

		std::cout << mScreenZoom << std::endl;
	}
}

void SceneTest::Update(float dt)
{
}

void SceneTest::Render()
{
	GraphicsManager::DrawFillCircleTessellated(100, 100, 35 + mScreenZoom, 0.0f, 0xffff0000);
}
