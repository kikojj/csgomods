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

ISkinchangerWeapon Settings::getWeaponSkinFromJsonXX(jsonxx::Value* skinObjC){
	auto skinObj = skinObjC->get<jsonxx::Object>();

	ISkinchangerWeapon skin;
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

	return skin;
}

jsonxx::Value Settings::weaponSkinToJsonXX(ISkinchangerWeapon skin){
	jsonxx::Object o;
	o <<
		"enable" << skin.enable <<
		"paintKit" << skin.paintKit <<
		"seed" << skin.seed <<
		"customName" << skin.customName <<
		"statTrack" << skin.statTrack <<
		"wear" << skin.wear <<
		"quality" << (int)skin.quality <<
		"itemDI" << (int)skin.itemDI;

	return o;
}

std::map<ItemDefinitionIndex, ISkinchangerWeapon> Settings::getWeaponSkinsFromJsonXX(jsonxx::Value* v){
	std::map<ItemDefinitionIndex, ISkinchangerWeapon> data;

	for (auto skinObjC: v->get<jsonxx::Object>().kv_map()) {
		data[(ItemDefinitionIndex)stoi(skinObjC.first)] = getWeaponSkinFromJsonXX(skinObjC.second);
	}

	return data;
}

jsonxx::Value Settings::weaponSkinsToJsonXX(std::map<ItemDefinitionIndex, ISkinchangerWeapon> data){
	jsonxx::Object v;

	for (auto d: data) {
		v << std::to_string(d.first) << weaponSkinToJsonXX(d.second);
	}

	return v;
}

std::map<TeamNum, ISkinchangerWeapon> Settings::getKnifesSkinsFromJsonXX(jsonxx::Value* v){
	std::map<TeamNum, ISkinchangerWeapon> data;

	for (auto skinObjC : v->get<jsonxx::Object>().kv_map()) {
		data[(TeamNum)stoi(skinObjC.first)] = getWeaponSkinFromJsonXX(skinObjC.second);
	}

	return data;
}

jsonxx::Value Settings::knifesSkinsToJsonXX(std::map<TeamNum, ISkinchangerWeapon> data){
	jsonxx::Object v;

	for (auto d : data) {
		v << std::to_string(d.first) << weaponSkinToJsonXX(d.second);
	}

	return v;
}

IAimbotSettings Settings::getAimbotSettingsFromJsonXX(jsonxx::Value* v){
	auto obj = v->get<jsonxx::Object>();

	IAimbotSettings settings;

	if (obj.has<jsonxx::Boolean>("enable")) {
		settings.enable = obj.get<jsonxx::Boolean>("enable");
	}
	if (obj.has<jsonxx::Number>("bone")) {
		settings.bone = (Skeleton)obj.get<jsonxx::Number>("bone");
	}
	if (obj.has<jsonxx::Number>("fov")) {
		settings.fov = (float)obj.get<jsonxx::Number>("fov");
	}
	if (obj.has<jsonxx::Number>("smooth")) {
		settings.smooth = (float)obj.get<jsonxx::Number>("smooth");
	}
	if (obj.has<jsonxx::Boolean>("rcs_enable")) {
		settings.rcs_enable = obj.get<jsonxx::Boolean>("rcs_enable");
	}
	if (obj.has<jsonxx::Number>("rcs_scale_x")) {
		settings.rcs_scale_x = (float)obj.get<jsonxx::Number>("rcs_scale_x");
	}
	if (obj.has<jsonxx::Number>("rcs_scale_y")) {
		settings.rcs_scale_y = (float)obj.get<jsonxx::Number>("rcs_scale_y");
	}

	return settings;
}

jsonxx::Value Settings::aimbotSettingsToJsonXX(IAimbotSettings settings){
	jsonxx::Object o;

	o <<
		"enable" << settings.enable <<
		"bone" << (int)settings.bone <<
		"fov" << settings.fov <<
		"smooth" << settings.smooth <<
		"rcs_enable" << settings.rcs_enable <<
		"rcs_scale_x" << settings.rcs_scale_x <<
		"rcs_scale_y" << settings.rcs_scale_y;

	return o;
}

std::map<ItemDefinitionIndex, IAimbotSettings> Settings::getAimbotWeaponsSettingsFromJsonXX(jsonxx::Value* v){
	std::map<ItemDefinitionIndex, IAimbotSettings> data;

	for (auto skinObjC : v->get<jsonxx::Object>().kv_map()) {
		data[(ItemDefinitionIndex)stoi(skinObjC.first)] = getAimbotSettingsFromJsonXX(skinObjC.second);
	}

	return data;
}

jsonxx::Value Settings::aimbotWeaponsSettingsToJsonXX(std::map<ItemDefinitionIndex, IAimbotSettings> data){
	jsonxx::Object v;

	for (auto d : data) {
		v << std::to_string(d.first) << aimbotSettingsToJsonXX(d.second);
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

	else if (name == "aimbot_global") aimbot_global = getAimbotSettingsFromJsonXX(value);
	else if (name == "aimbot_pistols") aimbot_pistols = getAimbotSettingsFromJsonXX(value);
	else if (name == "aimbot_heavies") aimbot_heavies = getAimbotSettingsFromJsonXX(value);
	else if (name == "aimbot_shoutguns") aimbot_shoutguns = getAimbotSettingsFromJsonXX(value);
	else if (name == "aimbot_smgs") aimbot_smgs = getAimbotSettingsFromJsonXX(value);
	else if (name == "aimbot_rifles") aimbot_rifles = getAimbotSettingsFromJsonXX(value);
	else if (name == "aimbot_snipers") aimbot_snipers = getAimbotSettingsFromJsonXX(value);
	else if (name == "aimbot_weapons") aimbot_weapons = getAimbotWeaponsSettingsFromJsonXX(value);

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
	else if (name == "visuals_glowEsp_mode") visuals_glowEsp_mode = (EVisualsGlowEspMode)value->get<jsonxx::Number>();
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
	else if (name == "skinchanger_weapons") skinchanger_weapons = getWeaponSkinsFromJsonXX(value);
	else if (name == "skinchanger_knifes") skinchanger_knifes = getKnifesSkinsFromJsonXX(value);

	//MISC
	else if (name == "misc_ingameRadar_enable") misc_ingameRadar_enable = value->get<bool>();
	else if (name == "misc_bhop_enable") misc_bhop_enable = value->get<bool>();
	else if (name == "misc_autoPistols_enable") misc_autoPistols_enable = value->get<bool>();
	else if (name == "misc_autoPistols_delay") misc_autoPistols_delay = value->get<jsonxx::Number>();
	else if (name == "misc_autoAccept_enable") misc_autoAccept_enable = value->get<bool>();
	else if (name == "misc_antiFlash_enable") misc_antiFlash_enable = value->get<bool>();
	else if (name == "misc_antiFlash_maxAlpha") misc_antiFlash_maxAlpha = value->get<jsonxx::Number>();
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

		<< "aimbot_global" << aimbotSettingsToJsonXX(Settings::aimbot_global)
		<< "aimbot_pistols" << aimbotSettingsToJsonXX(Settings::aimbot_pistols)
		<< "aimbot_heavies" << aimbotSettingsToJsonXX(Settings::aimbot_heavies)
		<< "aimbot_shoutguns" << aimbotSettingsToJsonXX(Settings::aimbot_shoutguns)
		<< "aimbot_smgs" << aimbotSettingsToJsonXX(Settings::aimbot_smgs)
		<< "aimbot_rifles" << aimbotSettingsToJsonXX(Settings::aimbot_rifles)
		<< "aimbot_snipers" << aimbotSettingsToJsonXX(Settings::aimbot_snipers)
		<< "aimbot_weapons" << aimbotWeaponsSettingsToJsonXX(Settings::aimbot_weapons)

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
		<< "skinchanger_enable" << Settings::skinchanger_enable
		<< "misc_antiFlash_enable" << Settings::misc_antiFlash_enable
		<< "misc_antiFlash_maxAlpha" << Settings::misc_antiFlash_maxAlpha;
	
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

IAimbotSettings Settings::aimbot_global = {
	true,
	1,
	NEAREST,
	0,
	true,
	100.0f,
	100.0f
};
IAimbotSettings Settings::aimbot_pistols = {
	false,
	5,
	HEAD,
	0,
	false,
	0.0f,
	0.0f
};
IAimbotSettings Settings::aimbot_heavies = {
	true,
	5,
	NEAREST,
	5,
	true,
	100.0f,
	100.0f
};
IAimbotSettings Settings::aimbot_shoutguns = {
	true,
	5,
	NEAREST,
	5,
	true,
	100.0f,
	100.0f
};
IAimbotSettings Settings::aimbot_smgs = {
	true,
	5,
	NEAREST,
	5,
	true,
	100.0f,
	100.0f
};
IAimbotSettings Settings::aimbot_rifles = {
	true,
	5,
	NEAREST,
	5,
	true,
	100.0f,
	100.0f
};
IAimbotSettings Settings::aimbot_snipers = {
	true,
	5,
	NEAREST,
	5,
	false,
	100.0f,
	100.0f
};
std::map<ItemDefinitionIndex, IAimbotSettings> Settings::aimbot_weapons = {};

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
EVisualsGlowEspMode Settings::visuals_glowEsp_mode = VISUALS_GLOWESP_MODE_COLOR;
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
std::map<ItemDefinitionIndex, ISkinchangerWeapon> Settings::skinchanger_weapons = {};
std::map<TeamNum, ISkinchangerWeapon> Settings::skinchanger_knifes = {};

//MISC
bool Settings::misc_ingameRadar_enable = true;
bool Settings::misc_bhop_enable = true;
bool Settings::misc_autoPistols_enable = false;
int Settings::misc_autoPistols_delay = 50;
bool Settings::misc_autoAccept_enable = true;
bool Settings::misc_antiFlash_enable = false;
int Settings::misc_antiFlash_maxAlpha = 255;