#include "Settings.hpp"

colorRGBA Settings::getColorFromJsonXX(jsonxx::Value* obj){
	auto color = obj->get<jsonxx::Object>();
	return colorRGBA{
		(float)color.get<jsonxx::Number>("r"),
		(float)color.get<jsonxx::Number>("g"),
		(float)color.get<jsonxx::Number>("b"),
		(float)color.get<jsonxx::Number>("a")
	};
}

jsonxx::Value Settings::rgbaToJsonXX(colorRGBA color) {
	jsonxx::Object o;
	o
		<< "r" << color.r
		<< "g" << color.g
		<< "b" << color.b
		<< "a" << color.a;
	return o;
}

std::map<ItemDefinitionIndex, SkinchangerWeapon> Settings::getWeaponSkinsFroJsonXX(jsonxx::Value* v){
	std::map<ItemDefinitionIndex, SkinchangerWeapon> data;

	for (auto skinObjC: v->get<jsonxx::Object>().kv_map()) {
		auto skinObj = skinObjC.second->get<jsonxx::Object>();

		SkinchangerWeapon skin;
		if (skinObj.has<jsonxx::Boolean>("enable")) {
			skin.enable = skinObj.get<jsonxx::Boolean>("enable");
		}
		if (skinObj.has<jsonxx::Number>("paintKit")) {
			skin.paintKit = skinObj.get<jsonxx::Number>("paintKit");
		}
		if (skinObj.has<jsonxx::Number>("seed")) {
			skin.seed = skinObj.get<jsonxx::Number>("seed");
		}
		if (skinObj.has<jsonxx::String>("customName")) {
			skin.customName = skinObj.get<jsonxx::String>("customName");
		}
		if (skinObj.has<jsonxx::Number>("wear")) {
			skin.wear = skinObj.get<jsonxx::Number>("wear");
		}
		if (skinObj.has<jsonxx::Number>("quality")) {
			skin.quality = (EntityQuality)skinObj.get<jsonxx::Number>("quality");
		}
		if (skinObj.has<jsonxx::Number>("statTrack")) {
			skin.statTrack = skinObj.get<jsonxx::Number>("statTrack");
		}
		if (skinObj.has<jsonxx::Number>("itemDI")) {
			skin.itemDI = (ItemDefinitionIndex)skinObj.get<jsonxx::Number>("itemDI");
		}

		data[(ItemDefinitionIndex)stoi(skinObjC.first)] = skin;
	}

	return data;
}

jsonxx::Value Settings::weaponSkinsToJsonXX(std::map<ItemDefinitionIndex, SkinchangerWeapon> data){
	jsonxx::Object v;

	for (auto d: data) {
		jsonxx::Object o;
		o <<
			"enable" << d.second.enable <<
			"paintKit" << d.second.paintKit <<
			"seed" << d.second.seed <<
			"customName" << d.second.customName <<
			"statTrack" << d.second.statTrack <<
			"wear" << d.second.wear <<
			"quality" << (int)d.second.quality <<
			"itemDI" << (int)d.second.itemDI;

		v << std::to_string(d.first) << o;
	}

	return v;
}

std::map<TeamNum, SkinchangerWeapon> Settings::getKnifesSkinsFromJsonXX(jsonxx::Value* v){
	std::map<TeamNum, SkinchangerWeapon> data;

	for (auto skinObjC : v->get<jsonxx::Object>().kv_map()) {
		auto skinObj = skinObjC.second->get<jsonxx::Object>();

		SkinchangerWeapon skin;
		if (skinObj.has<jsonxx::Boolean>("enable")) {
			skin.enable = skinObj.get<jsonxx::Boolean>("enable");
		}
		if (skinObj.has<jsonxx::Number>("paintKit")) {
			skin.paintKit = skinObj.get<jsonxx::Number>("paintKit");
		}
		if (skinObj.has<jsonxx::Number>("seed")) {
			skin.seed = skinObj.get<jsonxx::Number>("seed");
		}
		if (skinObj.has<jsonxx::String>("customName")) {
			skin.customName = skinObj.get<jsonxx::String>("customName");
		}
		if (skinObj.has<jsonxx::Number>("wear")) {
			skin.wear = skinObj.get<jsonxx::Number>("wear");
		}
		if (skinObj.has<jsonxx::Number>("quality")) {
			skin.quality = (EntityQuality)skinObj.get<jsonxx::Number>("quality");
		}
		if (skinObj.has<jsonxx::Number>("statTrack")) {
			skin.statTrack = skinObj.get<jsonxx::Number>("statTrack");
		}
		if (skinObj.has<jsonxx::Number>("itemDI")) {
			skin.itemDI = (ItemDefinitionIndex)skinObj.get<jsonxx::Number>("itemDI");
		}

		data[(TeamNum)stoi(skinObjC.first)] = skin;
	}

	return data;
}

jsonxx::Value Settings::knifesSkinsToJsonXX(std::map<TeamNum, SkinchangerWeapon> data){
	jsonxx::Object v;

	for (auto d : data) {
		jsonxx::Object o;
		o <<
			"enable" << d.second.enable <<
			"paintKit" << d.second.paintKit <<
			"seed" << d.second.seed <<
			"customName" << d.second.customName <<
			"statTrack" << d.second.statTrack <<
			"wear" << d.second.wear <<
			"quality" << (int)d.second.quality <<
			"itemDI" << (int)d.second.itemDI;

		v << std::to_string(d.first) << o;
	}

	return v;
}

std::filesystem::path Settings::getConfigDirectoryPath(){
	return std::filesystem::temp_directory_path() / "csgomods";
}

bool Settings::getFromFile(std::string fileName) {
	if (!std::filesystem::exists(getConfigDirectoryPath())) {
		return false;
	}

	auto path = getConfigDirectoryPath() / fileName;
	if (!std::filesystem::exists(path)) {
		return false;
	}

	try {
		std::fstream f(path);
		std::string jsonBuffer((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
		jsonxx::Object Settings;
		Settings.parse(jsonBuffer);

		for (auto prop : Settings.kv_map()) {
			setValue(prop.first, prop.second);
		}
		std::cout << "[Settings]: Loaded from '" << fileName << "'." << std::endl;
		f.close();
	}
	catch (const std::exception&) {
		return false;
	}
	return true;
}

bool Settings::saveToFile(std::string fileName){
	if (!std::filesystem::exists(getConfigDirectoryPath())) {
		std::filesystem::create_directories(getConfigDirectoryPath());
	}

	try {
		auto path = getConfigDirectoryPath() / fileName;

		std::ofstream f(path);
		f << toJsonxxObject().json();
		f.close();

		std::cout << "[Settings]: Saved to '" << fileName << "'." << std::endl;
	}
	catch (const std::exception&) {
		return false;
	}
	return true;
}

bool Settings::deleteFile(std::string fileName){
	if (!std::filesystem::exists(getConfigDirectoryPath())) {
		return false;
	}

	auto path = getConfigDirectoryPath() / fileName;
	if (!std::filesystem::exists(path)) {
		return false;
	}

	if (!std::remove(path.string().c_str())) {
		return false;
	}

	return true;
}

std::vector<std::string> Settings::getFilesList(){
	std::vector<std::string> filesList;

	if (!std::filesystem::exists(getConfigDirectoryPath())) {
		return filesList;
	}

	auto directoryIterator = std::filesystem::directory_iterator(getConfigDirectoryPath());
	for (auto entry : directoryIterator) {
		if (!entry.is_directory()) {
			filesList.push_back(entry.path().filename().string());
		}
	}

	return filesList;
}

jsonxx::Array Settings::getFilesListAsJsonxxArray(){
	jsonxx::Array filesList;
	for (auto v : getFilesList()) {
		filesList << jsonxx::Value(v);
	}
	return filesList;
}

void Settings::setValue(std::string name, jsonxx::Value* value) {
	//AIMBOT
	if (name == "aimbot_enable") aimbot_enable = value->get<bool>();
	else if (name == "aimbot_key") aimbot_key = value->get<jsonxx::Number>();
	else if (name == "aimbot_use_key") aimbot_use_key = value->get<bool>();
	else if (name == "aimbot_delay_enemy") aimbot_delay_enemy = value->get<jsonxx::Number>();
	else if (name == "aimbot_visible_check") aimbot_visible_check = value->get<bool>();
	else if (name == "aimbot_flash_check") aimbot_flash_check = value->get<bool>();
	else if (name == "aimbot_jump_check") aimbot_jump_check = value->get<bool>();
	else if (name == "aimbot_friendly_fire") aimbot_friendly_fire = value->get<bool>();

	else if (name == "aimbot_pistols_enable") aimbot_pistols_enable = value->get<bool>();
	else if (name == "aimbot_pistols_fov") aimbot_pistols_fov = value->get<jsonxx::Number>();
	else if (name == "aimbot_pistols_bone") aimbot_pistols_bone = (Skeleton)value->get<jsonxx::Number>();
	else if (name == "aimbot_pistols_smooth") aimbot_pistols_smooth = value->get<jsonxx::Number>();
	else if (name == "aimbot_pistols_rcs_enable") aimbot_pistols_rcs_enable = value->get<bool>();
	else if (name == "aimbot_pistols_rcs_scale_x") aimbot_pistols_rcs_scale_x = value->get<jsonxx::Number>();
	else if (name == "aimbot_pistols_rcs_scale_y") aimbot_pistols_rcs_scale_y = value->get<jsonxx::Number>();

	else if (name == "aimbot_heavies_enable") aimbot_heavies_enable = value->get<bool>();
	else if (name == "aimbot_heavies_fov") aimbot_heavies_fov = value->get<jsonxx::Number>();
	else if (name == "aimbot_heavies_bone") aimbot_heavies_bone = (Skeleton)value->get<jsonxx::Number>();
	else if (name == "aimbot_heavies_smooth") aimbot_heavies_smooth = value->get<jsonxx::Number>();
	else if (name == "aimbot_heavies_rcs_enable") aimbot_heavies_rcs_enable = value->get<bool>();
	else if (name == "aimbot_heavies_rcs_scale_x") aimbot_heavies_rcs_scale_x = value->get<jsonxx::Number>();
	else if (name == "aimbot_heavies_rcs_scale_y") aimbot_heavies_rcs_scale_y = value->get<jsonxx::Number>();

	else if (name == "aimbot_shoutguns_enable") aimbot_shoutguns_enable = value->get<bool>();
	else if (name == "aimbot_shoutguns_fov") aimbot_shoutguns_fov = value->get<jsonxx::Number>();
	else if (name == "aimbot_shoutguns_bone") aimbot_shoutguns_bone = (Skeleton)value->get<jsonxx::Number>();
	else if (name == "aimbot_shoutguns_smooth") aimbot_shoutguns_smooth = value->get<jsonxx::Number>();
	else if (name == "aimbot_shoutguns_rcs_enable") aimbot_shoutguns_rcs_enable = value->get<bool>();
	else if (name == "aimbot_shoutguns_rcs_scale_x") aimbot_shoutguns_rcs_scale_x = value->get<jsonxx::Number>();
	else if (name == "aimbot_shoutguns_rcs_scale_y") aimbot_shoutguns_rcs_scale_y = value->get<jsonxx::Number>();

	else if (name == "aimbot_smgs_enable") aimbot_smgs_enable = value->get<bool>();
	else if (name == "aimbot_smgs_fov") aimbot_smgs_fov = value->get<jsonxx::Number>();
	else if (name == "aimbot_smgs_bone") aimbot_smgs_bone = (Skeleton)value->get<jsonxx::Number>();
	else if (name == "aimbot_smgs_smooth") aimbot_smgs_smooth = value->get<jsonxx::Number>();
	else if (name == "aimbot_smgs_rcs_enable") aimbot_smgs_rcs_enable = value->get<bool>();
	else if (name == "aimbot_smgs_rcs_scale_x") aimbot_smgs_rcs_scale_x = value->get<jsonxx::Number>();
	else if (name == "aimbot_smgs_rcs_scale_y") aimbot_smgs_rcs_scale_y = value->get<jsonxx::Number>();

	else if (name == "aimbot_rifles_enable") aimbot_rifles_enable = value->get<bool>();
	else if (name == "aimbot_rifles_fov") aimbot_rifles_fov = value->get<jsonxx::Number>();
	else if (name == "aimbot_rifles_bone") aimbot_rifles_bone = (Skeleton)value->get<jsonxx::Number>();
	else if (name == "aimbot_rifles_smooth") aimbot_rifles_smooth = value->get<jsonxx::Number>();
	else if (name == "aimbot_rifles_rcs_enable") aimbot_rifles_rcs_enable = value->get<bool>();
	else if (name == "aimbot_rifles_rcs_scale_x") aimbot_rifles_rcs_scale_x = value->get<jsonxx::Number>();
	else if (name == "aimbot_rifles_rcs_scale_y") aimbot_rifles_rcs_scale_y = value->get<jsonxx::Number>();

	else if (name == "aimbot_snipers_enable") aimbot_snipers_enable = value->get<bool>();
	else if (name == "aimbot_snipers_fov") aimbot_snipers_fov = value->get<jsonxx::Number>();
	else if (name == "aimbot_snipers_bone") aimbot_snipers_bone = (Skeleton)value->get<jsonxx::Number>();
	else if (name == "aimbot_snipers_smooth") aimbot_snipers_smooth = value->get<jsonxx::Number>();
	else if (name == "aimbot_snipers_rcs_enable") aimbot_snipers_rcs_enable = value->get<bool>();
	else if (name == "aimbot_snipers_rcs_scale_x") aimbot_snipers_rcs_scale_x = value->get<jsonxx::Number>();
	else if (name == "aimbot_snipers_rcs_scale_y") aimbot_snipers_rcs_scale_y = value->get<jsonxx::Number>();

	//TRIGGERBOT
	else if (name == "triggerbot_enable") triggerbot_enable = value->get<bool>();
	else if (name == "triggerbot_use_key") triggerbot_use_key = value->get<bool>();
	else if (name == "triggerbot_key") triggerbot_key = (Skeleton)value->get<jsonxx::Number>();
	else if (name == "triggerbot_friendly_fire") triggerbot_friendly_fire = value->get<bool>();
	else if (name == "triggerbot_flash_check") triggerbot_flash_check = value->get<bool>();
	else if (name == "triggerbot_jump_check") triggerbot_jump_check = value->get<bool>();
	else if (name == "triggerbot_delay_before_shoot") triggerbot_delay_before_shoot = value->get<jsonxx::Number>();
	else if (name == "triggerbot_delay_after_shoot") triggerbot_delay_after_shoot = value->get<jsonxx::Number>();
	else if (name == "triggerbot_pistols_enable") triggerbot_pistols_enable = value->get<bool>();
	else if (name == "triggerbot_shoutguns_enable") triggerbot_shoutguns_enable = value->get<bool>();
	else if (name == "triggerbot_smgs_enable") triggerbot_smgs_enable = value->get<bool>();
	else if (name == "triggerbot_rifles_enable") triggerbot_rifles_enable = value->get<bool>();
	else if (name == "triggerbot_snipers_enable") triggerbot_snipers_enable = value->get<bool>();

	//VISUALS
	else if (name == "visuals_glowEsp_enable") visuals_glowEsp_enable = value->get<bool>();
	else if (name == "visuals_glowEsp_show_enemies") visuals_glowEsp_show_enemies = value->get<bool>();
	else if (name == "visuals_glowEsp_mode") visuals_glowEsp_mode = (Visuals_glowEsp_mode)value->get<jsonxx::Number>();
	else if (name == "visuals_glowEsp_style") visuals_glowEsp_style = (GlowStyle)value->get<jsonxx::Number>();
	else if (name == "visuals_glowEsp_enemy_visible_color") visuals_glowEsp_enemy_visible_color = getColorFromJsonXX(value);
	else if (name == "visuals_glowEsp_enemy_invisible_color") visuals_glowEsp_enemy_invisible_color = getColorFromJsonXX(value);
	else if (name == "visuals_glowEsp_show_friends") visuals_glowEsp_show_friends = value->get<bool>();
	else if (name == "visuals_glowEsp_friends_color") visuals_glowEsp_friends_color = getColorFromJsonXX(value);
	else if (name == "visuals_glowEsp_hpBased_0hp_color") visuals_glowEsp_hpBased_0hp_color = getColorFromJsonXX(value);
	else if (name == "visuals_glowEsp_hpBased_100hp_color") visuals_glowEsp_hpBased_100hp_color = getColorFromJsonXX(value);
	else if (name == "visuals_glowEsp_show_c4") visuals_glowEsp_show_c4 = value->get<bool>();
	else if (name == "visuals_glowEsp_c4_color") visuals_glowEsp_c4_color = getColorFromJsonXX(value);
	else if (name == "visuals_glowEsp_c4_planted_color") visuals_glowEsp_c4_planted_color = getColorFromJsonXX(value);

	else if (name == "visuals_chams_enable") visuals_chams_enable = value->get<bool>();
	else if (name == "visuals_chams_show_enemies") visuals_chams_show_enemies = value->get<bool>();
	else if (name == "visuals_chams_enemy_color") visuals_chams_enemy_color = getColorFromJsonXX(value);
	else if (name == "visuals_chams_show_friends") visuals_chams_show_friends = value->get<bool>();
	else if (name == "visuals_chams_friends_color") visuals_chams_friends_color = getColorFromJsonXX(value);

	//SKINCHANGER
	else if (name == "skinchanger_enable") skinchanger_enable = value->get<bool>();
	else if (name == "skinchanger_weapons") skinchanger_weapons = getWeaponSkinsFroJsonXX(value);
	else if (name == "skinchanger_knifes") skinchanger_knifes = getKnifesSkinsFromJsonXX(value);

	//MISC
	else if (name == "misc_ingameRadar_enable") misc_ingameRadar_enable = value->get<bool>();
	else if (name == "misc_bhop_enable") misc_bhop_enable = value->get<bool>();
	else if (name == "misc_autoPistols_enable") misc_autoPistols_enable = value->get<bool>();
	else if (name == "misc_autoPistols_delay") misc_autoPistols_delay = value->get<jsonxx::Number>();
	else if (name == "misc_autoAccept_enable") misc_autoAccept_enable = value->get<bool>();
}

jsonxx::Object Settings::toJsonxxObject() {
	jsonxx::Object settings;
	settings
		<< "aimbot_enable" << Settings::aimbot_enable
		<< "aimbot_key" << Settings::aimbot_key
		<< "aimbot_use_key" << Settings::aimbot_use_key
		<< "aimbot_delay_enemy" << Settings::aimbot_delay_enemy
		<< "aimbot_visible_check" << Settings::aimbot_visible_check
		<< "aimbot_flash_check" << Settings::aimbot_flash_check
		<< "aimbot_jump_check" << Settings::aimbot_jump_check
		<< "aimbot_friendly_fire" << Settings::aimbot_friendly_fire

		<< "aimbot_pistols_enable" << Settings::aimbot_pistols_enable
		<< "aimbot_pistols_fov" << Settings::aimbot_pistols_fov
		<< "aimbot_pistols_bone" << (int)Settings::aimbot_pistols_bone
		<< "aimbot_pistols_smooth" << Settings::aimbot_pistols_smooth
		<< "aimbot_pistols_rcs_enable" << Settings::aimbot_pistols_rcs_enable
		<< "aimbot_pistols_rcs_scale_x" << Settings::aimbot_pistols_rcs_scale_x
		<< "aimbot_pistols_rcs_scale_y" << Settings::aimbot_pistols_rcs_scale_y

		<< "aimbot_heavies_enable" << Settings::aimbot_heavies_enable
		<< "aimbot_heavies_fov" << Settings::aimbot_heavies_fov
		<< "aimbot_heavies_bone" << (int)Settings::aimbot_heavies_bone
		<< "aimbot_heavies_smooth" << Settings::aimbot_heavies_smooth
		<< "aimbot_heavies_rcs_enable" << Settings::aimbot_heavies_rcs_enable
		<< "aimbot_heavies_rcs_scale_x" << Settings::aimbot_heavies_rcs_scale_x
		<< "aimbot_heavies_rcs_scale_y" << Settings::aimbot_heavies_rcs_scale_y

		<< "aimbot_shoutguns_enable" << Settings::aimbot_shoutguns_enable
		<< "aimbot_shoutguns_fov" << Settings::aimbot_shoutguns_fov
		<< "aimbot_shoutguns_bone" << (int)Settings::aimbot_shoutguns_bone
		<< "aimbot_heavies_smooth" << Settings::aimbot_heavies_smooth
		<< "aimbot_shoutguns_smooth" << Settings::aimbot_shoutguns_smooth
		<< "aimbot_shoutguns_rcs_scale_x" << Settings::aimbot_shoutguns_rcs_scale_x
		<< "aimbot_shoutguns_rcs_scale_y" << Settings::aimbot_shoutguns_rcs_scale_y

		<< "aimbot_smgs_enable" << Settings::aimbot_smgs_enable
		<< "aimbot_smgs_fov" << Settings::aimbot_smgs_fov
		<< "aimbot_smgs_bone" << (int)Settings::aimbot_smgs_bone
		<< "aimbot_smgs_smooth" << Settings::aimbot_smgs_smooth
		<< "aimbot_smgs_rcs_enable" << Settings::aimbot_smgs_rcs_enable
		<< "aimbot_smgs_rcs_scale_x" << Settings::aimbot_smgs_rcs_scale_x
		<< "aimbot_smgs_rcs_scale_y" << Settings::aimbot_smgs_rcs_scale_y

		<< "aimbot_rifles_enable" << Settings::aimbot_rifles_enable
		<< "aimbot_rifles_fov" << Settings::aimbot_rifles_fov
		<< "aimbot_rifles_bone" << (int)Settings::aimbot_rifles_bone
		<< "aimbot_rifles_smooth" << Settings::aimbot_rifles_smooth
		<< "aimbot_rifles_rcs_enable" << Settings::aimbot_rifles_rcs_enable
		<< "aimbot_rifles_rcs_scale_x" << Settings::aimbot_rifles_rcs_scale_x
		<< "aimbot_rifles_rcs_scale_y" << Settings::aimbot_rifles_rcs_scale_y

		<< "aimbot_snipers_enable" << Settings::aimbot_snipers_enable
		<< "aimbot_snipers_fov" << Settings::aimbot_snipers_fov
		<< "aimbot_snipers_bone" << (int)Settings::aimbot_snipers_bone
		<< "aimbot_snipers_smooth" << Settings::aimbot_snipers_smooth
		<< "aimbot_snipers_rcs_enable" << Settings::aimbot_snipers_rcs_enable
		<< "aimbot_snipers_rcs_scale_x" << Settings::aimbot_snipers_rcs_scale_x
		<< "aimbot_snipers_rcs_scale_y" << Settings::aimbot_snipers_rcs_scale_y

		//TRIGGERBOT
		<< "triggerbot_enable" << Settings::triggerbot_enable
		<< "triggerbot_use_key" << Settings::triggerbot_use_key
		<< "triggerbot_key" << Settings::triggerbot_key
		<< "triggerbot_friendly_fire" << Settings::triggerbot_friendly_fire
		<< "triggerbot_flash_check" << Settings::triggerbot_flash_check
		<< "triggerbot_jump_check" << Settings::triggerbot_jump_check
		<< "triggerbot_delay_before_shoot" << Settings::triggerbot_delay_before_shoot
		<< "triggerbot_delay_after_shoot" << Settings::triggerbot_delay_after_shoot
		<< "triggerbot_pistols_enable" << Settings::triggerbot_pistols_enable
		<< "triggerbot_heavies_enable" << Settings::triggerbot_heavies_enable
		<< "triggerbot_shoutguns_enable" << Settings::triggerbot_shoutguns_enable
		<< "triggerbot_smgs_enable" << Settings::triggerbot_smgs_enable
		<< "triggerbot_rifles_enable" << Settings::triggerbot_rifles_enable
		<< "triggerbot_snipers_enable" << Settings::triggerbot_snipers_enable

		//VISUALS
		<< "visuals_glowEsp_enable" << Settings::visuals_glowEsp_enable
		<< "visuals_glowEsp_show_enemies" << Settings::visuals_glowEsp_show_enemies
		<< "visuals_glowEsp_mode" << (int)Settings::visuals_glowEsp_mode
		<< "visuals_glowEsp_style" << (int)Settings::visuals_glowEsp_style
		<< "visuals_glowEsp_enemy_visible_color" << rgbaToJsonXX(Settings::visuals_glowEsp_enemy_visible_color)
		<< "visuals_glowEsp_enemy_invisible_color" << rgbaToJsonXX(Settings::visuals_glowEsp_enemy_invisible_color)
		<< "visuals_glowEsp_show_friends" << Settings::visuals_glowEsp_show_friends
		<< "visuals_glowEsp_friends_color" << rgbaToJsonXX(Settings::visuals_glowEsp_friends_color)
		<< "visuals_glowEsp_hpBased_0hp_color" << rgbaToJsonXX(Settings::visuals_glowEsp_hpBased_0hp_color)
		<< "visuals_glowEsp_hpBased_100hp_color" << rgbaToJsonXX(Settings::visuals_glowEsp_hpBased_100hp_color)
		<< "visuals_glowEsp_show_c4" << Settings::visuals_glowEsp_show_c4
		<< "visuals_glowEsp_c4_color" << rgbaToJsonXX(Settings::visuals_glowEsp_c4_color)
		<< "visuals_glowEsp_c4_planted_color" << rgbaToJsonXX(Settings::visuals_glowEsp_c4_planted_color)

		<< "visuals_chams_enable" << Settings::visuals_chams_enable
		<< "visuals_chams_show_enemies" << Settings::visuals_chams_show_enemies
		<< "visuals_chams_enemy_color" << rgbaToJsonXX(Settings::visuals_chams_enemy_color)
		<< "visuals_chams_show_friends" << Settings::visuals_chams_show_friends
		<< "visuals_chams_friends_color" << rgbaToJsonXX(Settings::visuals_chams_friends_color)

		//SKINCHANGER
		<< "skinchanger_weapons" << weaponSkinsToJsonXX(Settings::skinchanger_weapons)
		<< "skinchanger_knifes" << knifesSkinsToJsonXX(Settings::skinchanger_knifes)

		//MISC
		<< "misc_ingameRadar_enable" << Settings::misc_ingameRadar_enable
		<< "misc_bhop_enable" << Settings::misc_bhop_enable
		<< "misc_autoPistols_enable" << Settings::misc_autoPistols_enable
		<< "misc_autoPistols_delay" << Settings::misc_autoPistols_delay
		<< "misc_autoAccept_enable" << Settings::misc_autoAccept_enable
		<< "skinchanger_enable" << Settings::skinchanger_enable;
	
	return settings;
}

//AIM BOT
bool Settings::aimbot_enable = true;
int Settings::aimbot_key = VK_LBUTTON;
bool Settings::aimbot_use_key = true;
int Settings::aimbot_delay_enemy = 100;
bool Settings::aimbot_visible_check = true;
bool Settings::aimbot_flash_check = true;
bool Settings::aimbot_jump_check = true;
bool Settings::aimbot_friendly_fire = false;

bool Settings::aimbot_pistols_enable = true;
float Settings::aimbot_pistols_fov = 5;
Skeleton Settings::aimbot_pistols_bone = HEAD;
float Settings::aimbot_pistols_smooth = 5;
bool Settings::aimbot_pistols_rcs_enable = true;
float Settings::aimbot_pistols_rcs_scale_x = 100.0f;
float Settings::aimbot_pistols_rcs_scale_y = 100.0f;

bool Settings::aimbot_heavies_enable = true;
float Settings::aimbot_heavies_fov = 5;
Skeleton Settings::aimbot_heavies_bone = NEAREST;
float Settings::aimbot_heavies_smooth = 5;
bool Settings::aimbot_heavies_rcs_enable = true;
float Settings::aimbot_heavies_rcs_scale_x = 90.0f;
float Settings::aimbot_heavies_rcs_scale_y = 90.0f;

bool Settings::aimbot_shoutguns_enable = false;
float Settings::aimbot_shoutguns_fov = 10;
Skeleton Settings::aimbot_shoutguns_bone = NEAREST;
float Settings::aimbot_shoutguns_smooth = 0.0f;
bool Settings::aimbot_shoutguns_rcs_enable = false;
float Settings::aimbot_shoutguns_rcs_scale_x = 0.0f;
float Settings::aimbot_shoutguns_rcs_scale_y = 0.0f;

bool Settings::aimbot_smgs_enable = true;
float Settings::aimbot_smgs_fov = 5;
Skeleton Settings::aimbot_smgs_bone = NEAREST;
float Settings::aimbot_smgs_smooth = 3;
bool Settings::aimbot_smgs_rcs_enable = true;
float Settings::aimbot_smgs_rcs_scale_x = 80.0f;
float Settings::aimbot_smgs_rcs_scale_y = 80.0f;

bool Settings::aimbot_rifles_enable = true;
float Settings::aimbot_rifles_fov = 10;
Skeleton Settings::aimbot_rifles_bone = NEAREST;
float Settings::aimbot_rifles_smooth = 10;
bool Settings::aimbot_rifles_rcs_enable = true;
float Settings::aimbot_rifles_rcs_scale_x = 100.0f;
float Settings::aimbot_rifles_rcs_scale_y = 100.0f;

bool Settings::aimbot_snipers_enable = true;
float Settings::aimbot_snipers_fov = 10;
Skeleton Settings::aimbot_snipers_bone = NEAREST;
float Settings::aimbot_snipers_smooth = 0;
bool Settings::aimbot_snipers_rcs_enable = false;
float Settings::aimbot_snipers_rcs_scale_x = 0.0f;
float Settings::aimbot_snipers_rcs_scale_y = 0.0f;

//TRIGGERBOT
bool Settings::triggerbot_enable = true;
bool Settings::triggerbot_use_key = true;
int Settings::triggerbot_key = VK_CONTROL;
bool Settings::triggerbot_friendly_fire = false;
bool Settings::triggerbot_flash_check = true;
bool Settings::triggerbot_jump_check = true;
int Settings::triggerbot_delay_before_shoot = 100;
int Settings::triggerbot_delay_after_shoot = 0;
bool Settings::triggerbot_pistols_enable = false;
bool Settings::triggerbot_heavies_enable = false;
bool Settings::triggerbot_shoutguns_enable = false;
bool Settings::triggerbot_smgs_enable = false;
bool Settings::triggerbot_rifles_enable = false;
bool Settings::triggerbot_snipers_enable = true;

//VISUALS
bool Settings::visuals_glowEsp_enable = true;
bool Settings::visuals_glowEsp_show_enemies = true;
Visuals_glowEsp_mode Settings::visuals_glowEsp_mode = VISUALS_GLOWESP_MODE_COLOR;
GlowStyle Settings::visuals_glowEsp_style = GLOW_STYLE_FULL_BODY;
colorRGBA Settings::visuals_glowEsp_enemy_visible_color = { 0.0f, 255.0f, 0.0f, 255.0f };
colorRGBA Settings::visuals_glowEsp_enemy_invisible_color = { 255.0f, 0.0f, 0.0f, 255.0f };
bool Settings::visuals_glowEsp_show_friends = false;
colorRGBA Settings::visuals_glowEsp_friends_color = { 0.0f, 0.0f, 255.0f, 255.0f };
colorRGBA Settings::visuals_glowEsp_hpBased_0hp_color = { 255.0f, 0.0f, 0.0f, 255.0f };
colorRGBA Settings::visuals_glowEsp_hpBased_100hp_color = { 0.0f, 255.0f, 0.0f, 255.0f };
bool Settings::visuals_glowEsp_show_c4 = true;
colorRGBA Settings::visuals_glowEsp_c4_color = { 255.0f, 0.0f, 0.0f, 255.0f };
colorRGBA Settings::visuals_glowEsp_c4_planted_color = { 0.0f, 0.0f, 255.0f, 255.0f };

bool Settings::visuals_chams_enable = true;
bool Settings::visuals_chams_show_enemies = true;
colorRGBA Settings::visuals_chams_enemy_color = { 0.0f, 255.0f, 0.0f, 255.0f };
bool Settings::visuals_chams_show_friends = false;
colorRGBA Settings::visuals_chams_friends_color = { 0.0f, 0.0f, 0.0f, 0.0f };

//SKINCHAGER
bool Settings::skinchanger_enable = true;
std::map<ItemDefinitionIndex, SkinchangerWeapon> Settings::skinchanger_weapons = {};
std::map<TeamNum, SkinchangerWeapon> Settings::skinchanger_knifes = {};

//MISC
bool Settings::misc_ingameRadar_enable = true;
bool Settings::misc_bhop_enable = true;
bool Settings::misc_autoPistols_enable = false;
int Settings::misc_autoPistols_delay = 50;
bool Settings::misc_autoAccept_enable = true;
int Settings::misc_antiFlash_maxAlpha = 255;