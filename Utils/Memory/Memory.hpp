#pragma once

#include <Windows.h>
#include <TlHelp32.h>
#include <comdef.h>
#include <string>
#include <map>

#include "PModule.hpp"

class Memory {
public:
	HANDLE _process;
	DWORD _pId;

	inline bool attach(const char* pName, DWORD dwAccess) {
		HANDLE handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

		PROCESSENTRY32 entry;
		entry.dwSize = sizeof(entry);

		do {
			if (!strcmp(_bstr_t(entry.szExeFile), pName)) {
				_pId = entry.th32ProcessID;
				CloseHandle(handle);
				_process = OpenProcess(dwAccess, false, _pId);
				return true;
			}
		} while (Process32Next(handle, &entry));
		return false;
	}

	inline PModule getModule(const char* pModule) {
		HANDLE module = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, _pId);
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
		ReadProcessMemory(_process, LPVOID(dwAddress), &_read, sizeof(T), NULL);
		return _read;
	}

	template<int size>
	std::string readStr(const DWORD dwAddress) {
		char _read[size];
		ReadProcessMemory(_process, LPVOID(dwAddress), _read, sizeof(char[size]), NULL);
		return std::string(_read);
	}

	template<class T>
	void write(const DWORD dwAddress, const T& value) {
		WriteProcessMemory(_process, LPVOID(dwAddress), &value, sizeof(T), NULL);
	}

	inline void createThread(uintptr_t address, LPVOID parameter = 0) {
		HANDLE hThread = CreateRemoteThread(_process, 0, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(address), parameter, 0, 0);
		if (!hThread) {
			return;
		}
		WaitForSingleObject(hThread, 5000);
		CloseHandle(hThread);
	}

	void exit() {
		CloseHandle(_process);
	}

	//allocator
	std::map<LPVOID, uintptr_t> allocators;

	LPVOID allocateNewPage(uintptr_t size) {
		auto address = VirtualAllocEx(_process, NULL, (size > 4096 ? size : 4096), MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
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
			VirtualFreeEx(_process, address, 4096, MEM_COMMIT | MEM_RESERVE);
		}
	}
};

extern Memory mem;
