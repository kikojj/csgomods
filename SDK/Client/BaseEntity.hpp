#pragma once

#include <string>

#include "../Vars.hpp"

#include "../Utils/ColorRGBA.hpp"
#include "../Utils/ClassID.hpp"

#include "../../Utils/Memory/Memory.hpp"
#include "../../Utils/Memory/Modules.hpp"
#include "../../Utils/Offsets/Offsets.hpp"

class BaseEntity {
public:
	int dwBase = 0;

	BaseEntity();
	BaseEntity(int);

	VAR_R_DEC(ClassID, m_iClassID)
	VAR_R_DEC(int, m_iGlowIndex)
	VAR_R_DEC(float, m_flC4Blow)

	void operator=(BaseEntity);
	virtual int get();
	int getEntityID();
};