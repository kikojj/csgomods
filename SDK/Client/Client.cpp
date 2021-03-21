#include "Client.hpp"

Client::Client() {
	localPlayer = new BaseLocalPlayer();
	entityList = new EntityList();
	glowObjectManager = new GlowObjectManager();
}

void Client::dwForceJump(KeyEvent v) {
	mem.write(clientDll.dwBase + Offsets::signatures::dwForceJump, v);
}

void Client::dwForceAttack(KeyEvent v) {
	mem.write(clientDll.dwBase + Offsets::signatures::dwForceAttack, v);
}

Input Client::dwInput(){
	return mem.read<Input>(clientDll.dwBase + Offsets::signatures::dwInput);
}

short Client::dwMouseEnable(){
	return mem.read<short>(clientDll.dwBase + Offsets::signatures::dwMouseEnable);
}

int Client::hConfirmMatch(){
	return clientDll.dwBase + Offsets::signatures::hConfirmMatch;
}

int Client::confirmReservationCallback(){
	return mem.read<int>(mem.read<int>(clientDll.dwBase + Offsets::signatures::hConfirmMatch + 0x7));
}
