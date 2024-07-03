#pragma once

#include "ECS.h"
#include "TransformComponent.h"
#include "RigidbodyComponent.h"

#include "Logger.h"

class MovementSystem : public System
{
public:
	MovementSystem()
	{
		RequireComponent<TransformComponent>();
		RequireComponent<RigidbodyComponent>();
	}

	void Update(const float deltaTime)
	{
		for (auto entity : GetSystemEntities())
		{
			auto& transform = entity.GetComponent<TransformComponent>();
			const auto& rigidbody = entity.GetComponent<RigidbodyComponent>();

			transform.position += rigidbody.velocity * deltaTime;
		}
	}
};