#pragma once

#include <string>

#include "../Utils/ColorRGBA.hpp"
#include "../Utils/ClassID.hpp"

#include "../../Utils/Memory/Memory.hpp"
#include "../../Utils/Memory/Modules.hpp"
#include "../../Utils/Offsets/Offsets.hpp"

class BaseEntity {
private:
public:
	int dwBase = 0;

	BaseEntity();
	BaseEntity(int);

	void operator=(BaseEntity);

	virtual int get();

	/// <summary>
	/// get entity class id
	/// </summary>
	/// <returns>EntityClassID variable</returns>
	ClassID m_iClassID();

	/// <summary>
	/// get entity glow index
	/// </summary>
	/// <returns>glow index</returns>
	int m_iGlowIndex();

	int getEntityID();
};