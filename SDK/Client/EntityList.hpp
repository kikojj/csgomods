#pragma once

#include <iostream>
#include <vector>

#include "BaseEntity.hpp"
#include "GlowObjectManager.hpp"

#include "../../Utils/Memory/Memory.hpp"
#include "../../Utils/Memory/Modules.hpp"
#include "../../Utils/Offsets/Offsets.hpp"

class EntityList {
private:
public:
	EntityList();

	/// <summary>
	/// get address to entityList
	/// </summary>
	/// <returns>address to entityList</returns>
	int get();

	BaseEntity getByID(int);

	/// <summary>
	/// get max size of entities
	/// </summary>
	/// <returns>vector of Entity</returns>
	int size();

	/// <summary>
	/// get vector of entities
	/// </summary>
	std::vector<BaseEntity> array();
 };