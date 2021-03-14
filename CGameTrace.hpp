#pragma once

#include <Windows.h>

#include "CBaseTrace.hpp"
#include "CSurface.hpp"

struct CGameTrace : public CBaseTrace {
public:
	float               fractionleftsolid;  // time we left a solid, only valid if we started in solid
	csurface_t          surface;            // surface hit (impact surface)
	int                 hitgroup;           // 0 == generic, non-zero is specific body part
	short               physicsbone;        // physics bone hit by trace in studio
	unsigned short      worldSurfaceIndex;  // Index of the msurface2_t, if applicable
	DWORD								hit_entity;
	int                 hitbox;                       // box hit by trace in studio
};