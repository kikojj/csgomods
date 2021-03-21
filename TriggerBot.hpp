#pragma once

#include <Windows.h>

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
	TriggerBot();
	void loop();
};