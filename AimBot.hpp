#pragma once

#include <Windows.h>
#include <vector>
#include <algorithm>

#include "Client.hpp"
#include "Engine.hpp"
#include "Offsets.hpp"
#include "Settings.hpp"

#include "BasePlayer.hpp"
#include "BaseCombatWeapon.hpp"

#include "Math.hpp"
#include "Skeleton.hpp"
#include "BoneVector.hpp"
#include "FlagsState.hpp"

#include "Helpers.hpp"

class AimBot {
private:
	//aim
	Skeleton bone = NEAREST;
	float fov = 0;
	float smooth = 0;

	//rcs
	bool rcsEnable = false;
	float rcsScaleX = 0;
	float rcsScaleY = 0;

	Vector3 getBonePos(BasePlayer&, Skeleton);
	Vector3 calcAngle(Vector3, Vector3);
	float getFov(Vector3, Vector2);
	void setAngle(Vector2);

public:
	AimBot();
	void loop();
};