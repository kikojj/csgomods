#pragma once

#define PROP_(type, name, base, offset, rType, wValue) \
type name(){\
  auto name = g_mem.read<rType>(base + offset);\
  return name;\
}\
void name(type value) {\
  g_mem.write(base + offset, wValue);\
}

#define PROP(type, name, base)      PROP_(type, name, base, c_offsets::netvars::name, type, value)
#define C_PROP(type, name)          PROP(type, name, g_client_dll.base)
#define E_PROP(type, name)          PROP(type, name, g_engine_dll.base)

#define PROP_PTR(type, name, base)  PROP_(type, name, base, c_offsets::signatures::name, type, value)
#define C_PROP_PTR(type, name)      PROP_PTR(type, name, g_client_dll.base)
#define E_PROP_PTR(type, name)      PROP_PTR(type, name, g_engine_dll.base)