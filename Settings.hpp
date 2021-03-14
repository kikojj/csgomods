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

enum Visuals_glowEsp_mode {
  VISUALS_GLOWESP_MODE_COLOR, VISUALS_GLOWESP_MODE_HP_BASED
};

struct SkinchangerWeapon {
  bool enable = false;
  int paintKit = 0;
  EntityQuality quality = INVALID_QUALITY;
  float wear = 0.0001f;
  std::string customName = "";
  int statTrack = -1;
  int seed = 0;
  ItemDefinitionIndex itemDI;
};

class Settings {
public:
  static colorRGBA getColorFromJsonXX(jsonxx::Value*);
  static jsonxx::Value rgbaToJsonXX(colorRGBA);

  static std::map<ItemDefinitionIndex, SkinchangerWeapon> getWeaponSkinsFroJsonXX(jsonxx::Value*);
  static jsonxx::Value weaponSkinsToJsonXX(std::map<ItemDefinitionIndex, SkinchangerWeapon>);

  static std::map<TeamNum, SkinchangerWeapon> getKnifesSkinsFromJsonXX(jsonxx::Value*);
  static jsonxx::Value knifesSkinsToJsonXX(std::map<TeamNum, SkinchangerWeapon>);

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

  static bool aimbot_pistols_enable;
  static float aimbot_pistols_fov;
  static Skeleton aimbot_pistols_bone;
  static float aimbot_pistols_smooth;
  static bool aimbot_pistols_rcs_enable;
  static float aimbot_pistols_rcs_scale_x;
  static float aimbot_pistols_rcs_scale_y;

  static bool aimbot_heavies_enable;
  static float aimbot_heavies_fov;
  static Skeleton aimbot_heavies_bone;
  static float aimbot_heavies_smooth;
  static bool aimbot_heavies_rcs_enable;
  static float aimbot_heavies_rcs_scale_x;
  static float aimbot_heavies_rcs_scale_y;

  static bool aimbot_shoutguns_enable;
  static float aimbot_shoutguns_fov;
  static Skeleton aimbot_shoutguns_bone;
  static float aimbot_shoutguns_smooth;
  static bool aimbot_shoutguns_rcs_enable;
  static float aimbot_shoutguns_rcs_scale_x;
  static float aimbot_shoutguns_rcs_scale_y;

  static bool aimbot_smgs_enable;
  static float aimbot_smgs_fov;
  static Skeleton aimbot_smgs_bone;
  static float aimbot_smgs_smooth;
  static bool aimbot_smgs_rcs_enable;
  static float aimbot_smgs_rcs_scale_x;
  static float aimbot_smgs_rcs_scale_y;

  static bool aimbot_rifles_enable;
  static float aimbot_rifles_fov;
  static Skeleton aimbot_rifles_bone;
  static float aimbot_rifles_smooth;
  static bool aimbot_rifles_rcs_enable;
  static float aimbot_rifles_rcs_scale_x;
  static float aimbot_rifles_rcs_scale_y;

  static bool aimbot_snipers_enable;
  static float aimbot_snipers_fov;
  static Skeleton aimbot_snipers_bone;
  static float aimbot_snipers_smooth;
  static bool aimbot_snipers_rcs_enable;
  static float aimbot_snipers_rcs_scale_x;
  static float aimbot_snipers_rcs_scale_y;

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
  static Visuals_glowEsp_mode visuals_glowEsp_mode;
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
  static std::map<ItemDefinitionIndex, SkinchangerWeapon> skinchanger_weapons;
  static std::map<TeamNum, SkinchangerWeapon> skinchanger_knifes;

  //MISC
  static bool misc_ingameRadar_enable;
  static bool misc_bhop_enable;
  static bool misc_autoPistols_enable;
  static int misc_autoPistols_delay;
  static bool misc_autoAccept_enable;
};