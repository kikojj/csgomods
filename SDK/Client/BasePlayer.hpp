#pragma once

#include <vector>

#include "../../Utils/Memory/Memory.hpp"
#include "../../Utils/Memory/Modules.hpp"
#include "../../Utils/Offsets/Offsets.hpp"
#include "../../Utils/BspParser/BspParser.hpp"

#include "../Utils/Vector.hpp"
#include "../Utils/TeamNum.hpp"
#include "../Utils/Skeleton.hpp"
#include "../Utils/LifeState.hpp"
#include "../Utils/ColorRGBA.hpp"
#include "../Utils/PlayerInfo.hpp"
#include "../Engine/Engine.hpp"

#include "../Vars.hpp"

#include "BaseEntity.hpp"
#include "BaseWeapon.hpp"
#include "EntityList.hpp"

class c_base_player : public c_base_entity {
//main methods
public:
	c_base_player() {}
	c_base_player(int base) {
		this->base = base;
	};
	c_base_player(c_base_entity entity) {
		this->base = entity.get();
	}
	c_base_player(c_base_player& player) {
		this->base = player.get();
	}

	virtual int get() {
		return this->base;
	}

//props
public:
	PROP(bool,				m_b_dormant,							get())
	PROP(bool,				m_b_spotted,							get())
	PROP(bool,				m_b_has_defuser,					get())
	PROP(bool,				m_b_is_defusing,					get())
	PROP(bool,				m_b_is_scoped,						get())
	PROP(bool,				m_b_has_helmet,						get())

	PROP(int,					m_i_health,								get())
	PROP(int,					m_armor_value,						get())
	PROP(int,					m_i_team_num,							get())
	PROP(int,					m_dw_bone_matrix,					get())	//player matrix of bones: [Bone] [x] [y] [z]
	PROP(int,					m_h_active_weapon,				get())
	PROP(int,					m_i_shots_fired,					get())	//how many bullets did player fired
	PROP(int,					m_f_flags,								get())
	PROP(int,					m_h_view_model,						get())
	PROP(int,					m_i_observer_mode,				get())
	PROP(int,					m_life_state,							get())
	PROP(int,					m_b_spotted_by_mask,			get())
	PROP(int,					m_n_tick_base,						get())
	PROP(int,					m_i_account,							get())

	PROP(float,				m_f_flash_duration,				get())
	PROP(float,				m_f_flash_alpha,					get())
	PROP(float,				m_f_flash_max_alpha,			get())

	PROP(s_vec2,			m_view_punch_angle,				get())
	PROP(s_vec2,			m_aim_punch_angle,				get())	//shoting angle on screen's plane, only if shooting
	PROP(s_vec3,			m_vec3_view_offset,				get())	//player eyes pos offset(must add this to m_vecOrigin to get real eyes pos)

	PROP(s_render_color, m_clr_render,					get())

//methods
public:
	en_team_num team_num() {
		auto i_team = m_i_team_num();
		if (i_team <= int(en_team_num::Invalid) || i_team >= int(en_team_num::InvalidLast)) {
			return en_team_num::Invalid;
		};
		return en_team_num(i_team);
	}
	en_life_state life_state() {
		auto i_lifeState = m_life_state();
		if (i_lifeState <= int(en_life_state::Invalid) || i_lifeState >= int(en_life_state::Invalid)) {
			return en_life_state::Invalid;
		}
		return en_life_state(i_lifeState);
	}
	bool spotted_by_mask(int id) {
		auto b_spotted = m_b_spotted_by_mask() & (1 << id);
		return b_spotted;
	}
	c_vector3 get_bone_pos(en_skeleton bone) {
		auto vec_bonePos = c_vector3(g_mem.read<s_bone_vector>(m_dw_bone_matrix() + 0x30 * (int)bone + 0x0C));
		return vec_bonePos;
	}
	void render(s_color_rgba color) {
		s_render_color renderColor{ (BYTE)color.r, (BYTE)color.g, (BYTE)color.b, (BYTE)color.a };
		m_clr_render(renderColor);
	}
	c_base_weapon active_weapon(){
		int i_active_weapon_id = m_h_active_weapon() & 0xfff;
		c_base_weapon active_weapon(c_entity_list::get_by_id(i_active_weapon_id - 1));
		return active_weapon;
	}
	int my_weapon_by_id(int id) {
		auto i_weapon_base = g_mem.read<int>(get() + c_offsets::netvars::m_h_my_weapons + id * 0x4);
		return i_weapon_base;
	}
	std::vector<int> my_weapons() {
		std::vector<int> weapons;
		for (int i = 0; i < 8; i++) {
			auto i_weapon_id = my_weapon_by_id(i) & 0xfff;
			weapons.push_back(i_weapon_id);
		}
		return weapons;
	}
	bool is_bsp_visible_from(c_vector3 origin) {
		for (auto bone : ALL_BONES) {
			if (g_bsp_parser.is_visible(origin.toMatrix(), get_bone_pos(bone).toMatrix())) {
				return true;
			}
		}
		return false;
	}
	c_player_info info() {
		auto i_items_base = g_mem.read<int>(g_mem.read<int>(g_engine.client_state->player_info() + 0x40) + 0xC);

		auto _i_player_info = g_mem.read<int>(i_items_base + 0x28 + c_entity_list::get_entity_id(get()) * 0x34);
		auto player_info = g_mem.read<c_player_info>(_i_player_info);

		return player_info;
	}

	int player_resource() {
		auto i_player_resource = g_mem.read<int>(g_client_dll.base + c_offsets::signatures::dw_player_resource);
		return i_player_resource;
	}
	int player_resource_base() {
		return player_resource() + (c_entity_list::get_entity_id(get()) + 1) * 4;
	}
	int competitive_ranking() {
		auto i_competitive_ranking = g_mem.read<int>(player_resource_base() + c_offsets::netvars::m_i_competitive_ranking);
		return i_competitive_ranking;
	}
	int competitive_wins() {
		auto i_competitive_wins = g_mem.read<int>(player_resource_base() + c_offsets::netvars::m_i_competitive_wins);
		return i_competitive_wins;
	}
	int ping() {
		auto ping = g_mem.read<int>(player_resource_base() + c_offsets::netvars::m_i_ping);
		return ping;
	}
	int kills() {
		auto i_kills = g_mem.read<int>(player_resource_base() + c_offsets::netvars::m_i_kills);
		return i_kills;
	}
	int assists() {
		auto i_assists = g_mem.read<int>(player_resource_base() + c_offsets::netvars::m_i_assists);
		return i_assists;
	}
	int deaths() {
		auto i_deaths = g_mem.read<int>(player_resource_base() + c_offsets::netvars::m_i_deaths);
		return i_deaths;
	}
	int score() {
		auto i_score = g_mem.read<int>(player_resource_base() + c_offsets::netvars::m_i_score);
		return i_score;
	}
	int mvps() {
		auto i_mvps = g_mem.read<int>(player_resource_base() + c_offsets::netvars::m_i_mvps);
		return i_mvps;
	}
	int clan() {
		auto i_clan = g_mem.read<int>(player_resource_base() + c_offsets::netvars::m_sz_clan);
		return i_clan;
	}
};