#pragma once

#include "../Vars.hpp"

#include "../Utils/Vector.hpp"
#include "../Utils/ClientStates.hpp"

#include "../../Utils/Memory/Memory.hpp"
#include "../../Utils/Memory/Modules.hpp"
#include "../../Utils/Offsets/Offsets.hpp"

class c_client_state {
	//main methods
public:
	c_client_state() {}

	int get() {
		return g_mem.read<int>(g_engine_dll.base + c_offsets::signatures::dw_client_state);
	}

	//methods
public:
	int get_local_player() {
		return g_mem.read<int>(get() + c_offsets::signatures::dw_cs_get_local_player);
	}
	s_vec2 view_angles() {
		return g_mem.read<s_vec2>(get() + c_offsets::signatures::dw_cs_view_angles);
	}
	void view_angles(s_vec2 vec) {
		auto _vec = c_vector2(vec);
		_vec.clamp();
		_vec.normalize();
		g_mem.write(get() + c_offsets::signatures::dw_cs_view_angles, _vec);
	}
	int delta_tick() {
		return g_mem.read<int>(get() + c_offsets::signatures::dw_cs_delta_ticks);
	}
	void delta_tick(int value) {
		g_mem.write(get() + c_offsets::signatures::dw_cs_delta_ticks, value);
	}
	en_client_states state() {
		auto i_state = g_mem.read<int>(get() + c_offsets::signatures::dw_cs_state);
		return (en_client_states)i_state;
	}
	std::array<char, 0x120> map_directory() {
		auto arr_map_directory = g_mem.read<std::array<char, 0x120>>(get() + c_offsets::signatures::dw_cs_map_directory);
		return arr_map_directory;
	}
	int model_precache() {
		//SHOULD FIND SIGNATURE
		auto i_model_precache = g_mem.read<int>(get() + 0x52A4);;
		return i_model_precache;
	}
	int player_info() {
		auto player_info = g_mem.read<int>(get() + c_offsets::signatures::dw_cs_player_info);
		return player_info;
	}
	int max_players() {
		auto i_max_players = g_mem.read<int>(get() + c_offsets::signatures::dw_cs_max_player);
		return i_max_players;
	}
};