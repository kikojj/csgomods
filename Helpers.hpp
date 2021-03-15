#pragma once

#include <Windows.h>
#include <string>

#include "GlobalVars.hpp"
#include "Memory.hpp"
#include "Modules.hpp"
#include "Client.hpp"
#include "Engine.hpp"
#include "Offsets.hpp"

#include "ItemDefinitionIndex.hpp"

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