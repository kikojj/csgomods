#pragma once

#include "Vector.hpp"

class CUserCmd {
public:
  virtual ~CUserCmd() { };
  int     commandNumber;      // 0x04 For matching server and client commands for debugging
  int     tickCount;          // 0x08 the tick the client created this command
  Vec3    viewAngles;         // 0x0C Player instantaneous view angles.
  Vec3    aimDirection;       // 0x18
  float   forwardMove;        // 0x24
  float   sideMove;           // 0x28
  float   upMove;             // 0x2C
  int     buttons;            // 0x30 Attack button states
  char    impulse;            // 0x34
  int     selectedWeapon;     // 0x38 Current weapon id
  int     weaponSubType;      // 0x3C
  int     randomSeed;        // 0x40 For shared random functions
  short   mouseDx;            // 0x44 mouse accum in x from create move
  short   mouseDy;            // 0x46 mouse accum in y from create move
  bool    hasBeenPredicted;   // 0x48 Client only, tracks whether we've predicted this command at least once
  char    pad_0x4C[0x18];     // 0x4C Current sizeof( usercmd ) =  100  = 0x64
};

struct VerifiedUserCmd {
  CUserCmd m_cmd;
  unsigned long  m_crc;
};