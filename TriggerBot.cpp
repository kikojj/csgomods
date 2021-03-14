#include "TriggerBot.hpp"

TriggerBot::TriggerBot() {}

void TriggerBot::loop() {
	if (!Settings::triggerbot_enable) {
		return;
	}

	if (
		engine.clientState->state() != INGAME ||
		engine.clientState->m_nDeltaTick() == -1 ||
		client.localPlayer->m_iHealth() <= 0 ||
		client.localPlayer->m_iTeamNum() < TERRORIST ||
		client.localPlayer->m_bDormant() ||
		!Helpers::isMouseActive()
		) {
		return;
	}

	if (Settings::triggerbot_use_key && !GetAsyncKeyState(Settings::triggerbot_key)) {
		return;
	}

	if (Settings::aimbot_flash_check && Helpers::isFlashed(client.localPlayer->m_flFlashAlpha())) {
		return;
	}

	if (Settings::aimbot_jump_check && !FlagsState::isOnGround(client.localPlayer->m_fFlags())) {
		return;
	}

	int activeWeaponID = client.localPlayer->m_hActiveWeapon() & 0xfff;
	BaseCombatWeapon activeWeapon = BaseCombatWeapon(client.entityList->getByID(activeWeaponID - 1));

	if (activeWeapon.isPistol()) {
		if (!Settings::triggerbot_pistols_enable) {
			return;
		}
	}
	else if (activeWeapon.isHeavy()) {
		if (!Settings::triggerbot_heavies_enable) {
			return;
		}
	}
	else if (activeWeapon.isShotgun()) {
		if (!Settings::triggerbot_shoutguns_enable) {
			return;
		}
	}
	else if (activeWeapon.isSMG()) {
		if (!Settings::triggerbot_smgs_enable) {
			return;
		}
	}
	else if (activeWeapon.isRifle()) {
		if (!Settings::triggerbot_rifles_enable) {
			return;
		}
	}
	else if (activeWeapon.isSnipers()) {
		if (!Settings::triggerbot_snipers_enable) {
			return;
		}
	}
	else if (activeWeapon.isKnife()) {
		return;
	}
	else if (activeWeapon.isBomb()) {
		return;
	}
	else if (activeWeapon.isGrenade()) {
		return;
	}
	else if (activeWeapon.isZeusX27()) {
		return;
	}
	else {
		std::cout << "[Trigger]: Undefined weapon ID = " << activeWeapon.m_iItemDefinitionIndex() << std::endl;
		return;
	}

	BaseEntity entity(client.entityList->getByID(client.localPlayer->m_iCrosshairId() - 1));
	if (entity.m_iClassID() != CCSPlayer) {
		Sleep(Settings::triggerbot_delay_before_shoot);
		return;
	}

	BasePlayer player(entity);
	if (!Settings::triggerbot_friendly_fire && player.m_iTeamNum() == client.localPlayer->m_iTeamNum()) {
		return;
	}

	Helpers::shoot();
	Sleep(Settings::triggerbot_delay_after_shoot);
}