#include "BaseCombatWeapon.hpp"

BaseCombatWeapon::BaseCombatWeapon(int _dwBase) {
	this->dwBase = _dwBase;
}
BaseCombatWeapon::BaseCombatWeapon(BaseEntity entity){
	this->dwBase = entity.dwBase;
}

VAR_R_DEF(int, m_iClip1, BaseCombatWeapon, get(), netvars)
VAR_R_DEF(float, m_flNextPrimaryAttack, BaseCombatWeapon, get(), netvars)
VAR_R_DEF(bool, m_bInReload, BaseCombatWeapon, get(), netvars)
VAR_R_DEF(int, m_OriginalOwnerXuidLow, BaseCombatWeapon, get(), netvars)
VAR_W_DEF(std::string, m_szCustomName, BaseCombatWeapon, get(), netvars)
VAR_W_DEF(int, m_nFallbackSeed, BaseCombatWeapon, get(), netvars)
VAR_W_DEF(int, m_nFallbackStatTrak, BaseCombatWeapon, get(), netvars)
VAR_W_DEF(int, m_iAccountID, BaseCombatWeapon, get(), netvars)
VAR_RW_DEF(int, m_iItemIDHigh, BaseCombatWeapon, get(), netvars)
VAR_RW_DEF(unsigned long, m_iViewModelIndex, BaseCombatWeapon, get(), netvars)
VAR_RW_DEF(unsigned long, m_nModelIndex, BaseCombatWeapon, get(), netvars)
VAR_W_DEF(EntityQuality, m_iEntityQuality, BaseCombatWeapon, get(), netvars)
EntityQuality BaseCombatWeapon::m_iEntityQuality() {
	auto entityQuality = mem.read<int>(get() + Offsets::netvars::m_iEntityQuality);
	if (entityQuality < 0 || entityQuality > 12) {
		return EntityQuality::Invalid;
	}
	return (EntityQuality)entityQuality;
}
VAR_RW_DEF(float, m_flFallbackWear, BaseCombatWeapon, get(), netvars)
VAR_RW_DEF(int, m_hWeaponWorldModel, BaseCombatWeapon, get(), netvars)
ItemDefinitionIndex BaseCombatWeapon::m_iItemDefinitionIndex() {
	auto itemDI = mem.read<short>(get() + Offsets::netvars::m_iItemDefinitionIndex);
	//std::cout << "BaseCombatWeapon::m_iItemDefinitionIndex(): " << itemDI << std::endl;
	if (itemDI <= 0) {
		return ItemDefinitionIndex::Invalid;
	}
	return (ItemDefinitionIndex)itemDI;
}
VAR_W_DEF(ItemDefinitionIndex, m_iItemDefinitionIndex, BaseCombatWeapon, get(), netvars)
VAR_RW_DEF(unsigned long, m_nFallbackPaintKit, BaseCombatWeapon, get(), netvars)

int BaseCombatWeapon::get() {
	return this->dwBase;
}
bool BaseCombatWeapon::isPistol() {
	return ItemDefinition::isPistol(m_iItemDefinitionIndex());
}
bool BaseCombatWeapon::isSMG() {
	return ItemDefinition::isSMG(m_iItemDefinitionIndex());
}
bool BaseCombatWeapon::isHeavy() {
	return ItemDefinition::isHeavy(m_iItemDefinitionIndex());
}
bool BaseCombatWeapon::isShotgun() {
	return ItemDefinition::isShotgun(m_iItemDefinitionIndex());
}
bool BaseCombatWeapon::isRifle() {
	return ItemDefinition::isRifle(m_iItemDefinitionIndex());
}
bool BaseCombatWeapon::isSnipers() {
	return ItemDefinition::isSnipers(m_iItemDefinitionIndex());
}
bool BaseCombatWeapon::isKnife() {
	return ItemDefinition::isKnife(m_iItemDefinitionIndex());
}
bool BaseCombatWeapon::isBomb() {
	auto itemDI = m_iItemDefinitionIndex();
	if (itemDI == ItemDefinitionIndex::ITEM_C4Explosive) {
		return true;
	}
	return false;
}
bool BaseCombatWeapon::isGrenade() {
	auto itemDI = m_iItemDefinitionIndex();
	if (
		itemDI == ItemDefinitionIndex::WEAPON_HEGrenade ||
		itemDI == ItemDefinitionIndex::WEAPON_Flashbang ||
		itemDI == ItemDefinitionIndex::WEAPON_Molotov ||
		itemDI == ItemDefinitionIndex::WEAPON_SmokeGrenade ||
		itemDI == ItemDefinitionIndex::WEAPON_IncendiaryGrenade ||
		itemDI == ItemDefinitionIndex::WEAPON_DecoyGrenade
		) {
		return true;
	}
	return false;
}
bool BaseCombatWeapon::isZeusX27() {
	auto itemDI = m_iItemDefinitionIndex();
	if (itemDI == ItemDefinitionIndex::WEAPON_Zeusx27) {
		return true;
	}
	return false;
}