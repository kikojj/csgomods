#pragma once

#include <iostream>
#include "../../Utils/Memory/Memory.hpp"
#include "../../Utils/Memory/Modules.hpp"
#include "../../Utils/Offsets/Offsets.hpp"

#include "../Utils/Defines.hpp"

#include "ClientState.hpp"

class c_engine {
//main variables
public:
	c_client_state* client_state = nullptr;

//main methods
public:
	c_engine() {
		client_state = new c_client_state();
	}

//methods
public:
	std::array<char, 0x120> game_dir() {
		auto arr_game_dir = g_mem.read<std::array<char, 0x120>>(g_engine_dll.base + c_offsets::signatures::dw_game_dir);
		return arr_game_dir;
	}
	bool is_overlay_active() {
		auto b_is_overlay_active = g_mem.read<bool>(g_engine_dll.base + c_offsets::signatures::overlay_activated1 + g_engine_dll.base + c_offsets::signatures::overlay_activated2);
		return b_is_overlay_active;
	}
};

extern c_engine g_engine;