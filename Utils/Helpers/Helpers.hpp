#pragma once

#include <Windows.h>
#include <string>

#include "../../SDK/Client/Client.hpp"
#include "../../SDK/Engine/Engine.hpp"
#include "../../SDK/Utils/ItemDefinitionIndex.hpp"

#include "../GlobalVars.hpp"
#include "../Memory/Memory.hpp"
#include "../Memory/Modules.hpp"
#include "../Offsets/Offsets.hpp"

class Helpers {
public:
  static void shoot();
  static void jump();
  static void keyboardPressKey(int key);
  static void toggleSteamOverlay();
  static bool isMouseActive();
  static bool isFlashed(float);
  static void exit();
  static int getModelIndex(std::string);
  static int getModelIndex(ItemDefinitionIndex);
  static void updateModelIndexes();
  static void fullForceUpdate();
};