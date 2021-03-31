#pragma once

#include <Windows.h>
#include <string>

#include "../Offsets/Offsets.hpp"
#include "../Memory/Memory.hpp"

class c_client_cmd {
private:
	uintptr_t address = 0;
	BYTE shellcode[15 + 128] = {
		0x6A, 0x00,										// push   0x0
		0x68, 0x00, 0x00, 0x00, 0x00,	// push   (pointer to command)
		0xB8, 0x00, 0x00, 0x00, 0x00,	// mov    eax,(ClientCmd_Un)
		0xFF, 0xD0,										// call   eax 
		0xC3
	};															// ret
																	// (command)
public:
	void init();
	bool execute(const char* command);
};

extern c_client_cmd g_client_cmd;