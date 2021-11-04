#pragma once

#include "../../Utils/Memory/Memory.hpp"
#include "../../Utils/Memory/Modules.hpp"
#include "../../Utils/Offsets/Offsets.hpp"

#include "../Utils/Defines.hpp"
#include "../Utils/GlowObjectDefinition.hpp"
#include "../Utils/Input.hpp"
#include "../Utils/KeyEvent.hpp"
#include "../Utils/ViewMatrix.hpp"

#include "../Vars.hpp"

#include "LocalPlayer.hpp"
#include "EntityList.hpp"
#include "GlowObjectManager.hpp"
#include "GlobalVars.hpp"

class c_client {
//main variables
public:
	c_global_vars*					global_vars;
	c_local_player*					local_player;
	c_entity_list*					entity_list;
	c_glow_object_manager*	glow_object_manager;

//main methods
public:
	c_client() {
		global_vars					= new c_global_vars();
		local_player				= new c_local_player();
		entity_list					= new c_entity_list();
		glow_object_manager = new c_glow_object_manager();
	}

//props
public:
	C_PROP_PTR(short, dw_mouse_enable)
	PROP_(int, confirm_reservation_callback, g_mem.read<int>(g_client_dll.base + c_offsets::signatures::h_confirm_match + 0x7), 0, int, value)

	C_PROP_PTR(c_input, dw_input)

	C_PROP_PTR(en_key_event, dw_force_jump)
	C_PROP_PTR(en_key_event, dw_force_attack)

	C_PROP_PTR(s_view_matrix, dw_view_matrix)

	enum class en_enemy_info : unsigned short {
		Show = 0x9090,
		Hide = 0xC63B,
	};
	PROP_PTR(en_enemy_info, dw_enemy_info, g_client_dll.base + 5)

//methods
public:
	int confirm_match() {
		return g_client_dll.base + c_offsets::signatures::h_confirm_match;
	}
};

extern c_client g_client;