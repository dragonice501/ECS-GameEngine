#pragma once

#include "Scene.h"
#include "ECS.h"
#include "EventBus.h"

#include <SDL.h>
#include <sol.hpp>
#include <map>
#include <string>
#include <memory>

class Engine
{
private:
	static bool mIsRunning;
	static bool mIsDebug;

	int mTimePreviousFrame;
	int mTimeToWait;
	float mDeltaTime;

	sol::state lua;

	std::unique_ptr<Registry> mRegistry;
	std::unique_ptr<EventBus> mEventBus;

private:
	Engine() = default;
	
public:
	static Engine& Instance();

	bool Init();
	void Run();
	void Shutdown();

	void Setup();

	std::unique_ptr<Registry>& GetRegistry() { return mRegistry; }
	std::unique_ptr<EventBus>& GetEventBus() { return mEventBus; }

	inline static void SetIsRunning(const bool running) { mIsRunning = running; }
};