#pragma once

#include <map>

#include "SDK/Engine/Engine.hpp"
#include "SDK/Client/Client.hpp"
#include "SDK/Client/BaseWeapon.hpp"
#include "SDK/Utils/ItemDefinitionIndex.hpp"

#include "Utils/Helpers/Helpers.hpp"
#include "Utils/Offsets/Offsets.hpp"
#include "Utils/Settings/Settings.hpp"

class Skinchanger {
private:
  void applyWeaponSettings(BaseWeapon, ISkinchangerWeapon);
  void applyKnifeSettings(BaseWeapon, ISkinchangerWeapon);

public:
  Skinchanger();
  void loop();
};

extern Skinchanger skinchanger;