#pragma once

#include <iostream>
#include <vector>

#include "Memory.hpp"
#include "Modules.hpp"
#include "Offsets.hpp"

#include "IGlowObjectDefinition.hpp"

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