#pragma once
#include <map>

#include "Offsets.hpp"
#include "Settings.hpp"

#include "Engine.hpp"
#include "Client.hpp"
#include "Helpers.hpp"

#include "BaseCombatWeapon.hpp"

#include "ItemDefinitionIndex.hpp"

class Skinchanger {
private:
  void applyWeaponSettings(BaseCombatWeapon, SkinchangerWeapon);
  void applyKnifeSettings(BaseCombatWeapon, SkinchangerWeapon);

public:
  Skinchanger();
  void loop();
};

extern Skinchanger skinchanger;