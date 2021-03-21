#pragma once

#include <iostream>
#include <vector>

#include "../Utils/IGlowObjectDefinition.hpp"

#include "../../Utils/Memory/Memory.hpp"
#include "../../Utils/Memory/Modules.hpp"
#include "../../Utils/Offsets/Offsets.hpp"

class GlowObjectManager {
public:
  int get();
  int size();
  std::vector<std::pair<int, IGlowObjectDefinition>> array();
};