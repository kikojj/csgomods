#pragma once

#include "../../Utils/Memory/Memory.hpp"
#include "../../Utils/Memory/Modules.hpp"
#include "../../Utils/Offsets/Offsets.hpp"

#include "../Utils/ClassID.hpp"

#include "../Vars.hpp"

#include "BaseEntity.hpp"

class c_planted_c4 : public c_base_entity {
//main methods
public:
	c_planted_c4() {}
	c_planted_c4(c_base_entity entity) {
		this->base = entity.get();
	};

	int get() {
		return this->base;
	}

//props
public:
		PROP(int,		m_n_bomb_site,					get())

		PROP(float, m_f_c4_blow,						get())
		PROP(float, m_f_timer_length,				get())
		PROP(float, m_f_defuse_length,			get())
		PROP(float, m_f_defuse_count_down,	get())
};