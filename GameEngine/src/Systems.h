#pragma once

#include "Engine.h"
#include "GraphicsManager.h"

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
					velocity.x = emitter.projectileVelocity.x * directionX;
					velocity.y = emitter.projectileVelocity.y * directionY;

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

class RenderSystem : public System
{
public:
	RenderSystem()
	{
		RequireComponent<SpriteComponent>();
		RequireComponent<TransformComponent>();
	}

	void Draw()
	{
		std::vector<Entity>& entities = GetSystemEntities();
		std::sort(entities.begin(), entities.end(), [](Entity& a, Entity& b)
			{
				const auto& spriteA = a.GetComponent<SpriteComponent>();
				const auto& spriteB = b.GetComponent<SpriteComponent>();

				return spriteA.zIndex < spriteB.zIndex;
			});

		SDL_Rect& camera = GraphicsManager::GetCamera();

		for (auto entity : GetSystemEntities())
		{
			const auto& sprite = entity.GetComponent<SpriteComponent>();
			const auto& transform = entity.GetComponent<TransformComponent>();

			if (sprite.assetId == "tank-texture")
			{

			}

			SDL_Rect dstRect =
			{
				transform.position.x - (sprite.isFixed ? 0 : camera.x),
				transform.position.y - (sprite.isFixed ? 0 : camera.y),
				sprite.width * transform.scale.x,
				sprite.height * transform.scale.y
			};

			SDL_RendererFlip flip = SDL_FLIP_NONE;
			SDL_RenderCopyEx(GraphicsManager::GetRenderer(), AssetManager::GetTexture(sprite.assetId), &sprite.srcRect, &dstRect, transform.rotation, NULL, flip);
		}
	}
};

class RenderGUISystem : public System
{
public:
	RenderGUISystem() {}

	void Draw()
	{
		ImGui::NewFrame();

		ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_AlwaysAutoResize;
		if (ImGui::Begin("Window"), NULL, flags);
		{
			ImGui::Text("This is text");
		}
		ImGui::End();

		ImGui::Render();
		ImGuiSDL::Render(ImGui::GetDrawData());
	}
};

class RenderTextSystem : public System
{
public:
	RenderTextSystem()
	{
		RequireComponent<TextLabelComponent>();
	}

	void Draw()
	{
		SDL_Rect camera = GraphicsManager::GetCamera();

		for (auto entity : GetSystemEntities())
		{
			const auto text = entity.GetComponent<TextLabelComponent>();

			SDL_Surface* surface = TTF_RenderText_Blended(AssetManager::GetFont(text.assetId), text.text.c_str(), text.color);
			SDL_Texture* texture = SDL_CreateTextureFromSurface(GraphicsManager::GetRenderer(), surface);

			int textWidth = 0;
			int textHeight = 0;

			SDL_QueryTexture(texture, NULL, NULL, &textWidth, &textHeight);

			GraphicsManager::DrawTexture(
				text.position.x - camera.x,
				text.position.y - camera.y,
				textWidth,
				textHeight,
				0.0f,
				texture);

			SDL_DestroyTexture(texture);
			SDL_FreeSurface(surface);
		}
	}
};

std::tuple<double, double> GetEntityPosition(Entity entity)
{
	if (entity.HasComponent<TransformComponent>())
	{
		const auto transform = entity.GetComponent<TransformComponent>();
		return std::make_tuple(transform.position.x, transform.position.y);
	}
	else
	{
		Logger::Error("Trying to get the position of an entity that has no transform component");
		return std::make_tuple(0.0, 0.0);
	}
}

std::tuple<double, double> GetEntityVelocity(Entity entity)
{
	if (entity.HasComponent<RigidbodyComponent>())
	{
		const auto rigidbody = entity.GetComponent<RigidbodyComponent>();
		return std::make_tuple(rigidbody.velocity.x, rigidbody.velocity.y);
	}
	else
	{
		Logger::Error("Trying to get the velocity of an entity that has no rigidbody component");
		return std::make_tuple(0.0, 0.0);
	}
}

void SetEntityPosition(Entity entity, double x, double y)
{
	if (entity.HasComponent<TransformComponent>())
	{
		auto& transform = entity.GetComponent<TransformComponent>();
		transform.position.x = x;
		transform.position.y = y;
	}
	else
	{
		Logger::Error("Trying to set the position of an entity that has no transform component");
	}
}

void SetEntityVelocity(Entity entity, double x, double y)
{
	if (entity.HasComponent<RigidbodyComponent>())
	{
		auto& rigidbody = entity.GetComponent<RigidbodyComponent>();
		rigidbody.velocity.x = x;
		rigidbody.velocity.y = y;
	}
	else
	{
		Logger::Error("Trying to set the velocity of an entity that has no rigidbody component");
	}
}

void SetEntityRotation(Entity entity, double angle) 
{
	if (entity.HasComponent<TransformComponent>())
	{
		auto& transform = entity.GetComponent<TransformComponent>();
		transform.rotation = angle;
	}
	else
	{
		Logger::Error("Trying to set the rotation of an entity that has no transform component");
	}
}

void SetEntityAnimationFrame(Entity entity, int frame)
{
	if (entity.HasComponent<AnimationComponent>())
	{
		auto& animation = entity.GetComponent<AnimationComponent>();
		animation.currentFrame = frame;
	}
	else
	{
		Logger::Error("Trying to set the animation frame of an entity that has no animation component");
	}
}

void SetProjectileVelocity(Entity entity, double x, double y)
{
	if (entity.HasComponent<ProjectileEmitterComponent>())
	{
		auto& projectileEmitter = entity.GetComponent<ProjectileEmitterComponent>();
		projectileEmitter.projectileVelocity.x = x;
		projectileEmitter.projectileVelocity.y = y;
	}
	else
	{
		Logger::Error("Trying to set the projectile velocity of an entity that has no projectile emitter component");
	}
}

class ScriptSystem : public System
{
public:
	ScriptSystem() {
		RequireComponent<ScriptComponent>();
	}

	void CreateLuaBindings(sol::state& lua)
	{
		lua.new_usertype<Entity>(
			"entity",
			"GetID", &Entity::GetID,
			"Destroy", &Entity::Kill,
			"HasTag", &Entity::HasTag,
			"BelongsToGroup", &Entity::BelongsToGroup
		);

		lua.set_function("GetPosition", GetEntityPosition);
		lua.set_function("GetVelocity", GetEntityVelocity);
		lua.set_function("SetPosition", SetEntityPosition);
		lua.set_function("SetVelocity", SetEntityVelocity);
		lua.set_function("SetRotation", SetEntityRotation);
		lua.set_function("SetProjectileVelocity", SetProjectileVelocity);
		lua.set_function("SetAnimationFrame", SetEntityAnimationFrame);
	}

	void Update(double deltaTime, int ellapsedTime)
	{
		for (auto entity : GetSystemEntities())
		{
			const auto script = entity.GetComponent<ScriptComponent>();
			script.func(entity, deltaTime, ellapsedTime);
		}
	}
};