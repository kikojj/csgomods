#pragma once

#include <Windows.h>
#include <vector>

#include "../Memory/Memory.hpp"
#include "../Memory/Modules.hpp"
#include "../Offsets/Offsets.hpp"
#include "../VirtualFunction/VirtualFunction.hpp"

#include "../../SDK/Utils/Vector.hpp"
#include "../../SDK/Utils/EngineTrace.hpp"
#include "../../SDK/Utils/GameTrace.hpp"
#include "../../SDK/Utils/UserCmd.hpp"

#define DW_CREATE_MOVE_VARS 0x00123456

class c_visible_check {
public:
	struct s_visible {
		bool player[64];
		bool player_bones[64][80];
	};
	struct s_create_move_vars {
		//offsets
		DWORD dw_trace_line;
		DWORD dw_client_state;
		DWORD dw_entity_list;
		DWORD dw_local_player;
		DWORD dw_delta_tick;
		DWORD dw_bone_matrix;
		DWORD dw_view_offset;
		DWORD dw_origin;
		DWORD dw_life_state;
		DWORD dw_team_num;
		DWORD dw_health;
		DWORD dw_dormant;

		//needable variables
		int all_bones[17];

		//local variables
		s_vec3 local_origin;
		s_vec3 local_view_offset;
		s_vec3 local_eye_position;
		s_vec3 enemy_bone_position;
		float min_fraction;

		//output trace_t struct
		c_game_trace* trace_output;

		//player's visible struct
		s_visible* visible_struct;
	};

private:
	bool hooked;
	DWORD dw_visible_struct;
	s_visible visible_struct;
	LPVOID p_allocated_trace_output;
	LPVOID p_allocated_visible_struct;
	LPVOID p_allocated_hook_code;

public:
	c_visible_check();
	~c_visible_check();

	bool 	init();
	bool 	update_visible_struct();
	bool 	is_visible(int);
	bool 	is_visible(int, int);

//lineGoesThroughSmoke
private:
	BYTE lgts_shellcode[105] = {
		//0xCC,									// int 3 [debug]

		// Prologue
		0x55,									// push ebp
		0x8B, 0xEC,								// mov ebp, ebp

		// Allocate space for the local Vector end (12 bytes)
		0x83, 0xEC, 0x0C,						// sub esp, 0xC

		// Have a temporary variable to store esp
		0x89, 0xE0,								// mov eax, esp

		// Load our end data
		// end.x
		0x8B, 0x0D, 0x12, 0x34, 0x56, 0x78,		// 	mov ecx, [0x12345678] (endAddr) [@ 0xA]
		0x89, 0x08,								//  mov [eax], ecx

		// end.y
		0x8B, 0x15, 0x12, 0x34, 0x56, 0x78,		// mov edx, [0x12345678] (endAddr + 4) [@ 0x12]
		0x89, 0x50, 0x04,						// mov [eax + 4], edx

		// end.z
		0x8B, 0x0D, 0x12, 0x34, 0x56, 0x78,		// mov ecx, [0x12345678] (endAddr + 8) [ @ 0x1B]
		0x89, 0x48, 0x08,						// mov [eax + 8], ecx

		// Allocate space for the local Vector start (12 bytes)
		0x83, 0xEC, 0x0C,						// sub esp, 0xC

		// Have a temporary variable to store esp
		0x89, 0xE2,								// mov edx, esp

		// Load our start data
		// start.x
		0xA1, 0x12, 0x34, 0x56, 0x78,			// mov eax, [0x12345678] (startAddr) [@ 0x28]
		0x89, 0x02,								// mov [edx], eax

		// start.y
		0x8B, 0x0D, 0x12, 0x34, 0x56, 0x78,		// mov ecx, [0x12345678] (startaddr + 4) [ @ 0x30]
		0x89, 0x4A, 0x04,						// mov [edx + 4], ecx

		// start.z
		0xA1, 0x12, 0x34, 0x56, 0x78,			// mov eax, [0x12345678] (startAddr + 8) [@ 0x38]
		0x89, 0x42, 0x08,						// mov [edx + 8], eax

		// Move our function to eax to ensure it calls correctly
		0xB8, 0x12, 0x34, 0x56, 0x78,			// mov eax, [0x12345678] (func address) [@ 0x40]
		0xFF, 0xD0,								// call eax

		0xA3, 0x12, 0x34, 0x56, 0x78,			// [0x12345678], eax  (returnValue) [@ 0x47]

		// clean up stack of local variables
		0x83, 0xC4, 0x18,						// add esp, 0x18

		// epilogue lazy way
		0xC9,									// leave
		0xC3,									// ret

		// -- End of function shellcode --

		// reserved memory for Vector start
		0x12,0x34,0x56,0x78,0x12,0x34,0x56,0x78,0x12,0x34,0x56,0x78,	// [@ 0x50]
		// reserved memory for Vector end
		0x12,0x34,0x56,0x78,0x12,0x34,0x56,0x78,0x12,0x34,0x56,0x78,	// [@ 0x5C] 
		// reserved memory for bool return value
		0x12															// [@ 0x68]
	};
	//sizeof(LGTSShellcode) - (0xC + 0xC + 0x1)
	const short LGTS_SHELLCODE_SIZE = 80;

public:
	bool line_goes_through_smoke(s_vec3, s_vec3);
};

extern c_visible_check g_visible_check;