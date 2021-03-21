#include "Client.hpp"

Client::Client() {
	localPlayer = new BaseLocalPlayer();
	entityList = new EntityList();
	glowObjectManager = new GlowObjectManager();
}

VAR_R_DEF(Input, dwInput, Client, clientDll.dwBase, signatures)
VAR_R_DEF(short, dwMouseEnable, Client, clientDll.dwBase, signatures)
int Client::hConfirmMatch() {
	return clientDll.dwBase + Offsets::signatures::hConfirmMatch;
}
int Client::confirmReservationCallback() {
	return mem.read<int>(mem.read<int>(clientDll.dwBase + Offsets::signatures::hConfirmMatch + 0x7));
}
VAR_W_DEF(KeyEvent, dwForceJump, Client, clientDll.dwBase, signatures)
VAR_W_DEF(KeyEvent, dwForceAttack, Client, clientDll.dwBase, signatures)