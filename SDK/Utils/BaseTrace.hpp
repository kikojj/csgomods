#pragma once

#include "Vector.hpp"
#include "Plane.hpp"

class c_base_trace {
public:
	s_vec3					start_pos;					// start position
	s_vec3					end_pos;						// final position
	s_plane					plane;							// surface normal at impact

	float						fraction;						// time completed, 1.0 = didn't hit anything

	int							contents;						// contents on other side of surface hit
	unsigned short	displacement_flags;	// displacement flags for marking surfaces with data

	bool						all_solid;					// if true, plane is not valid
	bool						start_solid;				// if true, the initial point was in a solid area
};