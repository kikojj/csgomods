#pragma once

#include <Windows.h>
#include <chrono>

#include "SDK/Engine/Engine.hpp"
#include "SDK/Client/Client.hpp"
#include "SDK/Client/BaseEntity.hpp"
#include "SDK/Client/BasePlayer.hpp"
#include "SDK/Client/BaseCombatWeapon.hpp"
#include "SDK/Utils/FlagsState.hpp"

#include "Utils/Helpers/Helpers.hpp"
#include "Utils/Offsets/Offsets.hpp"
#include "Utils/Settings/Settings.hpp"

class TriggerBot {
public:
	bool shouldShoot = false;
	bool shouldWait = false;
	TriggerBot();
	void loop();
};