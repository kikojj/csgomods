#include "AimBot.hpp"

c_aim_bot::c_aim_bot() {}

void c_aim_bot::reset_settings(){
	closest_enemy.base = 0;
	closest_angle = 360.0f;
	should_shoot = false;
	should_wait = false;
}

c_vector3 c_aim_bot::calc_angle(c_vector3 src, c_vector3 dst) {
	c_vector3 angle;

	auto delta = src - dst;
	auto hyp = fast_sqrt(pow(delta.x, 2) + pow(delta.y, 2));

	angle.x = (float)(atan(delta.z / hyp) * MATH_PI_RAD);
	angle.y = (float)(atan(delta.y / delta.x) * MATH_PI_RAD);
	angle.z = 0;

	//RCS for Aimbot
	if (this->rcs_enable && g_client.local_player->m_i_shots_fired() > 1){
		auto aimPunch = g_client.local_player->m_aim_punch_angle();

		angle.x -= aimPunch.x * (this->rcs_scale_x * 0.02f);
		angle.y -= aimPunch.y * (this->rcs_scale_y * 0.02f);
	}

	if (delta.x >= 0.0) {
		angle.y += 180.0f;
	}

	angle.clamp();

	return angle;
}

float c_aim_bot::get_fov(c_vector3 currentAngle, c_vector2 dstAngle) {
	return (float)fast_sqrt(pow(dstAngle.x - currentAngle.x, 2) + pow(dstAngle.y - currentAngle.y, 2) + pow(0 - currentAngle.z, 2));
}

void c_aim_bot::set_angle(c_vector2 dstAngle) {
	if (g_client.local_player->m_i_shots_fired() > 1) {
		c_vector2 viewAngle(g_engine.client_state->view_angles());

		auto delta = viewAngle - dstAngle;
		delta.clamp();

		//skip if delta is so low
		if (abs(delta.x) > 0.1 || abs(delta.y) > 0.1) {
			if (this->rcs_enable) {
				dstAngle.x = viewAngle.x - delta.x / (std::abs(100 - this->rcs_scale_x) >= 1 ? std::abs(100 - this->rcs_scale_x) : 1);
				dstAngle.y = viewAngle.y - delta.y / (std::abs(100 - this->rcs_scale_y) >= 1 ? std::abs(100 - this->rcs_scale_y) : 1);
			}
			else {
				dstAngle.x = viewAngle.x - delta.x / 100;
				dstAngle.y = viewAngle.y - delta.y / 100;
			}
		}
	}
	else {
		if (this->smooth > 0) {
			c_vector2 viewAngle(g_engine.client_state->view_angles());

			auto delta = viewAngle - dstAngle;
			delta.clamp();

			//skip if delta is so low
			if (abs(delta.x) > 0.1 || abs(delta.y) > 0.1) {
				dstAngle.x = viewAngle.x - delta.x / this->smooth;
				dstAngle.y = viewAngle.y - delta.y / this->smooth;
			}
		}
	}

	g_engine.client_state->view_angles(dstAngle.to_vec2());
}

void c_aim_bot::apply_weapon_settings(c_settings::s_aimbot_settings settings){
	this->first_perfect_shoot = settings.first_perfect_shoot;
	this->fov = settings.fov;
	this->bone = settings.bone;
	this->change_after_nearest = settings.change_after_nearest;
	this->smooth = settings.smooth;
	this->rcs_enable = settings.rcs_enable;
	this->rcs_scale_x = settings.rcs_scale_x;
	this->rcs_scale_y = settings.rcs_scale_y;
}

bool c_aim_bot::apply_weapons_settings(c_base_weapon weapon){
	auto itemDI = weapon.item_di();

	//weapon settings
	if (c_settings::aimbot_weapons[itemDI].use) {
		if (c_settings::aimbot_weapons[itemDI].enable) {
			apply_weapon_settings(c_settings::aimbot_weapons[itemDI]);
			return true;
		}
		else {
			return false;
		}
	}

	//section settings
	if (weapon.is_pistol()) {
		if (c_settings::aimbot_pistols.use) {
			if (c_settings::aimbot_pistols.enable) {
				apply_weapon_settings(c_settings::aimbot_pistols);
				return true;
			}
			else {
				return false;
			}
		}
	}
	else if (weapon.is_heavy()) {
		if (c_settings::aimbot_heavies.use) {
			if (c_settings::aimbot_heavies.enable) {
				apply_weapon_settings(c_settings::aimbot_heavies);
				return true;
			}
			else {
				return false;
			}
		}
	}
	else if (weapon.is_shotgun()) {
		if (c_settings::aimbot_shoutguns.use) {
			if (c_settings::aimbot_shoutguns.enable) {
				apply_weapon_settings(c_settings::aimbot_shoutguns);
				return true;
			}
			else {
				return false;
			}
		}
	}
	else if (weapon.is_smg()) {
		if (c_settings::aimbot_smgs.use) {
			if (c_settings::aimbot_smgs.enable) {
				apply_weapon_settings(c_settings::aimbot_smgs);
				return true;
			}
			else {
				return false;
			}
		}
	}
	else if (weapon.is_rifle()) {
		if (c_settings::aimbot_rifles.use) {
			if (c_settings::aimbot_rifles.enable) {
				apply_weapon_settings(c_settings::aimbot_rifles);
				return true;
			}
			else {
				return false;
			}
		}
	}
	else if (weapon.is_snipers()) {
		if (c_settings::aimbot_snipers.use) {
			if (c_settings::aimbot_snipers.enable) {
				apply_weapon_settings(c_settings::aimbot_snipers);
				return true;
			}
			else {
				return false;
			}
		}
	}
	else if (weapon.is_knife() || weapon.is_zeusx27() || weapon.is_bomb() || weapon.is_grenade()) {
		return false;
	}
	else {
		return false;
	}

	//global settings
	if (c_settings::aimbot_global.enable) {
		apply_weapon_settings(c_settings::aimbot_global);
		return true;
	}

	return false;
}

void c_aim_bot::loop() {
	if (!c_settings::aimbot_enable) {
		reset_settings();
		return;
	}

	if (
		g_engine.client_state->state() != en_client_states::InGame ||
		g_engine.client_state->delta_tick() == -1 ||
		g_client.local_player->m_i_health() <= 0 ||
		g_client.local_player->team_num() < en_team_num::Terrorist ||
		g_client.local_player->m_b_dormant() ||
		!c_helpers::is_mouse_active()
		) {
		reset_settings();
		return;
	}

	if (c_settings::aimbot_flash_check && c_helpers::is_flashed(g_client.local_player->m_f_flash_alpha())) {
		reset_settings();
		return;
	}

	if (c_settings::aimbot_jump_check && !c_flags_state::is_on_ground(g_client.local_player->m_f_flags())) {
		reset_settings();
		return;
	}

	if (c_settings::aimbot_use_key && !GetAsyncKeyState(c_settings::aimbot_key)) {
		reset_settings();
		return;
	}

	int activeWeaponID = g_client.local_player->m_h_active_weapon() & 0xfff;
	c_base_weapon activeWeapon(g_client.entity_list->get_by_id(activeWeaponID - 1));

	if (!activeWeapon.get() || !apply_weapons_settings(activeWeapon)) {
		reset_settings();
		return;
	}

	if (closest_enemy.get() <= 0) {
		for (const auto& entityObject : g_client.entity_list->players()) {
			c_base_player player(entityObject.first);

			if (!player.get() || player == (*g_client.local_player)) {
				continue;
			}

			if (player.m_i_health() <= 0) {
				continue;
			}

			if (!c_settings::aimbot_friendly_fire && player.team_num() == g_client.local_player->team_num()) {
				continue;
			}

			if (c_settings::aimbot_visible_check && !g_client.local_player->can_see_player({entityObject.first, entityObject.second}, (int)bone, c_settings::aimbot_smoke_check)) {
				continue;
			}

			for (auto bone : (this->bone == en_skeleton::Nearest ? ALL_BONES : std::vector<en_skeleton>{ this->bone })) {
				c_vector3 localPlayerPos = c_vector3(g_client.local_player->m_vec3_origin()) + c_vector3(g_client.local_player->m_vec3_view_offset());
				auto bonePos = player.get_bone_pos(bone);
				if (c_settings::aimbot_visible_check && !g_client.local_player->can_see_player({ entityObject.first, entityObject.second }, (int)bone, c_settings::aimbot_smoke_check)) {
					continue;
				}
				auto enemyAngle = calc_angle(localPlayerPos, bonePos);
				float fov = get_fov(enemyAngle, g_engine.client_state->view_angles());

				if (fov < this->fov && fov < closest_angle) {
					closest_enemy.base = player.base;
					closest_angle = fov;
					closest_bone = bone;
				}
			}
		}
	}

	if (closest_enemy.get() <= 0) {
		reset_settings();
		return;
	}

	if (c_settings::aimbot_use_key && !GetAsyncKeyState(c_settings::aimbot_key)) {
		reset_settings();
		return;
	}

	if (
		closest_enemy.m_i_health() > 0 &&
		(!c_settings::aimbot_visible_check || g_client.local_player->can_see_player(closest_enemy, (int)bone, c_settings::aimbot_smoke_check))
		) {
		c_vector3 localPlayerPos = c_vector3(g_client.local_player->m_vec3_origin()) + c_vector3(g_client.local_player->m_vec3_view_offset());
		auto enemyAngle = calc_angle(localPlayerPos, closest_enemy.get_bone_pos(closest_bone));

		set_angle(enemyAngle.to_vector2());

		//TRY TO DO GOOD SMOOTH(NEED UNBIND MOUSE1 IN GAME)
		if (get_fov(enemyAngle, c_vector2(g_engine.client_state->view_angles())) != 0 && g_client.local_player->m_i_shots_fired() == 0) {
			should_shoot = false;
			if (first_perfect_shoot) {
				should_wait = true;
			}
			else {
				should_wait = false;
			}
		}
		else {
			should_shoot = true;
			should_wait = false;
		}

		//If nearest go to the main bone after closest bone
		if (
			bone == en_skeleton::Nearest &&
			change_after_nearest &&
			get_fov(enemyAngle, g_engine.client_state->view_angles()) == 0 &&
			std::find(MAIN_BONES.begin(), MAIN_BONES.end(), closest_bone) == MAIN_BONES.end()
			) {
			closest_angle = 360.f;
			for (auto bone : MAIN_BONES) {
				auto bonePos = closest_enemy.get_bone_pos(bone);
				if (c_settings::aimbot_visible_check && !g_client.local_player->can_see_player(closest_enemy, (int)bone, c_settings::aimbot_smoke_check)) {
					continue;
				}
				auto _enemyAngle = calc_angle(localPlayerPos, bonePos);
				float fov = get_fov(_enemyAngle, g_engine.client_state->view_angles());

				if (fov < closest_angle) {
					closest_angle = fov;
					closest_bone = bone;
				}
			}
		}
	}
	else {
		if (!should_wait) {
			last_kill_time = std::chrono::high_resolution_clock::now();
		}
		if (closest_enemy.m_i_health() <= 0 || should_wait) {
			if (
				std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - last_kill_time).count()
				>
				(double)((double)c_settings::aimbot_delay_enemy / (double)1000)
				) {
				reset_settings();
			}
			else {
				should_wait = true;
			}
		}
	}
}
