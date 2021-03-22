#include "BaseEntity.hpp"

BaseEntity::BaseEntity() {}
BaseEntity::BaseEntity(int _dwBase): dwBase(_dwBase) {};

ClassID BaseEntity::m_iClassID() {
	auto id = mem.read<int>(mem.read<int>(mem.read<int>(mem.read<int>(get() + 0x8) + 0x8) + 0x1) + 0x14);
	if (id < 0) {
		return ClassID::Invalid;
	}

	return ClassID(id);
}
VAR_R_DEF(int, m_iGlowIndex, BaseEntity, get(), netvars)
VAR_R_DEF(float, m_flC4Blow, BaseEntity, get(), netvars)

void BaseEntity::operator=(BaseEntity BaseEntity) {
	this->dwBase = BaseEntity.dwBase;
}
int BaseEntity::get(){
	return this->dwBase;
}
int BaseEntity::getEntityID(){
	for (int i = 0; i <= 64; i++) {
		int pEntity = mem.read<int>(clientDll.dwBase + Offsets::signatures::dwEntityList + i * 0x10);
		if (pEntity == this->dwBase) {
			return i;
		}
	}
	return -1;
}
