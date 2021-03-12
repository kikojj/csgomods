#include "Scanner.hpp"

HMODULE Scanner::loadLibrary(ProcEx proc, std::string name){
	ModEx mod(name.c_str(), proc);
	std::filesystem::path p(mod.modEntry.szExePath);

	p = p.parent_path().parent_path().parent_path() / "bin";
	AddDllDirectory(p.wstring().c_str());

	return LoadLibraryEx(mod.modEntry.szExePath, NULL, LOAD_LIBRARY_SEARCH_DEFAULT_DIRS);
}

int Scanner::getOffset(RecvTable* table, const char* tableName, const char* netvarName)
{
	for (int i = 0; i < table->m_nProps; i++)
	{
		RecvProp prop = table->m_pProps[i];

		if (!_stricmp(prop.m_pVarName, netvarName))
		{
			return prop.m_Offset;
		}

		if (prop.m_pDataTable)
		{
			intptr_t offset = getOffset(prop.m_pDataTable, tableName, netvarName);

			if (offset)
			{
				return offset + prop.m_Offset;
			}
		}
	}
	return 0;
}

int Scanner::getNetVarOffset(const char* tableName, const char* netvarName, ClientClass* clientClass)
{
	ClientClass* currNode = clientClass;

	for (auto currNode = clientClass; currNode; currNode = currNode->m_pNext)
	{
		if (!_stricmp(tableName, currNode->m_pRecvTable->m_pNetTableName))
		{
			return getOffset(currNode->m_pRecvTable, tableName, netvarName);
		}
	}

	return 0;
}


int Scanner::getAllClassesSignature() {
	return getSignature(CLIENT_DLL_NAME, "A1 ? ? ? ? C3 CC CC CC CC CC CC CC CC CC CC A1 ? ? ? ? B9", { 1, 0 });
}

int Scanner::getSignature(std::string module, std::string comboPattern, std::vector<int> offsets, int extra, bool relative, bool read) {
	SigData signature{module, comboPattern, offsets, extra, relative, read};

	auto process = ProcEx(TO_WCHAR_T((char*)std::string(GAME_NAME).c_str()));
	signature.Scan(process);
	return signature.result;
}

int Scanner::getNetvar(std::string name, std::string prop, std::string table, int offset){
	NetvarData netvar{name, prop, table, offset};

	auto process = ProcEx(TO_WCHAR_T((char*)std::string(GAME_NAME).c_str()));
	HMODULE hMod = loadLibrary(process, CLIENT_DLL_NAME);
	ClientClass* dwGetallClassesAddr = (ClientClass*)((intptr_t)hMod + getAllClassesSignature());

	netvar.result = getNetVarOffset(netvar.table.c_str(), netvar.prop.c_str(), dwGetallClassesAddr);
	if (netvar.offset)
	{
		netvar.result += netvar.offset;
	}
	return netvar.result;
}
