#pragma once

#include <map>

#include "SDK/Engine/Engine.hpp"
#include "SDK/Client/Client.hpp"
#include "SDK/Client/BaseCombatWeapon.hpp"
#include "SDK/Utils/ItemDefinitionIndex.hpp"

#include "Utils/Helpers/Helpers.hpp"
#include "Utils/Offsets/Offsets.hpp"
#include "Utils/Settings/Settings.hpp"

class Skinchanger {
private:
  void applyWeaponSettings(BaseCombatWeapon, ISkinchangerWeapon);
  void applyKnifeSettings(BaseCombatWeapon, ISkinchangerWeapon);

public:
  Skinchanger();
  void loop();
};

extern Skinchanger skinchanger;