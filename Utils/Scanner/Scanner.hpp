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

class c_scanner {
private:
  static HMODULE load_library(ProcEx, std::string);
  static int get_offset(c_recv_table*, const char*, const char*);
  static int get_netvar_offset(const char*, const char*, c_client_class*);

public:
  static int get_all_classes();
  static int get_signature(std::string module, std::string combo_pattern, std::vector<int> offsets = { 0 }, int extra = 0, bool relative = true, bool read = true);
  static int get_netvar(std::string name, std::string prop, std::string table, int offset = 0);
};