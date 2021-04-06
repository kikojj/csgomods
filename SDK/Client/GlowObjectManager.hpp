#pragma once

#include <vector>

#include "../Utils/GlowObjectDefinition.hpp"

#include "../../Utils/Memory/Memory.hpp"
#include "../../Utils/Memory/Modules.hpp"
#include "../../Utils/Offsets/Offsets.hpp"

class c_glow_object_manager {
//types
public:
	typedef std::pair<s_glow_object_definition, int> t_glow_object;

//main methods
public:
	c_glow_object_manager() {};

	static int get() {
		return g_mem.read<int>(g_client_dll.base + c_offsets::signatures::dw_glow_object_manager);
	}

//methods
public:
	static int size() {
		auto i_size = g_mem.read<int>(g_client_dll.base + c_offsets::signatures::dw_glow_object_manager + 0x4);
		return i_size;
	}
	static std::vector<t_glow_object> array(int size = size()) {
		std::vector<t_glow_object> vec_glow_object_array;

		for (int i = 0; i <= size; i++) {
			auto glow_object_definition = g_mem.read<s_glow_object_definition>(get() + i * 0x38);

			if (glow_object_definition.base_entity <= 0) {
				continue;
			}

			vec_glow_object_array.push_back({ glow_object_definition, i });
		}
		return vec_glow_object_array;
	}
	static int get_object_base_by_id(int id) {
		auto i_base = get() + id * 0x38;
		return i_base;
	}
	static int get_object_base(t_glow_object obj) {
		auto i_base = get_object_base_by_id(obj.second);
		return i_base;
	}
};