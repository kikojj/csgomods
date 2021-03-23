#include "Skinchanger.hpp"

void Skinchanger::applyWeaponSettings(BaseCombatWeapon weapon, ISkinchangerWeapon settings){
	weapon.m_iItemIDHigh(-1);
	weapon.m_iAccountID(weapon.m_OriginalOwnerXuidLow());

	weapon.m_nFallbackPaintKit(settings.paintKit);

	weapon.m_flFallbackWear(settings.wear);

	if (settings.quality != EntityQuality::Invalid) {
		weapon.entityQuality(settings.quality);
	}
	else if (weapon.isKnife()) {
		weapon.entityQuality(EntityQuality::QUALITY_UNUSUAL);
	}

	if (settings.customName != "") {
		weapon.m_szCustomName(settings.customName);
	}
	if (settings.statTrack >= 0) {
		if (settings.quality == EntityQuality::Invalid || settings.quality == EntityQuality::QUALITY_NORMAL) {
			weapon.entityQuality(EntityQuality::QUALITY_STRANGE);
		}
		weapon.m_nFallbackStatTrak(settings.statTrack);
	}
	if (settings.seed > 0) {
		weapon.m_nFallbackSeed(settings.seed);
	}
}

void Skinchanger::applyKnifeSettings(BaseCombatWeapon knife, ISkinchangerWeapon settings){
	auto weaponModel = modelIndexes[settings.itemDI];

	knife.itemDI(settings.itemDI);
	knife.m_nModelIndex(weaponModel);
	knife.m_iViewModelIndex(weaponModel);

	applyWeaponSettings(knife, settings);
}

Skinchanger::Skinchanger(){}

void Skinchanger::loop() {
	if (
		engine.clientState->state() != ClientStates::INGAME ||
		client.localPlayer->m_iHealth() <= 0 ||
		client.localPlayer->teamNum() < TeamNum::TERRORIST
		) {
		return;
	}

	if (!Settings::skinchanger_enable) {
		return;
	}

	auto localPlayerTeam = client.localPlayer->teamNum();

	for (auto weaponId : client.localPlayer->myWeapons()) {
		BaseCombatWeapon weapon(client.entityList->getByID(weaponId - 1));

		if (!weapon.get()) {
			continue;
		}

		auto weaponDI = weapon.itemDI();
		auto weaponModel =  modelIndexes[Settings::skinchanger_knives[localPlayerTeam].itemDI];
		if (weapon.isKnife() && weaponModel > 0 && Settings::skinchanger_knives[localPlayerTeam].enable) {
			applyKnifeSettings(weapon, Settings::skinchanger_knives[localPlayerTeam]);
		}
		else if (Settings::skinchanger_weapons[weaponDI].enable) {
			applyWeaponSettings(weapon, Settings::skinchanger_weapons[weaponDI]);
		}
	}

	auto activeWeaponID = client.localPlayer->m_hActiveWeapon() & 0xfff;
	BaseCombatWeapon activeWeapon(client.entityList->getByID(activeWeaponID - 1));
	if (!activeWeapon.get() || !activeWeapon.isKnife()) {
		return;
	}

	int knifeViewModelID = client.localPlayer->m_hViewModel() & 0xfff;
	BaseCombatWeapon knife(client.entityList->getByID((knifeViewModelID - 1)));
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