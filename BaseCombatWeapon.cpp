#include "BaseCombatWeapon.hpp"

BaseCombatWeapon::BaseCombatWeapon(int _dwBase) {
	this->dwBase = _dwBase;
}

BaseCombatWeapon::BaseCombatWeapon(BaseEntity entity){
	this->dwBase = entity.dwBase;
}

int BaseCombatWeapon::get(){
	return this->dwBase;
}
;

ItemDefinitionIndex BaseCombatWeapon::m_iItemDefinitionIndex() {
	auto itemDI = mem.Read<short>(get() + Offsets::netvars::m_iItemDefinitionIndex);
	//std::cout << "BaseCombatWeapon::m_iItemDefinitionIndex(): " << itemDI << std::endl;
	if (itemDI <= 0) {
		return INVALID_ITEM_DI;
	}
	return (ItemDefinitionIndex)itemDI;
}

void BaseCombatWeapon::m_iItemDefinitionIndex(ItemDefinitionIndex v){
	mem.Write(get() + Offsets::netvars::m_iItemDefinitionIndex, v);
}

int BaseCombatWeapon::m_iClip1(){
	auto clip = mem.Read<int>(get() + Offsets::netvars::m_iClip1);
	//std::cout << "BaseCombatWeapon::m_iClip1(): " << clip << std::endl;
	return clip;
}

float BaseCombatWeapon::m_flNextPrimaryAttack(){
	auto nextPrimaryAttack = mem.Read<float>(get() + Offsets::netvars::m_flNextPrimaryAttack);
	//std::cout << "BaseCombatWeapon::m_flNextPrimaryAttack(): " << nextPrimaryAttack << std::endl;
	return nextPrimaryAttack;
}

bool BaseCombatWeapon::m_bInReload(){
	auto inReload = mem.Read<bool>(get() + Offsets::netvars::m_bInReload);
	//std::cout << "BaseCombatWeapon::m_bInReload(): " << inReload << std::endl;
	return inReload;
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

bool BaseCombatWeapon::isKnife(){
	return ItemDefinition::isKnife(m_iItemDefinitionIndex());
}

bool BaseCombatWeapon::isBomb(){
	auto itemDI = m_iItemDefinitionIndex();
	if (itemDI == ITEM_C4Explosive) {
		return true;
	}
	return false;
}

bool BaseCombatWeapon::isGrenade(){
	auto itemDI = m_iItemDefinitionIndex();
	if (
		itemDI == WEAPON_HEGrenade ||
		itemDI == WEAPON_Flashbang ||
		itemDI == WEAPON_Molotov ||
		itemDI == WEAPON_SmokeGrenade ||
		itemDI == WEAPON_IncendiaryGrenade ||
		itemDI == WEAPON_DecoyGrenade
		) {
		return true;
	}
	return false;
}

bool BaseCombatWeapon::isZeusX27(){
	auto itemDI = m_iItemDefinitionIndex();
	if (itemDI == WEAPON_Zeusx27) {
		return true;
	}
	return false;
}

unsigned long BaseCombatWeapon::m_nFallbackPaintKit(){
	return mem.Read<unsigned long>(get() + Offsets::netvars::m_nFallbackPaintKit);
}

void BaseCombatWeapon::m_nFallbackPaintKit(unsigned long v){
	mem.Write(get() + Offsets::netvars::m_nFallbackPaintKit, v);
}

int BaseCombatWeapon::m_iItemIDHigh(){
	return mem.Read<int>(get() + Offsets::netvars::m_iItemIDHigh);
}

void BaseCombatWeapon::m_iItemIDHigh(int v){
	mem.Write(get() + Offsets::netvars::m_iItemIDHigh, v);
}

unsigned long BaseCombatWeapon::m_iViewModelIndex(){
	return mem.Read<unsigned long>(get() + Offsets::netvars::m_iViewModelIndex);
}

void BaseCombatWeapon::m_iViewModelIndex(unsigned long v){
	mem.Write(get() + Offsets::netvars::m_iViewModelIndex, v);
}

unsigned long BaseCombatWeapon::m_nModelIndex(){
	return mem.Read<unsigned long>(get() + Offsets::netvars::m_nModelIndex);
}

void BaseCombatWeapon::m_nModelIndex(unsigned long v){
	mem.Write(get() + Offsets::netvars::m_nModelIndex, v);
}

EntityQuality BaseCombatWeapon::m_iEntityQuality(){
	auto entityQuality = mem.Read<int>(get() + Offsets::netvars::m_iEntityQuality);
	if (entityQuality < 0 || entityQuality > 12) {
		return INVALID_QUALITY;
	}
	return (EntityQuality)entityQuality;
}

void BaseCombatWeapon::m_iEntityQuality(EntityQuality v){
	mem.Write(get() + Offsets::netvars::m_iEntityQuality, (int)v);
}

float BaseCombatWeapon::m_flFallbackWear(){
	return mem.Read<float>(get() + Offsets::netvars::m_flFallbackWear);
}

void BaseCombatWeapon::m_flFallbackWear(float v){
	mem.Write(get() + Offsets::netvars::m_flFallbackWear, v);
}

void BaseCombatWeapon::m_nModelIndex(int v){
	mem.Write(get() + Offsets::netvars::m_nModelIndex, v);
}

int BaseCombatWeapon::m_hWeaponWorldModel(){
	return mem.Read<int>(get() + Offsets::netvars::m_hWeaponWorldModel);
}

void BaseCombatWeapon::m_hWeaponWorldModel(int v){
	mem.Write(get() + Offsets::netvars::m_hWeaponWorldModel, v);
}

void BaseCombatWeapon::m_szCustomName(std::string name){
	std::array<char, 32> str = {'\0'};
	std::copy(name.begin(), name.end(), str.data());
	mem.Write(get() + Offsets::netvars::m_szCustomName, str);
}

void BaseCombatWeapon::m_nFallbackSeed(int v){
	mem.Write(get() + Offsets::netvars::m_nFallbackSeed, v);
}

void BaseCombatWeapon::m_nFallbackStatTrak(int v){
	mem.Write(get() + Offsets::netvars::m_nFallbackStatTrak, v);
}

int BaseCombatWeapon::m_OriginalOwnerXuidLow(){
	return mem.Read<int>(get() + Offsets::netvars::m_OriginalOwnerXuidLow);
}

void BaseCombatWeapon::m_iAccountID(int v){
	mem.Write(get() + Offsets::netvars::m_iAccountID, v);
}
