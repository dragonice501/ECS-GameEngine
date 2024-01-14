#pragma once

class InputManager
{
public:
	static void Update(const float dt);

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
	static inline const bool KeyPressedSpace() { return mKeyPressedSpace;  }

private:
	InputManager() {}
	~InputManager() {}

	static bool mKeyPressedW;
	static bool mKeyHeldW;
	static bool mKeyReleasedW;
	static float mKeyHeldTimeW;

	static bool mKeyPressedS;
	static bool mKeyHeldS;
	static bool mKeyReleasedS;
	static float mKeyHeldTimeS;

	static bool mKeyPressedA;
	static bool mKeyHeldA;
	static bool mKeyReleasedA;
	static float mKeyHeldTimeA;

	static bool mKeyPressedD;
	static bool mKeyHeldD;
	static bool mKeyReleasedD;
	static float mKeyHeldTimeD;

	static bool mKeyPressedE;
	static bool mKeyPressedO;
	static bool mKeyPressedSpace;
};