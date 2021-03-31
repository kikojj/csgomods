#include "Skinchanger.hpp"

void c_skinchanger::apply_weapon_settings(c_base_weapon weapon, c_settings::s_skinchanger_weapon settings){
	weapon.m_i_item_id_high(-1);
	weapon.m_i_account_id(weapon.m_original_owner_xuid_low());

	weapon.m_n_fallback_paint_kit(settings.paint_kit);

	weapon.m_f_fallback_wear(settings.wear);

	if (settings.quality != en_entity_quality::Invalid) {
		weapon.entity_quality(settings.quality);
	}
	else if (weapon.is_knife()) {
		weapon.entity_quality(en_entity_quality::Unusual);
	}

	if (settings.custom_name != "") {
		weapon.m_sz_custom_name(settings.custom_name);
	}
	if (settings.stat_track >= 0) {
		if (settings.quality == en_entity_quality::Invalid || settings.quality == en_entity_quality::Normal) {
			weapon.entity_quality(en_entity_quality::Strange);
		}
		weapon.m_n_fallback_stat_trak(settings.stat_track);
	}
	if (settings.seed > 0) {
		weapon.m_n_fallback_seed(settings.seed);
	}
}

void c_skinchanger::apply_knife_settings(c_base_weapon knife, c_settings::s_skinchanger_weapon settings){
	auto weaponModel = g_model_indexes[settings.item_di];

	knife.item_di(settings.item_di);
	knife.m_n_model_index(weaponModel);
	knife.m_i_view_model_index(weaponModel);

	apply_weapon_settings(knife, settings);
}

c_skinchanger::c_skinchanger(){}

void c_skinchanger::loop() {
	if (
		g_engine.client_state->state() != en_client_states::InGame ||
		g_client.local_player->m_i_health() <= 0 ||
		g_client.local_player->team_num() == en_team_num::Invalid
		) {
		return;
	}

	if (!c_settings::skinchanger_enable) {
		return;
	}

	auto localPlayerTeam = g_client.local_player->team_num();

	for (auto weaponId : g_client.local_player->my_weapons()) {
		c_base_weapon weapon(g_client.entity_list->get_by_id(weaponId - 1));

		if (!weapon.get()) {
			continue;
		}

		auto weaponDI = weapon.item_di();
		auto weaponModel =  g_model_indexes[c_settings::skinchanger_knives[localPlayerTeam].item_di];
		if (weapon.is_knife() && weaponModel > 0 && c_settings::skinchanger_knives[localPlayerTeam].enable) {
			apply_knife_settings(weapon, c_settings::skinchanger_knives[localPlayerTeam]);
		}
		else if (c_settings::skinchanger_weapons[weaponDI].enable) {
			apply_weapon_settings(weapon, c_settings::skinchanger_weapons[weaponDI]);
		}
	}

	auto activeWeaponID = g_client.local_player->m_h_active_weapon() & 0xfff;
	c_base_weapon activeWeapon(g_client.entity_list->get_by_id(activeWeaponID - 1));
	if (!activeWeapon.get() || !activeWeapon.is_knife()) {
		return;
	}

	int knifeViewModelID = g_client.local_player->m_h_view_model() & 0xfff;
	c_base_weapon knife(g_client.entity_list->get_by_id((knifeViewModelID - 1)));
	if (!knife.get() || !c_settings::skinchanger_knives[localPlayerTeam].enable) {
		return;
	}

	auto knifeModel = g_model_indexes[c_settings::skinchanger_knives[localPlayerTeam].item_di];
	if (knifeModel <= 0) {
		return;
	}

	knife.m_n_model_index(knifeModel);
	knife.m_h_weapon_world_model(knifeModel + 1);
}