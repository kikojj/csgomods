#pragma once

#include <Windows.h>
#include <fstream>
#include <string>
#include <fstream>
#include <filesystem>
#include <map>

#include "jsonxx/jsonxx.h"

#include "Skeleton.hpp"
#include "ColorRGBA.hpp"
#include "IGlowObjectDefinition.hpp"
#include "EntityQuality.hpp"
#include "ItemDefinitionIndex.hpp"
#include "TeamNum.hpp"

enum EVisualsGlowEspMode {
  VISUALS_GLOWESP_MODE_COLOR, VISUALS_GLOWESP_MODE_HP_BASED
};

struct ISkinchangerWeapon {
  bool enable = false;
  int paintKit = 0;
  EntityQuality quality = INVALID_QUALITY;
  float wear = 0.0001f;
  std::string customName = "";
  int statTrack = -1;
  int seed = 0;
  ItemDefinitionIndex itemDI;
};

struct IAimbotSettings {
  bool use = false;
  bool enable = false;
  float fov = 0.0f;
  Skeleton bone = NEAREST;
  float smooth = 0.0f;
  bool rcs_enable = false;
  float rcs_scale_x = 0.0f;
  float rcs_scale_y = 0.0f;
};

class Settings {
public:
  static colorRGBA getColorFromJsonXX(jsonxx::Value*);
  static jsonxx::Value rgbaToJsonXX(colorRGBA);

  static ISkinchangerWeapon getWeaponSkinFromJsonXX(jsonxx::Value*);
  static jsonxx::Value weaponSkinToJsonXX(ISkinchangerWeapon);

  static std::map<ItemDefinitionIndex, ISkinchangerWeapon> getWeaponSkinsFromJsonXX(jsonxx::Value*);
  static jsonxx::Value weaponSkinsToJsonXX(std::map<ItemDefinitionIndex, ISkinchangerWeapon>);
  static std::map<TeamNum, ISkinchangerWeapon> getKnifesSkinsFromJsonXX(jsonxx::Value*);
  static jsonxx::Value knifesSkinsToJsonXX(std::map<TeamNum, ISkinchangerWeapon>);

  static IAimbotSettings getAimbotSettingsFromJsonXX(jsonxx::Value*);
  static jsonxx::Value aimbotSettingsToJsonXX(IAimbotSettings);
  static std::map<ItemDefinitionIndex, IAimbotSettings> getAimbotWeaponsSettingsFromJsonXX(jsonxx::Value*);
  static jsonxx::Value aimbotWeaponsSettingsToJsonXX(std::map<ItemDefinitionIndex, IAimbotSettings>);

  static std::filesystem::path getConfigDirectoryPath();
  static void setValue(std::string, jsonxx::Value*);
  static jsonxx::Object toJsonxxObject();
  static bool getFromFile(std::string);
  static bool saveToFile(std::string);
  static bool deleteFile(std::string);
  static std::vector<std::string> getFilesList();
  static jsonxx::Array getFilesListAsJsonxxArray();

  //AIM BOT
  static bool aimbot_enable;
  static bool aimbot_use_key;
  static int aimbot_key;
  static int aimbot_delay_enemy;
  static bool aimbot_visible_check;
  static bool aimbot_flash_check;
  static bool aimbot_jump_check;
  static bool aimbot_friendly_fire;

  static IAimbotSettings aimbot_global;
  static IAimbotSettings aimbot_pistols;
  static IAimbotSettings aimbot_heavies;
  static IAimbotSettings aimbot_shoutguns;
  static IAimbotSettings aimbot_smgs;
  static IAimbotSettings aimbot_rifles;
  static IAimbotSettings aimbot_snipers;

  static std::map<ItemDefinitionIndex, IAimbotSettings> aimbot_weapons;

  //TRIGGER_BOT
  static bool triggerbot_enable;
  static bool triggerbot_use_key;
  static int triggerbot_key;
  static bool triggerbot_friendly_fire;
  static bool triggerbot_flash_check;
  static bool triggerbot_jump_check;
  static int triggerbot_delay_before_shoot;
  static int triggerbot_delay_after_shoot;
  static bool triggerbot_pistols_enable;
  static bool triggerbot_heavies_enable;
  static bool triggerbot_shoutguns_enable;
  static bool triggerbot_smgs_enable;
  static bool triggerbot_rifles_enable;
  static bool triggerbot_snipers_enable;

  //VISUALS
  static bool visuals_glowEsp_enable;
  static bool visuals_glowEsp_show_enemies;
  static bool visuals_glowEsp_show_friends;
  static EVisualsGlowEspMode visuals_glowEsp_mode;
  static GlowStyle visuals_glowEsp_style;
  //if color mode
  static colorRGBA visuals_glowEsp_enemy_visible_color;
  static colorRGBA visuals_glowEsp_enemy_invisible_color;
  static colorRGBA visuals_glowEsp_friends_color;
  //else if hp based mode
  static colorRGBA visuals_glowEsp_hpBased_0hp_color;
  static colorRGBA visuals_glowEsp_hpBased_100hp_color;
  //other
  static bool visuals_glowEsp_show_c4;
  static colorRGBA visuals_glowEsp_c4_color;
  static colorRGBA visuals_glowEsp_c4_planted_color;

  static bool visuals_chams_enable;
  static bool visuals_chams_show_enemies;
  static colorRGBA visuals_chams_enemy_color;
  static bool visuals_chams_show_friends;
  static colorRGBA visuals_chams_friends_color;

  //SKINCHANGER
  static bool skinchanger_enable;
  static std::map<ItemDefinitionIndex, ISkinchangerWeapon> skinchanger_weapons;
  static std::map<TeamNum, ISkinchangerWeapon> skinchanger_knifes;

  //MISC
  static bool misc_ingameRadar_enable;
  static bool misc_bhop_enable;
  static bool misc_autoPistols_enable;
  static int misc_autoPistols_delay;
  static bool misc_autoAccept_enable;
  static bool misc_antiFlash_enable;
  static int misc_antiFlash_maxAlpha;
};