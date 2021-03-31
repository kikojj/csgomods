#pragma once

#include <Windows.h>
#include <TlHelp32.h>
#include <comdef.h>
#include <string>
#include <map>

#include "PModule.hpp"

class c_memory {
public:
	HANDLE process;
	DWORD proccess_id;

	inline DWORD find_process(const char* name) {
		HANDLE handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

		PROCESSENTRY32 entry;
		entry.dwSize = sizeof(entry);

		do {
			if (!strcmp(_bstr_t(entry.szExeFile), name)) {
				DWORD id = entry.th32ProcessID;
				CloseHandle(handle);
				return id;
			}
		} while (Process32Next(handle, &entry));
		return 0;
	}

	inline void attach(DWORD id, DWORD access) {
		process = OpenProcess(access, false, id);
		proccess_id = id;
	}

	inline s_pm_module get_module(const char* module) {
		HANDLE h_module = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, proccess_id);
		MODULEENTRY32 entry;
		entry.dwSize = sizeof(entry);

		do {
			if (!strcmp(_bstr_t(entry.szModule), module)) {
				CloseHandle(h_module);
				return s_pm_module{
					reinterpret_cast<DWORD>(entry.hModule),
					entry.modBaseSize
				};
			}
		} while (Module32Next(h_module, &entry));

		return s_pm_module{ 0, 0 };
	}

	template<class T>
	T read(const DWORD address) {
		T _read;
		ReadProcessMemory(process, LPVOID(address), &_read, sizeof(T), NULL);
		return _read;
	}

	template<int size>
	std::string read_str(const DWORD address) {
		char _read[size];
		ReadProcessMemory(process, LPVOID(address), _read, sizeof(char[size]), NULL);
		return std::string(_read);
	}

	template<class T>
	bool write(const DWORD address, const T& value, SIZE_T size = sizeof(T)) {
		return WriteProcessMemory(process, LPVOID(address), &value, size, NULL);
	}

	inline void createThread(uintptr_t address, LPVOID parameter = 0) {
		HANDLE h_thread = CreateRemoteThread(process, 0, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(address), parameter, 0, 0);
		if (!h_thread) {
			return;
		}
		WaitForSingleObject(h_thread, 5000);
		CloseHandle(h_thread);
	}

	void exit() {
		CloseHandle(process);
	}

	//allocator
	std::map<LPVOID, uintptr_t> allocators;

	LPVOID allocate_new_page(uintptr_t size) {
		auto p_address = VirtualAllocEx(process, NULL, (size > 4096 ? size : 4096), MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
		allocators[p_address] = size;
		return p_address;
	}

	LPVOID allocate(uintptr_t size = 4096) {
		for (auto allocator : allocators) {
			uintptr_t ui_value = allocator.second + size;
			if (ui_value < 4096) {
				LPVOID currentAddres = LPVOID(uintptr_t(allocator.first) + allocator.second);
				allocator.second = ui_value;
				return currentAddres;
			}
		}
		return allocate_new_page(size);
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

extern c_memory g_mem;
