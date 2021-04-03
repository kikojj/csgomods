#pragma once

#include <iostream>

#include "../../Utils/Memory/Memory.hpp"
#include "../../Utils/Memory/Modules.hpp"
#include "../../Utils/Offsets/Offsets.hpp"
#include "../../Utils/VisibleCheck/VisibleCheck.hpp"

#include "../Utils/Vector.hpp"
#include "../Utils/Skeleton.hpp"

#include "../Vars.hpp"

#include "BasePlayer.hpp"
#include "EntityList.hpp"

class c_local_player : public c_base_player {
//main methods
public:
	c_local_player() {}

	virtual int get(){
		return g_mem.read<int>(g_client_dll.base + c_offsets::signatures::dw_local_player);
	}

//props
public:
	PROP(int,			m_i_crosshair_id, get())	//entity in crosshair

	PROP(s_vec3,	m_vec3_velocity,	get())	//direction of movement of the player

//methods
public:
	bool can_see_player(c_base_player player, int bone = -1, bool smoke_check = false) {
		auto i_player_id = c_entity_list::get_entity_id(player.get());
		return can_see_player({ player, i_player_id }, bone, smoke_check);
	}
	bool can_see_player(c_entity_list::t_entity_object entity_object, int bone = -1, bool smoke_check = false) {
		auto i_player_id = entity_object.second;

		if (i_player_id < 0) {
			return false;
		}

		bool b_is_visible = false;

		if (bone <= 0) {
			b_is_visible = g_visible_check.is_visible(i_player_id);
		}
		else {
			b_is_visible = g_visible_check.is_visible(i_player_id, bone);
		}

		if (smoke_check && b_is_visible) {
			auto myView = (c_vector3(m_vec3_origin()) + c_vector3(m_vec3_view_offset())).to_vec3();

			c_base_player player(entity_object.first);
			auto playerBonePos = player.get_bone_pos(bone <= 0 ? en_skeleton::Chest : (en_skeleton)bone).to_vec3();

			if (!g_visible_check.line_goes_through_smoke(myView, playerBonePos)) {
				b_is_visible = true;
			}
			else {
				b_is_visible = false;
			}
		}

		return b_is_visible;
	}
};