#include "BaseEntity.hpp"

BaseEntity::BaseEntity() {}

BaseEntity::BaseEntity(int _dwBase): dwBase(_dwBase) {};

void BaseEntity::operator=(BaseEntity BaseEntity) {
	this->dwBase = BaseEntity.dwBase;
}

int BaseEntity::get(){
	return this->dwBase;
}

ClassID BaseEntity::m_iClassID(){
	auto id = mem.Read<int>(mem.Read<int>(mem.Read<int>(mem.Read<int>(get() + 0x8) + 0x8) + 0x1) + 0x14);
	if (id < 0) {
		return INVALID_CLASS_ID;
	}

	return ClassID(id);
}

int BaseEntity::m_iGlowIndex(){
	auto glowIndex = mem.Read<int>(get() + Offsets::netvars::m_iGlowIndex);
	//std::cout << "Player::m_iGlowIndex():" << glowIndex << std::endl;
	return glowIndex;
}