#pragma once

#include <algorithm>
#include <chrono>

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
	void antiFlash();

private:
	std::chrono::high_resolution_clock::time_point lastPressTime = std::chrono::high_resolution_clock::now();
public:
	bool shouldShoot = false;
	bool shouldWait = false;
	void autoPistols();

private:
	bool found = false;
	bool accepted = false;
	int prevCallback = 0;
	int callback = 0;

public:
	void autoAccept();

private:
	LPVOID rankRevealAddress = nullptr;
	bool revealedGame = false;
	bool holdingTab = false;
	bool revealedWarmup = false;
public:
	void showRanks();
	void rankReveal();
};