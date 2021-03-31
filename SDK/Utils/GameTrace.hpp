#pragma once

#include "BaseTrace.hpp"
#include "Surface.hpp"

class c_game_trace : public c_base_trace {
public:
	float								fraction_left_solid;  // time we left a solid, only valid if we started in solid
	s_surface						surface;							// surface hit (impact surface)
	int                 hit_group;						// 0 == generic, non-zero is specific body part
	short               physics_bone;					// physics bone hit by trace in studio
	unsigned short      world_surface_index;	// Index of the msurface2_t, if applicable
	unsigned long				hit_entity;
	int                 hitbox;								// box hit by trace in studio
};