#pragma once

#include <iostream>
#include <array>
#include <string>

#include "Memory.hpp"
#include "Modules.hpp"
#include "Offsets.hpp"
#include "BaseEntity.hpp"

#include "ItemDefinitionIndex.hpp"
#include "EntityQuality.hpp"

class BaseCombatWeapon : public BaseEntity {
private:
public:
	BaseCombatWeapon(int);
	BaseCombatWeapon(BaseEntity);

	int get();

	/// <summary>
	/// get weapon item ID
	/// </summary>
	/// <returns>Item ID</returns>
	ItemDefinitionIndex m_iItemDefinitionIndex();

	void m_iItemDefinitionIndex(ItemDefinitionIndex);

	/// <summary>
	/// get current count of bullets in weapon
	/// </summary>
	/// <returns>Count of bullets</returns>
	int m_iClip1();

	/// <summary>
	/// get next weapon attack in ticks
	/// </summary>
	/// <returns>ticks</returns>
	float m_flNextPrimaryAttack();

	/// <summary>
	/// check if weapon in reload
	/// </summary>
	/// <returns>True if reload</returns>
	bool m_bInReload();

	/// <summary>
	/// check if weapon is pistol
	/// </summary>
	/// <returns>True if pistol</returns>
	bool isPistol();

	/// <summary>
	/// check if weapon is SMG
	/// </summary>
	/// <returns>True if SMG</returns>
	bool isSMG();

	/// <summary>
	/// check if weapon is heavy machine gun
	/// </summary>
	/// <returns>True if heavy machine gun</returns>
	bool isHeavy();

	/// <summary>
	/// check if weapon is heavy shotgun
	/// </summary>
	/// <returns>True if heavy shotgun</returns>
	bool isShotgun();

	/// <summary>
	/// check if weapon is rifle machine gun
	/// </summary>
	/// <returns>True if rifle machine gun</returns>
	bool isRifle();

	/// <summary>
	/// check if weapon is rifle sniper
	/// </summary>
	/// <returns>True if rifle sniper</returns>
	bool isSnipers();

	/// <summary>
	/// check if weapon is knife
	/// </summary>
	/// <returns>True if knife</returns>
	bool isKnife();

	/// <summary>
	/// check if weapon is bomb
	/// </summary>
	/// <returns>True if bomb</returns>
	bool isBomb();

	/// <summary>
	/// check if weapon is grenade
	/// </summary>
	/// <returns>True if grenade</returns>
	bool isGrenade();

	bool isZeusX27();

	unsigned long m_nFallbackPaintKit();

	void m_nFallbackPaintKit(unsigned long);

	int m_iItemIDHigh();

	void m_iItemIDHigh(int);

	unsigned long m_iViewModelIndex();

	void m_iViewModelIndex(unsigned long);

	unsigned long m_nModelIndex();

	void m_nModelIndex(unsigned long);

	EntityQuality m_iEntityQuality();

	void m_iEntityQuality(EntityQuality);

	float m_flFallbackWear();

	void m_flFallbackWear(float);

	void m_nModelIndex(int);

	int m_hWeaponWorldModel();

	void m_hWeaponWorldModel(int);

	void m_szCustomName(std::string);

	void m_nFallbackSeed(int);

	void m_nFallbackStatTrak(int);

	 int m_OriginalOwnerXuidLow();

	 void m_iAccountID(int);
};