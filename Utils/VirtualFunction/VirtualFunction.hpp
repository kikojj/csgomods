#pragma once

#include <Windows.h>
#include <map>

#include "../Memory/Memory.hpp"

class VirtualFunction {
private:
  DWORD dwBase;
  std::map <int, DWORD> hooks;

  DWORD getVirtualFunction(int);

public:
  VirtualFunction(DWORD);
  void hook(int, DWORD);

};