#include "Misc.hpp"

Misc::Misc() {}

void Misc::radarHack(){
	if (!Settings::misc_ingameRadar_enable) {
		return;
	}

	if (engine.clientState->state() != ClientStates::INGAME || engine.clientState->m_nDeltaTick() == -1) {
		return;
	}

	for (auto entity : client.entityList->array()) {
		if (entity.classID() != ClassID::CCSPlayer) {
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
		engine.clientState->state() != ClientStates::INGAME ||
		client.localPlayer->m_iHealth() <= 0 ||
		client.localPlayer->teamNum() < TeamNum::TERRORIST ||
		engine.clientState->m_nDeltaTick() == -1 ||
		!Helpers::isMouseActive()
		) {
		return;
	}

	if (!GetAsyncKeyState(VK_SPACE)) {
		return;
	}

	if (Vector3(client.localPlayer->m_vecVelocity()).isZero()) {
		return;
	}

	if (FlagsState::isOnGround(client.localPlayer->m_fFlags())) {
		client.dwForceJump(KeyEvent::KEY_DOWN);
	}
	else {
		client.dwForceJump(KeyEvent::KEY_UP);
	}
}

void Misc::autoPistols(){
	if (!Settings::misc_autoPistols_enable) {
		shouldShoot = false;
		shouldWait = false;
		return;
	}

	if (
		engine.clientState->state() != ClientStates::INGAME ||
		client.localPlayer->m_iHealth() <= 0 ||
		client.localPlayer->teamNum() < TeamNum::TERRORIST ||
		engine.clientState->m_nDeltaTick() == -1 ||
		!Helpers::isMouseActive()
		) {
		shouldShoot = false;
		shouldWait = false;
		return;
	}

	if (!GetAsyncKeyState(VK_LBUTTON)) {
		shouldShoot = false;
		shouldWait = false;
		return;
	}

	int activeWeaponID = client.localPlayer->m_hActiveWeapon() & 0xfff;
	BaseCombatWeapon activeWeapon(client.entityList->getByID(activeWeaponID - 1));

	if (activeWeapon.isPistol() && activeWeapon.itemDI() != ItemDefinitionIndex::WEAPON_R8Revolver && activeWeapon.itemDI() != ItemDefinitionIndex::WEAPON_CZ75Auto) {
		while (GetAsyncKeyState(VK_LBUTTON)) {
			shouldShoot = true;

			using namespace std::chrono;

			high_resolution_clock::time_point killTime = high_resolution_clock::now();
			shouldWait = true;
			while (
				GetAsyncKeyState(Settings::triggerbot_key) &&
				duration_cast<std::chrono::duration<double>>(high_resolution_clock::now() - killTime).count() <= (double)((double)Settings::misc_autoPistols_delay / (double)1000)
				) {
			}
			shouldWait = false;
		}
	}
}

void Misc::antiFlash(){
	if (!Settings::misc_antiFlash_enable) {
		return;
	}

	if (
		engine.clientState->state() != ClientStates::INGAME ||
		client.localPlayer->m_iHealth() <= 0 ||
		client.localPlayer->teamNum() < TeamNum::TERRORIST ||
		engine.clientState->m_nDeltaTick() == -1
		) {
		return;
	}

	if (client.localPlayer->m_flFlashMaxAlpha() != Settings::misc_antiFlash_maxAlpha) {
		client.localPlayer->m_flFlashMaxAlpha((float)Settings::misc_antiFlash_maxAlpha);
	}
}

void Misc::autoAccept(){
	if (!Settings::misc_autoAccept_enable) {
		return;
	}

	if (engine.clientState->state() != ClientStates::LOBBY) {
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
