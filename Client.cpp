#include "Client.hpp"

Client::Client() {
	localPlayer = new BaseLocalPlayer();
	entityList = new EntityList();
	glowObjectManager = new GlowObjectManager();
}

void Client::dwForceJump(KeyEvent v) {
	mem.Write(clientDll.dwBase + Offsets::signatures::dwForceJump, v);
}

void Client::dwForceAttack(KeyEvent v) {
	mem.Write(clientDll.dwBase + Offsets::signatures::dwForceAttack, v);
}

Input Client::dwInput(){
	return mem.Read<Input>(clientDll.dwBase + Offsets::signatures::dwInput);
}

short Client::dwMouseEnable(){
	return mem.Read<short>(clientDll.dwBase + Offsets::signatures::dwMouseEnable);
}

int Client::hConfirmMatch(){
	return clientDll.dwBase + Offsets::signatures::hConfirmMatch;
}

int Client::confirmReservationCallback(){
	return mem.Read<int>(mem.Read<int>(clientDll.dwBase + Offsets::signatures::hConfirmMatch + 0x7));
}
