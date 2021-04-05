#include "Settings.hpp"

#pragma region Files
std::filesystem::path c_settings::get_config_directory_path() {
	return std::filesystem::temp_directory_path() / "csgomods";
}

bool c_settings::get_from_file(std::string file_name) {
	if (!std::filesystem::exists(get_config_directory_path())) {
		return false;
	}

	auto path = get_config_directory_path() / file_name;
	if (!std::filesystem::exists(path)) {
		return false;
	}

	try {
		std::fstream f(path);
		std::string str_json_buffer((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
		jsonxx::Object js_obj_settings;
		js_obj_settings.parse(str_json_buffer);

		for (auto prop: js_obj_settings.kv_map()) {
			set_value(prop.first, prop.second);
		}
		std::cout << "[Settings]: Loaded from '" << file_name << "'." << std::endl;
		f.close();
	}
	catch (const std::exception&) {
		return false;
	}
	return true;
}

bool c_settings::save_to_file(std::string file_name) {
	if (!std::filesystem::exists(get_config_directory_path())) {
		std::filesystem::create_directories(get_config_directory_path());
	}

	try {
		auto path = get_config_directory_path() / file_name;

		std::ofstream f(path);
		f << to_jsonxx_object().json();
		f.close();

		std::cout << "[Settings]: Saved to '" << file_name << "'." << std::endl;
	}
	catch (const std::exception&) {
		return false;
	}
	return true;
}

bool c_settings::delete_file(std::string file_name) {
	if (!std::filesystem::exists(get_config_directory_path())) {
		return false;
	}

	auto path = get_config_directory_path() / file_name;
	if (!std::filesystem::exists(path)) {
		return false;
	}

	if (!std::remove(path.string().c_str())) {
		return false;
	}

	return true;
}

std::vector<std::string> c_settings::get_files_list() {
	std::vector<std::string> vec_files_list;

	if (!std::filesystem::exists(get_config_directory_path())) {
		return vec_files_list;
	}

	auto iter_directory = std::filesystem::directory_iterator(get_config_directory_path());
	for (auto entry: iter_directory) {
		if (!entry.is_directory()) {
			vec_files_list.push_back(entry.path().filename().string());
		}
	}

	return vec_files_list;
}

jsonxx::Array c_settings::get_files_list_as_jsonxx_array() {
	jsonxx::Array files_list;
	for (auto str_file_name : get_files_list()) {
		files_list << jsonxx::Value(str_file_name);
	}
	return files_list;
}
#pragma endregion

void c_settings::set_value(std::string name, jsonxx::Value* value, bool is_set_from_file) {
	//AIMBOT
	IF_READ_SETTING_BOOL(aimbot_enable)
	EL_IF_READ_SETTING_INT(aimbot_key)
	EL_IF_READ_SETTING_BOOL(aimbot_use_key)
	EL_IF_READ_SETTING_INT(aimbot_delay_enemy)
	EL_IF_READ_SETTING_BOOL(aimbot_visible_check)
	EL_IF_READ_SETTING_BOOL(aimbot_smoke_check)
	EL_IF_READ_SETTING_BOOL(aimbot_flash_check)
	EL_IF_READ_SETTING_BOOL(aimbot_jump_check)
	EL_IF_READ_SETTING_BOOL(aimbot_friendly_fire)

	EL_IF_READ_SETTING_CLASS(aimbot_global, s_aimbot_settings)
	EL_IF_READ_SETTING_CLASS(aimbot_pistols, s_aimbot_settings)
	EL_IF_READ_SETTING_CLASS(aimbot_heavies, s_aimbot_settings)
	EL_IF_READ_SETTING_CLASS(aimbot_shoutguns, s_aimbot_settings)
	EL_IF_READ_SETTING_CLASS(aimbot_smgs, s_aimbot_settings)
	EL_IF_READ_SETTING_CLASS(aimbot_rifles, s_aimbot_settings)
	EL_IF_READ_SETTING_CLASS(aimbot_snipers, s_aimbot_settings)
	EL_IF_READ_SETTING_CLASS_MAP(aimbot_weapons, s_aimbot_settings, c_item::en_defenition_index)

	//TRIGGERBOT
	EL_IF_READ_SETTING_BOOL(triggerbot_enable)
	EL_IF_READ_SETTING_BOOL(triggerbot_use_key)
	EL_IF_READ_SETTING_INT(triggerbot_key)
	EL_IF_READ_SETTING_BOOL(triggerbot_friendly_fire)
	EL_IF_READ_SETTING_BOOL(triggerbot_flash_check)
	EL_IF_READ_SETTING_BOOL(triggerbot_jump_check)
	EL_IF_READ_SETTING_INT(triggerbot_delay_before_shoot)
	EL_IF_READ_SETTING_INT(triggerbot_delay_after_shoot)

	EL_IF_READ_SETTING_BOOL(triggerbot_pistols_enable)
	EL_IF_READ_SETTING_BOOL(triggerbot_shoutguns_enable)
	EL_IF_READ_SETTING_BOOL(triggerbot_smgs_enable)
	EL_IF_READ_SETTING_BOOL(triggerbot_rifles_enable)
	EL_IF_READ_SETTING_BOOL(triggerbot_snipers_enable)

	//VISUALS
	EL_IF_READ_SETTING_BOOL(visuals_glow_esp_enable)
	EL_IF_READ_SETTING_CLASS(visuals_glow_esp_enemies, s_glow_esp_settings)
	EL_IF_READ_SETTING_CLASS(visuals_glow_esp_friends, s_glow_esp_settings)
	EL_IF_READ_SETTING_CLASS(visuals_glow_esp_c4, s_glow_esp_settings)
	EL_IF_READ_SETTING_CLASS(visuals_glow_esp_defusing, s_glow_esp_settings)
	EL_IF_READ_SETTING_CLASS(visuals_glow_esp_grenades, s_glow_esp_settings)

	EL_IF_READ_SETTING_BOOL(visuals_chams_enable)
	EL_IF_READ_SETTING_CLASS(visuals_chams_friends, s_chams_settings)
	EL_IF_READ_SETTING_CLASS(visuals_chams_enemies, s_chams_settings)

	//SKINCHANGER
	EL_IF_READ_SETTING_BOOL(skinchanger_enable)
	EL_IF_READ_SETTING_CLASS_MAP(skinchanger_weapons, s_skinchanger_weapon, c_item::en_defenition_index)
	EL_IF_READ_SETTING_CLASS_MAP(skinchanger_knives, s_skinchanger_weapon, en_team_num)

	//MISC
	EL_IF_READ_SETTING_BOOL(misc_ingame_radar_enable)
	EL_IF_READ_SETTING_BOOL(misc_bhop_enable)
	EL_IF_READ_SETTING_BOOL(misc_auto_pistols_enable)
	EL_IF_READ_SETTING_INT(misc_auto_pistols_delay)
	EL_IF_READ_SETTING_BOOL(misc_auto_accept_enable)
	EL_IF_READ_SETTING_BOOL(misc_anti_flash_enable)
	EL_IF_READ_SETTING_INT(misc_anti_flash_max_alpha)

	if (!is_set_from_file) {
		//PERSONAL SETTINGS
		IF_READ_SETTING_CLASS_MAP(personal_settings, s_personal_settings, int)
	}
}

jsonxx::Object c_settings::to_jsonxx_object(bool is_to_file) {
	jsonxx::Object settings;

	settings
		//AIMBOT
		SET_SETTING(aimbot_enable)
		SET_SETTING(aimbot_key)
		SET_SETTING(aimbot_use_key)
		SET_SETTING(aimbot_delay_enemy)
		SET_SETTING(aimbot_visible_check)
		SET_SETTING(aimbot_smoke_check)
		SET_SETTING(aimbot_flash_check)
		SET_SETTING(aimbot_jump_check)
		SET_SETTING(aimbot_friendly_fire)

		SET_SETTING_CLASS(aimbot_global)
		SET_SETTING_CLASS(aimbot_pistols)
		SET_SETTING_CLASS(aimbot_heavies)
		SET_SETTING_CLASS(aimbot_shoutguns)
		SET_SETTING_CLASS(aimbot_smgs)
		SET_SETTING_CLASS(aimbot_rifles)
		SET_SETTING_CLASS(aimbot_snipers)
		SET_SETTING_CLASS_MAP(aimbot_weapons, s_aimbot_settings, c_item::en_defenition_index)

		//TRIGGERBOT
		SET_SETTING(triggerbot_enable)
		SET_SETTING(triggerbot_use_key)
		SET_SETTING(triggerbot_key)
		SET_SETTING(triggerbot_friendly_fire)
		SET_SETTING(triggerbot_flash_check)
		SET_SETTING(triggerbot_jump_check)
		SET_SETTING(triggerbot_delay_before_shoot)
		SET_SETTING(triggerbot_delay_after_shoot)
		SET_SETTING(triggerbot_pistols_enable)
		SET_SETTING(triggerbot_heavies_enable)
		SET_SETTING(triggerbot_shoutguns_enable)
		SET_SETTING(triggerbot_smgs_enable)
		SET_SETTING(triggerbot_rifles_enable)
		SET_SETTING(triggerbot_snipers_enable)

		//VISUALS
		SET_SETTING(visuals_glow_esp_enable)
		SET_SETTING_CLASS(visuals_glow_esp_enemies)
		SET_SETTING_CLASS(visuals_glow_esp_friends)
		SET_SETTING_CLASS(visuals_glow_esp_c4)
		SET_SETTING_CLASS(visuals_glow_esp_defusing)
		SET_SETTING_CLASS(visuals_glow_esp_grenades)

		SET_SETTING(visuals_chams_enable)
		SET_SETTING_CLASS(visuals_chams_friends)
		SET_SETTING_CLASS(visuals_chams_enemies)

		//SKINCHANGER
		SET_SETTING_CLASS_MAP(skinchanger_weapons, s_skinchanger_weapon, c_item::en_defenition_index)
		SET_SETTING_CLASS_MAP(skinchanger_knives, s_skinchanger_weapon, en_team_num)

		//MISC
		SET_SETTING(misc_ingame_radar_enable)
		SET_SETTING(misc_bhop_enable)
		SET_SETTING(misc_auto_pistols_enable)
		SET_SETTING(misc_auto_pistols_delay)
		SET_SETTING(misc_auto_accept_enable)
		SET_SETTING(skinchanger_enable)
		SET_SETTING(misc_anti_flash_enable)
		SET_SETTING(misc_anti_flash_max_alpha);

		if (!is_to_file) {
			settings
				//PERSONAL SETTINGS
				SET_SETTING_CLASS_MAP(personal_settings, s_personal_settings, int);
		}
	
	return settings;
}

#pragma region Initialization
//AIM BOT
bool c_settings::aimbot_enable = false;
int c_settings::aimbot_key = 0;
bool c_settings::aimbot_use_key = false;
int c_settings::aimbot_delay_enemy = 0;
bool c_settings::aimbot_visible_check = false;
bool c_settings::aimbot_smoke_check = false;
bool c_settings::aimbot_flash_check = false;
bool c_settings::aimbot_jump_check = false;
bool c_settings::aimbot_friendly_fire = false;

c_settings::s_aimbot_settings c_settings::aimbot_global;
c_settings::s_aimbot_settings c_settings::aimbot_pistols;
c_settings::s_aimbot_settings c_settings::aimbot_heavies;
c_settings::s_aimbot_settings c_settings::aimbot_shoutguns;
c_settings::s_aimbot_settings c_settings::aimbot_smgs;
c_settings::s_aimbot_settings c_settings::aimbot_rifles;
c_settings::s_aimbot_settings c_settings::aimbot_snipers;
std::map<c_item::en_defenition_index, c_settings::s_aimbot_settings> c_settings::aimbot_weapons;

//TRIGGERBOT
bool c_settings::triggerbot_enable = false;
bool c_settings::triggerbot_use_key = false;
int c_settings::triggerbot_key = 0;
bool c_settings::triggerbot_friendly_fire = false;
bool c_settings::triggerbot_flash_check = false;
bool c_settings::triggerbot_jump_check = false;
int c_settings::triggerbot_delay_before_shoot = 0;
int c_settings::triggerbot_delay_after_shoot = 0;
bool c_settings::triggerbot_pistols_enable = false;
bool c_settings::triggerbot_heavies_enable = false;
bool c_settings::triggerbot_shoutguns_enable = false;
bool c_settings::triggerbot_smgs_enable = false;
bool c_settings::triggerbot_rifles_enable = false;
bool c_settings::triggerbot_snipers_enable = false;

//VISUALS
bool c_settings::visuals_glow_esp_enable = false;
c_settings::s_glow_esp_settings c_settings::visuals_glow_esp_enemies;
c_settings::s_glow_esp_settings c_settings::visuals_glow_esp_friends;
c_settings::s_glow_esp_settings c_settings::visuals_glow_esp_c4;
c_settings::s_glow_esp_settings c_settings::visuals_glow_esp_defusing;
c_settings::s_glow_esp_settings c_settings::visuals_glow_esp_grenades;
bool c_settings::visuals_chams_enable = false;
c_settings::s_chams_settings c_settings::visuals_chams_friends;
c_settings::s_chams_settings c_settings::visuals_chams_enemies;

//SKINCHAGER
bool c_settings::skinchanger_enable = false;
std::map<c_item::en_defenition_index, c_settings::s_skinchanger_weapon> c_settings::skinchanger_weapons = {};
std::map<en_team_num, c_settings::s_skinchanger_weapon> c_settings::skinchanger_knives = {};

//MISC
bool c_settings::misc_ingame_radar_enable = false;
bool c_settings::misc_bhop_enable = false;
bool c_settings::misc_auto_pistols_enable = false;
int c_settings::misc_auto_pistols_delay = 0;
bool c_settings::misc_auto_accept_enable = false;
bool c_settings::misc_anti_flash_enable = false;
int c_settings::misc_anti_flash_max_alpha = 255;

//PERSONAL SETTINGS
std::map<int, c_settings::s_personal_settings> c_settings::personal_settings;
#pragma endregion