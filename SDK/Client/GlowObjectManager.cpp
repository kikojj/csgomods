#include "GlowObjectManager.hpp"

int GlowObjectManager::get(){
  return mem.read<int>(clientDll.dwBase + Offsets::signatures::dwGlowObjectManager);
}

int GlowObjectManager::size(){
  auto size = mem.read<int>(clientDll.dwBase + Offsets::signatures::dwGlowObjectManager + 0x4);
  //std::cout << "GlowObjectManager::size(): " << size << std::endl;
  return size;
}

std::vector<std::pair<int, IGlowObjectDefinition>> GlowObjectManager::array(){
	std::vector<std::pair<int, IGlowObjectDefinition>> glowObjectArray;
	auto vecSize = size();
	for (int i = 0; i <= vecSize; i++) {
		auto glowObjectDefinition = mem.read<IGlowObjectDefinition>(get() + i * 0x38);

		if (glowObjectDefinition.dwBaseEntity  > 0) {
			glowObjectArray.push_back({ get() + i * 0x38, glowObjectDefinition });
		}
	}
	return glowObjectArray;
}
