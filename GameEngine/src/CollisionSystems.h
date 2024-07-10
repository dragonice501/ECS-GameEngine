#pragma once

#include "Engine.h"

#include "ECS.h"
#include "Components.h"
#include "Events.h"
#include "Logger.h"

#include <math.h>

class Particle2DLine2DCollisionSystem : public System
{
public:
	Particle2DLine2DCollisionSystem() {}

	void Update(const float deltaTime)
	{
		for (auto& particle : mRegistry->GetEntitiesByGroup("particles"))
		{
			auto& transform = particle.GetComponent<TransformComponent>();
			auto& rigidbody = particle.GetComponent<RigidbodyComponent>();

			for (auto& line : mRegistry->GetEntitiesByGroup("lines"))
			{
				auto& lineComponent = line.GetComponent<LineComponent>();
				
				Vec2 v = lineComponent.p2 - lineComponent.p1;

				if (CheckLineIntersection(rigidbody.previousPosition, transform.position, lineComponent.p1, lineComponent.p2))
				{
					transform.position = GetIntersection(rigidbody.previousPosition, transform.position, lineComponent.p1, lineComponent.p2);
					rigidbody.velocity = rigidbody.velocity.Reflect(v.Normal());

					return;
				}

				Vec2 w = transform.position - lineComponent.p1;

				float l = v.Magnitude();
				float t = v.Dot(w) / (l * l);

				/*if (t < 0.0f)
				{
					GraphicsManager::DrawLine(
						static_cast<int>(transform.position.x),
						static_cast<int>(transform.position.y),
						static_cast<int>(lineComponent.p1.x),
						static_cast<int>(lineComponent.p1.y),
						0xFF00FF00,
						false);
				}
				else if (t > 1.0f)
				{
					GraphicsManager::DrawLine(
						static_cast<int>(transform.position.x),
						static_cast<int>(transform.position.y),
						static_cast<int>(lineComponent.p2.x),
						static_cast<int>(lineComponent.p2.y),
						0xFF00FF00,
						false);
				}
				else
				{
					Vec2 u = v * t;

					GraphicsManager::DrawLine(
						static_cast<int>(transform.position.x),
						static_cast<int>(transform.position.y),
						static_cast<int>(lineComponent.p1.x + u.x),
						static_cast<int>(lineComponent.p1.y + u.y),
						0xFF00FF00,
						false);
				}*/
			}
		}
	}

	float Orientation(const Vec2& p, const Vec2& q, const Vec2& r)
	{
		return (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
	}

	bool CheckLineIntersection(const Vec2& a, const Vec2& b, const Vec2& c, const Vec2& d)
	{
		float o1 = Orientation(a, b, c);
		float o2 = Orientation(a, b, d);
		float o3 = Orientation(c, d, a);
		float o4 = Orientation(c, d, b);

		// Check for intersection
		if (((o1 > 0 && o2 < 0) || (o1 < 0 && o2 > 0)) &&
			((o3 > 0 && o4 < 0) || (o3 < 0 && o4 > 0)))
		{
			return true;
		}

		return false;
	}

	Vec2 GetIntersection(const Vec2& a, const Vec2& b, const Vec2& c, const Vec2& d)
	{
		float a1 = b.y - a.y;
		float b1 = a.x - b.x;
		float c1 = a1 * a.x + b1 * a.y;

		float a2 = d.y - c.y;
		float b2 = c.x - d.x;
		float c2 = a2 * c.x + b2 * c.y;

		float dt = a1 * b2 - a2 * b1;

		if (dt == 0) return Vec2();
		else
		{
			float x = (b2 * c1 - b1 * c2) / dt;
			float y = (a1 * c2 - a2 * c1) / dt;
			
			return Vec2(x, y);
		}
	}
};