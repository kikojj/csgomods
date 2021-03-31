#pragma once

#include <map>

#include "SDK/Engine/Engine.hpp"
#include "SDK/Client/Client.hpp"
#include "SDK/Client/BaseWeapon.hpp"
#include "SDK/Utils/Item.hpp"

#include "Utils/Helpers/Helpers.hpp"
#include "Utils/Offsets/Offsets.hpp"
#include "Utils/Settings/Settings.hpp"

class c_skinchanger {
private:
  void apply_weapon_settings(c_base_weapon, c_settings::s_skinchanger_weapon);
  void apply_knife_settings(c_base_weapon, c_settings::s_skinchanger_weapon);

public:
  c_skinchanger();
  void loop();
};