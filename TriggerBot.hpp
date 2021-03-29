#pragma once

#include <Windows.h>
#include <chrono>

#include "SDK/Engine/Engine.hpp"
#include "SDK/Client/Client.hpp"
#include "SDK/Client/BaseEntity.hpp"
#include "SDK/Client/BasePlayer.hpp"
#include "SDK/Client/BaseWeapon.hpp"
#include "SDK/Utils/FlagsState.hpp"

#include "Utils/Helpers/Helpers.hpp"
#include "Utils/Offsets/Offsets.hpp"
#include "Utils/Settings/Settings.hpp"

class TriggerBot {
private:
	std::chrono::high_resolution_clock::time_point lastPressTime = std::chrono::high_resolution_clock::now();

public:
	bool shouldShoot = false;
	bool shouldWait = false;

	TriggerBot();
	void loop();
};