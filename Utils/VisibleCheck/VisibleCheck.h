#pragma once

#include <Windows.h>
#include <vector>

#include "../Memory/Memory.hpp"
#include "../Memory/Modules.hpp"
#include "../Offsets/Offsets.hpp"
#include "../VirtualFunction/VirtualFunction.hpp"

#include "../../SDK/Utils/Vector.hpp"
#include "../../SDK/Utils/IEngineTrace.hpp"
#include "../../SDK/Utils/CGameTrace.hpp"
#include "../../SDK/Utils/CUserCmd.hpp"

#define dwCreateMoveVars 0x00123456

class CVisibleCheck {
public:
	struct IVisible {
		bool player[64];
		bool playerBones[64][80];
	};
	struct ICreateMoveVars {
		//offsets
		DWORD dwTraceLine;
		DWORD dwClientState;
		DWORD dwEntityList;
		DWORD dwLocalPlayer;
		DWORD m_nDeltaTick;
		DWORD m_dwBoneMatrix;
		DWORD m_vecViewOffset;
		DWORD m_vecOrigin;
		DWORD m_lifeState;
		DWORD m_iTeamNum;
		DWORD m_iHealth;
		DWORD m_bDormant;

		//needable variables
		int all_bones[17];

		//local variables
		Vec3 localOrigin;
		Vec3 localViewOffset;
		Vec3 localEyePosition;
		Vec3 enemyBonePosition;
		float min_fraction;

		//output trace_t struct
		CGameTrace* traceOutput;

		//player's visible struct
		IVisible* visibleStruct;
	};

private:
	bool hooked;
	DWORD dwVisibleStruct;
	IVisible visibleStruct;
	LPVOID allocatedAddressTraceOutput;
	LPVOID allocatedAddressVisibleStruct;
	LPVOID allocatedAddressHookCode;

public:
	CVisibleCheck();
	~CVisibleCheck();

	bool 	init();
	bool 	updateVisibleStruct();
	bool 	isVisible(int);
	bool 	isVisible(int, int);

//lineGoesThroughSmoke
private:
	BYTE LGTSShellcode[105] = {
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
	bool lineGoesThroughSmoke(Vec3, Vec3);
};

extern CVisibleCheck visibleCheck;