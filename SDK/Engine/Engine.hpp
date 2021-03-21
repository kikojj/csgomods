#pragma once

#include <iostream>

#include "ClientState.hpp"

#include "../Utils/Defines.hpp"
#include "../../Utils/Memory/Memory.hpp"
#include "../../Utils/Memory/Modules.hpp"
#include "../../Utils/Offsets/Offsets.hpp"

class Engine {
private:
public:
	ClientState* clientState = nullptr;

	Engine();

	std::array<char, 0x120> dwGameDir();
	bool isOverlayActive();
};

extern Engine engine;