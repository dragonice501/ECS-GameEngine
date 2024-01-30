#pragma once

#include "../Commands/Command.h"
#include "../Utils/Constants.h"
#include "../Utils/Vec2.h"

class InputManager
{
private:
	static bool mMouseLeftClick;
	static Vec2 mMousePosition;

	static bool mKeyPressedA;
	static bool mKeyHeldA;
	static bool mKeyReleasedA;
	static float mKeyHeldTimeA;

	static bool mKeyPressedD;
	static bool mKeyHeldD;
	static bool mKeyReleasedD;
	static float mKeyHeldTimeD;

	static bool mKeyPressedS;
	static bool mKeyHeldS;
	static bool mKeyReleasedS;
	static float mKeyHeldTimeS;

	static bool mKeyPressedW;
	static bool mKeyHeldW;
	static bool mKeyReleasedW;
	static float mKeyHeldTimeW;

	static bool mKeyPressedE;
	static bool mKeyPressedO;
	static bool mKeyPressedR;
	static bool mKeyPressedZ;

	static bool mKeyPressedSpace;

	static Command* mCommandA;
	static Command* mCommandD;
	static Command* mCommandS;
	static Command* mCommandW;

public:
	static void Update(const float dt);

	static inline const bool MouseLeftClick() { return mMouseLeftClick; }
	static inline const Vec2& GetMousePosition() { return mMousePosition * SCREEN_SCALE; }

	static inline const bool KeyPressedW() { return mKeyPressedW; }
	static inline const bool KeyHeldW() { return mKeyHeldW; }
	static inline const bool KeyReleasedW() { return mKeyReleasedW; }
	static inline const float KeyHeldTimeW() { return mKeyHeldTimeW; }

	static inline const bool KeyPressedS() { return mKeyPressedS; }
	static inline const bool KeyHeldS() { return mKeyHeldS; }
	static inline const bool KeyReleasedS() { return mKeyReleasedS; }
	static inline const float KeyHeldTimeS() { return mKeyHeldTimeS; }

	static inline const bool KeyPressedA() { return mKeyPressedA; }
	static inline const bool KeyHeldA() { return mKeyHeldA; }
	static inline const bool KeyReleasedA() { return mKeyReleasedA; }
	static inline const float KeyHeldTimeA() { return mKeyHeldTimeA; }

	static inline const bool KeyPressedD() { return mKeyPressedD; }
	static inline const bool KeyHeldD() { return mKeyHeldD; }
	static inline const bool KeyReleasedD() { return mKeyReleasedD; }
	static inline const float KeyHeldTimeD() { return mKeyHeldTimeD; }

	static inline const bool KeyPressedE() { return mKeyPressedE; }
	static inline const bool KeyPressedO() { return mKeyPressedO; }
	static inline const bool KeyPressedR() { return mKeyPressedR; }
	static inline const bool KeyPressedZ() { return mKeyPressedZ; }
	static inline const bool KeyPressedSpace() { return mKeyPressedSpace;  }

	static inline void SetCommandA(Command& command) { mCommandA = &command; }
	static inline void SetCommandD(Command& command) { mCommandD = &command; }
	static inline void SetCommandS(Command& command) { mCommandS = &command; }
	static inline void SetCommandW(Command& command) { mCommandW = &command; }
	
	static void ClearCommands();
	static Command* GetCommand();

private:
	InputManager() {}
	~InputManager() {}
};