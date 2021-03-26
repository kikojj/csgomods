#pragma once

#include <Windows.h>
#include <vector>
#include <algorithm>
#include <chrono>

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
	bool firstPerfectShoot = false;
	Skeleton bone = Skeleton::NEAREST;
	bool changeAfterNearest = false;
	float fov = 0;
	float smooth = 0;

	//rcs
	bool rcsEnable = false;
	float rcsScaleX = 0;
	float rcsScaleY = 0;

	//neccesary variables
	BasePlayer closestEnemy;
	float closestAngle = 360.0f;
	Skeleton closestBone = Skeleton::HEAD;
	std::chrono::high_resolution_clock::time_point lastKillTime = std::chrono::high_resolution_clock::now();

	void resetSettings();
	Vector3 getBonePos(BasePlayer&, Skeleton);
	Vector3 calcAngle(Vector3, Vector3);
	float getFov(Vector3, Vector2);
	void setAngle(Vector2);
	void applyWeaponSettings(IAimbotSettings);
	bool applyWeaponsSettings(BaseCombatWeapon);

public:
	bool shouldShoot = false;
	bool shouldWait = false;

	AimBot();
	void loop();
};