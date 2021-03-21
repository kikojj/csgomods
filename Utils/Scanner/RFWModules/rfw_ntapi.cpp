#include "stdafx.h"
#include "rfw_ntapi.h"

tNtQueryInformationProcess NtQueryInfoProc{ nullptr };

tNtQueryInformationProcess ImportNTQueryInfo()
{
	NtQueryInfoProc = (tNtQueryInformationProcess)GetProcAddress(GetModuleHandleA("ntdll.dll"), "NtQueryInformationProcess");

	return NtQueryInfoProc;
}

//redundant, already included in IProc
PEB* GetPEB()
{
#ifdef _WIN64
	PEB* peb = (PEB*)__readgsword(0x60); //64bit

#else
	PEB* peb = (PEB*)__readfsdword(0x30); //32bit
#endif

	return peb;
}