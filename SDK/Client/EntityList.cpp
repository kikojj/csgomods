#include "EntityList.hpp"

EntityList::EntityList() {};

int EntityList::get() {
	return clientDll.dwBase + Offsets::signatures::dwEntityList;
}
int EntityList::size() {
	auto count = mem.read<int>(get() + 0x24);
	//std::cout << "EntityList::size(): " << count << std::endl;
	return count;
}
std::vector<BaseEntity> EntityList::array() {
	std::vector<BaseEntity> entityList;
	auto vecSize = size();
	for (int i = 0; i <= vecSize; i++) {
		int pEntity = mem.read<int>(clientDll.dwBase + Offsets::signatures::dwEntityList + i * 0x10);
		if (pEntity <= 0) {
			continue;
		}

		BaseEntity entity(pEntity);
		entityList.push_back(entity);
	}
	GlowObjectManager gom;
	for (auto glowObject : gom.array()) {
		BaseEntity entity(glowObject.second.dwBaseEntity);
		if (int(entity.m_iClassID()) > 0) {
			entityList.push_back(entity);
		}
	}
	return entityList;
}
BaseEntity EntityList::getByID(int id){
	return BaseEntity(mem.read<int>(clientDll.dwBase + Offsets::signatures::dwEntityList + id * 0x10));
}
