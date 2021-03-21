#pragma once

#include "../Vars.hpp"

#include "../Utils/Vector.hpp"
#include "../Utils/ClientStates.hpp"

#include "../../Utils/Memory/Memory.hpp"
#include "../../Utils/Memory/Modules.hpp"
#include "../../Utils/Offsets/Offsets.hpp"

class ClientState {
public:
	ClientState();

	/// <summary>get the ID of localPlayer in entityList</summary>
	VAR_R_DEC(int, getLocalPlayer)
	/// <summary> get user state</summary>
	/// <returns>LOBBY = 0, LOADING = 1, CONNECTIONG = 2, CONNECTED = 5, INGAME = 6</returns>
	VAR_R_DEC(ClientStates, state)
	/// <summary>get current map directory</summary>
	std::array<char, 0x120> mapDirectory();
	VAR_R_DEC(int, dwModelPrecache)
	/// <summary> get/set variable that stores vec2(x, y) the screen's center in the plane of the screen</summary>
	VAR_RW_DEC(Vector2, dwViewAngles)
	VAR_RW_DEC(int, m_nDeltaTick)

	int get();
};