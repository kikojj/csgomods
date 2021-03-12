#pragma once
#include <Windows.h>
#include "rfw-modules/ProcEx.h"
#include "rfw-modules/Mod.h"
#include "SigData.h"

const std::string LocalEntityOffsetNames[] =
{
	"m_iHealth"
};

struct NetvarData
{
	std::string name;
	std::string prop;
	std::string table;
	int offset{ 0 };
	intptr_t result;

	void Get(ProcEx proc, SigData dwGetAllClasses);

	DataType GetDataType();
	std::string GetCEVariableTypeString();
};