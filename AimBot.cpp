#include "AimBot.hpp"

c_aim_bot::c_aim_bot() {}

void c_aim_bot::reset_settings(){
	target_was_reached = false;
	closest_target.base = 0;
	closest_angle = 360.0f;
	should_shoot = false;
	should_wait = false;
}

c_vector3 c_aim_bot::calc_angle(c_vector3 src, c_vector3 dst) {
	c_vector3 vec3_angle;

	auto vec3_delta = src - dst;
	auto vec3_hyp = fast_sqrt(pow(vec3_delta.x, 2) + pow(vec3_delta.y, 2));

	vec3_angle.x = (float)(atan(vec3_delta.z / vec3_hyp) * MATH_PI_RAD);
	vec3_angle.y = (float)(atan(vec3_delta.y / vec3_delta.x) * MATH_PI_RAD);
	vec3_angle.z = 0;

	//RCS for Aimbot
	if (this->rcs_enable && g_client.local_player->m_i_shots_fired() > 1){
		auto vec2_aim_punch = g_client.local_player->m_aim_punch_angle();

		vec3_angle.x -= vec2_aim_punch.x * (this->rcs_scale_x * 0.02f);
		vec3_angle.y -= vec2_aim_punch.y * (this->rcs_scale_y * 0.02f);
	}

	if (vec3_delta.x >= 0.0) {
		vec3_angle.y += 180.0f;
	}

	vec3_angle.clamp();

	return vec3_angle;
}

float c_aim_bot::get_fov(c_vector2 current_angle, c_vector3 dist_angle) {
	return (float)fast_sqrt(pow(current_angle.x - dist_angle.x, 2) + pow(current_angle.y - dist_angle.y, 2) + pow(0 - dist_angle.z, 2));
}

void c_aim_bot::set_angle(c_vector2 dist_angle) {
	if (target_was_reached) {
		c_vector2 vec2_view_angles(g_engine.client_state->view_angles());
		auto vec2_delta = vec2_view_angles - dist_angle;
		vec2_delta.clamp();

		if (this->rcs_enable) {
			dist_angle.x = vec2_view_angles.x - vec2_delta.x / (std::abs(100 - this->rcs_scale_x) > 1 ? std::abs(100 - this->rcs_scale_x) : 1);
			dist_angle.y = vec2_view_angles.y - vec2_delta.y / (std::abs(100 - this->rcs_scale_y) > 1 ? std::abs(100 - this->rcs_scale_y) : 1);
		}
		else {
			dist_angle.x = vec2_view_angles.x - vec2_delta.x / 100;
			dist_angle.y = vec2_view_angles.y - vec2_delta.y / 100;
		}
	}
	else {
		if (this->smooth > 0) {
			c_vector2 vec2_view_angles(g_engine.client_state->view_angles());

			auto vec2_delta = vec2_view_angles - dist_angle;
			vec2_delta.clamp();

			//skip if delta is so low
			if (abs(vec2_delta.x) > 0.1 || abs(vec2_delta.y) > 0.1) {
				dist_angle.x = vec2_view_angles.x - vec2_delta.x / this->smooth;
				dist_angle.y = vec2_view_angles.y - vec2_delta.y / this->smooth;
			}
			else {
				target_was_reached = true;
			}
		}
		else {
			target_was_reached = true;
		}
	}

	g_engine.client_state->view_angles(dist_angle.to_vec2());
}

void c_aim_bot::apply_weapon_settings(c_settings::s_aimbot_settings settings){
	this->fov = settings.fov;
	this->smooth = settings.smooth;
	this->bone = settings.bone;
	this->first_perfect_shoot = settings.first_perfect_shoot;
	this->change_after_nearest = settings.change_after_nearest;
	this->rcs_enable = settings.rcs_enable;
	this->rcs_scale_x = settings.rcs_scale_x;
	this->rcs_scale_y = settings.rcs_scale_y;
}

bool c_aim_bot::apply_weapons_settings(c_base_weapon weapon){
	auto item_di = weapon.item_di();

	//weapon settings
	if (c_settings::aimbot_weapons[item_di].use) {
		if (c_settings::aimbot_weapons[item_di].enable) {
			apply_weapon_settings(c_settings::aimbot_weapons[item_di]);
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
		g_engine.client_state->delta_tick() == -1 ||
		g_engine.client_state->state() != en_client_states::InGame ||
		g_client.local_player->m_b_dormant() ||
		g_client.local_player->m_i_health() <= 0 ||
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

	c_base_weapon active_weapon(g_client.local_player->active_weapon());

	if (!active_weapon.get() || !apply_weapons_settings(active_weapon)) {
		reset_settings();
		return;
	}

	if (closest_target.get() <= 0) {
		for (const auto& entity_obj: g_client.entity_list->players()) {
			c_base_player player(entity_obj.first);

			if (!player.get() || player == (*g_client.local_player)) {
				continue;
			}

			if (player.m_i_health() <= 0 || player.m_b_dormant()) {
				continue;
			}

			if (!c_settings::aimbot_friendly_fire && player.team_num() == g_client.local_player->team_num()) {
				continue;
			}

			if (
				c_settings::aimbot_visible_check &&
				!g_client.local_player->can_see_player({ entity_obj.first, entity_obj.second }, (int)bone, c_settings::aimbot_smoke_check)
			) {
				continue;
			}

			for (
				auto _bone:
				(this->bone == en_skeleton::Nearest ? ALL_BONES : std::vector<en_skeleton>{ this->bone })
			) {
				c_vector3 vec3_local_pos = c_vector3(g_client.local_player->m_vec3_origin()) + c_vector3(g_client.local_player->m_vec3_view_offset());

				if (
					c_settings::aimbot_visible_check &&
					!g_client.local_player->can_see_player({ entity_obj.first, entity_obj.second }, (int)_bone, c_settings::aimbot_smoke_check)
				) {
					continue;
				}

				auto vec3_player_angle = calc_angle(vec3_local_pos, player.get_bone_pos(_bone));
				float f_fov = get_fov(g_engine.client_state->view_angles(), vec3_player_angle);

				if (f_fov < this->fov && f_fov < closest_angle) {
					closest_target.base = player.base;
					closest_angle = f_fov;
					closest_bone = _bone;
				}
			}
		}
	}

	if (closest_target.get() <= 0) {
		reset_settings();
		return;
	}

	if (
		closest_target.m_i_health() > 0 &&
		(!c_settings::aimbot_visible_check || g_client.local_player->can_see_player(closest_target, (int)bone, c_settings::aimbot_smoke_check))
	) {
		c_vector3 vec3_local_pos = c_vector3(g_client.local_player->m_vec3_origin()) + c_vector3(g_client.local_player->m_vec3_view_offset());
		auto vec3_player_angle = calc_angle(vec3_local_pos, closest_target.get_bone_pos(closest_bone));

		set_angle(vec3_player_angle.to_vector2());

		auto f_total_fov = get_fov(c_vector2(g_engine.client_state->view_angles()), vec3_player_angle);

		//DO SMOOTH(NEED UNBIND MOUSE1 IN GAME)
		if (f_total_fov != 0 && g_client.local_player->m_i_shots_fired() == 0) {
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

		//need it for rcs smooth
		if (!target_was_reached && f_total_fov == 0) {
			target_was_reached = true;
		}

		//If nearest go to the main bone after closest bone
		if (
			this->bone == en_skeleton::Nearest &&
			this->change_after_nearest &&
			f_total_fov == 0 &&
			std::find(MAIN_BONES.begin(), MAIN_BONES.end(), closest_bone) == MAIN_BONES.end()
		) {
			closest_angle = 360.f;
			for (auto _bone: MAIN_BONES) {
				if (c_settings::aimbot_visible_check && !g_client.local_player->can_see_player(closest_target, (int)_bone, c_settings::aimbot_smoke_check)) {
					continue;
				}
				auto _vec3_player_angle = calc_angle(vec3_local_pos, closest_target.get_bone_pos(_bone));
				float f_fov = get_fov(g_engine.client_state->view_angles(), _vec3_player_angle);

				if (f_fov < closest_angle) {
					closest_angle = f_fov;
					closest_bone = _bone;
				}
			}
		}
	}
	else {
		if (!should_wait) {
			last_kill_time = std::chrono::high_resolution_clock::now();
		}
		if (closest_target.m_i_health() <= 0 || should_wait) {
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
