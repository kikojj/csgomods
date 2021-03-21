#include "Misc.hpp"

Misc::Misc() {}

void Misc::radarHack(){
	if (!Settings::misc_ingameRadar_enable) {
		return;
	}

	if (engine.clientState->state() != INGAME || engine.clientState->m_nDeltaTick() == -1) {
		return;
	}

	for (auto entity : client.entityList->array()) {
		if (entity.m_iClassID() != CCSPlayer) {
			continue;
		}

		BasePlayer player(entity);

		if (player.m_iTeamNum() == client.localPlayer->m_iTeamNum()) {
			continue;
		}

		if (player.m_iHealth() <= 0) {
			continue;
		}

		if (!player.m_bSpotted()) {
			player.m_bSpotted(true);
		}
	}
}

void Misc::bhop() {
	if (!Settings::misc_bhop_enable) {
		return;
	}

	if (
		engine.clientState->state() != INGAME ||
		client.localPlayer->m_iHealth() <= 0 ||
		client.localPlayer->m_iTeamNum() < TERRORIST ||
		engine.clientState->m_nDeltaTick() == -1 ||
		!Helpers::isMouseActive()
		) {
		return;
	}

	if (!GetAsyncKeyState(VK_SPACE)) {
		return;
	}

	if (client.localPlayer->m_vecVelocity().isZero()) {
		return;
	}

	if (FlagsState::isOnGround(client.localPlayer->m_fFlags())) {
		client.dwForceJump(KEY_DOWN);
	}
	else {
		client.dwForceJump(KEY_UP);
	}
}

void Misc::autoPistols(){
	if (!Settings::misc_autoPistols_enable) {
		return;
	}

	if (
		engine.clientState->state() != INGAME ||
		client.localPlayer->m_iHealth() <= 0 ||
		client.localPlayer->m_iTeamNum() < TERRORIST ||
		engine.clientState->m_nDeltaTick() == -1 ||
		!Helpers::isMouseActive()
		) {
		return;
	}

	if (!GetAsyncKeyState(VK_LBUTTON)) {
		return;
	}

	int activeWeaponID = client.localPlayer->m_hActiveWeapon() & 0xfff;
	BaseCombatWeapon activeWeapon = BaseCombatWeapon(client.entityList->getByID(activeWeaponID - 1));

	if (activeWeapon.isPistol() && activeWeapon.m_iItemDefinitionIndex() != WEAPON_R8Revolver && activeWeapon.m_iItemDefinitionIndex() != WEAPON_CZ75Auto) {
		while (GetAsyncKeyState(VK_LBUTTON)) {
			client.dwForceAttack(KEY_PRESS);
			Sleep(Settings::misc_autoPistols_delay);
		}
	}
}

void Misc::antiFlash(){
	if (!Settings::misc_antiFlash_enable) {
		return;
	}

	if (
		engine.clientState->state() != INGAME ||
		client.localPlayer->m_iHealth() <= 0 ||
		client.localPlayer->m_iTeamNum() < TERRORIST ||
		engine.clientState->m_nDeltaTick() == -1
		) {
		return;
	}

	if (client.localPlayer->m_flFlashMaxAlpha() != Settings::misc_antiFlash_maxAlpha) {
		client.localPlayer->m_flFlashMaxAlpha(Settings::misc_antiFlash_maxAlpha);
	}
}

void Misc::autoAccept(){
	if (!Settings::misc_autoAccept_enable) {
		return;
	}

	if (engine.clientState->state() != LOBBY) {
		return;
	}

	callback = client.confirmReservationCallback();

	if (callback){
		if (prevCallback != callback){
			prevCallback = callback;
			found = false;
			accepted = false;
		}

		if (!found){
			found = true;
			Sleep(5000);
		}
		else if (!accepted){
			accepted = true;
			mem.createThread(client.hConfirmMatch());
			std::cout << "[AUTO ACCEPT]: Math was found. Tried to accept the match." << std::endl;
		}
	}
	else{
		found = false;
		accepted = false;
	}
}
