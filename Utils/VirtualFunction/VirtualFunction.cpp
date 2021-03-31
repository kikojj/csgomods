#include "VirtualFunction.hpp"

c_virtual_function::c_virtual_function(DWORD base):base(base) {}

DWORD c_virtual_function::get_virtual_function(int index) {
	auto dw_table = g_mem.read<DWORD>(base);
	return (DWORD)(dw_table + sizeof(DWORD) * index);
}

void c_virtual_function::hook(int index, DWORD function) {
	hooks[index] = function;

	uintptr_t p_function = get_virtual_function(index);
	DWORD dw_protection;
	VirtualProtectEx(g_mem.process, (LPVOID)p_function, sizeof(DWORD), PAGE_EXECUTE_READWRITE, &dw_protection);
	g_mem.write(p_function, function);
	VirtualProtectEx(g_mem.process, (LPVOID)p_function, sizeof(DWORD), dw_protection, &dw_protection);
}