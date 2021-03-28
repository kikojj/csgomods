#pragma once

#include <iostream>
#include <vector>

#include "../Utils/IGlowObjectDefinition.hpp"

#include "../../Utils/Memory/Memory.hpp"
#include "../../Utils/Memory/Modules.hpp"
#include "../../Utils/Offsets/Offsets.hpp"

class GlowObjectManager {
//types
public:
	typedef std::pair<IGlowObjectDefinition, int> GlowObject;

//main methods
public:
  GlowObjectManager() {};

	static int get() {
		return mem.read<int>(clientDll.dwBase + Offsets::signatures::dwGlowObjectManager);
	}

//methods
public:
	static int size() {
		auto size = mem.read<int>(clientDll.dwBase + Offsets::signatures::dwGlowObjectManager + 0x4);
		return size;
	}
	static std::vector<GlowObject> array() {
		std::vector<GlowObject> glowObjectArray;
		auto vecSize = size();
		for (int i = 0; i <= vecSize; i++) {
			auto glowObjectDefinition = mem.read<IGlowObjectDefinition>(get() + i * 0x38);

			if (glowObjectDefinition.dwBaseEntity > 0) {
				glowObjectArray.push_back({ glowObjectDefinition, i });
			}
		}
		return glowObjectArray;
	}
	static int getObjectBase(int id) {
		int base = get() + id * 0x38;
		return base;
	}
	static int getObjectBase(GlowObject obj) {
		int base = getObjectBase(obj.second);
		return base;
	}
};