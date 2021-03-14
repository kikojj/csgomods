#pragma once

#include <Windows.h>
#include <vector>

#include "../Memory.hpp"
#include "../Modules.hpp"
#include "../Offsets.hpp"

#include "../Vector.hpp"
#include "../IEngineTrace.hpp"
#include "../CGameTrace.hpp"
#include "../CUserCmd.hpp"

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

	DWORD getVFunc(DWORD, int);
	void hook(DWORD, int, DWORD);

public:
	CVisibleCheck();

	bool 	init();
	bool 	updateVisibleStruct();
	bool 	isVisible(int);
	bool 	isVisible(int, int);
};

extern CVisibleCheck visibleCheck;