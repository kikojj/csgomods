#pragma once

#include <iostream>
#include "../../Utils/Memory/Memory.hpp"
#include "../../Utils/Memory/Modules.hpp"
#include "../../Utils/Offsets/Offsets.hpp"

#include "../Utils/Defines.hpp"

#include "ClientState.hpp"

class Engine {
//main variables
public:
	ClientState* clientState = nullptr;

//main methods
public:
	Engine() {
		clientState = new ClientState();
	}

//methods
public:
	std::array<char, 0x120> dwGameDir() {
		auto gameDir = mem.read<std::array<char, 0x120>>(engineDll.dwBase + Offsets::signatures::dwGameDir);
		return gameDir;
	}
	bool isOverlayActive() {
		auto overlayIsActive = mem.read<bool>(engineDll.dwBase + Offsets::signatures::overlayActivated1 + engineDll.dwBase + Offsets::signatures::overlayActivated2);
		return overlayIsActive;
	}
};

extern Engine engine;