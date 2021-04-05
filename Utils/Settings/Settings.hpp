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
#define IF_READ_SETTING_CLASS(setting_name, class_name) if (name == #setting_name) setting_name = class_name::get(value);
#define IF_READ_SETTING_CLASS_MAP(setting_name, class_name, first_type) if (name == #setting_name) setting_name = class_name::map_get<first_type>(value);
#define EL_IF_READ_SETTING_CLASS(setting_name, class_name) else if (name == #setting_name) setting_name = class_name::get(value);
#define EL_IF_READ_SETTING_CLASS_MAP(setting_name, class_name, first_type) else if (name == #setting_name) setting_name = class_name::map_get<first_type>(value);

#define SET_SETTING(setting_name) << #setting_name << c_settings::setting_name
#define SET_SETTING_INT(setting_name) << #setting_name << (int)c_settings::setting_name
#define SET_SETTING_CLASS(setting_name) << #setting_name << c_settings::setting_name.json()
#define SET_SETTING_CLASS_MAP(setting_name, class_name, first_type) << #setting_name << class_name::map_json<first_type>(c_settings::setting_name)
#pragma endregion

class c_settings {
//main types for settings
public:
  enum struct en_glow_mode: int {
    Color,
    HpBased
  };
  struct s_settings_color : public s_color_rgba{
    jsonxx::Object json() {
      jsonxx::Object js_obj;
      js_obj
        << "r" << r
        << "g" << g
        << "b" << b
        << "a" << a;
      return js_obj;
    }
    static s_settings_color get(jsonxx::Object js_obj_color) {
      s_settings_color color{ 0,0,0,0 };

      if (js_obj_color.has<jsonxx::Number>("r")) {
        color.r = (float)js_obj_color.get<jsonxx::Number>("r");
      }
      if (js_obj_color.has<jsonxx::Number>("g")) {
        color.g = (float)js_obj_color.get<jsonxx::Number>("g");
      }
      if (js_obj_color.has<jsonxx::Number>("b")) {
        color.b = (float)js_obj_color.get<jsonxx::Number>("b");
      }
      if (js_obj_color.has<jsonxx::Number>("a")) {
        color.a = (float)js_obj_color.get<jsonxx::Number>("a");
      }

      return color;
    }
    static s_settings_color get(jsonxx::Value* value) {
      return get(value->get<jsonxx::Object>());
    }
  };
  struct s_glow_esp_settings {
    bool              enable = false;
    en_glow_mode      mode = en_glow_mode::Color;
    en_glow_style     style = en_glow_style::FullBody;
    s_settings_color  visible_color = { 0,0,0,0 };
    s_settings_color  invisible_color = { 0,0,0,0 };
    s_settings_color  hp_based_0hp_color = { 0,0,0,0 };
    s_settings_color  hp_based_100hp_color = { 0,0,0,0 };

    jsonxx::Object json() {
      jsonxx::Object js_obj;
      js_obj
        << "enable" << enable
        << "mode" << (int)mode
        << "style" << (int)style
        << "visible_color" << visible_color.json()
        << "invisible_color" << invisible_color.json()
        << "hp_based_0hp_color" << hp_based_0hp_color.json()
        << "hp_based_100hp_color" << hp_based_100hp_color.json();
      return js_obj;
    }
    static s_glow_esp_settings get(jsonxx::Object js_obj) {
      s_glow_esp_settings settings;

      if (js_obj.has<jsonxx::Boolean>("enable")) {
        settings.enable = js_obj.get<jsonxx::Boolean>("enable");
      }
      if (js_obj.has<jsonxx::Number>("mode")) {
        settings.mode = en_glow_mode((int)js_obj.get<jsonxx::Number>("mode"));
      }
      if (js_obj.has<jsonxx::Number>("style")) {
        settings.style = en_glow_style((int)js_obj.get<jsonxx::Number>("style"));
      }
      if (js_obj.has<jsonxx::Object>("visible_color")) {
        settings.visible_color = s_settings_color::get(js_obj.get<jsonxx::Object>("visible_color"));
      }
      if (js_obj.has<jsonxx::Object>("invisible_color")) {
        settings.invisible_color = s_settings_color::get(js_obj.get<jsonxx::Object>("invisible_color"));
      }
      if (js_obj.has<jsonxx::Object>("hp_based_0hp_color")) {
        settings.hp_based_0hp_color = s_settings_color::get(js_obj.get<jsonxx::Object>("hp_based_0hp_color"));
      }
      if (js_obj.has<jsonxx::Object>("hp_based_100hp_color")) {
        settings.hp_based_100hp_color = s_settings_color::get(js_obj.get<jsonxx::Object>("hp_based_100hp_color"));
      }

      return settings;
    }
    static s_glow_esp_settings get(jsonxx::Value* value) {
      return get(value->get<jsonxx::Object>());
    }
  };
  struct s_chams_settings {
    bool              enable = false;
    s_settings_color  color = { 0,0,0,0 };

    jsonxx::Object json() {
      jsonxx::Object js_obj;

      js_obj
        << "enable" << enable
        << "color" << color.json();

      return js_obj;
    }
    static s_chams_settings get(jsonxx::Object js_obj) {
      s_chams_settings settings;

      if (js_obj.has<jsonxx::Boolean>("enable")) {
        settings.enable = js_obj.get<jsonxx::Boolean>("enable");
      }
      if (js_obj.has<jsonxx::Object>("color")) {
        settings.color = s_settings_color::get(js_obj.get<jsonxx::Object>("color"));
      }

      return settings;
    }
    static s_chams_settings get(jsonxx::Value* value) {
      return get(value->get<jsonxx::Object>());
    }
  };
  struct s_aimbot_settings {
    bool        use = false;
    bool        enable = false;
    float       fov = 0.0f;
    float       smooth = 0.0f;
    en_skeleton bone = en_skeleton::Nearest;
    bool        first_perfect_shoot = false;
    bool        change_after_nearest = false;
    bool        rcs_enable = false;
    float       rcs_scale_x = 0.0f;
    float       rcs_scale_y = 0.0f;

    jsonxx::Object json() {
      jsonxx::Object js_obj;

      js_obj
        << "use" << use
        << "enable" << enable
        << "fov" << fov
        << "smooth" << smooth
        << "bone" << (int)bone
        << "first_perfect_shoot" << first_perfect_shoot
        << "change_after_nearest" << change_after_nearest
        << "rcs_enable" << rcs_enable
        << "rcs_scale_x" << rcs_scale_x
        << "rcs_scale_y" << rcs_scale_y;

      return js_obj;
    }
    static s_aimbot_settings get(jsonxx::Object js_obj) {
      s_aimbot_settings settings;

      if (js_obj.has<jsonxx::Boolean>("use")) {
        settings.use = js_obj.get<jsonxx::Boolean>("use");
      }
      if (js_obj.has<jsonxx::Boolean>("enable")) {
        settings.enable = js_obj.get<jsonxx::Boolean>("enable");
      }
      if (js_obj.has<jsonxx::Number>("fov")) {
        settings.fov = (float)js_obj.get<jsonxx::Number>("fov");
      }
      if (js_obj.has<jsonxx::Number>("smooth")) {
        settings.smooth = (float)js_obj.get<jsonxx::Number>("smooth");
      }
      if (js_obj.has<jsonxx::Number>("bone")) {
        settings.bone = en_skeleton((int)js_obj.get<jsonxx::Number>("bone"));
      }
      if (js_obj.has<jsonxx::Boolean>("first_perfect_shoot")) {
        settings.first_perfect_shoot = js_obj.get<jsonxx::Boolean>("first_perfect_shoot");
      }
      if (js_obj.has<jsonxx::Boolean>("change_after_nearest")) {
        settings.change_after_nearest = js_obj.get<jsonxx::Boolean>("change_after_nearest");
      }
      if (js_obj.has<jsonxx::Boolean>("rcs_enable")) {
        settings.rcs_enable = js_obj.get<jsonxx::Boolean>("rcs_enable");
      }
      if (js_obj.has<jsonxx::Number>("rcs_scale_x")) {
        settings.rcs_scale_x = (float)js_obj.get<jsonxx::Number>("rcs_scale_x");
      }
      if (js_obj.has<jsonxx::Number>("rcs_scale_y")) {
        settings.rcs_scale_y = (float)js_obj.get<jsonxx::Number>("rcs_scale_y");
      }

      return settings;
    }
    static s_aimbot_settings get(jsonxx::Value* value) {
      return get(value->get<jsonxx::Object>());
    }

    template<class T>
    static jsonxx::Object map_json(std::map<T, s_aimbot_settings> map_data) {
      jsonxx::Object js_obj;

      for (auto data : map_data) {
        js_obj << std::to_string((int)data.first) << data.second.json();
      }

      return js_obj;
    }
    template<class T>
    static std::map<T, s_aimbot_settings> map_get(jsonxx::Object js_obj) {
      std::map<T, s_aimbot_settings> map_data;

      for (auto skin_obj : js_obj.kv_map()) {
        map_data[(T)stoi(skin_obj.first)] = s_aimbot_settings::get(skin_obj.second);
      }

      return map_data;
    }
    template<class T>
    static std::map<T, s_aimbot_settings> map_get(jsonxx::Value* value) {
      return map_get<T>(value->get<jsonxx::Object>());
    }
  };
  struct s_skinchanger_weapon {
    bool                          enable = false;
    int                           paint_kit = 0;
    float                         wear = 0.0001f;
    en_entity_quality             quality = en_entity_quality::Invalid;
    int                           seed = 0;
    std::string                   custom_name = "";
    int                           stat_track = -1;
    c_item::en_defenition_index   item_di = c_item::en_defenition_index::Invalid;

    jsonxx::Object json() {
      jsonxx::Object js_obj;

      js_obj
        << "enable" << enable
        << "paint_kit" << paint_kit
        << "wear" << wear
        << "quality" << (int)quality
        << "seed" << seed
        << "custom_name" << custom_name
        << "stat_track" << stat_track
        << "item_di" << (int)item_di;

      return js_obj;
    }
    static s_skinchanger_weapon get(jsonxx::Object js_obj) {
      s_skinchanger_weapon settings;

      if (js_obj.has<jsonxx::Boolean>("enable")) {
        settings.enable = js_obj.get<jsonxx::Boolean>("enable");
      }
      if (js_obj.has<jsonxx::Number>("paint_kit")) {
        settings.paint_kit = (int)js_obj.get<jsonxx::Number>("paint_kit");
      }
      if (js_obj.has<jsonxx::Number>("wear")) {
        settings.wear = (float)js_obj.get<jsonxx::Number>("wear");
      }
      if (js_obj.has<jsonxx::Number>("quality")) {
        settings.quality = en_entity_quality((int)js_obj.get<jsonxx::Number>("quality"));
      }
      if (js_obj.has<jsonxx::Number>("seed")) {
        settings.seed = (int)js_obj.get<jsonxx::Number>("seed");
      }
      if (js_obj.has<jsonxx::String>("custom_name")) {
        settings.custom_name = js_obj.get<jsonxx::String>("custom_name");
      }
      if (js_obj.has<jsonxx::Number>("stat_track")) {
        settings.stat_track = (int)js_obj.get<jsonxx::Number>("stat_track");
      }
      if (js_obj.has<jsonxx::Number>("item_di")) {
        settings.item_di = c_item::en_defenition_index((int)js_obj.get<jsonxx::Number>("item_di"));
      }

      return settings;
    }
    static s_skinchanger_weapon get(jsonxx::Value* value) {
      return get(value->get<jsonxx::Object>());
    }

    template<class T>
    static jsonxx::Object map_json(std::map<T, s_skinchanger_weapon> map_data) {
      jsonxx::Object js_obj;

      for (auto data : map_data) {
        js_obj << std::to_string((int)data.first) << data.second.json();
      }

      return js_obj;
    }
    template<class T>
    static std::map<T, s_skinchanger_weapon> map_get(jsonxx::Object js_obj) {
      std::map<T, s_skinchanger_weapon> map_data;

      for (auto skin_obj : js_obj.kv_map()) {
        map_data[(T)stoi(skin_obj.first)] = s_skinchanger_weapon::get(skin_obj.second);
      }

      return map_data;
    }
    template<class T>
    static std::map<T, s_skinchanger_weapon> map_get(jsonxx::Value* value) {
      return map_get<T>(value->get<jsonxx::Object>());
    }
  };
  struct s_personal_settings {
    bool                enable = false;
    s_glow_esp_settings glow_settings;
    s_chams_settings    chams_settings;

    jsonxx::Object json() {
      jsonxx::Object js_obj;

      js_obj
        << "enable" << enable
        << "glow_settings" << glow_settings.json()
        << "chams_settings" << chams_settings.json();

      return js_obj;
    }
    static s_personal_settings get(jsonxx::Object js_obj) {
      s_personal_settings settings;

      if (js_obj.has<jsonxx::Boolean>("enable")) {
        settings.enable = js_obj.get<jsonxx::Boolean>("enable");
      }
      if (js_obj.has<jsonxx::Object>("glow_settings")) {
        settings.glow_settings = s_glow_esp_settings::get(js_obj.get<jsonxx::Object>("glow_settings"));
      }
      if (js_obj.has<jsonxx::Object>("chams_settings")) {
        settings.chams_settings = s_chams_settings::get(js_obj.get<jsonxx::Object>("chams_settings"));
      }

      return settings;
    }
    static s_personal_settings get(jsonxx::Value* value) {
      return get(value->get<jsonxx::Object>());
    }

    template<class T>
    static jsonxx::Object map_json(std::map<T, s_personal_settings> map_data) {
      jsonxx::Object js_obj;

      for (auto data : map_data) {
        js_obj << std::to_string((int)data.first) << data.second.json();
      }

      return js_obj;
    }
    template<class T>
    static std::map<T, s_personal_settings> map_get(jsonxx::Object js_obj) {
      std::map<T, s_personal_settings> map_data;

      for (auto skin_obj : js_obj.kv_map()) {
        map_data[(T)stoi(skin_obj.first)] = s_personal_settings::get(skin_obj.second);
      }

      return map_data;
    }
    template<class T>
    static std::map<T, s_personal_settings> map_get(jsonxx::Value* value) {
      return map_get<T>(value->get<jsonxx::Object>());
    }
  };

//utils methods
 public:
  static std::filesystem::path get_config_directory_path();
  static bool get_from_file(std::string);
  static bool save_to_file(std::string);
  static bool delete_file(std::string);
  static std::vector<std::string> get_files_list();
  static jsonxx::Array get_files_list_as_jsonxx_array();

//main methods
 public:
  static void set_value(std::string, jsonxx::Value*, bool = true);
  static jsonxx::Object to_jsonxx_object(bool = true);

//varibales
public:
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
  static s_glow_esp_settings      visuals_glow_esp_enemies;
  static s_glow_esp_settings      visuals_glow_esp_friends;
  static s_glow_esp_settings      visuals_glow_esp_c4;
  static s_glow_esp_settings      visuals_glow_esp_defusing;
  static s_glow_esp_settings      visuals_glow_esp_grenades;
  static bool                     visuals_chams_enable;
  static s_chams_settings         visuals_chams_friends;
  static s_chams_settings         visuals_chams_enemies;

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

  //PERSONAL SETTINGS
  static std::map<int, s_personal_settings> personal_settings;
  #pragma endregion
};