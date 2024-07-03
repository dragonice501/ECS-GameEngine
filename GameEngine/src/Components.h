#pragma once

#include "Vec2.h"
#include "Constants.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include <sol.hpp>
#include <string>

struct AnimationComponent
{
	size_t numFrames;
	size_t currentFrame;
	float animTime;
	float frameRate;
	bool shouldLoop;

	AnimationComponent(size_t numFrames = 1, size_t frameRate = 1, bool shouldLoop = false)
	{
		this->numFrames = numFrames;
		this->currentFrame = 0;
		this->animTime = 0.0f;
		this->frameRate = 1.0f / frameRate;
		this->shouldLoop = shouldLoop;
	}
};

struct CameraFollowComponent
{
	CameraFollowComponent() {}
};

struct BoxCollider2DComponent
{
	size_t width;
	size_t height;
	Vec2 offset;

	BoxCollider2DComponent(const size_t width = 10, const size_t height = 10, const Vec2& offset = Vec2(0.0f, 0.0f))
	{
		this->width = width;
		this->height = height;
		this->offset = offset;
	}
};

struct HealthComponent
{
	int health;

	HealthComponent(const int health = 10)
	{
		this->health = health;
	}
};

struct KeyboardControlComponent
{
	Vec2 upVelocity;
	Vec2 downVelocity;
	Vec2 rightVelocity;
	Vec2 leftVelocity;

	KeyboardControlComponent(
		Vec2 upVelocity = Vec2(0.0f, 0.0f),
		Vec2 downVelocity = Vec2(0.0f, 0.0f),
		Vec2 rightVelocity = Vec2(0.0f, 0.0f),
		Vec2 leftVelocity = Vec2(0.0f, 0.0f))
	{
		this->upVelocity = upVelocity;
		this->downVelocity = downVelocity;
		this->rightVelocity = rightVelocity;
		this->leftVelocity = leftVelocity;
	}
};

struct ProjectileEmitterComponent
{
	Vec2 projectileVelocity;
	float frequency;
	float duration;
	float emitTime;
	size_t damage;
	bool isFriendly;

	ProjectileEmitterComponent(
		const Vec2& projectileVelocty = Vec2(0.0f, 0.0f), 
		size_t frequency = 1, float duration = 1.0f, size_t damage = 1,
		bool isFriendly = true)
	{
		this->projectileVelocity = projectileVelocty;
		this->frequency = 1.0f / frequency;
		this->duration = duration;
		this->damage = damage;
		this->isFriendly = isFriendly;
		emitTime = 0.0f;
	}
};

struct ProjectileComponent
{
	float lifeTime;
	int damage;

	ProjectileComponent(const float lifeTime = 1.0f, const int damage = 10)
	{
		this->lifeTime = lifeTime;
	}
};

struct RigidbodyComponent
{
	Vec2 velocity;

	RigidbodyComponent(Vec2 velocity = Vec2(0.0f, 0.0f))
	{
		this->velocity = velocity;
	}
};

struct ScriptComponent
{
	sol::function func;

	ScriptComponent(sol::function func = sol::lua_nil)
	{
		this->func = func;
	}

	void Update()
	{

	}
};

struct SpriteComponent
{
	unsigned int width;
	unsigned int height;
	unsigned int zIndex;
	SDL_Rect srcRect;
	std::string assetId;
	bool isFixed;

	SpriteComponent(
		const std::string& assetId = "",
		const unsigned int zIndex = 0,
		const unsigned int width = 0, const unsigned int height = 0,
		const unsigned int srcX = 0, const unsigned int srcY = 0,
		bool isFixed = false)
	{
		this->width = width;
		this->height = height;
		this->zIndex = zIndex;
		this->assetId = assetId;
		this->srcRect =
		{
			static_cast<int>(srcX),
			static_cast<int>(srcY),
			static_cast<int>(width),
			static_cast<int>(height)
		};
		this->isFixed = isFixed;
	}
};

struct TextLabelComponent
{
	Vec2 position;
	std::string text;
	std::string assetId;
	SDL_Color color;
	bool isFixed;

	TextLabelComponent(const Vec2& position = Vec2(0.0f, 0.0f), const std::string& text = "", const std::string& assetId = "", const SDL_Color& color = {0, 0, 0}, bool isFixed = true)
	{
		this->position = position;
		this->text = text;
		this->assetId = assetId;
		this->color = color;
		this->isFixed = isFixed;
	}
};

struct TransformComponent
{
	Vec2 position;
	Vec2 scale;
	double rotation;

	TransformComponent(const Vec2& position = Vec2(0.0f, 0.0f), const Vec2& scale = Vec2(1.0f, 1.0f), double rotation = 0.0)
	{
		this->position = position;
		this->scale = scale;
		this->rotation = rotation;
	}
};