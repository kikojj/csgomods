#pragma once

#include <Windows.h>
#include <TlHelp32.h>
#include <string>
#include <comdef.h>
#include "PModule.hpp"

class Memory {
public:
	HANDLE _process;
	DWORD _pId;

	inline bool Attach(const char* pName, DWORD dwAccess) {
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

	inline PModule GetModule(const char* pModule) {
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
	T Read(const DWORD dwAddress) {
		T _read;
		ReadProcessMemory(_process, LPVOID(dwAddress), &_read, sizeof(T), NULL);
		return _read;
	}

	std::string ReadCharArray(const DWORD dwAddress) {
		char _read[128];
		ReadProcessMemory(_process, LPVOID(dwAddress), _read, sizeof(char[128]), NULL);
		return std::string(_read);
	}

	template<class T>
	void Write(const DWORD dwAddress, const T value) {
		WriteProcessMemory(_process, LPVOID(dwAddress), &value, sizeof(T), NULL);
	}


	inline void CreateThread(uintptr_t address, LPVOID parameter = 0){
		HANDLE hThread = CreateRemoteThread(_process, 0, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(address), parameter, 0, 0);
		if (!hThread){
			return;
		}
		WaitForSingleObject(hThread, 5000);
		CloseHandle(hThread);
	}

	void Exit() {
		CloseHandle(_process);
	}
};

extern Memory mem;
