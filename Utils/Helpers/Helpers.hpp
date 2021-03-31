#pragma once

#include <Windows.h>
#include <string>

#include "../../SDK/Client/Client.hpp"
#include "../../SDK/Engine/Engine.hpp"
#include "../../SDK/Utils/Item.hpp"

#include "../GlobalVars.hpp"
#include "../Memory/Memory.hpp"
#include "../Memory/Modules.hpp"
#include "../Offsets/Offsets.hpp"

class c_helpers {
public:
  static void shoot();
  static void jump();
  static void keyboard_press_key(int key);
  static void toggle_steam_overlay();
  static bool is_mouse_active();
  static bool is_flashed(float);
  static void exit();
  static int get_model_index(std::string);
  static int get_model_index(c_item::en_defenition_index);
  static void update_model_indexes();
  static void full_force_update();
};