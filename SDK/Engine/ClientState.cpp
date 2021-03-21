#include "ClientState.hpp"

ClientState::ClientState() {}

VAR_R_DEF_OFFNAME(int, getLocalPlayer, ClientState, get(), signatures, dwClientState_GetLocalPlayer)
ClientStates ClientState::state() {
	auto state = (ClientStates)(mem.read<int>(get() + Offsets::signatures::dwClientState_State));
	return state;
}
std::array<char, 0x120> ClientState::mapDirectory() {
	auto mapDirectory = mem.read<std::array<char, 0x120>>(get() + Offsets::signatures::dwClientState_MapDirectory);
	return mapDirectory;
}
int ClientState::dwModelPrecache() {
	//SHOULD FIND SIGNATURE
	return mem.read<int>(get() + 0x52A4);
}
void ClientState::dwViewAngles(Vector2 vec) {
	vec.clamp();
	vec.normalize();
	mem.write(get() + Offsets::signatures::dwClientState_ViewAngles, vec);
}
VAR_R_DEF_OFFNAME(Vector2, dwViewAngles, ClientState, get(), signatures, dwClientState_ViewAngles)
VAR_RW_DEF_OFFNAME(int, m_nDeltaTick, ClientState, get(), signatures, clientstate_delta_ticks)

int ClientState::get() {
	return mem.read<int>(engineDll.dwBase + Offsets::signatures::dwClientState);
}