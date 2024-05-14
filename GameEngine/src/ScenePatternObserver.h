#pragma once

#include "Scene.h"

#include "AARectangle.h"
#include "Vec2.h"

class ScenePatternObserver : public Scene
{
public:
	ScenePatternObserver();
	~ScenePatternObserver();

	void Setup() override;
	void Shutdown() override;

	void Input() override;
	void Update(float dt) override;
	void Render() override;

private:
	class Player : GameObject
	{
	private:
		Vec2 position;
		AARectangle rect;
		float speed = 100.0f;

		Vec2 moveVector;

	public:
		bool moveUp = false;
		bool moveDown = false;
		bool moveLeft = false;
		bool moveRight = false;

	public:
		Player() : Player(Vec2(100.0f, 100.0f), 10) {}
		Player(const Vec2 position, const int size)
		{
			this->position = position;
			rect.topLeft = position;
			rect.bottomRight = position + Vec2(size, size);
		}

		void Input() override
		{
			moveLeft = InputManager::KeyHeldA();
			moveRight = InputManager::KeyHeldD();
			moveDown = InputManager::KeyHeldS();
			moveUp = InputManager::KeyHeldW();
		}

		void Update(const float dt) override
		{
			moveVector = Vec2(0.0f, 0.0f);

			if (moveLeft) moveVector += Vec2(-1.0f, 0.0f);
			if (moveRight) moveVector += Vec2(1.0f, 0.0f);
			if (moveUp) moveVector += Vec2(0.0f, -1.0f);
			if (moveDown) moveVector += Vec2(0.0f, 1.0f);

			if (moveVector.MagnitudeSquared() > 0.0f)
			{
				moveVector.Normalize();
				moveVector *= speed * dt;

				position += moveVector;
				rect.bottomRight += moveVector;
				rect.topLeft += moveVector;
			}
		}
		
		void Render() override
		{
			GraphicsManager::DrawFillAARect(rect, 0xFFFF0000);
		}
	};

	Player mPlayer;
};