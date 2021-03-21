#include "Skinchanger.hpp"

void Skinchanger::applyWeaponSettings(BaseCombatWeapon weapon, ISkinchangerWeapon settings){
	weapon.m_iItemIDHigh(-1);
	weapon.m_iAccountID(weapon.m_OriginalOwnerXuidLow());

	weapon.m_nFallbackPaintKit(settings.paintKit);

	weapon.m_flFallbackWear(settings.wear);

	if (settings.quality != INVALID_QUALITY) {
		weapon.m_iEntityQuality(settings.quality);
	}
	else if (weapon.isKnife()) {
		weapon.m_iEntityQuality(QUALITY_UNUSUAL);		
	}

	if (settings.customName != "") {
		weapon.m_szCustomName(settings.customName);
	}
	if (settings.statTrack >= 0) {
		if (settings.quality == INVALID_QUALITY || settings.quality == QUALITY_NORMAL) {
			weapon.m_iEntityQuality(QUALITY_STRANGE);
		}
		weapon.m_nFallbackStatTrak(settings.statTrack);
	}
	if (settings.seed > 0) {
		weapon.m_nFallbackSeed(settings.seed);
	}
}

void Skinchanger::applyKnifeSettings(BaseCombatWeapon knife, ISkinchangerWeapon settings){
	auto weaponModel = modelIndexes[settings.itemDI];

	knife.m_iItemDefinitionIndex(settings.itemDI);
	knife.m_nModelIndex(weaponModel);
	knife.m_iViewModelIndex(weaponModel);

	applyWeaponSettings(knife, settings);
}

Skinchanger::Skinchanger(){}

void Skinchanger::loop() {
	if (
		engine.clientState->state() != INGAME ||
		client.localPlayer->m_iHealth() <= 0 ||
		client.localPlayer->m_iTeamNum() < TERRORIST
		) {
		return;
	}

	if (!Settings::skinchanger_enable) {
		return;
	}

	auto localPlayerTeam = client.localPlayer->m_iTeamNum();

	for (auto weaponId : client.localPlayer->myWeapons()) {
		BaseCombatWeapon weapon = BaseCombatWeapon(client.entityList->getByID(weaponId - 1));

		if (!weapon.get()) {
			continue;
		}

		auto weaponDI = weapon.m_iItemDefinitionIndex();
		auto weaponModel =  modelIndexes[Settings::skinchanger_knives[localPlayerTeam].itemDI];
		if (weapon.isKnife() && weaponModel > 0 && Settings::skinchanger_knives[localPlayerTeam].enable) {
			applyKnifeSettings(weapon, Settings::skinchanger_knives[localPlayerTeam]);
		}
		else if (Settings::skinchanger_weapons[weaponDI].enable) {
			applyWeaponSettings(weapon, Settings::skinchanger_weapons[weaponDI]);
		}
	}

	auto activeWeaponID = client.localPlayer->m_hActiveWeapon() & 0xfff;
	BaseCombatWeapon activeWeapon = BaseCombatWeapon(client.entityList->getByID(activeWeaponID - 1));
	if (!activeWeapon.get() || !activeWeapon.isKnife()) {
		return;
	}

	int knifeViewModelID = client.localPlayer->m_hViewModel() & 0xfff;
	auto knife = BaseCombatWeapon(client.entityList->getByID((knifeViewModelID - 1)));
	if (!knife.get() || !Settings::skinchanger_knives[localPlayerTeam].enable) {
		return;
	}

	auto knifeModel = modelIndexes[Settings::skinchanger_knives[localPlayerTeam].itemDI];
	if (knifeModel <= 0) {
		return;
	}

	knife.m_nModelIndex(knifeModel);
	knife.m_hWeaponWorldModel(knifeModel + 1);
}