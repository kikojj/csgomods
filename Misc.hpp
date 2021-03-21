#pragma once

#include <algorithm>

#include "SDK/Client/BaseEntity.hpp"
#include "SDK/Client/BaseCombatWeapon.hpp"
#include "SDK/Utils/FlagsState.hpp"

#include "Utils/Memory/Memory.hpp"
#include "Utils/Memory/Modules.hpp"
#include "Utils/Helpers/Helpers.hpp"
#include "Utils/Offsets/Offsets.hpp"
#include "Utils/Settings/Settings.hpp"

class Misc {
public:
	Misc();

	void radarHack();
	void bhop();
	void autoPistols();
	void antiFlash();

private:
	bool found = false;
	bool accepted = false;
	int prevCallback = 0;
	int callback = 0;

public:
	void autoAccept();
};