#include "VirtualFunction.hpp"

VirtualFunction::VirtualFunction(DWORD _dwBase):dwBase(_dwBase) {}

DWORD VirtualFunction::getVirtualFunction(int index) {
	auto table = mem.read<DWORD>(dwBase);
	return (DWORD)(table + sizeof(DWORD) * index);
}

void VirtualFunction::hook(int index, DWORD hkFunction) {
	hooks[index] = hkFunction;

	uintptr_t VFunction = getVirtualFunction(index);
	DWORD dwProtection;
	VirtualProtectEx(mem.process, (LPVOID)VFunction, sizeof(DWORD), PAGE_EXECUTE_READWRITE, &dwProtection);
	mem.write(VFunction, hkFunction);
	VirtualProtectEx(mem.process, (LPVOID)VFunction, sizeof(DWORD), dwProtection, &dwProtection);
}