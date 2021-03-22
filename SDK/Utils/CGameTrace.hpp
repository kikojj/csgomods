#pragma once

#include <Windows.h>

#include "CBaseTrace.hpp"
#include "ISurface.hpp"

struct CGameTrace : public CBaseTrace {
	float								fractionLeftSolid;  // time we left a solid, only valid if we started in solid
	ISurface						surface;            // surface hit (impact surface)
	int                 hitGroup;           // 0 == generic, non-zero is specific body part
	short               physicsBone;        // physics bone hit by trace in studio
	unsigned short      worldSurfaceIndex;  // Index of the msurface2_t, if applicable
	DWORD								hitEntity;
	int                 hitbox;							// box hit by trace in studio
};