#pragma once

#include <functional>

#include "../Utils/Memory/Memory.hpp"

template<class T>
class c_prop {
private:
  std::function<int()> get_base;

public:
  c_prop(std::function<int()> get_base): get_base(get_base) {};
  void operator=(c_prop<T> prop) {
    this->get_base = prop.get_base;
  }

  T operator()() {
    return g_mem.read<T>(get_base());
  }
  bool operator=(T value) {
    return g_mem.write(get_base(), value);
  }
};

#define PROP_(type, name, base, offset) c_prop<type> name{ [this]()-> int { return (base + offset); } }

#define PROP(type, name, base)      PROP_(type, name, base, c_offsets::netvars::name, type, value)
#define C_PROP(type, name)          PROP(type, name, g_client_dll.base)
#define E_PROP(type, name)          PROP(type, name, g_engine_dll.base)

#define PROP_PTR(type, name, base)  PROP_(type, name, base, c_offsets::signatures::name, type, value)
#define C_PROP_PTR(type, name)      PROP_PTR(type, name, g_client_dll.base)
#define E_PROP_PTR(type, name)      PROP_PTR(type, name, g_engine_dll.base)