#include "ClientCmd.hpp"

void c_client_cmd::init(){
	const char* command = "";
	address = reinterpret_cast<uintptr_t>(g_mem.allocate(143));

	*reinterpret_cast<uintptr_t*>(&shellcode[3]) = address + 15;
	*reinterpret_cast<uintptr_t*>(&shellcode[8]) = c_offsets::signatures::dw_client_cmd;
	strcpy_s(reinterpret_cast<char*>(&shellcode[15]), 128, command);

	g_mem.write<BYTE[143]>((DWORD)address, shellcode);
}

bool c_client_cmd::execute(const char* command){
	if (strlen(command) > 254) {
		return false;
	}

	g_mem.write((DWORD)address + 15, *command, strlen(command) + 1);
	g_mem.create_thread(address);

	return true;
}