#include "Scanner.hpp"

HMODULE c_scanner::load_library(ProcEx proc, std::string name){
	ModEx mod(name.c_str(), proc);
	std::filesystem::path p(mod.modEntry.szExePath);

	p = p.parent_path().parent_path().parent_path() / "bin";
	AddDllDirectory(p.wstring().c_str());

	return LoadLibraryEx(mod.modEntry.szExePath, NULL, LOAD_LIBRARY_SEARCH_DEFAULT_DIRS);
}

int c_scanner::get_offset(c_recv_table* table, const char* table_name, const char* netvar_name)
{
	for (int i = 0; i < table->i_props; i++)
	{
		c_recv_prop prop = table->p_props[i];

		if (!_stricmp(prop.var_name, netvar_name))
		{
			return prop.offset;
		}

		if (prop.data_table)
		{
			intptr_t offset = get_offset(prop.data_table, table_name, netvar_name);

			if (offset)
			{
				return offset + prop.offset;
			}
		}
	}
	return 0;
}

int c_scanner::get_netvar_offset(const char* table_name, const char* netvar_name, c_client_class* client_class)
{
	c_client_class* p_curr_node = client_class;

	for (auto p_curr_node = client_class; p_curr_node; p_curr_node = p_curr_node->next)
	{
		if (!_stricmp(table_name, p_curr_node->recv_table->net_table__name))
		{
			return get_offset(p_curr_node->recv_table, table_name, netvar_name);
		}
	}

	return 0;
}


int c_scanner::get_all_classes() {
	return get_signature(CLIENT_DLL_NAME, "A1 ? ? ? ? C3 CC CC CC CC CC CC CC CC CC CC A1 ? ? ? ? B9", { 1, 0 });
}

int c_scanner::get_signature(std::string module, std::string combo_pattern, std::vector<int> offsets, int extra, bool relative, bool read) {
	SigData signature{module, combo_pattern, offsets, extra, relative, read};

	auto process = ProcEx(TO_WCHAR_T((char*)std::string(GAME_NAME).c_str()));
	signature.Scan(process);
	return signature.result;
}

int c_scanner::get_netvar(std::string name, std::string prop, std::string table, int offset){
	NetvarData netvar{name, prop, table, offset};

	auto process = ProcEx(TO_WCHAR_T((char*)std::string(GAME_NAME).c_str()));
	HMODULE h_mod = load_library(process, CLIENT_DLL_NAME);
	c_client_class* p_get_all_classes = (c_client_class*)((intptr_t)h_mod + get_all_classes());

	netvar.result = get_netvar_offset(netvar.table.c_str(), netvar.prop.c_str(), p_get_all_classes);
	if (netvar.offset)
	{
		netvar.result += netvar.offset;
	}
	return netvar.result;
}
