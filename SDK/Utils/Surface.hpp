#pragma once

struct s_surface {
	const char*			name;
	short						surface_props;
	unsigned short	flags;					// BUGBUG: These are declared per surface, not per material, but this database is per-material now
};