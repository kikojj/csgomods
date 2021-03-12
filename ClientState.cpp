#include "ClientState.hpp"

ClientState::ClientState() {}

int ClientState::get(){
	return mem.Read<int>(engineDll.dwBase + Offsets::signatures::dwClientState);
}

Vector2 ClientState::dwViewAngles(){
	auto vec = Vector2(mem.Read<Vec2>(get() + Offsets::signatures::dwClientState_ViewAngles));
	//std::cout << "ClientState::dwViewAngles(): (" << vec << ")\n";
	return vec;
}

void ClientState::dwViewAngles(Vector2 vec){
	vec.clamp();
	vec.normalize();
	mem.Write(get() + Offsets::signatures::dwClientState_ViewAngles, vec);
}

int ClientState::getLocalPlayer(){
	auto localPlayerID = mem.Read<int>(get() + Offsets::signatures::dwClientState_GetLocalPlayer);
	//std::cout << "ClientState::GetLocalPlayer(): " << localPlayerID << ")\n";
	return localPlayerID;
}

ClientStates ClientState::state(){
	auto state = (ClientStates)(mem.Read<int>(get() + Offsets::signatures::dwClientState_State));
	/*
	switch (state)
	{
	case LOBBY:
		std::cout << "ClientState::dwClientState_State(): LOBBY\n";
		break;
	case LOADING:
		std::cout << "ClientState::dwClientState_State(): LOADING\n";
		break;
	case CONNECTING:
		std::cout << "ClientState::dwClientState_State(): CONNECTING\n";
		break;
	case CONNECTED:
		std::cout << "ClientState::dwClientState_State(): CONNECTED\n";
		break;
	case INGAME:
		std::cout << "ClientState::dwClientState_State(): INGAME\n";
		break;
	default:
		break;
	}
	*/
	return state;
}

std::array<char, 0x120> ClientState::mapDirectory(){
	auto mapDirectory = mem.Read<std::array<char, 0x120>>(get() + Offsets::signatures::dwClientState_MapDirectory);
	return mapDirectory;
}

int ClientState::dwModelPrecache(){
	//SHOULD FIND SIGNATURE
	return mem.Read<int>(get() + 0x52A4);
}

void ClientState::m_nDeltaTick(int v){
	mem.Write(get() + Offsets::signatures::clientstate_delta_ticks, v);
}

