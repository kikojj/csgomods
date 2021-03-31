#pragma once

#include "Vector.hpp"
#include "UserCmd.hpp"
#include "VerifiedUserCmd.hpp"

class c_input {
public:
	char									pad_0x00[0x0C];
	bool									track_ir_available;
	bool									mouse_initialized;
	bool									mouse_active;
	bool									joystick_advanced_init;
	char									pad_0x08[0x2C];
	void*									keys;
	char									pad_0x38[0x6C];
	bool									camera_intercepting_mouse;
	bool									camera_in_third_person;
	bool									camera_moving_with_mouse;
	s_vec3								camera_offset;
	bool									camera_distance_move;
	int										camera_old_x;
	int										camera_old_y;
	int										camera_x;
	int										camera_y;
	bool									camera_is_orthographic;
	s_vec3								previous_view_angles;
	s_vec3								previous_view_angles_tilt;
	float									last_forward_move;
	int										clear_input_state;
	char									pad_0xE4[0x8];
	c_user_cmd*						commands;										//0xF4
	c_verified_user_cmd*	verifiedCommands;						//0xF8
};