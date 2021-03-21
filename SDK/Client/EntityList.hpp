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

	int get();
	int size();
	std::vector<BaseEntity> array();
	BaseEntity getByID(int);
 };