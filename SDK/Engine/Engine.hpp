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

	/// <summary>
	/// get game directory
	/// </summary>
	/// <returns></returns>
	std::array<char, 0x120> dwGameDir();

	/// <summary>
	/// check if steam overlay is open
	/// </summary>
	/// <returns>True if open</returns>
	bool isOverlayActive();
};

extern Engine engine;