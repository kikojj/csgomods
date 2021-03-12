#pragma once

#include <Windows.h>

#include "Client.hpp"
#include "Engine.hpp"
#include "Offsets.hpp"
#include "Settings.hpp"

#include "BaseEntity.hpp"
#include "BasePlayer.hpp"
#include "BaseCombatWeapon.hpp"

#include "FlagsState.hpp"
#include "Helpers.hpp"

class TriggerBot {
public:
	bool shouldShoot = false;
	bool shouldHold = false;

	TriggerBot();

	void loop();
};