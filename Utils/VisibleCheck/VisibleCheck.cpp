#include "VisibleCheck.hpp"

#pragma optimize("", off)
typedef int(__fastcall* t_trace_line)(const s_vec3&, const s_vec3&, unsigned int mask, const DWORD player_base, int, c_game_trace* trace);
bool WINAPI hkCreateMove(float input_sample_time, c_user_cmd* cmd) {
	// hkCreateMove + 0x9 = pointer to Vars;
	// Initialize in InitCreateMoveHook()
	c_visible_check::s_create_move_vars* vars = (c_visible_check::s_create_move_vars*)DW_CREATE_MOVE_VARS;

	DWORD p_local_player = *(DWORD*)(vars->dw_local_player);
	bool b_is_in_game = *(int*)(vars->dw_client_state + 0x108) == 6;
	int i_delta_tick = *(int*)(vars->dw_client_state + vars->dw_delta_tick);
	t_trace_line trace_line = (t_trace_line)vars->dw_trace_line;

	if (!cmd->command_number || !b_is_in_game || !p_local_player || i_delta_tick == -1) {
		return true;
	}

	bool b_local_is_alive = !*(bool*)(p_local_player + vars->dw_life_state);
	if (!b_local_is_alive) {
		return true;
	}

	vars->local_origin = *(s_vec3*)(p_local_player + vars->dw_origin);
	vars->local_view_offset = *(s_vec3*)(p_local_player + vars->dw_view_offset);
	vars->local_eye_position.x = vars->local_origin.x + vars->local_view_offset.x;
	vars->local_eye_position.y = vars->local_origin.y + vars->local_view_offset.y;
	vars->local_eye_position.z = vars->local_origin.z + vars->local_view_offset.z;

	for (int i = 0; i < 64; i++) {
		vars->visible_struct->player[i] = false;

		DWORD p_entity = *(DWORD*)(vars->dw_entity_list + i * 0x10);

		if (!p_entity || p_entity == p_local_player) {
			continue;
		}

		bool b_life_state = *(bool*)(p_entity + vars->dw_life_state);
		bool b_dormant = *(bool*)(p_entity + vars->dw_origin);
		int i_health = *(int*)(p_entity + vars->dw_health);

		if (b_life_state || b_dormant || i_health <= 0) {
			continue;
		}

		// Get Enemy Head Position
		DWORD p_bone_matrix = *(DWORD*)(p_entity + vars->dw_bone_matrix);
		if (!p_bone_matrix) {
			continue;
		}

		bool b_is_visible = false;
		for (int j = 0; j < 17; j++) {
			auto i_bone = vars->all_bones[j];

			vars->enemy_bone_position.x = *(float*)(p_bone_matrix + 0x30 * i_bone + 0x0C);
			vars->enemy_bone_position.y = *(float*)(p_bone_matrix + 0x30 * i_bone + 0x1C);
			vars->enemy_bone_position.z = *(float*)(p_bone_matrix + 0x30 * i_bone + 0x2C);

			// Visible check
			trace_line(vars->local_eye_position, vars->enemy_bone_position, MASK_SHOT | CONTENTS_GRATE, p_local_player, 0, vars->trace_output);

			if (vars->trace_output->fraction > vars->min_fraction || vars->trace_output->hit_entity == p_entity) {
				b_is_visible = true;
				vars->visible_struct->player_bones[i][i_bone] = true;
			}
			else {
				vars->visible_struct->player_bones[i][i_bone] = false;
			}
		}
		vars->visible_struct->player[i] = b_is_visible;
	}

	return true;
}
DWORD WINAPI hkCreateMoveEnd(){ return 0; }
#pragma optimize("", on)

c_visible_check::c_visible_check(){
	hooked = false;
	dw_visible_struct = 0;
	p_allocated_trace_output = nullptr;
	p_allocated_visible_struct = nullptr;
	p_allocated_hook_code = nullptr;
	
	for (int i = 0; i < 64; i++){
		visible_struct.player[i] = false;

		for (int j = 0; j < 80; j++) {
			visible_struct.player_bones[i][j] = false;
		}
	}
}

c_visible_check::~c_visible_check() {
	if (p_allocated_trace_output) {
		g_mem.free(p_allocated_trace_output);
	}
	if (p_allocated_visible_struct) {
		g_mem.free(p_allocated_visible_struct);
	}
	if (p_allocated_hook_code) {
		g_mem.free(p_allocated_hook_code);
	}
}

bool c_visible_check::init() {
	if (hooked) {
		return true;
	}

	// Set CreateMove local Vars
	s_create_move_vars create_move_vars;
#pragma region create_move_vars init
	create_move_vars.dw_client_state = g_mem.read<DWORD>(g_engine_dll.base + c_offsets::signatures::dw_client_state);
	create_move_vars.dw_entity_list = g_client_dll.base + c_offsets::signatures::dw_entity_list;
	create_move_vars.dw_local_player = g_client_dll.base + c_offsets::signatures::dw_local_player;
	create_move_vars.dw_delta_tick = g_mem.read<DWORD>(g_engine_dll.base + c_offsets::signatures::dw_cs_delta_ticks);
	create_move_vars.dw_bone_matrix = c_offsets::netvars::m_dw_bone_matrix;
	create_move_vars.dw_view_offset = c_offsets::netvars::m_vec3_view_offset;
	create_move_vars.dw_origin = c_offsets::netvars::m_vec3_origin;
	create_move_vars.dw_life_state = c_offsets::netvars::m_life_state;
	create_move_vars.dw_team_num = c_offsets::netvars::m_i_team_num;
	create_move_vars.dw_health = c_offsets::netvars::m_i_health;
	create_move_vars.dw_dormant = c_offsets::netvars::m_b_dormant;
	create_move_vars.dw_trace_line = c_offsets::signatures::dw_trace_line;
	create_move_vars.min_fraction = 0.97f;
	create_move_vars.all_bones[0] = 3;
	create_move_vars.all_bones[1] = 4;
	create_move_vars.all_bones[2] = 6;
	create_move_vars.all_bones[3] = 7;
	create_move_vars.all_bones[4] = 8;
	create_move_vars.all_bones[5] = 11;
	create_move_vars.all_bones[6] = 12;
	create_move_vars.all_bones[7] = 13;
	create_move_vars.all_bones[8] = 41;
	create_move_vars.all_bones[9] = 42;
	create_move_vars.all_bones[10] = 43;
	create_move_vars.all_bones[11] = 70;
	create_move_vars.all_bones[12] = 71;
	create_move_vars.all_bones[13] = 72;
	create_move_vars.all_bones[14] = 77;
	create_move_vars.all_bones[15] = 78;
	create_move_vars.all_bones[16] = 79;
#pragma endregion

	// Allocate memory for result TraceLine function
	p_allocated_trace_output = g_mem.allocate();
	create_move_vars.trace_output = (c_game_trace*)p_allocated_trace_output;

	// Allocate memory for visibleStruct
	p_allocated_visible_struct = g_mem.allocate(sizeof(s_visible));
	create_move_vars.visible_struct = (s_visible*)p_allocated_visible_struct;

	// Allocate memory for Hook
	p_allocated_hook_code = g_mem.allocate();

	if (!create_move_vars.trace_output || !create_move_vars.visible_struct || !(DWORD)p_allocated_hook_code) {
		return false;
	}

	// Write hkCreateMove function in to CSGO
	if (!g_mem.write((DWORD)p_allocated_hook_code, hkCreateMove, (DWORD)hkCreateMoveEnd - (DWORD)hkCreateMove)) {
		return false;
	}

	// Write hkCreateMoveVars(Local Variables for CreateMove hook)
	DWORD p_create_move_vars = (DWORD)p_allocated_hook_code + (DWORD)hkCreateMoveEnd - (DWORD)hkCreateMove;
	if (!g_mem.write(p_create_move_vars, create_move_vars)) {
		return false;
	}

	// Set pointer to hkCreateMoveVars
	if (!g_mem.write((DWORD)p_allocated_hook_code + 0x9, p_create_move_vars))
		return false;

	DWORD p_client_mode = g_mem.read<DWORD>(g_mem.read<DWORD>(c_offsets::signatures::dw_client_mode));

	c_virtual_function vf_client_mode(p_client_mode);
	vf_client_mode.hook(24, (DWORD)p_allocated_hook_code);

	dw_visible_struct = (DWORD)create_move_vars.visible_struct;
	hooked = true;

	return hooked;
}
	
bool c_visible_check::update_visible_struct(){
	if (!hooked) {
		return false;
	}

	if (!dw_visible_struct) {
		return false;
	}

	visible_struct = g_mem.read<s_visible>(dw_visible_struct);
	
	return true;
}

bool c_visible_check::is_visible(int entity_id){
	if (!hooked) {
		return false;
	}

	if (!dw_visible_struct) {
		return false;
	}

	if (entity_id >= 64) {
		return false;
	}
	
	return visible_struct.player[entity_id];
}

bool c_visible_check::is_visible(int entity_id, int bone) {
	if (!hooked) {
		return false;
	}

	if (!dw_visible_struct) {
		return false;
	}

	if (entity_id >= 64) {
		return false;
	}

	if (bone >= 80) {
		return false;
	}

	return visible_struct.player_bones[entity_id][bone];
}

bool c_visible_check::line_goes_through_smoke(s_vec3 start, s_vec3 end) {
	// Allocate room for our shellcode in csgo
	auto p_shellcode = g_mem.allocate(sizeof(lgts_shellcode));

	DWORD dw_line_through_smoke = c_offsets::signatures::dw_line_through_smoke;

	DWORD param_startAddr = (DWORD)p_shellcode + LGTS_SHELLCODE_SIZE;
	DWORD param_endAddr = (DWORD)param_startAddr + sizeof(s_vec3);
	DWORD dw_return = param_endAddr + sizeof(s_vec3);

	DWORD param_end_y = (DWORD)param_endAddr + 4;
	DWORD param_end_z = (DWORD)param_endAddr + 8;

	DWORD param_start_y = (DWORD)param_startAddr + 4;
	DWORD param_start_z = (DWORD)param_startAddr + 8;

	// write our end vector and data member positions in the asm
	memcpy(lgts_shellcode + 0xA, &param_endAddr, sizeof(DWORD));
	memcpy(lgts_shellcode + 0x12, &param_end_y, sizeof(DWORD));
	memcpy(lgts_shellcode + 0x1B, &param_end_z, sizeof(DWORD));

	// write our start vector and data member positions in the asm
	memcpy(lgts_shellcode + 0x28, &param_startAddr, sizeof(DWORD));
	memcpy(lgts_shellcode + 0x30, &param_start_y, sizeof(DWORD));
	memcpy(lgts_shellcode + 0x38, &param_start_z, sizeof(DWORD));

	// write the addr of the function
	memcpy(lgts_shellcode + 0x40, &dw_line_through_smoke, sizeof(DWORD));

	// write the addr of where we store the return value
	memcpy(lgts_shellcode + 0x47, &dw_return, sizeof(DWORD));

	// plug in our passed parameters
	memcpy(lgts_shellcode + 0x50, &start, sizeof(s_vec3));
	memcpy(lgts_shellcode + 0x5C, &end, sizeof(s_vec3));


	// Write our shellcode
	g_mem.write((DWORD)p_shellcode, lgts_shellcode);

	// Run the shellcode
	g_mem.createThread((uintptr_t)p_shellcode);

	// Get our return value
	bool b_return = g_mem.read<bool>(dw_return);

	// Free our allocated memory
	g_mem.free(p_shellcode);

	return b_return;
}