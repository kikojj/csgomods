#pragma once

#include <vector>

#include "BaseEntity.hpp"
#include "BaseCombatWeapon.hpp"

#include "../Vars.hpp"

#include "../Utils/Vector.hpp"
#include "../Utils/TeamNum.hpp"
#include "../Utils/Skeleton.hpp"
#include "../Utils/LifeState.hpp"

#include "../../Utils/Memory/Memory.hpp"
#include "../../Utils/Memory/Modules.hpp"
#include "../../Utils/Offsets/Offsets.hpp"
#include "../../Utils/BspParser/BspParser.hpp"

class BasePlayer : public BaseEntity {
private:
public:
	BasePlayer();
	BasePlayer(int);
	BasePlayer(BaseEntity);

	/// <summary>get entity team</summary>
	/// <returns>SPECTATOR = 1, TERRORIST = 2, COUNTER_TERRORIST = 3</returns>
	VAR_R_DEC(TeamNum, m_iTeamNum)
	/// <summary> get entity health</summary>
	VAR_R_DEC(int, m_iHealth)
	/// <summary>get entity matrix of bones</summary>
	/// <returns>The matrix like: [Bone] [x] [y] [z]</returns>
	VAR_R_DEC(int, m_dwBoneMatrix)
	/// <summary>get bone positon</summary>
	VAR_R_P_DEC(Vector3, getBonePos, Skeleton)
	/// <summary>get entity position</summary>
	VAR_R_DEC(Vector3, m_vecOrigin)
	/// <summary>get entity eyes pos(must add this to m_vecOrigin to get real eyes pos)</summary>
	VAR_R_DEC(Vector3, m_vecViewOffset)
	/// <summary>get spotted by mask, that has struct like this 10001, in binary. Where 4 and 0 pos is '1'.
	/// It tells us which players with current ids(0 and 4) are spotted the enemy. And clientState->GetLocalPlayer() gets the id of localplayer</summary>
	VAR_R_DEC(int, m_bSpottedByMask)
	/// <summary>get if player is visible using a bsp parser</summary>
	VAR_R_P_DEC(bool, isBspVisibleFrom, Vector3)
	/// <summary>get spotted</summary>
	VAR_R_DEC(bool, m_bSpotted)
	/// <summary>m_bSpottedByMask by another entity ID</summary>
	VAR_R_P_DEC(bool, m_bSpottedByMask, int)
	/// <summary>get how many bullets did entity fired</summary>
	VAR_R_DEC(int, m_iShotsFired)
	/// <summary>get the shoting angle on screen's plane, only if shooting</summary>
	VAR_R_DEC(Vector2, m_viewPunchAngle)
	/// <summary>get active weapon</summary>
	VAR_R_DEC(int, m_hActiveWeapon)
	/// <summary>get flags state</summary>
	VAR_R_DEC(int, m_fFlags)
	VAR_R_DEC(bool, m_bIsDefusing)
	VAR_R_DEC(int, m_ArmorValue)
	VAR_R_DEC(int, m_iCompetitiveWins)
	VAR_R_DEC(bool, m_bHasDefuser)
	VAR_R_DEC(bool, m_bIsScoped)
	VAR_R_DEC(bool, m_bHasHelmet)
	VAR_R_DEC(int, m_nTickBase)
	VAR_R_DEC(LifeState, m_lifeState)
	VAR_R_DEC(float, m_flFlashDuration)
	VAR_R_DEC(float, m_flFlashAlpha)
	VAR_R_DEC(int, m_hViewModel)
	VAR_R_DEC(std::vector<int>, myWeapons)
	VAR_R_DEC(bool, m_bDormant)
	VAR_R_P_DEC(int, myWeaponByID, int)
	/// <summary>change rendering color of entity</summary>
	VAR_W_DEC(colorRGBA, m_clrRender)
	/// <summary>set entity spotted value</summary>
	VAR_W_DEC(bool, m_bSpotted)
	/// <summary>set new view ounch angle</summary>
	VAR_W_DEC(Vector2&, m_viewPunchAngle)
	/// <summary>get/set the shoting angle on screen's plane, only if shooting</summary>
	VAR_RW_DEC(Vector2, m_aimPunchAngle)
	VAR_RW_DEC(float, m_flFlashMaxAlpha)
	VAR_RW_DEC(int, m_iObserverMode)

	int get();
	void operator=(BasePlayer);
};