#include "AimBot.hpp"

AimBot::AimBot() {}

Vector3 AimBot::getBonePos(BasePlayer& player, Skeleton bone) {
	return Vector3(mem.Read<BoneVector>(player.m_dwBoneMatrix() + 0x30 * bone + 0x0C));
}

Vector3 AimBot::calcAngle(Vector3 src, Vector3 dst) {
	Vector3 angle;

	auto delta = src - dst;
	auto hyp = FastSQRT(pow(delta.x, 2) + pow(delta.y, 2));

	angle.x = (float)(atan(delta.z / hyp) * M_RADPI);
	angle.y = (float)(atan(delta.y / delta.x) * M_RADPI);
	angle.z = 0;

	//RCS for Aimbot
	if (this->rcsEnable && client.localPlayer->m_iShotsFired() > 1){
		auto aimPunch = client.localPlayer->m_aimPunchAngle();

		angle.x -= aimPunch.x * (this->rcsScaleX * 0.02f);
		angle.y -= aimPunch.y * (this->rcsScaleY * 0.02f);
	}

	if (delta.x >= 0.0) {
		angle.y += 180.0f;
	}

	angle.clamp();

	return angle;
}

float AimBot::getFov(Vector3 currentAngle, Vector2 dstAngle) {
	return (float)FastSQRT(pow(dstAngle.x - currentAngle.x, 2) + pow(dstAngle.y - currentAngle.y, 2) + pow(0 - currentAngle.z, 2));
}

void AimBot::setAngle(Vector2 dstAngle) {
	if (this->smooth > 0)
	{
		auto viewAngle = engine.clientState->dwViewAngles();

		auto delta = viewAngle - dstAngle;
		delta.clamp();

		//set dstAngle if delta is so low
		if (abs(delta.x) > 0.1 || abs(delta.y) > 0.1) {
			dstAngle.x = viewAngle.x - delta.x / (5.f * this->smooth);
			dstAngle.y = viewAngle.y - delta.y / (5.f * this->smooth);
		}
	}

	engine.clientState->dwViewAngles(dstAngle);
}

void AimBot::applyWeaponSettings(IAimbotSettings settings){
	this->fov = settings.fov;
	this->bone = settings.bone;
	this->smooth = settings.smooth;
	this->rcsEnable = settings.rcs_enable;
	this->rcsScaleX = settings.rcs_scale_x;
	this->rcsScaleY = settings.rcs_scale_y;
}

bool AimBot::applyWeaponsSettings(BaseCombatWeapon weapon){
	auto itemDI = weapon.m_iItemDefinitionIndex();

	//weapon settings
	if (Settings::aimbot_weapons[itemDI].enable) {
		applyWeaponSettings(Settings::aimbot_weapons[itemDI]);
		return true;
	}

	//section settings
	if (weapon.isPistol()) {
		if (Settings::aimbot_pistols.enable) {
			applyWeaponSettings(Settings::aimbot_pistols);
			return true;
		}
	}
	else if (weapon.isHeavy()) {
		if (Settings::aimbot_heavies.enable) {
			applyWeaponSettings(Settings::aimbot_heavies);
			return true;
		}
	}
	else if (weapon.isShotgun()) {
		if (Settings::aimbot_shoutguns.enable) {
			applyWeaponSettings(Settings::aimbot_shoutguns);
			return true;
		}
	}
	else if (weapon.isSMG()) {
		if (Settings::aimbot_smgs.enable) {
			applyWeaponSettings(Settings::aimbot_smgs);
			return true;
		}
	}
	else if (weapon.isRifle()) {
		if (Settings::aimbot_rifles.enable) {
			applyWeaponSettings(Settings::aimbot_rifles);
			return true;
		}
	}
	else if (weapon.isSnipers()) {
		if (Settings::aimbot_snipers.enable) {
			applyWeaponSettings(Settings::aimbot_snipers);
			return true;
		}
	}
	else if (weapon.isKnife() || weapon.isZeusX27() || weapon.isBomb() || weapon.isGrenade()) {
		return false;
	}
	else {
		return false;
	}

	//global settings
	if (Settings::aimbot_global.enable) {
		applyWeaponSettings(Settings::aimbot_global);
		return true;
	}

	return false;
}

void AimBot::loop() {
	if (!Settings::aimbot_enable) {
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

	if (Settings::aimbot_flash_check && Helpers::isFlashed(client.localPlayer->m_flFlashAlpha())) {
		return;
	}

	if (Settings::aimbot_jump_check && !FlagsState::isOnGround(client.localPlayer->m_fFlags())) {
		return;
	}

	if (Settings::aimbot_use_key && !GetAsyncKeyState(Settings::aimbot_key)) {
		return;
	}

	int activeWeaponID = client.localPlayer->m_hActiveWeapon() & 0xfff;
	BaseCombatWeapon activeWeapon = BaseCombatWeapon(client.entityList->getByID(activeWeaponID - 1));

	if (!activeWeapon.dwBase || !applyWeaponsSettings(activeWeapon)) {
		return;
	}

	BasePlayer closestEnemy;
	float closestAngle = 360.0f;
	Skeleton closestBone = HEAD;

	for (auto entity : client.entityList->array()) {
		if (!entity.dwBase || entity.dwBase == client.localPlayer->get()) {
			continue;
		}

		if (entity.m_iClassID() != CCSPlayer) {
			continue;
		}

		BasePlayer player(entity);

		if (player.m_iHealth() <= 0) {
			continue;
		}

		if (!Settings::aimbot_friendly_fire && player.m_iTeamNum() == client.localPlayer->m_iTeamNum()) {
			continue;
		}

		if (Settings::aimbot_visible_check && !client.localPlayer->canSeePlayer(player)) {
			continue;
		}

		std::vector<Skeleton> aimBones;
		if (this->bone == NEAREST) {
			aimBones = ALL_BONES;
		}
		else {
			aimBones.push_back(this->bone);
		}

		for (auto bone : aimBones) {
			auto localPlayerPos = client.localPlayer->m_vecOrigin() + client.localPlayer->m_vecViewOffset();
			auto bonePos = getBonePos(player, bone);
			if (!client.localPlayer->canSeePlayer(player, bone)) {
				continue;
			}
			auto enemyAngle = calcAngle(localPlayerPos, bonePos);
			float fov = getFov(enemyAngle, engine.clientState->dwViewAngles());

			if (fov < this->fov && fov < closestAngle) {
				closestEnemy = player;
				closestAngle = fov;
				closestBone = bone;
			}
		}

	}

	if (closestEnemy.dwBase <= 0) {
		return;
	}

	if (Settings::aimbot_use_key) {
		while (
			GetAsyncKeyState(VK_LBUTTON) &&
			closestEnemy.m_iHealth() > 0 &&
			(!Settings::aimbot_visible_check || client.localPlayer->canSeePlayer(closestEnemy))
			) {
			auto localPlayerPos = client.localPlayer->m_vecOrigin() + client.localPlayer->m_vecViewOffset();
			auto enemyAngle = calcAngle(localPlayerPos, getBonePos(closestEnemy, closestBone));

			setAngle(enemyAngle.toVector2());

			//If nearest go to the main bone after closest bone
			if (bone == NEAREST && getFov(enemyAngle, engine.clientState->dwViewAngles()) == 0 && std::find(MAIN_BONES.begin(), MAIN_BONES.end(), closestBone) == MAIN_BONES.end()) {
				closestAngle = 360.f;
				for (auto bone : MAIN_BONES) {
					auto bonePos = getBonePos(closestEnemy, bone);
					if (!client.localPlayer->canSeePlayer(closestEnemy, bone)) {
						continue;
					}
					auto _enemyAngle = calcAngle(localPlayerPos, bonePos);
					float fov = getFov(_enemyAngle, engine.clientState->dwViewAngles());

					if (fov < closestAngle) {
						closestAngle = fov;
						closestBone = bone;
					}
				}
			}
			/*
			// CHANGE BONE TO MAIN BONE AFTER GETTING CURRENT BONE IF BONE IS NOT MAIN

			if (std::find(MAIN_BONES.begin(), MAIN_BONES.end(), closestBone) == MAIN_BONES.end() && getFov(enemyAngle, engine.clientState->dwViewAngles()) == 0) {
				closestAngle = 360.0f;
				for (auto bone : MAIN_BONES) {
					auto enemyAngle = calcAngle(client.localPlayer->m_vecOrigin() + client.localPlayer->m_vecViewOffset(), getBonePos(closestEnemy, bone));
					float fov = getFov(enemyAngle, engine.clientState->dwViewAngles());

					if (fov < this->_fov && fov < closestAngle) {
						closestAngle = fov;
						closestBone = bone;
					}
				}
			}
			*/

			//TRY TO DO GOOD SMOOTH(NEED UNBIND MOUSE1 IN GAME)
			//if (getFov(enemyAngle, engine.clientState->dwViewAngles()) == 0 && client.localPlayer->m_iShotsFired() == 0){
			//	client.dwForceAttack(KEY_PRESS);
			//}
		}
	}
	else {
		if (
			closestEnemy.m_iHealth() > 0 &&
			(!Settings::aimbot_visible_check || client.localPlayer->canSeePlayer(closestEnemy))
			) {
			auto localPlayerPos = client.localPlayer->m_vecOrigin() + client.localPlayer->m_vecViewOffset();
			auto enemyAngle = calcAngle(localPlayerPos, getBonePos(closestEnemy, closestBone));

			setAngle(enemyAngle.toVector2());
		}
	}

	if (closestEnemy.m_iHealth() <= 0) {
		Sleep(Settings::aimbot_delay_enemy);
	}
}
