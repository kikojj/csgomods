#pragma once

#include "Vector.hpp"

struct s_plane {
	s_vec3	normal;
	float		dist;
	uint8_t type;					// for fast side tests
	uint8_t sign_bits;		// signx + (signy<<1) + (signz<<1)
	uint8_t _pad0x18[2];
};