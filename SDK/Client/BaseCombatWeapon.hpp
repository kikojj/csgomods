#pragma once

#include <iostream>
#include <array>
#include <string>

#include "BaseEntity.hpp"

#include "../Vars.hpp"

#include "../Utils/ItemDefinitionIndex.hpp"
#include "../Utils/EntityQuality.hpp"

#include "../../Utils/Memory/Memory.hpp"
#include "../../Utils/Memory/Modules.hpp"
#include "../../Utils/Offsets/Offsets.hpp"

class BaseCombatWeapon : public BaseEntity {
public:
	BaseCombatWeapon(int);
	BaseCombatWeapon(BaseEntity);

	/// <summary>get current count of bullets in weapon</summary>
	VAR_R_DEC(int, m_iClip1)
	/// <summary>get next weapon attack in ticks</summary>
	VAR_R_DEC(float, m_flNextPrimaryAttack)
	/// <summary>check if weapon in reload</summary>
	VAR_R_DEC(bool, m_bInReload)
	VAR_R_DEC(int, m_OriginalOwnerXuidLow)
	VAR_W_DEC(std::string, m_szCustomName)
	VAR_W_DEC(int, m_nFallbackSeed)
	VAR_W_DEC(int, m_nFallbackStatTrak)
	VAR_W_DEC(int, m_iAccountID)
	VAR_RW_DEC(int, m_iItemIDHigh)
	VAR_RW_DEC(unsigned long, m_iViewModelIndex)
	VAR_RW_DEC(unsigned long, m_nModelIndex)
	VAR_RW_DEC(EntityQuality, m_iEntityQuality)
	VAR_RW_DEC(float, m_flFallbackWear)
	VAR_RW_DEC(int, m_hWeaponWorldModel)
	VAR_RW_DEC(ItemDefinitionIndex, m_iItemDefinitionIndex)
	VAR_RW_DEC(unsigned long, m_nFallbackPaintKit)

	int get();
	/// <summary>check if weapon is pistol</summary>
	bool isPistol();
	/// <summary>check if weapon is SMG</summary>
	bool isSMG();
	/// <summary>check if weapon is heavy machine gun</summary>
	bool isHeavy();
	/// <summary>check if weapon is heavy shotgun</summary>
	bool isShotgun();
	/// <summary>check if weapon is rifle machine gun</summary>
	bool isRifle();
	/// <summary>check if weapon is rifle sniper</summary>
	bool isSnipers();
	/// <summary>check if weapon is knife</summary>
	bool isKnife();
	/// <summary>check if weapon is bomb</summary>
	bool isBomb();
	/// <summary>check if weapon is grenade</summary>
	bool isGrenade();
	/// <summary>check if weapon is zeusX27</summary>
	bool isZeusX27();
};