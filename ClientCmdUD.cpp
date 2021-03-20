#include "ClientCmdUD.hpp"

void ClientCmdUD::init(){
	const char* command = "";
	address = reinterpret_cast<uintptr_t>(mem.allocate(143));

	*reinterpret_cast<uintptr_t*>(&shellcode[3]) = address + 15;
	*reinterpret_cast<uintptr_t*>(&shellcode[8]) = Offsets::signatures::dwClientCmdUD;
	strcpy_s(reinterpret_cast<char*>(&shellcode[15]), 128, command);

	mem.Write<BYTE[143]>((DWORD)address, shellcode);
}

bool ClientCmdUD::execute(const char* command){
	if (strlen(command) > 254) {
		return false;
	}

	WriteProcessMemory(mem._process, reinterpret_cast<LPVOID>(address + 15), command, strlen(command) + 1, 0);
	mem.CreateThread(address);

	return true;
}