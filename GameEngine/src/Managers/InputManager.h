#pragma once

class InputManager
{
public:
	static void Update(const float dt);

	static inline const bool UpPressed() { return mUpPressed; }
	static inline const bool UpHeld() { return mUpHeld; }
	static inline const bool UpReleased() { return mUpReleased; }
	static inline const float UpHeldTime() { return mUpHeldTime; }

	static inline const bool DownPressed() { return mDownPressed; }
	static inline const bool DownHeld() { return mDownHeld; }
	static inline const bool DownReleased() { return mDownReleased; }
	static inline const float DownHeldTime() { return mDownHeldTime; }

	static inline const bool LeftPressed() { return mLeftPressed; }
	static inline const bool LeftHeld() { return mLeftHeld; }
	static inline const bool LeftReleased() { return mLeftReleased; }
	static inline const float LeftHeldTime() { return mLeftHeldTime; }

	static inline const bool RightPressed() { return mRightPressed; }
	static inline const bool RightHeld() { return mRightHeld; }
	static inline const bool RightReleased() { return mRightReleased; }
	static inline const float RightHeldTime() { return mRightHeldTime; }

	static inline const bool EPressed() { return mEPressed; }
	static inline const bool OPressed() { return mOPressed; }
	static inline const bool SpacebarPresssed() { return mSpacebarPressed;  }

private:
	InputManager() {}
	~InputManager() {}

	static bool mUpPressed;
	static bool mUpHeld;
	static bool mUpReleased;
	static float mUpHeldTime;

	static bool mDownPressed;
	static bool mDownHeld;
	static bool mDownReleased;
	static float mDownHeldTime;

	static bool mLeftPressed;
	static bool mLeftHeld;
	static bool mLeftReleased;
	static float mLeftHeldTime;

	static bool mRightPressed;
	static bool mRightHeld;
	static bool mRightReleased;
	static float mRightHeldTime;

	static bool mEPressed;
	static bool mOPressed;
	static bool mSpacebarPressed;
};