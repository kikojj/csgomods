#include "TriggerBot.hpp"

TriggerBot::TriggerBot() {}

void TriggerBot::loop() {
	if (!Settings::triggerbot_enable) {
		shouldShoot = false;
		shouldWait = false;
		return;
	}

	if (
		engine.clientState->state() != ClientStates::INGAME ||
		engine.clientState->m_nDeltaTick() == -1 ||
		client.localPlayer->m_iHealth() <= 0 ||
		client.localPlayer->teamNum() < TeamNum::TERRORIST ||
		client.localPlayer->m_bDormant() ||
		!Helpers::isMouseActive()
		) {
		shouldShoot = false;
		shouldWait = false;
		return;
	}

	if (Settings::triggerbot_use_key && !GetAsyncKeyState(Settings::triggerbot_key)) {
		shouldShoot = false;
		shouldWait = false;
		return;
	}

	if (Settings::aimbot_flash_check && Helpers::isFlashed(client.localPlayer->m_flFlashAlpha())) {
		shouldShoot = false;
		shouldWait = false;
		return;
	}

	if (Settings::aimbot_jump_check && !FlagsState::isOnGround(client.localPlayer->m_fFlags())) {
		shouldShoot = false;
		shouldWait = false;
		return;
	}

	int activeWeaponID = client.localPlayer->m_hActiveWeapon() & 0xfff;
	BaseWeapon activeWeapon(client.entityList->getByID(activeWeaponID - 1));

	if (activeWeapon.isPistol()) {
		if (!Settings::triggerbot_pistols_enable) {
			shouldShoot = false;
			shouldWait = false;
			return;
		}
	}
	else if (activeWeapon.isHeavy()) {
		if (!Settings::triggerbot_heavies_enable) {
			shouldShoot = false;
			shouldWait = false;
			return;
		}
	}
	else if (activeWeapon.isShotgun()) {
		if (!Settings::triggerbot_shoutguns_enable) {
			shouldShoot = false;
			shouldWait = false;
			return;
		}
	}
	else if (activeWeapon.isSMG()) {
		if (!Settings::triggerbot_smgs_enable) {
			shouldShoot = false;
			shouldWait = false;
			return;
		}
	}
	else if (activeWeapon.isRifle()) {
		if (!Settings::triggerbot_rifles_enable) {
			shouldShoot = false;
			shouldWait = false;
			return;
		}
	}
	else if (activeWeapon.isSnipers()) {
		if (!Settings::triggerbot_snipers_enable) {
			shouldShoot = false;
			shouldWait = false;
			return;
		}
	}
	else if (activeWeapon.isKnife()) {
		shouldShoot = false;
		shouldWait = false;
		return;
	}
	else if (activeWeapon.isBomb()) {
		shouldShoot = false;
		shouldWait = false;
		return;
	}
	else if (activeWeapon.isGrenade()) {
		shouldShoot = false;
		shouldWait = false;
		return;
	}
	else if (activeWeapon.isZeusX27()) {
		shouldShoot = false;
		shouldWait = false;
		return;
	}
	else {
		std::cout << "[Trigger]: Undefined weapon ID = " << (int)activeWeapon.itemDI() << std::endl;
		shouldShoot = false;
		shouldWait = false;
		return;
	}

	BaseEntity entity(client.entityList->getByID(client.localPlayer->m_iCrosshairId() - 1));
	if (entity.classID() != ClassID::CCSPlayer) {
		shouldShoot = false;
		shouldWait = false;
		return;
	}

	BasePlayer player(entity);
	if (!Settings::triggerbot_friendly_fire && player.m_iTeamNum() == client.localPlayer->m_iTeamNum()) {
		shouldShoot = false;
		shouldWait = false;
		return;
	}

	if (!shouldShoot) {
		lastPressTime = std::chrono::high_resolution_clock::now();
		shouldShoot = true;
	}
	else if (!shouldWait) {
		if (activeWeapon.isPistol()) {
			shouldShoot = false;
		}
	}

	if (
		std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - lastPressTime).count() >
		(double)((double)Settings::triggerbot_delay_before_shoot / (double)1000)
		) {
		shouldWait = false;
	}
	else {
		shouldWait = true;
	}
}