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

class c_trigger_bot {
private:
	std::chrono::high_resolution_clock::time_point last_press_time = std::chrono::high_resolution_clock::now();

	void reset_settings();

public:
	bool should_shoot = false;
	bool should_wait = false;

	c_trigger_bot();
	void loop();
};