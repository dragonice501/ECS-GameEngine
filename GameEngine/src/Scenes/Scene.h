#pragma once

#include "../Input/Input.h"
#include "../Graphics/Graphics.h"

class Scene
{
public:
	virtual ~Scene() = default;

	virtual void Input() = 0;
	virtual void Update(float dt) = 0;
	virtual void Render() = 0;

	virtual inline const bool IsRunning() const { return mIsRunning; }

protected:
	bool mIsRunning = false;
};