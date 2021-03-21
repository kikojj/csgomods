#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <filesystem>

#include "SrcSDK.h"
#include "SigData.h"
#include "Netvar.h"
#include "stdafx.h"
#include "RFWModules/ProcEx.h"

#include "../../SDK/Utils/Defines.hpp"
#include "../Offsets/Offsets.hpp"

class Scanner {
private:
  static HMODULE loadLibrary(ProcEx, std::string);
  static int getOffset(RecvTable*, const char*, const char*);
  static int getNetVarOffset(const char*, const char*, ClientClass*);

public:
  static int getAllClassesSignature();
  static int getSignature(std::string module, std::string comboPattern, std::vector<int> offsets = { 0 }, int extra = 0, bool relative = true, bool read = true);
  static int getNetvar(std::string name, std::string prop, std::string table, int offset = 0);
};