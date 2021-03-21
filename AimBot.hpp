#pragma once

#include <Windows.h>
#include <vector>
#include <algorithm>

#include "SDK/Client/Client.hpp"
#include "SDK/Client/BasePlayer.hpp"
#include "SDK/Client/BaseCombatWeapon.hpp"
#include "SDK/Engine/Engine.hpp"
#include "SDK/Utils/Skeleton.hpp"
#include "SDK/Utils/BoneVector.hpp"
#include "SDK/Utils/FlagsState.hpp"

#include "Utils/Math.hpp"
#include "Utils/Offsets/Offsets.hpp"
#include "Utils/Settings/Settings.hpp"
#include "Utils/Helpers/Helpers.hpp"

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
	void applyWeaponSettings(IAimbotSettings);
	bool applyWeaponsSettings(BaseCombatWeapon);

public:
	AimBot();
	void loop();
};