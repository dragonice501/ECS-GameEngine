#pragma once

#include "ECS.h"

#include <sol.hpp>
#include <memory>

class GameManager
{
private:
	GameManager();
	~GameManager();

public:
	static void LoadMainScript(std::unique_ptr<Registry>& registry, sol::state& lua);
	static void LoadLevel(size_t numLevel, std::unique_ptr<Registry>& registry, sol::state& lua);
};