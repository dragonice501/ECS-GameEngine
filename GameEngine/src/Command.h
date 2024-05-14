#pragma once

#include "GameObject.h"

class Command
{
public:
	virtual ~Command() {}
	virtual void Execute(GameObject& object) = 0;
	virtual void Undo(GameObject& object) = 0;
};