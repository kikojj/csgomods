#pragma once

#include <Windows.h>

#include "../../Utils/Memory/Memory.hpp"
#include "../../Utils/Memory/Modules.hpp"
#include "../../Utils/Offsets/Offsets.hpp"

#include "../Vars.hpp"

class GlobalVars {
public:
  GlobalVars() {};

  int get() {
    return mem.read<int>(clientDll.dwBase + Offsets::signatures::dwGlobalVars);
  }

public:
  PROP_(float,  realTime,                     get(), 0x0000, float, value)
  PROP_(int,    frameCount,                   get(), 0x0004, int,   value)
  PROP_(float,  absoluteFrameTime,            get(), 0x0008, float, value)
  PROP_(float,  absoluteFrameStartTimeStdDev, get(), 0x000C, float, value)
  PROP_(float,  curTime,                      get(), 0x0010, float, value)
  PROP_(float,  frameTime,                    get(), 0x0014, float, value)
  PROP_(int,    maxClients,                   get(), 0x0018, int,   value)
  PROP_(int,    tickCount,                    get(), 0x001C, int,   value)
  PROP_(float,  intervalPerTick,              get(), 0x0020, float, value)
  PROP_(float,  interpolationAmount,          get(), 0x0024, float, value)
  PROP_(int,    simTicksThisFrame,            get(), 0x0028, int,   value)
  PROP_(int,    networkProtocol,              get(), 0x002C, int,   value)
};

/*
struct IGlobalVars{
public:
  float     realTime;                     // 0x0000
  int       frameCount;                   // 0x0004
  float     absoluteFrameTime;            // 0x0008
  float     absoluteFrameStartTimeStdDev; // 0x000C
  float     curTime;                      // 0x0010
  float     frameTime;                    // 0x0014
  int       maxClients;                   // 0x0018
  int       tickCount;                    // 0x001C
  float     intervalPerTick;              // 0x0020
  float     interpolationAmount;          // 0x0024
  int       simTicksThisFrame;            // 0x0028
  int       networkProtocol;              // 0x002C
  void*     pSaveData;                    // 0x0030
  bool      m_bClient;                    // 0x0031
  bool      m_bRemoteClient;              // 0x0032

private:
  // 100 (i.e., tickcount is rounded down to this base and then the "delta" from this base is networked
  int       nTimestampNetworkingBase;
  // 32 (entindex() % nTimestampRandomizeWindow ) is subtracted from gpGlobals->tickcount to Set the networking basis, prevents
  //  all of the entities from forcing a new PackedEntity on the same tick (i.e., prevents them from getting lockstepped on this)
  int       nTimestampRandomizeWindow;
};
*/