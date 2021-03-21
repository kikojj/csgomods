#pragma once
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <Windows.h>
#include "RFWModules/ProcEx.h"
#include "RFWModules/Mod.h"
#include "RFWModules/patternscan.h"
#include "../JsonXX/jsonxx.h"

enum class DataType
{
	DT_BYTE, DT_FLOAT, DT_INT, DT_INT_HEX
};

struct SigData
{
	//json config vars
	std::string module;
	std::string comboPattern;
	std::vector<int> offsets{ 0 };
	int extra{ 0 };
	bool relative{ true };
	bool read{ true };

	intptr_t result;

	//extra vars for output
	DataType dataType;
	std::string offsetBase;

	//Perform the pattern scan
	void Scan(ProcEx proc);
};