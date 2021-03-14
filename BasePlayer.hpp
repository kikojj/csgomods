#pragma once

#include <vector>

#include "Memory.hpp"
#include "Modules.hpp"
#include "Offsets.hpp"

#include "BaseEntity.hpp"
#include "BspParser.hpp"

#include "Vector.hpp"
#include "TeamNum.hpp"
#include "Skeleton.hpp"
#include "LifeState.hpp"
#include "BaseCombatWeapon.hpp"

class BasePlayer : public BaseEntity {
private:
public:
	BasePlayer();
	BasePlayer(BaseEntity);
	BasePlayer(int);

	void operator=(BasePlayer);

	int get();

	/// <summary>
	/// get entity team
	/// </summary>
	/// <returns>TeamNum: SPECTATOR = 1, TERRORIST = 2, COUNTER_TERRORIST = 3</returns>
	TeamNum m_iTeamNum();

	/// <summary>
	/// get entity health
	/// </summary>
	/// <returns>int value of health</returns>
	int m_iHealth();

	/// <summary>
	/// get entity matrix of bones
	/// </summary>
	/// <returns>The metrix like: [Bone] [x] [y] [z]</returns>
	int m_dwBoneMatrix();

	/// <summary>
	/// get bone positon
	/// </summary>
	/// <param name="bone">Skeleton</param>
	/// <returns>Vector3</returns>
	Vector3 getBonePos(Skeleton);

	/// <summary>
	/// get entity position
	/// </summary>
	/// <returns>Vec3(x,y,z)</returns>
	Vector3 m_vecOrigin();

	/// <summary>
	/// get entity eyes pos(must add this to m_vecOrigin to get real eyes pos)
	/// </summary>
	/// <returns>Vec3(x,y,z)</returns>
	Vector3 m_vecViewOffset();

	/// <summary>
	/// get spotted by mask, that has struct like this 10001, in binary.
	/// Where 4 and 0 pos is '1'. It tells us which players with current ids(0 and 4) are spotted the enemy.
	/// And clientState->GetLocalPlayer() gets the id of localplayer
	/// </summary>
	/// <returns>Int</returns>
	int m_bSpottedByMask();

	/// <summary>
	/// get if player is visible using a bsp parser
	/// </summary>
	/// <returns></returns>
	bool isBspVisibleFrom(Vector3);

	/// <summary>
	///get spotted
	/// </summary>
	/// <returns>True if spotted</returns>
	bool m_bSpotted();

	/// <summary>
	/// set entity spotted value
	/// </summary>
	/// <param name="value">Bool</param>
	void m_bSpotted(bool);

	/// <summary>
	///m_bSpottedByMask by another entity ID
	/// </summary>
	/// <returns>True if spooted</returns>
	bool m_bSpottedByMask(int);

	/// <summary>
	/// get how many bullets did entity fire
	/// </summary>
	/// <returns>Number of bullets</returns>
	int m_iShotsFired();

	/// <summary>
	/// get the shoting angle on screen's plane, only if shooting
	/// </summary>
	/// <returns>Vec2(x,y)</returns>
	Vector2 m_aimPunchAngle();

	/// <summary>
	/// set new aim punch angle
	/// </summary>
	/// <param name="ang">Vec2(x,y)</param>
	void m_aimPunchAngle(Vector2& ang);

	/// <summary>
	/// get the shoting angle on screen's plane, only if shooting
	/// </summary>
	/// <returns>Vec2(x,y)</returns>
	Vector2 m_viewPunchAngle();

	/// <summary>
	/// set new view ounch angle
	/// </summary>
	/// <param name="ang">Vec2(x,y)</param>
	void m_viewPunchAngle(Vector2& ang);

	/// <summary>
	/// get active weapon
	/// </summary>
	/// <returns>Int</returns>
	int m_hActiveWeapon();

	/// <summary>
	/// get flags state
	/// </summary>
	/// <returns>Value that might be manipulated with FlagsState class methods</returns>
	int m_fFlags();

	/// <summary>
	/// change rendering color of entity
	/// </summary>
	/// <param name="color">RGBA color</param>
	void m_clrRender(colorRGBA);

	bool m_bIsDefusing();

	int m_ArmorValue();

	int m_iCompetitiveWins();

	bool m_bHasDefuser();

	bool m_bIsScoped();

	bool m_bHasHelmet();

	int m_nTickBase();

	LifeState m_lifeState();

	float m_flFlashMaxAlpha();

	void m_flFlashMaxAlpha(float);

	float m_flFlashDuration();

	float m_flFlashAlpha();

	int m_hViewModel();

	std::vector<int> myWeapons();

	int myWeaponByID(int);

	int m_iObserverMode();

	void m_iObserverMode(int);

	bool m_bDormant();
};