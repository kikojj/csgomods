#pragma once

#include <algorithm>
#include <chrono>

#include "SDK/Client/BaseEntity.hpp"
#include "SDK/Client/BaseWeapon.hpp"
#include "SDK/Utils/FlagsState.hpp"

#include "Utils/Memory/Memory.hpp"
#include "Utils/Memory/Modules.hpp"
#include "Utils/Helpers/Helpers.hpp"
#include "Utils/Offsets/Offsets.hpp"
#include "Utils/Settings/Settings.hpp"

class c_misc {
public:
	c_misc();

	void radar_hack();
	void bhop();
	void anti_flash();

private:
	std::chrono::high_resolution_clock::time_point last_press_time = std::chrono::high_resolution_clock::now();
	void reset_settings();
public:
	bool should_shoot = false;
	bool should_wait = false;
	void auto_pistols();

private:
	bool found = false;
	bool accepted = false;
	int prev_callback = 0;
	int callback = 0;

public:
	void auto_accept();
};