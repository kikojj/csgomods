#pragma once

#include "Vector.hpp"
#include "CUserCmd.hpp"

struct Input {
	char                pad_0x00[0x0C];
	bool                trackIRAvailable;
	bool                mouseInitialized;
	bool                mouseActive;
	bool                joystickAdvancedInit;
	char                pad_0x08[0x2C];
	void*								m_pKeys;
	char                pad_0x38[0x6C];
	bool                cameraInterceptingMouse;
	bool                cameraInThirdPerson;
	bool                cameraMovingWithMouse;
	Vec3								vecCameraOffset;
	bool                cameraDistanceMove;
	int                 cameraOldX;
	int                 cameraOldY;
	int                 cameraX;
	int                 cameraY;
	bool                cameraIsOrthographic;
	Vec3								angPreviousViewAngles;
	Vec3								angPreviousViewAnglesTilt;
	float               flLastForwardMove;
	int                 clearInputState;
	char                pad_0xE4[0x8];
	/// <summary>0xF4</summary>
	CUserCmd*						commands;
	/// <summary>0xF8</summary>
	VerifiedUserCmd*		verifiedCommands;
};