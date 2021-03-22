#include "Settings.hpp"

#pragma region Utils
colorRGBA Settings::getColorFromJsonXX(jsonxx::Value* obj) {
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

ISkinchangerWeapon Settings::getWeaponSkinFromJsonXX(jsonxx::Value* skinObjC) {
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

jsonxx::Value Settings::weaponSkinToJsonXX(ISkinchangerWeapon skin) {
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

IAimbotSettings Settings::getAimbotSettingsFromJsonXX(jsonxx::Value* v) {
	auto obj = v->get<jsonxx::Object>();

	IAimbotSettings settings;

	if (obj.has<jsonxx::Boolean>("use")) {
		settings.use = obj.get<jsonxx::Boolean>("use");
	}
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

jsonxx::Value Settings::aimbotSettingsToJsonXX(IAimbotSettings settings) {
	jsonxx::Object o;

	o <<
		"use" << settings.use <<
		"enable" << settings.enable <<
		"bone" << (int)settings.bone <<
		"fov" << settings.fov <<
		"smooth" << settings.smooth <<
		"rcs_enable" << settings.rcs_enable <<
		"rcs_scale_x" << settings.rcs_scale_x <<
		"rcs_scale_y" << settings.rcs_scale_y;

	return o;
}
#pragma endregion

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
		v << std::to_string((int)d.first) << weaponSkinToJsonXX(d.second);
	}

	return v;
}

std::map<TeamNum, ISkinchangerWeapon> Settings::getKnivesSkinsFromJsonXX(jsonxx::Value* v){
	std::map<TeamNum, ISkinchangerWeapon> data;

	for (auto skinObjC : v->get<jsonxx::Object>().kv_map()) {
		data[(TeamNum)stoi(skinObjC.first)] = getWeaponSkinFromJsonXX(skinObjC.second);
	}

	return data;
}

jsonxx::Value Settings::knivesSkinsToJsonXX(std::map<TeamNum, ISkinchangerWeapon> data){
	jsonxx::Object v;

	for (auto d : data) {
		v << std::to_string((int)d.first) << weaponSkinToJsonXX(d.second);
	}

	return v;
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
		v << std::to_string((int)d.first) << aimbotSettingsToJsonXX(d.second);
	}

	return v;
}

#pragma region Files
std::filesystem::path Settings::getConfigDirectoryPath() {
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

bool Settings::saveToFile(std::string fileName) {
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

bool Settings::deleteFile(std::string fileName) {
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

std::vector<std::string> Settings::getFilesList() {
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

jsonxx::Array Settings::getFilesListAsJsonxxArray() {
	jsonxx::Array filesList;
	for (auto v : getFilesList()) {
		filesList << jsonxx::Value(v);
	}
	return filesList;
}
#pragma endregion

void Settings::setValue(std::string name, jsonxx::Value* value) {
	//AIMBOT
	IfReadSettingBool(aimbot_enable)
	ElifReadSettingInt(aimbot_key)
	ElifReadSettingBool(aimbot_use_key)
	ElifReadSettingInt(aimbot_delay_enemy)
	ElifReadSettingBool(aimbot_visible_check)
	ElifReadSettingBool(aimbot_flash_check)
	ElifReadSettingBool(aimbot_jump_check)
	ElifReadSettingBool(aimbot_friendly_fire)

	ElifReadSettingAim(aimbot_global)
	ElifReadSettingAim(aimbot_pistols)
	ElifReadSettingAim(aimbot_heavies)
	ElifReadSettingAim(aimbot_shoutguns)
	ElifReadSettingAim(aimbot_smgs)
	ElifReadSettingAim(aimbot_rifles)
	ElifReadSettingAim(aimbot_snipers)
	ElifReadSettingAimWeapons(aimbot_weapons)

	//TRIGGERBOT
	ElifReadSettingBool(triggerbot_enable)
	ElifReadSettingBool(triggerbot_use_key)
	ElifReadSettingInt(triggerbot_key)
	ElifReadSettingBool(triggerbot_friendly_fire)
	ElifReadSettingBool(triggerbot_flash_check)
	ElifReadSettingBool(triggerbot_jump_check)
	ElifReadSettingInt(triggerbot_delay_before_shoot)
	ElifReadSettingInt(triggerbot_delay_after_shoot)

	ElifReadSettingBool(triggerbot_pistols_enable)
	ElifReadSettingBool(triggerbot_shoutguns_enable)
	ElifReadSettingBool(triggerbot_smgs_enable)
	ElifReadSettingBool(triggerbot_rifles_enable)
	ElifReadSettingBool(triggerbot_snipers_enable)

	//VISUALS
	ElifReadSettingBool(visuals_glowEsp_enable)
	ElifReadSettingBool(visuals_glowEsp_show_enemies)
	ElifReadSettingGlowMode(visuals_glowEsp_mode)
	ElifReadSettingGlowStyle(visuals_glowEsp_style)
	ElifReadSettingColor(visuals_glowEsp_enemy_visible_color)
	ElifReadSettingColor(visuals_glowEsp_enemy_invisible_color)
	ElifReadSettingBool(visuals_glowEsp_show_friends)
	ElifReadSettingColor(visuals_glowEsp_friends_color)
	ElifReadSettingColor(visuals_glowEsp_hpBased_0hp_color)
	ElifReadSettingColor(visuals_glowEsp_hpBased_100hp_color)
	ElifReadSettingBool(visuals_glowEsp_show_c4)
	ElifReadSettingColor(visuals_glowEsp_c4_color)
	ElifReadSettingColor(visuals_glowEsp_c4_planted_color)
	ElifReadSettingBool(visuals_glowEsp_show_defusing)
	ElifReadSettingColor(visuals_glowEsp_defusing_color)
		ElifReadSettingBool(visuals_glowEsp_show_grenades)
		ElifReadSettingColor(visuals_glowEsp_grenades_color)

	ElifReadSettingBool(visuals_chams_enable)
	ElifReadSettingBool(visuals_chams_show_enemies)
	ElifReadSettingColor(visuals_chams_enemy_color)
	ElifReadSettingBool(visuals_chams_show_friends)
	ElifReadSettingColor(visuals_chams_friends_color)

	//SKINCHANGER
	ElifReadSettingBool(skinchanger_enable)
	ElifReadSettingSkinchangerWeapon(skinchanger_weapons)
	ElifReadSettingSkinchangerKnives(skinchanger_knives)

	//MISC
	ElifReadSettingBool(misc_ingameRadar_enable)
	ElifReadSettingBool(misc_bhop_enable)
	ElifReadSettingBool(misc_autoPistols_enable)
	ElifReadSettingInt(misc_autoPistols_delay)
	ElifReadSettingBool(misc_autoAccept_enable)
	ElifReadSettingBool(misc_antiFlash_enable)
	ElifReadSettingInt(misc_antiFlash_maxAlpha)
}

jsonxx::Object Settings::toJsonxxObject() {
	jsonxx::Object settings;
	settings
		SetSetting(aimbot_enable)
		SetSetting(aimbot_key)
		SetSetting(aimbot_use_key)
		SetSetting(aimbot_delay_enemy)
		SetSetting(aimbot_visible_check)
		SetSetting(aimbot_flash_check)
		SetSetting(aimbot_jump_check)
		SetSetting(aimbot_friendly_fire)

		SetSettingAim(aimbot_global)
		SetSettingAim(aimbot_pistols)
		SetSettingAim(aimbot_heavies)
		SetSettingAim(aimbot_shoutguns)
		SetSettingAim(aimbot_smgs)
		SetSettingAim(aimbot_rifles)
		SetSettingAim(aimbot_snipers)
		SetSettingAimWeapons(aimbot_weapons)

		//TRIGGERBOT
		SetSetting(triggerbot_enable)
		SetSetting(triggerbot_use_key)
		SetSetting(triggerbot_key)
		SetSetting(triggerbot_friendly_fire)
		SetSetting(triggerbot_flash_check)
		SetSetting(triggerbot_jump_check)
		SetSetting(triggerbot_delay_before_shoot)
		SetSetting(triggerbot_delay_after_shoot)
		SetSetting(triggerbot_pistols_enable)
		SetSetting(triggerbot_heavies_enable)
		SetSetting(triggerbot_shoutguns_enable)
		SetSetting(triggerbot_smgs_enable)
		SetSetting(triggerbot_rifles_enable)
		SetSetting(triggerbot_snipers_enable)

		//VISUALS
		SetSetting(visuals_glowEsp_enable)
		SetSetting(visuals_glowEsp_show_enemies)
		SetSettingInt(visuals_glowEsp_mode)
		SetSettingInt(visuals_glowEsp_style)
		SetSettingColor(visuals_glowEsp_enemy_visible_color)
		SetSettingColor(visuals_glowEsp_enemy_invisible_color)
		SetSetting(visuals_glowEsp_show_friends)
		SetSettingColor(visuals_glowEsp_friends_color)
		SetSettingColor(visuals_glowEsp_hpBased_0hp_color)
		SetSettingColor(visuals_glowEsp_hpBased_100hp_color)
		SetSetting(visuals_glowEsp_show_c4)
		SetSettingColor(visuals_glowEsp_c4_color)
		SetSettingColor(visuals_glowEsp_c4_planted_color)
		SetSetting(visuals_glowEsp_show_defusing)
		SetSettingColor(visuals_glowEsp_defusing_color)
		SetSetting(visuals_glowEsp_show_grenades)
		SetSettingColor(visuals_glowEsp_grenades_color)

		SetSetting(visuals_chams_enable)
		SetSetting(visuals_chams_show_enemies)
		SetSettingColor(visuals_chams_enemy_color)
		SetSetting(visuals_chams_show_friends)
		SetSettingColor(visuals_chams_friends_color)

		//SKINCHANGER
		SetSettingSkinchangerWeapons(skinchanger_weapons)
		SetSettingSkinchangerKnives(skinchanger_knives)

		//MISC
		SetSetting(misc_ingameRadar_enable)
		SetSetting(misc_bhop_enable)
		SetSetting(misc_autoPistols_enable)
		SetSetting(misc_autoPistols_delay)
		SetSetting(misc_autoAccept_enable)
		SetSetting(skinchanger_enable)
		SetSetting(misc_antiFlash_enable)
		SetSetting(misc_antiFlash_maxAlpha);
	
	return settings;
}

#pragma region Initialization
//AIM BOT
bool Settings::aimbot_enable = false;
int Settings::aimbot_key = 0;
bool Settings::aimbot_use_key = false;
int Settings::aimbot_delay_enemy = 0;
bool Settings::aimbot_visible_check = false;
bool Settings::aimbot_flash_check = false;
bool Settings::aimbot_jump_check = false;
bool Settings::aimbot_friendly_fire = false;

IAimbotSettings Settings::aimbot_global = {
	false,
	false,
	0,
	Skeleton::NEAREST,
	0,
	false,
	0.0f,
	0.0f
};
IAimbotSettings Settings::aimbot_pistols = {
	false,
	false,
	0,
	Skeleton::NEAREST,
	0,
	false,
	0.0f,
	0.0f
};
IAimbotSettings Settings::aimbot_heavies = {
	false,
	false,
	0,
	Skeleton::NEAREST,
	0,
	false,
	0.0f,
	0.0f
};
IAimbotSettings Settings::aimbot_shoutguns = {
	false,
	false,
	0,
	Skeleton::NEAREST,
	0,
	false,
	0.0f,
	0.0f
};
IAimbotSettings Settings::aimbot_smgs = {
	false,
	false,
	0,
	Skeleton::NEAREST,
	0,
	false,
	0.0f,
	0.0f
};
IAimbotSettings Settings::aimbot_rifles = {
	false,
	false,
	0,
	Skeleton::NEAREST,
	0,
	false,
	0.0f,
	0.0f
};
IAimbotSettings Settings::aimbot_snipers = {
	false,
	false,
	0,
	Skeleton::NEAREST,
	0,
	false,
	0.0f,
	0.0f
};
std::map<ItemDefinitionIndex, IAimbotSettings> Settings::aimbot_weapons = {};

//TRIGGERBOT
bool Settings::triggerbot_enable = false;
bool Settings::triggerbot_use_key = false;
int Settings::triggerbot_key = 0;
bool Settings::triggerbot_friendly_fire = false;
bool Settings::triggerbot_flash_check = false;
bool Settings::triggerbot_jump_check = false;
int Settings::triggerbot_delay_before_shoot = 0;
int Settings::triggerbot_delay_after_shoot = 0;
bool Settings::triggerbot_pistols_enable = false;
bool Settings::triggerbot_heavies_enable = false;
bool Settings::triggerbot_shoutguns_enable = false;
bool Settings::triggerbot_smgs_enable = false;
bool Settings::triggerbot_rifles_enable = false;
bool Settings::triggerbot_snipers_enable = false;

//VISUALS
bool Settings::visuals_glowEsp_enable = false;
bool Settings::visuals_glowEsp_show_enemies = false;
EVisualsGlowEspMode Settings::visuals_glowEsp_mode = VISUALS_GLOWESP_MODE_COLOR;
GlowStyle Settings::visuals_glowEsp_style = GlowStyle::GLOW_STYLE_FULL_BODY;
colorRGBA Settings::visuals_glowEsp_enemy_visible_color = { 0.0f, 0.0f, 0.0f, 0.0f };
colorRGBA Settings::visuals_glowEsp_enemy_invisible_color = { 0.0f, 0.0f, 0.0f, 0.0f };
bool Settings::visuals_glowEsp_show_friends = false;
colorRGBA Settings::visuals_glowEsp_friends_color = { 0.0f, 0.0f, 0.0f, 0.0f };
colorRGBA Settings::visuals_glowEsp_hpBased_0hp_color = { 0.0f, 0.0f, 0.0f, 0.0f };
colorRGBA Settings::visuals_glowEsp_hpBased_100hp_color = { 0.0f, 0.0f, 0.0f, 0.0f };
bool Settings::visuals_glowEsp_show_c4 = false;
colorRGBA Settings::visuals_glowEsp_c4_color = { 0.0f, 0.0f, 0.0f, 0.0f };
colorRGBA Settings::visuals_glowEsp_c4_planted_color = { 0.0f, 0.0f, 0.0f, 0.0f };
bool Settings::visuals_glowEsp_show_defusing = false;
colorRGBA Settings::visuals_glowEsp_defusing_color = { 0.0f, 0.0f, 0.0f, 0.0f };
bool Settings::visuals_glowEsp_show_grenades = false;
colorRGBA Settings::visuals_glowEsp_grenades_color = { 0.0f, 0.0f, 0.0f, 0.0f };

bool Settings::visuals_chams_enable = false;
bool Settings::visuals_chams_show_enemies = false;
colorRGBA Settings::visuals_chams_enemy_color = { 0.0f, 0.0f, 0.0f, 0.0f };
bool Settings::visuals_chams_show_friends = false;
colorRGBA Settings::visuals_chams_friends_color = { 0.0f, 0.0f, 0.0f, 0.0f };

//SKINCHAGER
bool Settings::skinchanger_enable = false;
std::map<ItemDefinitionIndex, ISkinchangerWeapon> Settings::skinchanger_weapons = {};
std::map<TeamNum, ISkinchangerWeapon> Settings::skinchanger_knives = {};

//MISC
bool Settings::misc_ingameRadar_enable = false;
bool Settings::misc_bhop_enable = false;
bool Settings::misc_autoPistols_enable = false;
int Settings::misc_autoPistols_delay = 0;
bool Settings::misc_autoAccept_enable = false;
bool Settings::misc_antiFlash_enable = false;
int Settings::misc_antiFlash_maxAlpha = 255;
#pragma endregion