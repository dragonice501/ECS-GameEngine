#include "Engine.h"

#include "Constants.h"
#include "Logger.h"

#include "AssetManager.h"
#include "GraphicsManager.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "GameManager.h"

#include "Systems.h"
#include "Components.h"

#include <random>
#include <fstream>

bool Engine::mIsRunning = true;
bool Engine::mIsDebug = false;

Engine& Engine::Instance()
{
	static Engine* engine = new Engine();
	return *engine;
}

bool Engine::Init()
{
	// Seed Random Number Generator
	srand(time(NULL));

	// Create Window
	if (!GraphicsManager::OpenWindow())
	{
		std::cerr << "Error initializing TTF" << std::endl;
		return false;
	}

	// Init True Type Font
	if (TTF_Init() != 0) return false;

	// Create Registry
	mRegistry = std::make_unique<Registry>();
	if (!mRegistry) return false;

	// Create Event Bus
	mEventBus = std::make_unique<EventBus>();
	if (!mEventBus) return false;

	// Init ImGui
	ImGui::CreateContext();
	ImGuiSDL::Initialize(GraphicsManager::GetRenderer(), GraphicsManager::WindowWidth(), GraphicsManager::WindowHeight());

	return true;
}

void Engine::Shutdown()
{
	// Destroy ImGui
	ImGuiSDL::Deinitialize();
	ImGui::DestroyContext();

	// Destroy Window
	GraphicsManager::CloseWindow();
}

void Engine::Run()
{
	//SceneManager::LoadScene();
	Setup();

	while (mIsRunning)
	{
		// Delta Time
		mTimeToWait = MILLISECONDS_PER_FRAME - (SDL_GetTicks() - mTimePreviousFrame);
		if (mTimeToWait > 0)
		{
			SDL_Delay(mTimeToWait);
		}

		mDeltaTime = (SDL_GetTicks() - mTimePreviousFrame) / 1000.0f;
		if (mDeltaTime > 0.016f) mDeltaTime = 0.016f;

		mTimePreviousFrame = SDL_GetTicks();

		// Update Input
		InputManager::Update(mDeltaTime);
		if (InputManager::KeyPressedB()) mIsDebug = !mIsDebug;

		// Reset all event handlers
		mEventBus->Reset();

		// Perfom event subscriptions
		mRegistry->GetSystem<DamageSystem>().SubscribeToEvents();
		mRegistry->GetSystem<KeyboardControlSystem>().SubscribeToEvents();
		mRegistry->GetSystem<ProjectileEmitSystem>().SubscribeToEvents();

		// Update systems
		mRegistry->Update();
		mRegistry->GetSystem<AnimationSystem>().Update(mDeltaTime);
		//mRegistry->GetSystem<Collision2DSystem>().Update();
		mRegistry->GetSystem<MovementSystem>().Update(mDeltaTime);
		mRegistry->GetSystem<CameraMovementSystem>().Update(25 * 64, 20 * 64);
		mRegistry->GetSystem<ProjectileEmitSystem>().Update(mDeltaTime);
		mRegistry->GetSystem<ProjectileSystem>().Update(mDeltaTime);
		mRegistry->GetSystem<ScriptSystem>().Update(mDeltaTime, SDL_GetTicks());

		// Render
		SDL_SetRenderDrawColor(GraphicsManager::GetRenderer(), 21, 21, 21, 255);
		SDL_RenderClear(GraphicsManager::GetRenderer());

		mRegistry->GetSystem<RenderSystem>().Draw();
		mRegistry->GetSystem<RenderTextSystem>().Draw();

		// Draw ImGui
		if (mIsDebug)
		{
			mRegistry->GetSystem<RenderGUISystem>().Draw();
		}

		SDL_RenderPresent(GraphicsManager::GetRenderer());
	}
}

void Engine::Setup()
{
	mRegistry->AddSystem<AnimationSystem>();
	mRegistry->AddSystem<MovementSystem>();
	mRegistry->AddSystem<RenderSystem>();
	mRegistry->AddSystem<RenderTextSystem>();
	mRegistry->AddSystem<RenderGUISystem>();
	//mRegistry->AddSystem<Collision2DSystem>();
	mRegistry->AddSystem<DamageSystem>();
	mRegistry->AddSystem<KeyboardControlSystem>();
	mRegistry->AddSystem<CameraMovementSystem>();
	mRegistry->AddSystem<ProjectileEmitSystem>();
	mRegistry->AddSystem<ProjectileSystem>();
	mRegistry->AddSystem<ScriptSystem>();

	mRegistry->GetSystem<ScriptSystem>().CreateLuaBindings(lua);

	lua.open_libraries(sol::lib::base, sol::lib::math, sol::lib::os);
	GameManager::LoadLevel(2, mRegistry, lua);
}
