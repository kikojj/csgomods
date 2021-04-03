#pragma once

#include <Windows.h>
#include <vector>
#include <algorithm>
#include <chrono>

#include "SDK/Engine/Engine.hpp"
#include "SDK/Client/Client.hpp"
#include "SDK/Client/BasePlayer.hpp"
#include "SDK/Client/BaseWeapon.hpp"
#include "SDK/Utils/Skeleton.hpp"
#include "SDK/Utils/BoneVector.hpp"
#include "SDK/Utils/FlagsState.hpp"

#include "Utils/Math.hpp"
#include "Utils/Offsets/Offsets.hpp"
#include "Utils/Settings/Settings.hpp"
#include "Utils/Helpers/Helpers.hpp"

class c_aim_bot {
private:
	//aim
	float				fov = 0;
	float				smooth = 0;
	en_skeleton bone = en_skeleton::Nearest;
	bool				first_perfect_shoot = false;
	bool				change_after_nearest = false;

	//rcs
	bool	rcs_enable = false;
	float rcs_scale_x = 0;
	float rcs_scale_y = 0;

	//neccesary variables
	bool																						target_was_reached = false;
	float																						closest_angle = 360.0f;
	en_skeleton																			closest_bone = en_skeleton::Head;
	c_base_player																		closest_target;
	std::chrono::high_resolution_clock::time_point	last_kill_time = std::chrono::high_resolution_clock::now();

	void reset_settings();
	c_vector3 calc_angle(c_vector3, c_vector3);
	float get_fov(c_vector2, c_vector3);
	void set_angle(c_vector2);
	void apply_weapon_settings(c_settings::s_aimbot_settings);
	bool apply_weapons_settings(c_base_weapon);

public:
	bool should_shoot = false;
	bool should_wait = false;

	c_aim_bot();
	void loop();
};