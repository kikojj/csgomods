#pragma once

#include <iostream>
#include <vector>

#include "../../Utils/Memory/Memory.hpp"
#include "../../Utils/Memory/Modules.hpp"
#include "../../Utils/Offsets/Offsets.hpp"

#include "BaseEntity.hpp"
#include "GlowObjectManager.hpp"

class EntityList {
//types
public:
	typedef std::pair<BaseEntity, int> EntityObject;

//main methods
public:
	EntityList() {};

	static int get() {
		return clientDll.dwBase + Offsets::signatures::dwEntityList;
	}

//methods
public:
	static int size() {
		auto count = mem.read<int>(get() + 0x24);
		return count;
	}
	static std::vector<EntityObject> array(int size = size()) {
		std::vector<EntityObject> entityList;

		for (int i = 0; i <= size; i++) {
			BaseEntity entity(getByID(i));

			if (entity.get() <= 0 ) {
				continue;
			}

			entityList.push_back({ entity, i });
		}

		return entityList;
	}
	static std::vector<EntityObject> players(int size = engine.clientState->maxPlayers()) {
		std::vector<EntityObject> playerList;

		for (int i = 0; i <= size; i++) {
			BaseEntity entity(getByID(i));

			if (entity.get() <= 0) {
				continue;
			}

			if (entity.classID() != ClassID::CCSPlayer) {
				continue;
			}

			playerList.push_back({ entity, i });
		}

		return playerList;
	}
	static BaseEntity getByID(int id) {
		return BaseEntity(mem.read<int>(clientDll.dwBase + Offsets::signatures::dwEntityList + id * 0x10));
	}
	static int getEntityID(int base) {
		int vecSize = size();
		for (int i = 0; i < vecSize; i++) {
			auto entity = getByID(i);
			if (entity.get() == base) {
				return i;
			}
		}
		return -1;
	}
 };