#pragma once

#include <iostream>
#include <string>

#include "../../Utils/Memory/Memory.hpp"
#include "../../Utils/Memory/Modules.hpp"
#include "../../Utils/Offsets/Offsets.hpp"

#include "../Utils/Item.hpp"
#include "../Utils/EntityQuality.hpp"

#include "../Vars.hpp"

#include "BaseEntity.hpp"

class c_base_weapon : public c_base_entity {
//main methods
public:
	c_base_weapon(int base) {
		this->base = base;
	}
	c_base_weapon(c_base_entity entity) {
		this->base = entity.get();
	}
	c_base_weapon(c_base_weapon& weapon) {
		this->base = weapon.get();
	}

//props
public:
	PROP(bool,					m_b_in_reload,							get())

	PROP(short,					m_i_item_definition_index,	get())
	PROP(int,						m_i_clip1,									get())	//the number of remaining bullets in the clip
	PROP(int,						m_original_owner_xuid_low,	get())
	PROP(int,						m_n_fallback_seed,					get())
	PROP(int,						m_n_fallback_stat_trak,			get())
	PROP(int,						m_i_account_id,							get())
	PROP(int,						m_i_item_id_high,						get())
	PROP(int,						m_h_weapon_world_model,			get())
	PROP(int,						m_i_entity_quality,					get())
	PROP(unsigned long, m_i_view_model_index,				get())
	PROP(unsigned long, m_n_model_index,						get())
	PROP(unsigned long, m_n_fallback_paint_kit,			get())

	PROP(float,					m_f_fallback_wear,					get())
	PROP(float,					m_f_next_primary_attack,		get())	//next weapon attack in ticks

	PROP(std::string,		m_sz_custom_name,						get())

//methods
public:
	en_entity_quality entity_quality() {
		auto entity_quality = m_i_entity_quality();
		if (entity_quality <= int(en_entity_quality::Invalid) || entity_quality >= int(en_entity_quality::InvalidLast)) {
			return en_entity_quality::Invalid;
		}

		return (en_entity_quality)entity_quality;
	}
	void entity_quality(en_entity_quality value) {
		m_i_entity_quality((int)value);
	}
	c_item::en_defenition_index item_di() {
		auto di = m_i_item_definition_index();
		if (di <= (int)c_item::en_defenition_index::Invalid || di >= (int)c_item::en_defenition_index::InvalidLast) {
			return c_item::en_defenition_index::Invalid;
		}

		return (c_item::en_defenition_index)di;
	}
	void item_di(c_item::en_defenition_index value) {
		m_i_item_definition_index((int)value);
	}

	bool is_pistol() {
		return c_item::is_pistol(item_di());
	}
	bool is_smg() {
		return c_item::is_smg(item_di());
	}
	bool is_heavy() {
		return c_item::is_heavy(item_di());
	}
	bool is_shotgun() {
		return c_item::is_shotgun(item_di());
	}
	bool is_rifle() {
		return c_item::is_rifle(item_di());
	}
	bool is_snipers() {
		return c_item::is_snipers(item_di());
	}
	bool is_knife() {
		return c_item::is_knife(item_di());
	}
	bool is_bomb() {
		return c_item::is_bomb(item_di());
	}
	bool is_grenade() {
		return c_item::is_grenade(item_di());
	}
	bool is_zeusx27() {
		return c_item::is_zeusx27(item_di());
	}
};