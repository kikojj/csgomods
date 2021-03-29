#include "AimBot.hpp"

AimBot::AimBot() {}

void AimBot::resetSettings(){
	closestEnemy.base = 0;
	closestAngle = 360.0f;
	shouldShoot = false;
	shouldWait = false;
}

Vector3 AimBot::getBonePos(BasePlayer& player, Skeleton bone) {
	return Vector3(mem.read<BoneVector>(player.m_dwBoneMatrix() + 0x30 * (int)bone + 0x0C));
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
	if (client.localPlayer->m_iShotsFired() > 1) {
		Vector2 viewAngle = Vector2(engine.clientState->dwViewAngles());

		auto delta = viewAngle - dstAngle;
		delta.clamp();

		//skip if delta is so low
		if (abs(delta.x) > 0.1 || abs(delta.y) > 0.1) {
			if (this->rcsEnable) {
				dstAngle.x = viewAngle.x - delta.x / (std::abs(100 - this->rcsScaleX) >= 1 ? std::abs(100 - this->rcsScaleX) : 1);
				dstAngle.y = viewAngle.y - delta.y / (std::abs(100 - this->rcsScaleY) >= 1 ? std::abs(100 - this->rcsScaleY) : 1);
			}
			else {
				dstAngle.x = viewAngle.x - delta.x / 100;
				dstAngle.y = viewAngle.y - delta.y / 100;
			}
		}
	}
	else {
		if (this->smooth > 0) {
			Vector2 viewAngle = Vector2(engine.clientState->dwViewAngles());

			auto delta = viewAngle - dstAngle;
			delta.clamp();

			//skip if delta is so low
			if (abs(delta.x) > 0.1 || abs(delta.y) > 0.1) {
				dstAngle.x = viewAngle.x - delta.x / this->smooth;
				dstAngle.y = viewAngle.y - delta.y / this->smooth;
			}
		}
	}

	engine.clientState->dwViewAngles(dstAngle.toVec2());
}

void AimBot::applyWeaponSettings(IAimbotSettings settings){
	this->firstPerfectShoot = settings.firstPerfectShoot;
	this->fov = settings.fov;
	this->bone = settings.bone;
	this->changeAfterNearest = settings.changeAfterNearest;
	this->smooth = settings.smooth;
	this->rcsEnable = settings.rcsEnable;
	this->rcsScaleX = settings.rcsScaleX;
	this->rcsScaleY = settings.rcsScaleY;
}

bool AimBot::applyWeaponsSettings(BaseWeapon weapon){
	auto itemDI = weapon.itemDI();

	//weapon settings
	if (Settings::aimbot_weapons[itemDI].use) {
		if (Settings::aimbot_weapons[itemDI].enable) {
			applyWeaponSettings(Settings::aimbot_weapons[itemDI]);
			return true;
		}
		else {
			return false;
		}
	}

	//section settings
	if (weapon.isPistol()) {
		if (Settings::aimbot_pistols.use) {
			if (Settings::aimbot_pistols.enable) {
				applyWeaponSettings(Settings::aimbot_pistols);
				return true;
			}
			else {
				return false;
			}
		}
	}
	else if (weapon.isHeavy()) {
		if (Settings::aimbot_heavies.use) {
			if (Settings::aimbot_heavies.enable) {
				applyWeaponSettings(Settings::aimbot_heavies);
				return true;
			}
			else {
				return false;
			}
		}
	}
	else if (weapon.isShotgun()) {
		if (Settings::aimbot_shoutguns.use) {
			if (Settings::aimbot_shoutguns.enable) {
				applyWeaponSettings(Settings::aimbot_shoutguns);
				return true;
			}
			else {
				return false;
			}
		}
	}
	else if (weapon.isSMG()) {
		if (Settings::aimbot_smgs.use) {
			if (Settings::aimbot_smgs.enable) {
				applyWeaponSettings(Settings::aimbot_smgs);
				return true;
			}
			else {
				return false;
			}
		}
	}
	else if (weapon.isRifle()) {
		if (Settings::aimbot_rifles.use) {
			if (Settings::aimbot_rifles.enable) {
				applyWeaponSettings(Settings::aimbot_rifles);
				return true;
			}
			else {
				return false;
			}
		}
	}
	else if (weapon.isSnipers()) {
		if (Settings::aimbot_snipers.use) {
			if (Settings::aimbot_snipers.enable) {
				applyWeaponSettings(Settings::aimbot_snipers);
				return true;
			}
			else {
				return false;
			}
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
		resetSettings();
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
		resetSettings();
		return;
	}

	if (Settings::aimbot_flash_check && Helpers::isFlashed(client.localPlayer->m_flFlashAlpha())) {
		resetSettings();
		return;
	}

	if (Settings::aimbot_jump_check && !FlagsState::isOnGround(client.localPlayer->m_fFlags())) {
		resetSettings();
		return;
	}

	if (Settings::aimbot_use_key && !GetAsyncKeyState(Settings::aimbot_key)) {
		resetSettings();
		return;
	}

	int activeWeaponID = client.localPlayer->m_hActiveWeapon() & 0xfff;
	BaseWeapon activeWeapon(client.entityList->getByID(activeWeaponID - 1));

	if (!activeWeapon.get() || !applyWeaponsSettings(activeWeapon)) {
		resetSettings();
		return;
	}

	if (closestEnemy.get() <= 0) {
		for (const auto& entityObject : client.entityList->players()) {
			BasePlayer player(entityObject.first);

			if (!player.get() || player == (*client.localPlayer)) {
				continue;
			}

			if (player.m_iHealth() <= 0) {
				continue;
			}

			if (!Settings::aimbot_friendly_fire && player.m_iTeamNum() == client.localPlayer->m_iTeamNum()) {
				continue;
			}

			if (Settings::aimbot_visible_check && !client.localPlayer->canSeePlayer({entityObject.first, entityObject.second}, (int)bone, Settings::aimbot_smoke_check)) {
				continue;
			}

			for (auto bone : (this->bone == Skeleton::NEAREST ? ALL_BONES : std::vector<Skeleton>{ this->bone })) {
				Vector3 localPlayerPos = Vector3(client.localPlayer->m_vecOrigin()) + Vector3(client.localPlayer->m_vecViewOffset());
				auto bonePos = getBonePos(player, bone);
				if (Settings::aimbot_visible_check && !client.localPlayer->canSeePlayer({ entityObject.first, entityObject.second }, (int)bone, Settings::aimbot_smoke_check)) {
					continue;
				}
				auto enemyAngle = calcAngle(localPlayerPos, bonePos);
				float fov = getFov(enemyAngle, engine.clientState->dwViewAngles());

				if (fov < this->fov && fov < closestAngle) {
					closestEnemy.base = player.base;
					closestAngle = fov;
					closestBone = bone;
				}
			}
		}
	}

	if (closestEnemy.get() <= 0) {
		resetSettings();
		return;
	}

	if (Settings::aimbot_use_key && !GetAsyncKeyState(Settings::aimbot_key)) {
		resetSettings();
		return;
	}

	if (
		closestEnemy.m_iHealth() > 0 &&
		(!Settings::aimbot_visible_check || client.localPlayer->canSeePlayer(closestEnemy, (int)bone, Settings::aimbot_smoke_check))
		) {
		Vector3 localPlayerPos = Vector3(client.localPlayer->m_vecOrigin()) + Vector3(client.localPlayer->m_vecViewOffset());
		auto enemyAngle = calcAngle(localPlayerPos, getBonePos(closestEnemy, closestBone));

		setAngle(enemyAngle.toVector2());

		//TRY TO DO GOOD SMOOTH(NEED UNBIND MOUSE1 IN GAME)
		if (getFov(enemyAngle, Vector2(engine.clientState->dwViewAngles())) != 0 && client.localPlayer->m_iShotsFired() == 0) {
			shouldShoot = false;
			if (firstPerfectShoot) {
				shouldWait = true;
			}
			else {
				shouldWait = false;
			}
		}
		else {
			shouldShoot = true;
			shouldWait = false;
		}

		//If nearest go to the main bone after closest bone
		if (
			bone == Skeleton::NEAREST &&
			changeAfterNearest &&
			getFov(enemyAngle, engine.clientState->dwViewAngles()) == 0 &&
			std::find(MAIN_BONES.begin(), MAIN_BONES.end(), closestBone) == MAIN_BONES.end()
			) {
			closestAngle = 360.f;
			for (auto bone : MAIN_BONES) {
				auto bonePos = getBonePos(closestEnemy, bone);
				if (Settings::aimbot_visible_check && !client.localPlayer->canSeePlayer(closestEnemy, (int)bone, Settings::aimbot_smoke_check)) {
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
	}
	else {
		if (!shouldWait) {
			lastKillTime = std::chrono::high_resolution_clock::now();
		}
		if (closestEnemy.m_iHealth() <= 0 || shouldWait) {
			if (
				std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - lastKillTime).count()
				>
				(double)((double)Settings::aimbot_delay_enemy / (double)1000)
				) {
				resetSettings();
			}
			else {
				shouldWait = true;
			}
		}
	}
}
