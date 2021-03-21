#include "Engine.hpp"

Engine::Engine(){
	clientState = new ClientState();
}

std::array<char, 0x120> Engine::dwGameDir(){
	auto gameDir = mem.read<std::array<char, 0x120>>(engineDll.dwBase + Offsets::signatures::dwGameDir);
	return gameDir;
}
bool Engine::isOverlayActive(){
	auto overlayIsActive = mem.read<bool>(engineDll.dwBase + Offsets::signatures::overlayActivated1 + engineDll.dwBase + Offsets::signatures::overlayActivated2);
	return overlayIsActive;
}
