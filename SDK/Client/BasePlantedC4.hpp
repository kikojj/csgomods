#pragma once

#include <string>

#include "../../Utils/Memory/Memory.hpp"
#include "../../Utils/Memory/Modules.hpp"
#include "../../Utils/Offsets/Offsets.hpp"

#include "../Utils/ClassID.hpp"

#include "../Vars.hpp"

#include "BaseEntity.hpp"

class BasePlantedC4 : public BaseEntity {
//main methods
public:
	BasePlantedC4() {}
	BasePlantedC4(BaseEntity entity) {
		this->base = entity.get();
	};

	virtual int get() {
		return this->base;
	}

//props
public:
		PROP(float, m_flDefuseCountDown, get())
		PROP(float, m_flTimerLength, get())
		PROP(float, m_flDefuseLength, get())
		PROP(float, m_flC4Blow, get())
		PROP(int,		m_nBombSite, get())
};