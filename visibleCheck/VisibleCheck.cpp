#include "VisibleCheck.h"

#pragma optimize("", off)
typedef int(__fastcall* UTIL_TraceLine_t)(const Vec3&, const Vec3&, unsigned int fMask, const DWORD basePlayer, int, CGameTrace* trace);
bool WINAPI hkCreateMove(float flInputSampleTime, CUserCmd* pCmd) {
	// hkCreateMove + 0x9 = pointer to Vars; 
	CVisibleCheck::ICreateMoveVars* Vars = (CVisibleCheck::ICreateMoveVars*)0x00123456; // Initialize in InitCreateMoveHook()
	DWORD localPlayer = *(DWORD*)(Vars->dwLocalPlayer);
	bool isInGame = *(int*)(Vars->dwClientState + 0x108) == 6;
	bool deltaTick = *(int*)(Vars->dwClientState + Vars->m_nDeltaTick);
	UTIL_TraceLine_t TraceLine = (UTIL_TraceLine_t)Vars->dwTraceLine;

	if (!pCmd->command_number || !isInGame || !localPlayer || deltaTick == -1) {
		return true;
	}

	bool localIsAlive = !*(bool*)(localPlayer + Vars->m_lifeState);
	if (!localIsAlive) {
		return true;
	}

	Vars->localOrigin = *(Vec3*)(localPlayer + Vars->m_vecOrigin);
	Vars->localViewOffset = *(Vec3*)(localPlayer + Vars->m_vecViewOffset);
	Vars->localEyePosition.x = Vars->localOrigin.x + Vars->localViewOffset.x;
	Vars->localEyePosition.y = Vars->localOrigin.y + Vars->localViewOffset.y;
	Vars->localEyePosition.z = Vars->localOrigin.z + Vars->localViewOffset.z;

	for (int i = 0; i < 64; i++) {
		Vars->visibleStruct->player[i] = false;

		DWORD pEntity = *(DWORD*)(Vars->dwEntityList + i * 0x10);

		if (!pEntity || pEntity == localPlayer) {
			continue;
		}

		bool lifeState = *(bool*)(pEntity + Vars->m_lifeState);
		bool dormant = *(bool*)(pEntity + Vars->m_bDormant);
		int  health = *(int*)(pEntity + Vars->m_iHealth);

		if (lifeState || dormant || health <= 0) {
			continue;
		}

		// Get Enemy Head Position
		DWORD boneMatrix = *(DWORD*)(pEntity + Vars->m_dwBoneMatrix);
		if (!boneMatrix) {
			continue;
		}

		bool isVisible = false;
		for (int j = 0; j < 17; j++) {
			auto bone = Vars->all_bones[j];

			Vars->enemyBonePosition.x = *(float*)(boneMatrix + 0x30 * bone + 0x0C);
			Vars->enemyBonePosition.y = *(float*)(boneMatrix + 0x30 * bone + 0x1C);
			Vars->enemyBonePosition.z = *(float*)(boneMatrix + 0x30 * bone + 0x2C);

			// Visible check
			TraceLine(Vars->localEyePosition, Vars->enemyBonePosition, MASK_SHOT | CONTENTS_GRATE, localPlayer, 0, Vars->traceOutput);

			if (Vars->traceOutput->fraction > Vars->min_fraction || Vars->traceOutput->hit_entity == pEntity) {
				isVisible = true;
				Vars->visibleStruct->playerBones[i][bone] = true;
			}
			else {
				Vars->visibleStruct->playerBones[i][bone] = false;
			}
		}
		Vars->visibleStruct->player[i] = isVisible;
	}

	return true;
}
DWORD WINAPI hkCreateMoveEnd(){ return 0; }
#pragma optimize("", on)

CVisibleCheck::CVisibleCheck(){
	hooked = false;
	
	for (int i = 0; i < 64; i++){
		visibleStruct.player[i] = false;

		for (int j = 0; j < 80; j++) {
			visibleStruct.playerBones[i][j] = false;
		}
	}
}
	
bool CVisibleCheck::updateVisibleStruct(){
	if (!hooked) {
		return false;
	}

	if (!dwVisibleStruct) {
		return false;
	}

	if (!ReadProcessMemory(mem._process, (LPVOID)dwVisibleStruct, &visibleStruct, sizeof(IVisible), NULL)) {
		return false;
	}
	
	return true;
}

bool CVisibleCheck::isVisible(int entityId){
	if (!hooked) {
		return false;
	}

	if (!dwVisibleStruct) {
		return false;
	}

	if (entityId >= 64) {
		return false;
	}
	
	return visibleStruct.player[entityId];
}

bool CVisibleCheck::isVisible(int entityId, int bone) {
	if (!hooked) {
		return false;
	}

	if (!dwVisibleStruct) {
		return false;
	}

	if (entityId >= 64) {
		return false;
	}

	if (bone >= 80) {
		return false;
	}

	return visibleStruct.playerBones[entityId][bone];
}

bool CVisibleCheck::init(){
	if (hooked) {
		return true;
	}

	DWORD dwClientMode = mem.Read<DWORD>(Offsets::signatures::dwClientMode);
				dwClientMode = mem.Read<DWORD>(dwClientMode);
	DWORD dwTraceLine = Offsets::signatures::dwTraceLine;
	DWORD dwLocalPlayer = clientDll.dwBase + Offsets::signatures::dwLocalPlayer;
	DWORD dwEntityList = clientDll.dwBase + Offsets::signatures::dwEntityList;
	DWORD dwClientState = mem.Read<DWORD>(engineDll.dwBase + Offsets::signatures::dwClientState);
	DWORD m_nDeltaTick = mem.Read<DWORD>(engineDll.dwBase + Offsets::signatures::clientstate_delta_ticks);

	DWORD m_dwBoneMatrix = Offsets::netvars::m_dwBoneMatrix;
	DWORD m_vecViewOffset = Offsets::netvars::m_vecViewOffset;
	DWORD m_vecOrigin = Offsets::netvars::m_vecOrigin;
	DWORD m_lifeState = Offsets::netvars::m_lifeState;
	DWORD m_iTeamNum = Offsets::netvars::m_iTeamNum;
	DWORD m_iHealth = Offsets::netvars::m_iHealth;
	DWORD m_bDormant = Offsets::netvars::m_bDormant;
	
	// Check offsets
	if (!dwClientMode || !dwTraceLine || !dwLocalPlayer || !dwEntityList || !dwClientState || !m_nDeltaTick) {
		return false;
	}
	if (!m_dwBoneMatrix || !m_vecViewOffset || !m_vecOrigin || !m_lifeState || !m_iTeamNum || !m_iHealth || !m_bDormant) {
		return false;
	}
	
	// Set CreateMove local Vars
	ICreateMoveVars hkCreateMoveVars;
	hkCreateMoveVars.dwClientState 		= dwClientState;
	hkCreateMoveVars.dwEntityList 		= dwEntityList;
	hkCreateMoveVars.dwLocalPlayer 		= dwLocalPlayer;
	hkCreateMoveVars.m_nDeltaTick 		= m_nDeltaTick;
	hkCreateMoveVars.m_dwBoneMatrix 	= m_dwBoneMatrix;
	hkCreateMoveVars.m_vecViewOffset 	= m_vecViewOffset;
	hkCreateMoveVars.m_vecOrigin 			= m_vecOrigin;
	hkCreateMoveVars.m_lifeState 			= m_lifeState;
	hkCreateMoveVars.m_iTeamNum 			= m_iTeamNum;
	hkCreateMoveVars.m_iHealth 				= m_iHealth;
	hkCreateMoveVars.m_bDormant 			= m_bDormant;
	hkCreateMoveVars.dwTraceLine 			= dwTraceLine;
	hkCreateMoveVars.min_fraction			= 0.97f;
	hkCreateMoveVars.all_bones[0] = 3;
	hkCreateMoveVars.all_bones[1] = 4;
	hkCreateMoveVars.all_bones[2] = 6;
	hkCreateMoveVars.all_bones[3] = 7;
	hkCreateMoveVars.all_bones[4] = 8;
	hkCreateMoveVars.all_bones[5] = 11;
	hkCreateMoveVars.all_bones[6] = 12;
	hkCreateMoveVars.all_bones[7] = 13;
	hkCreateMoveVars.all_bones[8] = 41;
	hkCreateMoveVars.all_bones[9] = 42;
	hkCreateMoveVars.all_bones[10] = 43;
	hkCreateMoveVars.all_bones[11] = 70;
	hkCreateMoveVars.all_bones[12] = 71;
	hkCreateMoveVars.all_bones[13] = 72;
	hkCreateMoveVars.all_bones[14] = 77;
	hkCreateMoveVars.all_bones[15] = 78;
	hkCreateMoveVars.all_bones[16] = 79;
	
	// Allocate memory for result TraceLine function
	hkCreateMoveVars.traceOutput = (CGameTrace*)VirtualAllocEx(mem._process, NULL, 4096, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	
	// Allocate memory for visibleStruct
	hkCreateMoveVars.visibleStruct = (IVisible*)VirtualAllocEx(mem._process, NULL, sizeof(IVisible), MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	
	// Allocate memory for Hook
	LPVOID hookCodeAddress = VirtualAllocEx(mem._process, NULL, 4096, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
		
	if (!hkCreateMoveVars.traceOutput || !hkCreateMoveVars.visibleStruct || !(DWORD)hookCodeAddress)
		return false;
	
	// Write hkCreateMove function in to CSGO
	if (!WriteProcessMemory(mem._process, hookCodeAddress, hkCreateMove, (DWORD)hkCreateMoveEnd - (DWORD)hkCreateMove, NULL))
		return false;
	
	// Write hkCreateMoveVars(Local Variables for CreateMove hook)
	DWORD dw_hkCreateMoveVars = (DWORD)hookCodeAddress + (DWORD)hkCreateMoveEnd - (DWORD)hkCreateMove;
	if (!WriteProcessMemory(mem._process, (LPVOID)dw_hkCreateMoveVars, &hkCreateMoveVars, sizeof(ICreateMoveVars), NULL))
		return false;
	
	// Set pointer to hkCreateMoveVars
	if (!WriteProcessMemory(mem._process, (LPVOID)((DWORD)hookCodeAddress + 0x9), &dw_hkCreateMoveVars, sizeof(DWORD), NULL))
		return false;
		
	hook(dwClientMode, 24, (DWORD)hookCodeAddress);
	
	dwVisibleStruct = (DWORD)hkCreateMoveVars.visibleStruct;
	hooked = true;

	std::cout << "[VisibleCheck]: Hooked." << std::endl;

	return hooked;
}

DWORD CVisibleCheck::getVFunc(DWORD inst, int Index){
	DWORD table;
	ReadProcessMemory(mem._process, (LPVOID)inst, &table, sizeof(DWORD), NULL);
	DWORD func = table + sizeof(DWORD) * Index;
	return func;
}

void CVisibleCheck::hook(DWORD Instance, int Index, DWORD HookFunc){
	uintptr_t VFunc = getVFunc(Instance, Index);
	DWORD dwProtection;
	VirtualProtectEx(mem._process, (LPVOID)VFunc, sizeof(DWORD), PAGE_EXECUTE_READWRITE, &dwProtection);
	WriteProcessMemory(mem._process, (LPVOID)VFunc, &HookFunc, sizeof(DWORD), NULL);
	VirtualProtectEx(mem._process, (LPVOID)VFunc, sizeof(DWORD), dwProtection, &dwProtection);
}