#pragma once

#include "UserCmd.hpp"

class c_verified_user_cmd {
  c_user_cmd cmd;
  unsigned long  crc;
};