#pragma once

#include "Engine.h"

#include "ECS.h"
#include "Components.h"
#include "Events.h"

#include <SDL.h>
#include <algorithm>
#include <imgui.h>
#include <imgui_sdl.h>
#include <tuple>

class AnimationSystem : public System
{
public:
	AnimationSystem()
	{
		RequireComponent<AnimationComponent>();
		RequireComponent<SpriteComponent>();
	}

	void Update(const float deltaTime)
	{
		for (auto entity : GetSystemEntities())
		{
			auto& animation = entity.GetComponent<AnimationComponent>();
			auto& sprite = entity.GetComponent<SpriteComponent>();

			animation.animTime += deltaTime;
			if (animation.animTime >= animation.frameRate)
			{
				animation.currentFrame + 1 >= animation.numFrames ? animation.currentFrame = 0 : animation.currentFrame++;
				sprite.srcRect.x = animation.currentFrame * sprite.width;

				animation.animTime = 0.0f;
			}
		}
	}
};

class CameraMovementSystem : public System
{
public:
	CameraMovementSystem()
	{
		RequireComponent<TransformComponent>();
		RequireComponent<CameraFollowComponent>();
	}

	size_t width = GraphicsManager::WindowWidth();
	size_t height = GraphicsManager::WindowHeight();

	void Update(size_t mapWidth, size_t mapHeight)
	{
		for (auto entity : GetSystemEntities())
		{
			auto& transform = entity.GetComponent<TransformComponent>();

			SDL_Rect& camera = GraphicsManager::GetCamera();

			if(transform.position.x + (camera.w / 2) < mapWidth)
			{
				camera.x = transform.position.x - (width / 2);
			}

			if(transform.position.y + (camera.h / 2) < mapHeight)
			{
				camera.y = transform.position.y - (height / 2);
			}

			camera.x = camera.x < 0 ? 0 : camera.x;
			camera.x = camera.x > camera.w ? camera.w : camera.x;
			camera.y = camera.y < 0 ? 0 : camera.y;
			camera.y = camera.y > camera.h ? camera.h : camera.y;
		}
	}
};

class Collision2DSystem : public System
{
public:
	Collision2DSystem()
	{
		RequireComponent<TransformComponent>();
		RequireComponent<BoxCollider2DComponent>();
	}

	void Update()
	{
		auto entities = GetSystemEntities();

		for (auto i = entities.begin(); i != entities.end(); i++)
		{
			Entity& a = *i;
			const auto& aTransform = a.GetComponent<TransformComponent>();
			const auto& aCollider = a.GetComponent<BoxCollider2DComponent>();

			for (auto j = i; j != entities.end(); j++)
			{
				Entity& b = *j;
				if (a == b) continue;

				const auto& bTransform = b.GetComponent<TransformComponent>();
				const auto& bCollider = b.GetComponent<BoxCollider2DComponent>();

				// Perform AABB Collision check
				if (bTransform.position.x + bCollider.width < aTransform.position.x ||
					bTransform.position.x > aTransform.position.x + aCollider.width ||
					bTransform.position.y + bCollider.height < aTransform.position.y ||
					bTransform.position.y > aTransform.position.y + aCollider.height) continue;

				Engine::Instance().GetEventBus()->EmitEvent<CollisionEvent>(a, b);
			}
		}
	}
};

class DamageSystem : public System
{
public:
	DamageSystem()
	{
		RequireComponent<BoxCollider2DComponent>();
	}

	void SubscribeToEvents()
	{
		Engine::Instance().GetEventBus()->SubscribeToEvent<CollisionEvent>(this, &DamageSystem::OnCollision);
	}

	void OnCollision(CollisionEvent& event)
	{
		event.a.Kill();
		event.b.Kill();
	}

	void Update()
	{

	}
};

class KeyboardControlSystem : public System
{
public:
	KeyboardControlSystem()
	{
		RequireComponent<KeyboardControlComponent>();
		RequireComponent<RigidbodyComponent>();
		RequireComponent<SpriteComponent>();
	}

	void SubscribeToEvents()
	{
		Engine::Instance().GetEventBus()->SubscribeToEvent<KeyPressedEvent>(this, &KeyboardControlSystem::OnKeyPressed);
	}

	void OnKeyPressed(KeyPressedEvent& event)
	{
		for (auto entity : GetSystemEntities())
		{
			auto keyboardControl = entity.GetComponent<KeyboardControlComponent>();
			auto& sprite = entity.GetComponent<SpriteComponent>();
			auto& rigidbody = entity.GetComponent<RigidbodyComponent>();

			switch (event.key)
			{
			case SDLK_w:
			{
				rigidbody.velocity = keyboardControl.downVelocity;
				sprite.srcRect.y = sprite.height * 0;
				break;
			}
			case SDLK_s:
			{
				rigidbody.velocity = keyboardControl.upVelocity;
				sprite.srcRect.y = sprite.height * 2;
				break;
			}
			case SDLK_d:
			{
				rigidbody.velocity = keyboardControl.rightVelocity;
				sprite.srcRect.y = sprite.height * 1;
				break;
			}
			case SDLK_a:
			{
				rigidbody.velocity = keyboardControl.leftVelocity;
				sprite.srcRect.y = sprite.height * 3;
				break;
			}
			}
		}
	}
};

class MovementSystem : public System
{
public:
	MovementSystem()
	{
		RequireComponent<RigidbodyComponent>();
		RequireComponent<TransformComponent>();
	}

	void Update(const float deltaTime)
	{
		for (auto entity : GetSystemEntities())
		{
			const auto& rigidbody = entity.GetComponent<RigidbodyComponent>();
			auto& transform = entity.GetComponent<TransformComponent>();

			transform.position += rigidbody.velocity * deltaTime;
		}
	}
};

class ProjectileSystem : public System
{
public:
	ProjectileSystem()
	{
		RequireComponent<ProjectileComponent>();
	}

	void Update(const float deltaTime)
	{
		for (auto entity : GetSystemEntities())
		{
			auto& projectile = entity.GetComponent<ProjectileComponent>();

			projectile.lifeTime -= deltaTime;
			if (projectile.lifeTime <= 0.0f)
			{
				entity.Kill();
			}
		}
	}
};

class ProjectileEmitSystem : public System
{
public:
	ProjectileEmitSystem()
	{
		RequireComponent<TransformComponent>();
		RequireComponent<ProjectileEmitterComponent>();
	}

	void SubscribeToEvents()
	{
		Engine::Instance().GetEventBus()->SubscribeToEvent<KeyPressedEvent>(this, &ProjectileEmitSystem::OnKeyPressed);
	}

	void OnKeyPressed(KeyPressedEvent& event)
	{
		if (event.key == SDLK_SPACE)
		{
			for (auto entity : GetSystemEntities())
			{
				if (entity.HasComponent<CameraFollowComponent>())
				{
					auto& transform = entity.GetComponent<TransformComponent>();
					auto& emitter = entity.GetComponent<ProjectileEmitterComponent>();
					auto& rigidbody = entity.GetComponent<RigidbodyComponent>();

					Vec2 position;
					if (entity.HasComponent<SpriteComponent>())
					{
						auto& sprite = entity.GetComponent<SpriteComponent>();
						position.x += sprite.width / 2;
						position.y += sprite.height / 2;
					}

					Vec2 velocity = emitter.projectileVelocity;
					float directionX = 0.0f;
					float directionY = 0.0f;
					if (rigidbody.velocity.x > 0) directionX = 1;
					if (rigidbody.velocity.x < 0) directionX = -1;
					if (rigidbody.velocity.y > 0) directionY = 1;
					if (rigidbody.velocity.y < 0) directionY = -1;
					velocity.x = emitter.projectileVelocity.x * directionX + rigidbody.velocity.x;
					velocity.y = emitter.projectileVelocity.y * directionY + rigidbody.velocity.y;

					Entity projectile = Engine::Instance().GetRegistry()->CreateEntity();
					projectile.AddComponent<TransformComponent>(transform.position + position);
					projectile.AddComponent<RigidbodyComponent>(velocity);
					projectile.AddComponent<BoxCollider2DComponent>(4, 4);
					projectile.AddComponent<SpriteComponent>("bullet-texture", 5, 4, 4);
					projectile.AddComponent<ProjectileComponent>(emitter.duration, emitter.damage);
				}
			}
		}
	}

	void Update(const float deltaTime)
	{
		for (auto entity : GetSystemEntities())
		{
			auto& transform = entity.GetComponent<TransformComponent>();
			auto& emitter = entity.GetComponent<ProjectileEmitterComponent>();

			emitter.emitTime += deltaTime;

			if (emitter.emitTime == 0) continue;

			if (emitter.emitTime > emitter.frequency)
			{
				Vec2 position;
				if (entity.HasComponent<SpriteComponent>())
				{
					auto& sprite = entity.GetComponent<SpriteComponent>();
					position.x += sprite.width / 2;
					position.y += sprite.height / 2;
				}
				emitter.emitTime = 0.0f;

				Entity projectile = Engine::Instance().GetRegistry()->CreateEntity();
				projectile.AddComponent<TransformComponent>(transform.position + position);
				projectile.AddComponent<RigidbodyComponent>(emitter.projectileVelocity);
				projectile.AddComponent<BoxCollider2DComponent>(4, 4);
				projectile.AddComponent<SpriteComponent>("bullet-texture", 5, 4, 4);
				projectile.AddComponent<ProjectileComponent>(emitter.duration, emitter.damage);
			}
		}
	}
};