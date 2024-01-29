#pragma once

class GameObject
{
public:
	virtual void Input() = 0;
	virtual void Update(const float dt) = 0;
	virtual void Render() = 0;
};