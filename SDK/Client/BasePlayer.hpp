#pragma once

#include <vector>

#include "../../Utils/Memory/Memory.hpp"
#include "../../Utils/Memory/Modules.hpp"
#include "../../Utils/Offsets/Offsets.hpp"
#include "../../Utils/BspParser/BspParser.hpp"

#include "../Utils/Vector.hpp"
#include "../Utils/TeamNum.hpp"
#include "../Utils/Skeleton.hpp"
#include "../Utils/LifeState.hpp"
#include "../Utils/ColorRGBA.hpp"
#include "../Utils/IPlayerInfo.hpp"
#include "../Engine/Engine.hpp"

#include "../Vars.hpp"

#include "BaseEntity.hpp"
#include "EntityList.hpp"

class BasePlayer : public BaseEntity {
//main methods
public:
	BasePlayer() {}
	BasePlayer(int _base) {
		this->base = _base;
	};
	BasePlayer(BaseEntity entity) {
		this->base = entity.get();
	}

	virtual int get() {
		return this->base;
	}

//props
public:
	PROP(bool,				m_bDormant,							get())
	PROP(bool,				m_bSpotted,							get())
	PROP(bool,				m_bHasDefuser,					get())
	PROP(bool,				m_bIsDefusing,					get())
	PROP(bool,				m_bIsScoped,						get())
	PROP(bool,				m_bHasHelmet,						get())

	PROP(int,					m_iHealth,							get())
	PROP(int,					m_ArmorValue,						get())
	PROP(int,					m_iTeamNum,							get())
	PROP(int,					m_dwBoneMatrix,					get())	//player matrix of bones: [Bone] [x] [y] [z]
	PROP(int,					m_hActiveWeapon,				get())
	PROP(int,					m_iShotsFired,					get())	//how many bullets did player fired
	PROP(int,					m_fFlags,								get())
	PROP(int,					m_iCompetitiveWins,			get())
	PROP(int,					m_hViewModel,						get())
	PROP(int,					m_iObserverMode,				get())
	PROP(int,					m_lifeState,						get())
	PROP(int,					m_bSpottedByMask,				get())
	PROP(int,					m_nTickBase,						get())
	PROP(int,					m_iAccount,							get())

	PROP(float,				m_flFlashDuration,			get())
	PROP(float,				m_flFlashAlpha,					get())
	PROP(float,				m_flFlashMaxAlpha,			get())

	PROP(Vec2,				m_viewPunchAngle,				get())
	PROP(Vec2,				m_aimPunchAngle,				get())	//shoting angle on screen's plane, only if shooting
	PROP(Vec3,				m_vecViewOffset,				get())	//player eyes pos offset(must add this to m_vecOrigin to get real eyes pos)

	PROP(RenderColor, m_clrRender,						get())

//methods
public:
	TeamNum teamNum() {
		auto team = m_iTeamNum();
		if (team <= int(TeamNum::Invalid) || team >= int(TeamNum::InvalidLast)) {
			return TeamNum::Invalid;
		};
		return TeamNum(team);
	}
	LifeState lifeState() {
		auto lifeState = m_lifeState();
		if (lifeState <= int(LifeState::Invalid)) {
			return LifeState::Invalid;
		}
		return LifeState(lifeState);
	}
	bool spottedByMask(int id) {
		return m_bSpottedByMask() & (1 << id);
	}
	Vector3 getBonePos(Skeleton bone) {
		auto bonePos = Vector3(mem.read<BoneVector>(m_dwBoneMatrix() + 0x30 * (int)bone + 0x0C));
		return bonePos;
	}
	void render(colorRGBA color) {
		RenderColor renderColor{ (BYTE)color.r, (BYTE)color.g, (BYTE)color.b, (BYTE)color.a };
		m_clrRender(renderColor);
	}
	int myWeaponByID(int id) {
		return mem.read<int>(get() + Offsets::netvars::m_hMyWeapons + id * 0x4);
	}
	std::vector<int> myWeapons() {
		std::vector<int> weapons;
		for (int i = 0; i < 8; i++) {
			int weaponID = myWeaponByID(i) & 0xfff;
			weapons.push_back(weaponID);
		}
		return weapons;
	}
	bool isBspVisibleFrom(Vector3 origin) {
		for (auto bone : ALL_BONES) {
			if (bsp_parser.is_visible(origin.toMatrix(), getBonePos(bone).toMatrix())) {
				return true;
			}
		}
		return false;
	}
	IPlayerInfo info() {
		auto items = mem.read<int>(mem.read<int>(engine.clientState->playerInfo() + 0x40) + 0xC);

		auto _info = mem.read<int>(items + 0x28 + EntityList::getEntityID(get()) * 0x34);
		auto info = mem.read<IPlayerInfo>(_info);

		return info;
	}
	int competitiveRanking() {
		auto playerResource = mem.read<int>(clientDll.dwBase + Offsets::signatures::dwPlayerResource);
		auto competitiveRanking = mem.read<int>(playerResource + Offsets::netvars::m_iCompetitiveRanking + (EntityList::getEntityID(get()) + 1) * 4);

		return competitiveRanking;
	}
	int competitiveWins() {
		auto playerResource = mem.read<int>(clientDll.dwBase + Offsets::signatures::dwPlayerResource);
		auto competitiveWins = mem.read<int>(playerResource + Offsets::netvars::m_iCompetitiveWins + (EntityList::getEntityID(get()) + 1) * 4);

		return competitiveWins;
	}
	int ping() {
		auto playerResource = mem.read<int>(clientDll.dwBase + Offsets::signatures::dwPlayerResource);
		auto ping = mem.read<int>(playerResource + Offsets::netvars::m_iPing + (EntityList::getEntityID(get()) + 1) * 4);

		return ping;
	}
	int kills() {
		auto playerResource = mem.read<int>(clientDll.dwBase + Offsets::signatures::dwPlayerResource);
		auto kills = mem.read<int>(playerResource + Offsets::netvars::m_iKills + (EntityList::getEntityID(get()) + 1) * 4);

		return kills;
	}
	int assists() {
		auto playerResource = mem.read<int>(clientDll.dwBase + Offsets::signatures::dwPlayerResource);
		auto assists = mem.read<int>(playerResource + Offsets::netvars::m_iAssists + (EntityList::getEntityID(get()) + 1) * 4);

		return assists;
	}
	int deaths() {
		auto playerResource = mem.read<int>(clientDll.dwBase + Offsets::signatures::dwPlayerResource);
		auto deaths = mem.read<int>(playerResource + Offsets::netvars::m_iDeaths + (EntityList::getEntityID(get()) + 1) * 4);

		return deaths;
	}
	int score() {
		auto playerResource = mem.read<int>(clientDll.dwBase + Offsets::signatures::dwPlayerResource);
		auto score = mem.read<int>(playerResource + Offsets::netvars::m_iScore + (EntityList::getEntityID(get()) + 1) * 4);

		return score;
	}
	int MVPs() {
		auto playerResource = mem.read<int>(clientDll.dwBase + Offsets::signatures::dwPlayerResource);
		auto MVPs = mem.read<int>(playerResource + Offsets::netvars::m_iMVPs + (EntityList::getEntityID(get()) + 1) * 4);

		return MVPs;
	}
	int clan() {
		auto playerResource = mem.read<int>(clientDll.dwBase + Offsets::signatures::dwPlayerResource);
		auto clan = mem.read<int>(playerResource + Offsets::netvars::m_szClan + (EntityList::getEntityID(get()) + 1) * 4);

		return clan;
	}
};