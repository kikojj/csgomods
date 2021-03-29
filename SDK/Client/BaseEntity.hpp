#pragma once

#include <string>

#include "../../Utils/Memory/Memory.hpp"
#include "../../Utils/Memory/Modules.hpp"
#include "../../Utils/Offsets/Offsets.hpp"

#include "../Utils/ClassID.hpp"
#include "../Utils/Vector.hpp"

#include "../Vars.hpp"

class BaseEntity {
//main variable
public:
	int base = 0;

//main methods
public:
	BaseEntity() {}
	BaseEntity(int _base): base(_base) {};

	virtual int get() {
		return this->base;
	}
	void operator=(BaseEntity entity) {
		this->base = entity.get();
	}
	bool operator==(BaseEntity& entity) {
		return this->get() == entity.get();
	}

//props
public:
	PROP	(int,		m_iGlowIndex, get())
	PROP_	(int,		m_iClassID,		mem.read<int>(
																mem.read<int>(
																	mem.read<int>(get() + 0x8)	//IClientNetworkable
																	+ 0x8)											//GetClientClass
															+ 0x1),													//ClientClass
															0x14, int, value)

	PROP(Vec3,		m_vecOrigin, get())	//entity position

//methods
public:
	ClassID classID() {
		auto id = m_iClassID();
		if (id <= (int)ClassID::Invalid || id >= (int)ClassID::InvalidLast) {
			return ClassID::Invalid;
		}

		return ClassID(id);
	}
	void classID(ClassID value) {
		m_iClassID((int)value);
	}
};