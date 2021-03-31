#pragma once

#include <Windows.h>
#include <fstream>
#include <string>
#include <fstream>
#include <filesystem>
#include <map>

#include "../../SDK/Utils/Skeleton.hpp"
#include "../../SDK/Utils/ColorRGBA.hpp"
#include "../../SDK/Utils/GlowObjectDefinition.hpp"
#include "../../SDK/Utils/EntityQuality.hpp"
#include "../../SDK/Utils/Item.hpp"
#include "../../SDK/Utils/TeamNum.hpp"

#include "../JsonXX/jsonxx.h"

#pragma region Helper macros
#define IF_READ_SETTING_BOOL(setting_name) if (name == #setting_name) setting_name = value->get<bool>();
#define EL_IF_READ_SETTING_BOOL(setting_name) else if (name == #setting_name) setting_name = value->get<bool>();
#define EL_IF_READ_SETTING_INT(setting_name) else if (name == #setting_name) setting_name = (int)value->get<jsonxx::Number>();
#define EL_IF_READ_SETTING_FLOAT(setting_name) else if (name == #setting_name) setting_name = (float)value->get<jsonxx::Number>();
#define EL_IF_READ_SETTING_SKELETON(setting_name) else if (name == #setting_name) setting_name = (en_skeleton)value->get<jsonxx::Number>();
#define EL_IF_READ_SETTING_GLOW_MODE(setting_name) else if (name == #setting_name) setting_name = (en_visuals_glow_esp_mode)value->get<jsonxx::Number>();
#define EL_IF_READ_SETTING_GLOW_STYLE(setting_name) else if (name == #setting_name) setting_name = (en_glow_style)value->get<jsonxx::Number>();
#define EL_IF_READ_SETTING_AIM(setting_name) else if (name == #setting_name) setting_name = get_aimbot_settings_from_jsonxx(value);
#define EL_IF_READ_SETTING_AIM_WEAPONS(setting_name) else if (name == #setting_name) setting_name = get_aimbot_weapons_settings_from_jsonxx(value);
#define EL_IF_READ_SETTING_SKINCHANGER_WEAPONS(setting_name) else if (name == #setting_name) setting_name = get_weapon_skins_from_jsonxx(value);
#define EL_IF_READ_SETTING_SKINCHANGER_KNIVES(setting_name) else if (name == #setting_name) setting_name = get_knives_skins_from_jsonxx(value);
#define EL_IF_READ_SETTING_COLOR(setting_name) else if (name == #setting_name) setting_name = get_color_from_jsonxx(value);

#define SET_SETTING(setting_name) << #setting_name << c_settings::setting_name
#define SET_SETTING_INT(setting_name) << #setting_name << (int)c_settings::setting_name
#define SET_SETTING_COLOR(setting_name) << #setting_name << rgba_to_jsonxx(c_settings::setting_name)
#define SET_SETTING_AIM(setting_name) << #setting_name << aimbot_settings_to_jsonxx(c_settings::setting_name)
#define SET_SETTING_AIM_WEAPONS(setting_name) << #setting_name << aimbot_weapons_settings_to_jsonxx(c_settings::setting_name)
#define SET_SETTING_SKINCHANGER_WEAPONS(setting_name) << #setting_name << weapon_skins_to_jsonxx(c_settings::setting_name)
#define SET_SETTING_SKINCHANGER_KNIVES(setting_name) << #setting_name << knives_skins_to_jsonxx(c_settings::setting_name)
#pragma endregion

class c_settings {
public:
  enum struct en_visuals_glow_esp_mode {
    Color,
    HpBased
  };
  struct s_skinchanger_weapon {
    bool enable = false;
    int paint_kit = 0;
    en_entity_quality quality = en_entity_quality::Invalid;
    float wear = 0.0001f;
    std::string custom_name = "";
    int stat_track = -1;
    int seed = 0;
    c_item::en_defenition_index item_di;
  };
  struct s_aimbot_settings {
    bool use = false;
    bool enable = false;
    bool first_perfect_shoot = false;
    float fov = 0.0f;
    en_skeleton bone = en_skeleton::Nearest;
    bool change_after_nearest = false;
    float smooth = 0.0f;
    bool rcs_enable = false;
    float rcs_scale_x = 0.0f;
    float rcs_scale_y = 0.0f;
  };

  static s_color_rgba get_color_from_jsonxx(jsonxx::Value*);
  static jsonxx::Value rgba_to_jsonxx(s_color_rgba);
  static s_skinchanger_weapon get_weapon_skin_from_jsonxx(jsonxx::Value*);
  static jsonxx::Value weapon_skin_to_jsonxx(s_skinchanger_weapon);
  static s_aimbot_settings get_aimbot_settings_from_jsonxx(jsonxx::Value*);
  static jsonxx::Value aimbot_settings_to_jsonxx(s_aimbot_settings);

  static std::map<c_item::en_defenition_index, s_skinchanger_weapon> get_weapon_skins_from_jsonxx(jsonxx::Value*);
  static jsonxx::Value weapon_skins_to_jsonxx(std::map<c_item::en_defenition_index, s_skinchanger_weapon>);
  static std::map<en_team_num, s_skinchanger_weapon> get_knives_skins_from_jsonxx(jsonxx::Value*);
  static jsonxx::Value knives_skins_to_jsonxx(std::map<en_team_num, s_skinchanger_weapon>);
  static std::map<c_item::en_defenition_index, s_aimbot_settings> get_aimbot_weapons_settings_from_jsonxx(jsonxx::Value*);
  static jsonxx::Value aimbot_weapons_settings_to_jsonxx(std::map<c_item::en_defenition_index, s_aimbot_settings>);

  static std::filesystem::path get_config_directory_path();
  static void set_value(std::string, jsonxx::Value*);
  static jsonxx::Object to_jsonxx_object();
  static bool get_from_file(std::string);
  static bool save_to_file(std::string);
  static bool delete_file(std::string);

  static std::vector<std::string> get_files_list();
  static jsonxx::Array get_files_list_as_jsonxx_array();

  #pragma region Variables
  //AIM BOT
  static bool   aimbot_enable;
  static bool   aimbot_use_key;
  static int    aimbot_key;
  static int    aimbot_delay_enemy;
  static bool   aimbot_visible_check;
  static bool   aimbot_smoke_check;
  static bool   aimbot_flash_check;
  static bool   aimbot_jump_check;
  static bool   aimbot_friendly_fire;

  static s_aimbot_settings aimbot_global;
  static s_aimbot_settings aimbot_pistols;
  static s_aimbot_settings aimbot_heavies;
  static s_aimbot_settings aimbot_shoutguns;
  static s_aimbot_settings aimbot_smgs;
  static s_aimbot_settings aimbot_rifles;
  static s_aimbot_settings aimbot_snipers;

  static std::map<c_item::en_defenition_index, s_aimbot_settings> aimbot_weapons;

  //TRIGGER_BOT
  static bool   triggerbot_enable;
  static bool   triggerbot_use_key;
  static int    triggerbot_key;
  static bool   triggerbot_friendly_fire;
  static bool   triggerbot_flash_check;
  static bool   triggerbot_jump_check;
  static int    triggerbot_delay_before_shoot;
  static int    triggerbot_delay_after_shoot;
  static bool   triggerbot_pistols_enable;
  static bool   triggerbot_heavies_enable;
  static bool   triggerbot_shoutguns_enable;
  static bool   triggerbot_smgs_enable;
  static bool   triggerbot_rifles_enable;
  static bool   triggerbot_snipers_enable;

  //VISUALS
  static bool                     visuals_glow_esp_enable;
  static bool                     visuals_glow_esp_show_enemies;
  static bool                     visuals_glow_esp_show_friends;
  static en_visuals_glow_esp_mode visuals_glow_esp_mode;
  static en_glow_style            visuals_glow_esp_style;
  //if color mode
  static s_color_rgba             visuals_glow_esp_enemy_visible_color;
  static s_color_rgba             visuals_glow_esp_enemy_invisible_color;
  static s_color_rgba             visuals_glow_esp_friends_color;
  //else if hp based mode
  static s_color_rgba             visuals_glow_esp_hp_based_0hp_color;
  static s_color_rgba             visuals_glow_esp_hp_based_100hp_color;
  //other
  static bool                     visuals_glow_esp_show_c4;
  static s_color_rgba             visuals_glow_esp_c4_color;
  static s_color_rgba             visuals_glow_esp_c4_planted_color;
  static bool                     visuals_glow_esp_show_defusing;
  static s_color_rgba             visuals_glow_esp_defusing_color;
  static bool                     visuals_glow_esp_show_grenades;
  static s_color_rgba             visuals_glow_esp_grenades_color;
  //chams
  static bool                     visuals_chams_enable;
  static bool                     visuals_chams_show_enemies;
  static s_color_rgba             visuals_chams_enemy_color;
  static bool                     visuals_chams_show_friends;
  static s_color_rgba             visuals_chams_friends_color;

  //SKINCHANGER
  static bool                                                         skinchanger_enable;
  static std::map<c_item::en_defenition_index, s_skinchanger_weapon>  skinchanger_weapons;
  static std::map<en_team_num, s_skinchanger_weapon>                  skinchanger_knives;

  //MISC
  static bool misc_ingame_radar_enable;
  static bool misc_bhop_enable;
  static bool misc_auto_pistols_enable;
  static int  misc_auto_pistols_delay;
  static bool misc_auto_accept_enable;
  static bool misc_anti_flash_enable;
  static int misc_anti_flash_max_alpha;
  #pragma endregion
};