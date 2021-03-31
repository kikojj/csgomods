#pragma once

#include <Windows.h>
#include <map>

#include "../Memory/Memory.hpp"

class c_virtual_function {
private:
  DWORD base;
  std::map <int, DWORD> hooks;

  DWORD get_virtual_function(int);

public:
  c_virtual_function(DWORD);
  void hook(int, DWORD);

};