#include "Misc.hpp"

c_misc::c_misc() {}

void c_misc::radar_hack(){
	if (!c_settings::misc_ingame_radar_enable) {
		return;
	}

	if (g_engine.client_state->state() != en_client_states::InGame || g_engine.client_state->delta_tick() == -1) {
		return;
	}

	for (const auto& entityObject : g_client.entity_list->players()) {
		c_base_player player(entityObject.first);

		if (player.team_num() == g_client.local_player->team_num()) {
			continue;
		}

		if (player.m_i_health() <= 0) {
			continue;
		}

		if (!player.m_b_spotted()) {
			player.m_b_spotted(true);
		}
	}
}

void c_misc::bhop() {
	if (!c_settings::misc_bhop_enable) {
		return;
	}

	if (
		g_engine.client_state->state() != en_client_states::InGame ||
		g_client.local_player->m_i_health() <= 0 ||
		g_client.local_player->team_num() == en_team_num::Invalid ||
		g_engine.client_state->delta_tick() == -1 ||
		!c_helpers::is_mouse_active()
		) {
		return;
	}

	if (!GetAsyncKeyState(VK_SPACE)) {
		return;
	}

	if (c_vector3(g_client.local_player->m_vec3_velocity()).is_zero()) {
		return;
	}

	if (c_flags_state::is_on_ground(g_client.local_player->m_f_flags())) {
		g_client.dw_force_jump(en_key_event::KeyDown);
	}
	else {
		g_client.dw_force_jump(en_key_event::KeyUp);
	}
}

void c_misc::reset_settings() {
	should_shoot = false;
	should_wait = false;
}

void c_misc::auto_pistols(){
	if (!c_settings::misc_auto_pistols_enable) {
		reset_settings();
		return;
	}

	if (
		g_engine.client_state->state() != en_client_states::InGame ||
		g_client.local_player->m_i_health() <= 0 ||
		g_client.local_player->team_num() == en_team_num::Invalid ||
		g_engine.client_state->delta_tick() == -1 ||
		!c_helpers::is_mouse_active()
		) {
		reset_settings();
		return;
	}

	if (!GetAsyncKeyState(VK_LBUTTON)) {
		reset_settings();
		return;
	}

	int activeWeaponID = g_client.local_player->m_h_active_weapon() & 0xfff;
	c_base_weapon activeWeapon(g_client.entity_list->get_by_id(activeWeaponID - 1));

	if (activeWeapon.is_pistol() && activeWeapon.item_di() != c_item::en_defenition_index::WeaponR8Revolver && activeWeapon.item_di() != c_item::en_defenition_index::WeaponCZ75Auto) {
		if (!should_shoot) {
			last_press_time = std::chrono::high_resolution_clock::now();
			should_shoot = true;
		}
		else {
			if (
				std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - last_press_time).count() >
				(double)((double)c_settings::misc_auto_pistols_delay / (double)1000)
				) {
				reset_settings();
			}
			else {
				should_wait = true;
			}
		}
	}
}

void c_misc::anti_flash(){
	if (!c_settings::misc_anti_flash_enable) {
		return;
	}

	if (
		g_engine.client_state->state() != en_client_states::InGame ||
		g_client.local_player->m_i_health() <= 0 ||
		g_client.local_player->team_num() == en_team_num::Invalid ||
		g_engine.client_state->delta_tick() == -1
		) {
		return;
	}

	if (g_client.local_player->m_f_flash_max_alpha() != c_settings::misc_anti_flash_max_alpha) {
		g_client.local_player->m_f_flash_max_alpha((float)c_settings::misc_anti_flash_max_alpha);
	}
}

void c_misc::auto_accept(){
	if (!c_settings::misc_auto_accept_enable) {
		return;
	}

	if (g_engine.client_state->state() != en_client_states::Lobby) {
		return;
	}

	callback = g_client.confirm_reservation_callback();

	if (callback){
		if (prev_callback != callback){
			prev_callback = callback;
			found = false;
			accepted = false;
		}

		if (!found){
			found = true;
			Sleep(5000);
		}
		else if (!accepted){
			accepted = true;
			g_mem.createThread(g_client.confirm_match());
			std::cout << "[AUTO ACCEPT]: Math was found. Tried to accept the match." << std::endl;
		}
	}
	else{
		found = false;
		accepted = false;
	}
}