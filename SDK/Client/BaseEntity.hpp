#pragma once

#include "../../Utils/Memory/Memory.hpp"
#include "../../Utils/Memory/Modules.hpp"
#include "../../Utils/Offsets/Offsets.hpp"

#include "../Utils/ClassID.hpp"
#include "../Utils/Vector.hpp"

#include "../Vars.hpp"

class c_base_entity {
//main variable
public:
	int base = 0;

//main methods
public:
	c_base_entity() {}
	c_base_entity(int _base): base(_base) {};

	virtual int get() {
		return this->base;
	}
	void operator=(c_base_entity entity) {
		this->base = entity.get();
	}
	bool operator==(c_base_entity& entity) {
		return this->get() == entity.get();
	}

//props
public:
	PROP(int, m_i_glow_index, get())
	PROP_(int, m_i_class_id,	g_mem.read<int>(
															g_mem.read<int>(
																g_mem.read<int>(get() + 0x8)	//IClientNetworkable
																+ 0x8)												//GetClientClass
															+ 0x1),														//ClientClass
														0x14, int, value)

	PROP(s_vec3, m_vec3_origin, get())

//methods
public:
	en_class_id class_id() {
		auto i_id = m_i_class_id();
		if (i_id <= (int)en_class_id::Invalid || i_id >= (int)en_class_id::InvalidLast) {
			return en_class_id::Invalid;
		}

		return en_class_id(i_id);
	}
	void class_id(en_class_id value) {
		m_i_class_id((int)value);
	}
};