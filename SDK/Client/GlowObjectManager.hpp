#pragma once

#include <iostream>
#include <vector>

#include "../Utils/IGlowObjectDefinition.hpp"

#include "../../Utils/Memory/Memory.hpp"
#include "../../Utils/Memory/Modules.hpp"
#include "../../Utils/Offsets/Offsets.hpp"

class GlowObjectManager {
//main methods
public:
  GlowObjectManager() {};

	int get() {
		return mem.read<int>(clientDll.dwBase + Offsets::signatures::dwGlowObjectManager);
	}

//methods
public:
	int size() {
		auto size = mem.read<int>(clientDll.dwBase + Offsets::signatures::dwGlowObjectManager + 0x4);
		return size;
	}
	std::vector<std::pair<int, IGlowObjectDefinition>> array() {
		std::vector<std::pair<int, IGlowObjectDefinition>> glowObjectArray;
		auto vecSize = size();
		for (int i = 0; i <= vecSize; i++) {
			auto glowObjectDefinition = mem.read<IGlowObjectDefinition>(get() + i * 0x38);

			if (glowObjectDefinition.dwBaseEntity > 0) {
				glowObjectArray.push_back({ get() + i * 0x38, glowObjectDefinition });
			}
		}
		return glowObjectArray;
	}
};