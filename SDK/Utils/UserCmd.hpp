#pragma once

#include "Vector.hpp"

class c_user_cmd {
public:
  virtual ~c_user_cmd() { };
  int     command_number;     // 0x04 For matching server and client commands for debugging
  int     tick_count;         // 0x08 the tick the client created this command
  s_vec3  view_angles;        // 0x0C Player instantaneous view angles.
  s_vec3  aim_direction;      // 0x18
  float   forward_move;       // 0x24
  float   side_move;          // 0x28
  float   up_move;            // 0x2C
  int     buttons;            // 0x30 Attack button states
  char    impulse;            // 0x34
  int     selected_weapon;    // 0x38 Current weapon id
  int     weapon_sub_type;    // 0x3C
  int     random_seed;        // 0x40 For shared random functions
  short   mouse_dx;           // 0x44 mouse accum in x from create move
  short   mouse_dy;           // 0x46 mouse accum in y from create move
  bool    has_been_predicted; // 0x48 Client only, tracks whether we've predicted this command at least once
  char    pad_0x4C[0x18];     // 0x4C Current sizeof( usercmd ) =  100  = 0x64
};