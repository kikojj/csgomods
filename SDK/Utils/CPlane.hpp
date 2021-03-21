#pragma once

#include "Vector.hpp"

struct cplane_t {
	Vec3 normal;
	float dist;
	uint8_t type;				// for fast side tests
	uint8_t signbits;		// signx + (signy<<1) + (signz<<1)
	uint8_t pad[2];
};