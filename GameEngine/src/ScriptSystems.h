#pragma once

#include "Engine.h"
#include "CollisionSystems.h"
#include "PhysicsSystems.h"
#include "RenderSystems.h"

#include "ECS.h"
#include "Components.h"

#include <tuple>

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

void AddAnimationSystem()
{
	Engine::Instance().GetRegistry()->AddSystem<AnimationSystem>();
}

void AddCollision2DSystem()
{
	Engine::Instance().GetRegistry()->AddSystem<Collision2DSystem>();
}

void AddParticle2DLine2DCollisionSystem()
{
	Engine::Instance().GetRegistry()->AddSystem<Particle2DLine2DCollisionSystem>();
}

void AddKeyboardControlSystem()
{
	Engine::Instance().GetRegistry()->AddSystem<KeyboardControlSystem>();
}

void AddParticlePhysicsSystem()
{
	Engine::Instance().GetRegistry()->AddSystem<ParticlePhysicsSystem>();
}

void AddRenderSystem()
{
	Engine::Instance().GetRegistry()->AddSystem<RenderSystem>();
}

void AddRenderGuiSystem()
{
	Engine::Instance().GetRegistry()->AddSystem<RenderGUISystem>();
}

void AddRenderLineSystem()
{
	Engine::Instance().GetRegistry()->AddSystem<RenderLineSystem>();
}

void AddRenderParticleSystem()
{
	Engine::Instance().GetRegistry()->AddSystem<RenderParticleSystem>();
}

void AddRenderTextSystem()
{
	Engine::Instance().GetRegistry()->AddSystem<RenderTextSystem>();
}

class ScriptSystem : public System
{
public:
	ScriptSystem()
	{
		RequireComponent<ScriptComponent>();
	}

	void CreateLuaBindings(sol::state& lua)
	{
		lua.new_usertype<Entity>(
			"entity",
			"GetID", &Entity::GetID,
			"Destroy", &Entity::Kill,
			"HasTag", &Entity::HasTag,
			"BelongsToGroup", &Entity::BelongsToGroup);

		// Bind Lua Script Entity Functions
		lua.set_function("GetPosition", GetEntityPosition);
		lua.set_function("GetVelocity", GetEntityVelocity);
		lua.set_function("SetPosition", SetEntityPosition);
		lua.set_function("SetVelocity", SetEntityVelocity);
		lua.set_function("SetRotation", SetEntityRotation);
		lua.set_function("SetProjectileVelocity", SetProjectileVelocity);
		lua.set_function("SetAnimationFrame", SetEntityAnimationFrame);

		// Bind Lua System Functions
		lua.set_function("AddAnimationSystem", AddAnimationSystem);

		lua.set_function("AddCollision2DSystem", AddCollision2DSystem);
		lua.set_function("AddParticle2DLine2DCollisionSystem", AddParticle2DLine2DCollisionSystem);

		lua.set_function("AddKeyboardControlSystem", AddKeyboardControlSystem);

		lua.set_function("AddParticlePhsyicsSystem", AddParticlePhysicsSystem);

		lua.set_function("AddRenderSystem", AddRenderSystem);
		lua.set_function("AddRenderGUISystem", AddRenderGuiSystem);
		lua.set_function("AddRenderLineSystem", AddRenderLineSystem);
		lua.set_function("AddRenderParticleSystem", AddRenderParticleSystem);
		lua.set_function("AddRenderTextSystem", AddRenderTextSystem);
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