#pragma once

#include "ECS.h"
#include "Components.h"

class ParticlePhysicsSystem : public System
{
public:
	ParticlePhysicsSystem()
	{
		RequireComponent<ParticleComponent>();
		RequireComponent<TransformComponent>();
		RequireComponent<RigidbodyComponent>();
	}

	void Update(const float deltaTime)
	{
		for (auto entity : GetSystemEntities())
		{
			auto& transform = entity.GetComponent<TransformComponent>();
			auto& rigidbody = entity.GetComponent<RigidbodyComponent>();

			rigidbody.previousPosition = transform.position;
			transform.position += rigidbody.velocity * deltaTime;
		}
	}
};