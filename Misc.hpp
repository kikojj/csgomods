#pragma once

#include <algorithm>

#include "Client.hpp"
#include "Engine.hpp"
#include "Offsets.hpp"
#include "Settings.hpp"

#include "BaseEntity.hpp"
#include "BaseCombatWeapon.hpp"
#include "Helpers.hpp"

#include "FlagsState.hpp"

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