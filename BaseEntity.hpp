#pragma once

#include <string>

#include "Memory.hpp"
#include "Modules.hpp"
#include "Offsets.hpp"

#include "ColorRGBA.hpp"
#include "ClassID.hpp"

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