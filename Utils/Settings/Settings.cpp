#include "Settings.hpp"

#pragma region Utils
s_color_rgba c_settings::get_color_from_jsonxx(jsonxx::Value* obj) {
	auto js_obj_color = obj->get<jsonxx::Object>();
	return s_color_rgba{
		(float)js_obj_color.get<jsonxx::Number>("r"),
		(float)js_obj_color.get<jsonxx::Number>("g"),
		(float)js_obj_color.get<jsonxx::Number>("b"),
		(float)js_obj_color.get<jsonxx::Number>("a")
	};
}

jsonxx::Value c_settings::rgba_to_jsonxx(s_color_rgba color) {
	jsonxx::Object js_obj;

	js_obj
		<< "r" << color.r
		<< "g" << color.g
		<< "b" << color.b
		<< "a" << color.a;

	return js_obj;
}

c_settings::s_skinchanger_weapon c_settings::get_weapon_skin_from_jsonxx(jsonxx::Value* skin_obj) {
	auto js_obj_skin = skin_obj->get<jsonxx::Object>();

	s_skinchanger_weapon skin;
	if (js_obj_skin.has<jsonxx::Boolean>("enable")) {
		skin.enable = js_obj_skin.get<jsonxx::Boolean>("enable");
	}
	if (js_obj_skin.has<jsonxx::Number>("paint_kit")) {
		skin.paint_kit = js_obj_skin.get<jsonxx::Number>("paint_kit");
	}
	if (js_obj_skin.has<jsonxx::Number>("seed")) {
		skin.seed = js_obj_skin.get<jsonxx::Number>("seed");
	}
	if (js_obj_skin.has<jsonxx::String>("custom_name")) {
		skin.custom_name = js_obj_skin.get<jsonxx::String>("custom_name");
	}
	if (js_obj_skin.has<jsonxx::Number>("wear")) {
		skin.wear = js_obj_skin.get<jsonxx::Number>("wear");
	}
	if (js_obj_skin.has<jsonxx::Number>("quality")) {
		skin.quality = (en_entity_quality)js_obj_skin.get<jsonxx::Number>("quality");
	}
	if (js_obj_skin.has<jsonxx::Number>("stat_track")) {
		skin.stat_track = js_obj_skin.get<jsonxx::Number>("stat_track");
	}
	if (js_obj_skin.has<jsonxx::Number>("item_di")) {
		skin.item_di = (c_item::en_defenition_index)js_obj_skin.get<jsonxx::Number>("item_di");
	}

	return skin;
}

jsonxx::Value c_settings::weapon_skin_to_jsonxx(s_skinchanger_weapon skin) {
	jsonxx::Object js_obj;

	js_obj <<
		"enable" << skin.enable <<
		"paint_kit" << skin.paint_kit <<
		"seed" << skin.seed <<
		"custom_name" << skin.custom_name <<
		"stat_track" << skin.stat_track <<
		"wear" << skin.wear <<
		"quality" << (int)skin.quality <<
		"item_di" << (int)skin.item_di;

	return js_obj;
}

c_settings::s_aimbot_settings c_settings::get_aimbot_settings_from_jsonxx(jsonxx::Value* value) {
	auto js_obj = value->get<jsonxx::Object>();

	s_aimbot_settings settings;

	if (js_obj.has<jsonxx::Boolean>("use")) {
		settings.use = js_obj.get<jsonxx::Boolean>("use");
	}
	if (js_obj.has<jsonxx::Boolean>("enable")) {
		settings.enable = js_obj.get<jsonxx::Boolean>("enable");
	}
	if (js_obj.has<jsonxx::Boolean>("first_perfect_shoot")) {
		settings.first_perfect_shoot = js_obj.get<jsonxx::Boolean>("first_perfect_shoot");
	}
	if (js_obj.has<jsonxx::Number>("bone")) {
		settings.bone = (en_skeleton)js_obj.get<jsonxx::Number>("bone");
	}
	if (js_obj.has<jsonxx::Boolean>("change_after_nearest")) {
		settings.change_after_nearest = js_obj.get<jsonxx::Boolean>("change_after_nearest");
	}
	if (js_obj.has<jsonxx::Number>("fov")) {
		settings.fov = (float)js_obj.get<jsonxx::Number>("fov");
	}
	if (js_obj.has<jsonxx::Number>("smooth")) {
		settings.smooth = (float)js_obj.get<jsonxx::Number>("smooth");
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

jsonxx::Value c_settings::aimbot_settings_to_jsonxx(s_aimbot_settings settings) {
	jsonxx::Object js_obj;

	js_obj <<
		"use" << settings.use <<
		"enable" << settings.enable <<
		"first_perfect_shoot" << settings.first_perfect_shoot <<
		"bone" << (int)settings.bone <<
		"change_after_nearest" << settings.change_after_nearest <<
		"fov" << settings.fov <<
		"smooth" << settings.smooth <<
		"rcs_enable" << settings.rcs_enable <<
		"rcs_scale_x" << settings.rcs_scale_x <<
		"rcs_scale_y" << settings.rcs_scale_y;

	return js_obj;
}
#pragma endregion

std::map<c_item::en_defenition_index, c_settings::s_skinchanger_weapon> c_settings::get_weapon_skins_from_jsonxx(jsonxx::Value* p_value){
	std::map<c_item::en_defenition_index, s_skinchanger_weapon> map_data;

	for (auto skin_obj: p_value->get<jsonxx::Object>().kv_map()) {
		map_data[(c_item::en_defenition_index)stoi(skin_obj.first)] = get_weapon_skin_from_jsonxx(skin_obj.second);
	}

	return map_data;
}

jsonxx::Value c_settings::weapon_skins_to_jsonxx(std::map<c_item::en_defenition_index, s_skinchanger_weapon> map_data){
	jsonxx::Object value;

	for (auto data: map_data) {
		value << std::to_string((int)data.first) << weapon_skin_to_jsonxx(data.second);
	}

	return value;
}

std::map<en_team_num, c_settings::s_skinchanger_weapon> c_settings::get_knives_skins_from_jsonxx(jsonxx::Value* p_value){
	std::map<en_team_num, s_skinchanger_weapon> map_data;

	for (auto skin_obj : p_value->get<jsonxx::Object>().kv_map()) {
		map_data[(en_team_num)stoi(skin_obj.first)] = get_weapon_skin_from_jsonxx(skin_obj.second);
	}

	return map_data;
}

jsonxx::Value c_settings::knives_skins_to_jsonxx(std::map<en_team_num, s_skinchanger_weapon> map_data){
	jsonxx::Object value;

	for (auto data: map_data) {
		value << std::to_string((int)data.first) << weapon_skin_to_jsonxx(data.second);
	}

	return value;
}

std::map<c_item::en_defenition_index, c_settings::s_aimbot_settings> c_settings::get_aimbot_weapons_settings_from_jsonxx(jsonxx::Value* p_value){
	std::map<c_item::en_defenition_index, s_aimbot_settings> map_data;

	for (auto skin_obj : p_value->get<jsonxx::Object>().kv_map()) {
		map_data[(c_item::en_defenition_index)stoi(skin_obj.first)] = get_aimbot_settings_from_jsonxx(skin_obj.second);
	}

	return map_data;
}

jsonxx::Value c_settings::aimbot_weapons_settings_to_jsonxx(std::map<c_item::en_defenition_index, s_aimbot_settings> map_data){
	jsonxx::Object value;

	for (auto data : map_data) {
		value << std::to_string((int)data.first) << aimbot_settings_to_jsonxx(data.second);
	}

	return value;
}

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

void c_settings::set_value(std::string name, jsonxx::Value* value) {
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

	EL_IF_READ_SETTING_AIM(aimbot_global)
	EL_IF_READ_SETTING_AIM(aimbot_pistols)
	EL_IF_READ_SETTING_AIM(aimbot_heavies)
	EL_IF_READ_SETTING_AIM(aimbot_shoutguns)
	EL_IF_READ_SETTING_AIM(aimbot_smgs)
	EL_IF_READ_SETTING_AIM(aimbot_rifles)
	EL_IF_READ_SETTING_AIM(aimbot_snipers)
	EL_IF_READ_SETTING_AIM_WEAPONS(aimbot_weapons)

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
	EL_IF_READ_SETTING_BOOL(visuals_glow_esp_show_enemies)
	EL_IF_READ_SETTING_GLOW_MODE(visuals_glow_esp_mode)
	EL_IF_READ_SETTING_GLOW_STYLE(visuals_glow_esp_style)
	EL_IF_READ_SETTING_COLOR(visuals_glow_esp_enemy_visible_color)
	EL_IF_READ_SETTING_COLOR(visuals_glow_esp_enemy_invisible_color)
	EL_IF_READ_SETTING_BOOL(visuals_glow_esp_show_friends)
	EL_IF_READ_SETTING_COLOR(visuals_glow_esp_friends_color)
	EL_IF_READ_SETTING_COLOR(visuals_glow_esp_hp_based_0hp_color)
	EL_IF_READ_SETTING_COLOR(visuals_glow_esp_hp_based_100hp_color)
	EL_IF_READ_SETTING_BOOL(visuals_glow_esp_show_c4)
	EL_IF_READ_SETTING_COLOR(visuals_glow_esp_c4_color)
	EL_IF_READ_SETTING_COLOR(visuals_glow_esp_c4_planted_color)
	EL_IF_READ_SETTING_BOOL(visuals_glow_esp_show_defusing)
	EL_IF_READ_SETTING_COLOR(visuals_glow_esp_defusing_color)
	EL_IF_READ_SETTING_BOOL(visuals_glow_esp_show_grenades)
	EL_IF_READ_SETTING_COLOR(visuals_glow_esp_grenades_color)

	EL_IF_READ_SETTING_BOOL(visuals_chams_enable)
	EL_IF_READ_SETTING_BOOL(visuals_chams_show_enemies)
	EL_IF_READ_SETTING_COLOR(visuals_chams_enemy_color)
	EL_IF_READ_SETTING_BOOL(visuals_chams_show_friends)
	EL_IF_READ_SETTING_COLOR(visuals_chams_friends_color)

	//SKINCHANGER
	EL_IF_READ_SETTING_BOOL(skinchanger_enable)
	EL_IF_READ_SETTING_SKINCHANGER_WEAPONS(skinchanger_weapons)
	EL_IF_READ_SETTING_SKINCHANGER_KNIVES(skinchanger_knives)

	//MISC
	EL_IF_READ_SETTING_BOOL(misc_ingame_radar_enable)
	EL_IF_READ_SETTING_BOOL(misc_bhop_enable)
	EL_IF_READ_SETTING_BOOL(misc_auto_pistols_enable)
	EL_IF_READ_SETTING_INT(misc_auto_pistols_delay)
	EL_IF_READ_SETTING_BOOL(misc_auto_accept_enable)
	EL_IF_READ_SETTING_BOOL(misc_anti_flash_enable)
	EL_IF_READ_SETTING_INT(misc_anti_flash_max_alpha)
}

jsonxx::Object c_settings::to_jsonxx_object() {
	jsonxx::Object settings;
	settings
		SET_SETTING(aimbot_enable)
		SET_SETTING(aimbot_key)
		SET_SETTING(aimbot_use_key)
		SET_SETTING(aimbot_delay_enemy)
		SET_SETTING(aimbot_visible_check)
		SET_SETTING(aimbot_smoke_check)
		SET_SETTING(aimbot_flash_check)
		SET_SETTING(aimbot_jump_check)
		SET_SETTING(aimbot_friendly_fire)

		SET_SETTING_AIM(aimbot_global)
		SET_SETTING_AIM(aimbot_pistols)
		SET_SETTING_AIM(aimbot_heavies)
		SET_SETTING_AIM(aimbot_shoutguns)
		SET_SETTING_AIM(aimbot_smgs)
		SET_SETTING_AIM(aimbot_rifles)
		SET_SETTING_AIM(aimbot_snipers)
		SET_SETTING_AIM_WEAPONS(aimbot_weapons)

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
		SET_SETTING(visuals_glow_esp_show_enemies)
		SET_SETTING_INT(visuals_glow_esp_mode)
		SET_SETTING_INT(visuals_glow_esp_style)
		SET_SETTING_COLOR(visuals_glow_esp_enemy_visible_color)
		SET_SETTING_COLOR(visuals_glow_esp_enemy_invisible_color)
		SET_SETTING(visuals_glow_esp_show_friends)
		SET_SETTING_COLOR(visuals_glow_esp_friends_color)
		SET_SETTING_COLOR(visuals_glow_esp_hp_based_0hp_color)
		SET_SETTING_COLOR(visuals_glow_esp_hp_based_100hp_color)
		SET_SETTING(visuals_glow_esp_show_c4)
		SET_SETTING_COLOR(visuals_glow_esp_c4_color)
		SET_SETTING_COLOR(visuals_glow_esp_c4_planted_color)
		SET_SETTING(visuals_glow_esp_show_defusing)
		SET_SETTING_COLOR(visuals_glow_esp_defusing_color)
		SET_SETTING(visuals_glow_esp_show_grenades)
		SET_SETTING_COLOR(visuals_glow_esp_grenades_color)

		SET_SETTING(visuals_chams_enable)
		SET_SETTING(visuals_chams_show_enemies)
		SET_SETTING_COLOR(visuals_chams_enemy_color)
		SET_SETTING(visuals_chams_show_friends)
		SET_SETTING_COLOR(visuals_chams_friends_color)

		//SKINCHANGER
		SET_SETTING_SKINCHANGER_WEAPONS(skinchanger_weapons)
		SET_SETTING_SKINCHANGER_KNIVES(skinchanger_knives)

		//MISC
		SET_SETTING(misc_ingame_radar_enable)
		SET_SETTING(misc_bhop_enable)
		SET_SETTING(misc_auto_pistols_enable)
		SET_SETTING(misc_auto_pistols_delay)
		SET_SETTING(misc_auto_accept_enable)
		SET_SETTING(skinchanger_enable)
		SET_SETTING(misc_anti_flash_enable)
		SET_SETTING(misc_anti_flash_max_alpha);
	
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

c_settings::s_aimbot_settings c_settings::aimbot_global = {
	false,
	false,
	false,
	0,
	en_skeleton::Nearest,
	false,
	0,
	false,
	0.0f,
	0.0f
};
c_settings::s_aimbot_settings c_settings::aimbot_pistols = {
	false,
	false,
	false,
	0,
	en_skeleton::Nearest,
	false,
	0,
	false,
	0.0f,
	0.0f
};
c_settings::s_aimbot_settings c_settings::aimbot_heavies = {
	false,
	false,
	false,
	0,
	en_skeleton::Nearest,
	false,
	0,
	false,
	0.0f,
	0.0f
};
c_settings::s_aimbot_settings c_settings::aimbot_shoutguns = {
	false,
	false,
	false,
	0,
	en_skeleton::Nearest,
	false,
	0,
	false,
	0.0f,
	0.0f
};
c_settings::s_aimbot_settings c_settings::aimbot_smgs = {
	false,
	false,
	false,
	0,
	en_skeleton::Nearest,
	false,
	0,
	false,
	0.0f,
	0.0f
};
c_settings::s_aimbot_settings c_settings::aimbot_rifles = {
	false,
	false,
	false,
	0,
	en_skeleton::Nearest,
	false,
	0,
	false,
	0.0f,
	0.0f
};
c_settings::s_aimbot_settings c_settings::aimbot_snipers = {
	false,
	false,
	false,
	0,
	en_skeleton::Nearest,
	false,
	0,
	false,
	0.0f,
	0.0f
};
std::map<c_item::en_defenition_index, c_settings::s_aimbot_settings> c_settings::aimbot_weapons = {};

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
bool c_settings::visuals_glow_esp_show_enemies = false;
c_settings::en_visuals_glow_esp_mode c_settings::visuals_glow_esp_mode = c_settings::en_visuals_glow_esp_mode::Color;
en_glow_style c_settings::visuals_glow_esp_style = en_glow_style::FullBody;
s_color_rgba c_settings::visuals_glow_esp_enemy_visible_color = { 0.0f, 0.0f, 0.0f, 0.0f };
s_color_rgba c_settings::visuals_glow_esp_enemy_invisible_color = { 0.0f, 0.0f, 0.0f, 0.0f };
bool c_settings::visuals_glow_esp_show_friends = false;
s_color_rgba c_settings::visuals_glow_esp_friends_color = { 0.0f, 0.0f, 0.0f, 0.0f };
s_color_rgba c_settings::visuals_glow_esp_hp_based_0hp_color = { 0.0f, 0.0f, 0.0f, 0.0f };
s_color_rgba c_settings::visuals_glow_esp_hp_based_100hp_color = { 0.0f, 0.0f, 0.0f, 0.0f };
bool c_settings::visuals_glow_esp_show_c4 = false;
s_color_rgba c_settings::visuals_glow_esp_c4_color = { 0.0f, 0.0f, 0.0f, 0.0f };
s_color_rgba c_settings::visuals_glow_esp_c4_planted_color = { 0.0f, 0.0f, 0.0f, 0.0f };
bool c_settings::visuals_glow_esp_show_defusing = false;
s_color_rgba c_settings::visuals_glow_esp_defusing_color = { 0.0f, 0.0f, 0.0f, 0.0f };
bool c_settings::visuals_glow_esp_show_grenades = false;
s_color_rgba c_settings::visuals_glow_esp_grenades_color = { 0.0f, 0.0f, 0.0f, 0.0f };

bool c_settings::visuals_chams_enable = false;
bool c_settings::visuals_chams_show_enemies = false;
s_color_rgba c_settings::visuals_chams_enemy_color = { 0.0f, 0.0f, 0.0f, 0.0f };
bool c_settings::visuals_chams_show_friends = false;
s_color_rgba c_settings::visuals_chams_friends_color = { 0.0f, 0.0f, 0.0f, 0.0f };

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
#pragma endregion