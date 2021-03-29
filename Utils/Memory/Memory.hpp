#pragma once

#include <Windows.h>
#include <TlHelp32.h>
#include <comdef.h>
#include <string>
#include <map>

#include "PModule.hpp"

class Memory {
public:
	HANDLE process;
	DWORD pID;

	inline DWORD findProcess(const char* pName) {
		HANDLE handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

		PROCESSENTRY32 entry;
		entry.dwSize = sizeof(entry);

		do {
			if (!strcmp(_bstr_t(entry.szExeFile), pName)) {
				DWORD _pID = entry.th32ProcessID;
				CloseHandle(handle);
				return _pID;
			}
		} while (Process32Next(handle, &entry));
		return 0;
	}

	inline void attach(DWORD _pID, DWORD dwAccess) {
		process = OpenProcess(dwAccess, false, _pID);
		pID = _pID;
	}

	inline PModule getModule(const char* pModule) {
		HANDLE module = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pID);
		MODULEENTRY32 entry;
		entry.dwSize = sizeof(entry);

		do {
			if (!strcmp(_bstr_t(entry.szModule), pModule)) {
				CloseHandle(module);
				return PModule{
					reinterpret_cast<DWORD>(entry.hModule),
					entry.modBaseSize
				};
			}
		} while (Module32Next(module, &entry));

		return PModule{ 0, 0 };
	}

	template<class T>
	T read(const DWORD dwAddress) {
		T _read;
		ReadProcessMemory(process, LPVOID(dwAddress), &_read, sizeof(T), NULL);
		return _read;
	}

	template<int size>
	std::string readStr(const DWORD dwAddress) {
		char _read[size];
		ReadProcessMemory(process, LPVOID(dwAddress), _read, sizeof(char[size]), NULL);
		return std::string(_read);
	}

	template<class T>
	bool write(const DWORD dwAddress, const T& value, SIZE_T size = sizeof(T)) {
		return WriteProcessMemory(process, LPVOID(dwAddress), &value, size, NULL);
	}

	inline void createThread(uintptr_t address, LPVOID parameter = 0) {
		HANDLE hThread = CreateRemoteThread(process, 0, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(address), parameter, 0, 0);
		if (!hThread) {
			return;
		}
		WaitForSingleObject(hThread, 5000);
		CloseHandle(hThread);
	}

	void exit() {
		CloseHandle(process);
	}

	//allocator
	std::map<LPVOID, uintptr_t> allocators;

	LPVOID allocateNewPage(uintptr_t size) {
		auto address = VirtualAllocEx(process, NULL, (size > 4096 ? size : 4096), MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
		allocators[address] = size;
		return address;
	}

	LPVOID allocate(uintptr_t size = 4096) {
		for (auto allocator : allocators) {
			uintptr_t value = allocator.second + size;
			if (value < 4096) {
				LPVOID currentAddres = LPVOID(uintptr_t(allocator.first) + allocator.second);
				allocator.second = value;
				return currentAddres;
			}
		}
		return allocateNewPage(size);
	}

	void free() {
		for (auto allocator : allocators) {
			free(allocator.first);
		}
	}

	void free(LPVOID address) {
		if (allocators[address] > 0) {
			VirtualFreeEx(process, address, 4096, MEM_COMMIT | MEM_RESERVE);
		}
	}
};

extern Memory mem;
