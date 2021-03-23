#pragma once

#include <iostream>
#include <vector>

#include "../../Utils/Memory/Memory.hpp"
#include "../../Utils/Memory/Modules.hpp"
#include "../../Utils/Offsets/Offsets.hpp"

#include "BaseEntity.hpp"
#include "GlowObjectManager.hpp"

class EntityList {
//main methods
public:
	EntityList() {};

	int get() {
		return clientDll.dwBase + Offsets::signatures::dwEntityList;
	}

//methods
public:
	int size() {
		auto count = mem.read<int>(get() + 0x24);
		//std::cout << "EntityList::size(): " << count << std::endl;
		return count;
	}
	BaseEntity getByID(int id) {
		return BaseEntity(mem.read<int>(clientDll.dwBase + Offsets::signatures::dwEntityList + id * 0x10));
	}
	int getEntityID(BaseEntity entity) {
		auto vecSize = size();
		for (int i = 0; i <= vecSize; i++) {
			auto _entity = getByID(i);
			if (_entity.get() == entity.get()) {
				return i;
			}
		}

		return -1;
	}
	std::vector<BaseEntity> array() {
		std::vector<BaseEntity> entityList;
		auto vecSize = size();
		for (int i = 0; i <= vecSize; i++) {
			BaseEntity entity(getByID(i));
			if (entity.get() <= 0 || entity.classID() != ClassID::Invalid) {
				continue;
			}

			entityList.push_back(entity);
		}

		GlowObjectManager gom;
		for (const auto& glowObject : gom.array()) {
			BaseEntity entity(glowObject.second.dwBaseEntity);
			if (entity.get() <= 0 || entity.classID() == ClassID::Invalid) {
				continue;
			}

			entityList.push_back(entity);
		}
		return entityList;
	}
 };