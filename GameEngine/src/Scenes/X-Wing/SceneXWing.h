#pragma once
#include "../Scene.h"

#include "../../Utils/Vec2.h"
#include "../../Objects/Curves/Curve.h"
#include "../../Objects/Shapes/AARectangle.h"
#include "../../Objects/Shapes/Rectangle.h"

#include "../../Objects/X-Wing/Ship.h"

class SceneXWing : public Scene
{
public:
	SceneXWing();
	virtual ~SceneXWing();

	void Setup();
	void Shutdown() override;

	void Input() override;
	void Update(float dt) override;
	void Render() override;

	Ship* mSelectedShip = nullptr;

	Ship mShip;

	bool mIsPaused = true;
};

