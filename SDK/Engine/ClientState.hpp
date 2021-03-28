#pragma once

#include "../Vars.hpp"

#include "../Utils/Vector.hpp"
#include "../Utils/ClientStates.hpp"

#include "../../Utils/Memory/Memory.hpp"
#include "../../Utils/Memory/Modules.hpp"
#include "../../Utils/Offsets/Offsets.hpp"

class ClientState {
//main methods
public:
	ClientState() {}

	int get() {
		return mem.read<int>(engineDll.dwBase + Offsets::signatures::dwClientState);
	}

//methods
public:
	int getLocalPlayer() {
		return mem.read<int>(get() + Offsets::signatures::dwClientState_GetLocalPlayer);
	}
	Vec2 dwViewAngles() {
		return mem.read<Vec2>(get() + Offsets::signatures::dwClientState_ViewAngles);
	}
	void dwViewAngles(Vec2 vec) {
		auto _vec = Vector2(vec);
		_vec.clamp();
		_vec.normalize();
		mem.write(get() + Offsets::signatures::dwClientState_ViewAngles, _vec);
	}
	int m_nDeltaTick() {
		return mem.read<int>(get() + Offsets::signatures::clientstate_delta_ticks);
	}
	void m_nDeltaTick(int value) {
		mem.write(get() + Offsets::signatures::clientstate_delta_ticks, value);
	}
	ClientStates state() {
		auto state = (ClientStates)mem.read<int>(get() + Offsets::signatures::dwClientState_State);
		return state;
	}
	std::array<char, 0x120> mapDirectory() {
		auto mapDirectory = mem.read<std::array<char, 0x120>>(get() + Offsets::signatures::dwClientState_MapDirectory);
		return mapDirectory;
	}
	int dwModelPrecache() {
		//SHOULD FIND SIGNATURE
		return mem.read<int>(get() + 0x52A4);
	}
	int playerInfo() {
		auto playerInfo = mem.read<int>(get() + Offsets::signatures::dwClientState_PlayerInfo);
		return playerInfo;
	}
	int maxPlayers() {
		auto maxPlayers = mem.read<int>(get() + Offsets::signatures::dwClientState_MaxPlayer);
		return maxPlayers;
	}
};