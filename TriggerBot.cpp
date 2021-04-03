#include "TriggerBot.hpp"

c_trigger_bot::c_trigger_bot() {}

void c_trigger_bot::reset_settings() {
	should_shoot = false;
	should_wait = false;
}

void c_trigger_bot::loop() {
	if (!c_settings::triggerbot_enable) {
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

	if (c_settings::triggerbot_use_key && !GetAsyncKeyState(c_settings::triggerbot_key)){
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

	c_base_weapon active_weapon(g_client.local_player->active_weapon());

	if (active_weapon.is_pistol()) {
		if (!c_settings::triggerbot_pistols_enable) {
			reset_settings();
			return;
		}
	}
	else if (active_weapon.is_heavy()) {
		if (!c_settings::triggerbot_heavies_enable) {
			reset_settings();
			return;
		}
	}
	else if (active_weapon.is_shotgun()) {
		if (!c_settings::triggerbot_shoutguns_enable) {
			reset_settings();
			return;
		}
	}
	else if (active_weapon.is_smg()) {
		if (!c_settings::triggerbot_smgs_enable) {
			reset_settings();
			return;
		}
	}
	else if (active_weapon.is_rifle()) {
		if (!c_settings::triggerbot_rifles_enable) {
			reset_settings();
			return;
		}
	}
	else if (active_weapon.is_snipers()) {
		if (!c_settings::triggerbot_snipers_enable) {
			reset_settings();
			return;
		}
	}
	else if (active_weapon.is_knife()) {
		reset_settings();
		return;
	}
	else if (active_weapon.is_bomb()) {
		reset_settings();
		return;
	}
	else if (active_weapon.is_grenade()) {
		reset_settings();
		return;
	}
	else if (active_weapon.is_zeusx27()) {
		reset_settings();
		return;
	}
	else {
		std::cout << "[Trigger]: Undefined weapon ID = " << (int)active_weapon.item_di() << std::endl;
		reset_settings();
		return;
	}

	c_base_entity entity(g_client.entity_list->get_by_id(g_client.local_player->m_i_crosshair_id() - 1));
	if (entity.class_id() != en_class_id::CCSPlayer) {
		reset_settings();
		return;
	}

	c_base_player player(entity);
	if (!c_settings::triggerbot_friendly_fire && player.team_num() == g_client.local_player->team_num()) {
		reset_settings();
		return;
	}

	if (!should_shoot) {
		last_press_time = std::chrono::high_resolution_clock::now();
		should_shoot = true;
	}
	else if (!should_wait) {
		if (active_weapon.is_pistol()) {
			should_shoot = false;
		}
	}

	if (
		std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - last_press_time).count() >
		((double)c_settings::triggerbot_delay_before_shoot / (double)1000)
		) {
		should_wait = false;
	}
	else {
		should_wait = true;
	}
}