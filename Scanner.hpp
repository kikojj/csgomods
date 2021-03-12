#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <filesystem>

#include "dumper/SrcSDK.h"
#include "dumper/SigData.h"
#include "dumper/Netvar.h"
#include "dumper/stdafx.h"
#include "dumper/rfw-modules/ProcEx.h"

#include "Offsets.hpp"
#include "Defines.hpp"

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