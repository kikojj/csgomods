#pragma once

#include "Vector.hpp"
#include "CPlane.hpp"

struct CBaseTrace {
public:
	Vec3         startpos;            // start position
	Vec3         endpos;              // final position
	cplane_t       plane;               // surface normal at impact

	float          fraction;            // time completed, 1.0 = didn't hit anything

	int            contents;            // contents on other side of surface hit
	unsigned short dispFlags;           // displacement flags for marking surfaces with data

	bool           allsolid;            // if true, plane is not valid
	bool           startsolid;          // if true, the initial point was in a solid area
};