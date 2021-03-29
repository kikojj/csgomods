#pragma once

#include <iostream>
#include <array>
#include <string>

#include "../../Utils/Memory/Memory.hpp"
#include "../../Utils/Memory/Modules.hpp"
#include "../../Utils/Offsets/Offsets.hpp"

#include "../Utils/ItemDefinitionIndex.hpp"
#include "../Utils/EntityQuality.hpp"

#include "../Vars.hpp"

#include "BaseEntity.hpp"

class BaseWeapon : public BaseEntity {
//main methods
public:
	BaseWeapon(int _base) {
		this->base = _base;
	}
	BaseWeapon(BaseEntity entity) {
		this->base = entity.get();
	}

//props
public:
	PROP(bool,					m_bInReload,						get())

	PROP(short,					m_iItemDefinitionIndex, get())
	PROP(int,						m_iClip1,								get())	//the number of remaining bullets in the clip
	PROP(int,						m_OriginalOwnerXuidLow, get())
	PROP(int,						m_nFallbackSeed,				get())
	PROP(int,						m_nFallbackStatTrak,		get())
	PROP(int,						m_iAccountID,						get())
	PROP(int,						m_iItemIDHigh,					get())
	PROP(int,						m_hWeaponWorldModel,		get())
	PROP(int,						m_iEntityQuality,				get())
	PROP(unsigned long, m_iViewModelIndex,			get())
	PROP(unsigned long, m_nModelIndex,					get())
	PROP(unsigned long, m_nFallbackPaintKit,		get())

	PROP(float,					m_flFallbackWear,				get())
	PROP(float,					m_flNextPrimaryAttack,	get())	//next weapon attack in ticks

	PROP(std::string,		m_szCustomName,					get())

//methods
public:
	EntityQuality entityQuality() {
		auto entityQuality = m_iEntityQuality();
		if (entityQuality <= int(EntityQuality::Invalid) || entityQuality >= int(EntityQuality::InvalidLast)) {
			return EntityQuality::Invalid;
		}

		return (EntityQuality)entityQuality;
	}
	void entityQuality(EntityQuality value) {
		m_iEntityQuality((int)value);
	}
	ItemDefinitionIndex itemDI() {
		auto itemDI = m_iItemDefinitionIndex();
		if (itemDI <= (int)ItemDefinitionIndex::Invalid || itemDI >= (int)ItemDefinitionIndex::InvalidLast) {
			return ItemDefinitionIndex::Invalid;
		}

		return (ItemDefinitionIndex)itemDI;
	}
	void itemDI(ItemDefinitionIndex value) {
		m_iItemDefinitionIndex((int)value);
	}

	bool isPistol() {
		return ItemDefinition::isPistol(itemDI());
	}
	bool isSMG() {
		return ItemDefinition::isSMG(itemDI());
	}
	bool isHeavy() {
		return ItemDefinition::isHeavy(itemDI());
	}
	bool isShotgun() {
		return ItemDefinition::isShotgun(itemDI());
	}
	bool isRifle() {
		return ItemDefinition::isRifle(itemDI());
	}
	bool isSnipers() {
		return ItemDefinition::isSnipers(itemDI());
	}
	bool isKnife() {
		return ItemDefinition::isKnife(itemDI());
	}
	bool isBomb() {
		return ItemDefinition::isBomb(itemDI());
	}
	bool isGrenade() {
		return ItemDefinition::isGrenade(itemDI());
	}
	bool isZeusX27() {
		return ItemDefinition::isZeusX27(itemDI());
	}
};