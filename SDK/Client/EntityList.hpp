#pragma once

#include <iostream>
#include <vector>

#include "../../Utils/Memory/Memory.hpp"
#include "../../Utils/Memory/Modules.hpp"
#include "../../Utils/Offsets/Offsets.hpp"

#include "BaseEntity.hpp"
#include "GlowObjectManager.hpp"

class c_entity_list {
//types
public:
	typedef std::pair<c_base_entity, int> t_entity_object;

//main methods
public:
	c_entity_list() {};

	static int get() {
		return g_client_dll.base + c_offsets::signatures::dw_entity_list;
	}

//methods
public:
	static int size() {
		auto count = g_mem.read<int>(get() + 0x24);
		return count;
	}
	static int get_entity_id(int base) {
		auto i_vec_size = size();
		for (int i = 0; i < i_vec_size; i++) {
			auto entity = get_by_id(i);
			if (entity.get() == base) {
				return i;
			}
		}
		return -1;
	}
	static c_base_entity get_by_id(int id) {
		return c_base_entity(g_mem.read<int>(get() + id * 0x10));
	}
	static std::vector<t_entity_object> array(int size = size()) {
		std::vector<t_entity_object> vec_entity_list;

		for (int i = 0; i <= size; i++) {
			c_base_entity entity(get_by_id(i));

			if (entity.get() <= 0 ) {
				continue;
			}

			vec_entity_list.push_back({ entity, i });
		}

		return vec_entity_list;
	}
	static std::vector<t_entity_object> players(int size = g_engine.client_state->max_players()) {
		std::vector<t_entity_object> vec_player_list;

		for (int i = 0; i <= size; i++) {
			c_base_entity entity(get_by_id(i));

			if (entity.get() <= 0) {
				continue;
			}

			if (entity.class_id() != en_class_id::CCSPlayer) {
				continue;
			}

			vec_player_list.push_back({ entity, i });
		}

		return vec_player_list;
	}
 };