#pragma once

#define PROP_(type, name, base, offset, rType, wValue) \
type name(){\
  auto name = mem.read<rType>(base + offset);\
  return name;\
}\
void name(type value) {\
  mem.write(base + offset, wValue);\
}

#define PROP(type, name, base)      PROP_(type, name, base, Offsets::netvars::name, type, value)
#define C_PROP(type, name)          PROP(type, name, clientDll.dwBase)
#define E_PROP(type, name)          PROP(type, name, engineDll.dwBase)

#define PROP_PTR(type, name, base)  PROP_(type, name, base, Offsets::signatures::name, type, value)
#define C_PROP_PTR(type, name)      PROP_PTR(type, name, clientDll.dwBase)
#define E_PROP_PTR(type, name)      PROP_PTR(type, name, engineDll.dwBase)