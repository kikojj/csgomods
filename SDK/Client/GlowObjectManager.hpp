#pragma once

#include <iostream>
#include <vector>

#include "../Utils/IGlowObjectDefinition.hpp"

#include "../../Utils/Memory/Memory.hpp"
#include "../../Utils/Memory/Modules.hpp"
#include "../../Utils/Offsets/Offsets.hpp"

class GlowObjectManager {
public:
	/// <summary>
	/// get glowObjectManager address
	/// </summary>
	/// <returns>Address to glowObjectManager</returns>
  int get();

	/// <summary>
	/// get size of glowObjects
	/// </summary>
	/// <returns>GlowObjects size</returns>
  int size();

  /// <summary>
  /// get glowObjectsArray as std::vector
  /// </summary>
  /// <returns>pair(dwBase, IGlowObjectDefinition)</returns>
  std::vector<std::pair<int, IGlowObjectDefinition>> array();
};