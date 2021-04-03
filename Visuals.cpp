#include "Visuals.hpp"

c_visuals::c_visuals() {}

void c_visuals::draw_entity(c_glow_object_manager::t_glow_object glowObject, s_color_rgba color, en_glow_style style) {
	glowObject.first.color(color);
	glowObject.first.style = (int)style;
	glowObject.first.render_when_occluded = true;
	g_mem.write<s_glow_object_definition>(g_client.glow_object_manager->get_object_base(glowObject), glowObject.first);
}

void c_visuals::reset_render(c_base_player& player) {
	player.render({ 255, 255, 255, 0 });
}

s_color_rgba c_visuals::get_hp_based_color(c_base_player& player){
	s_color_rgba hp0 = c_settings::visuals_glow_esp_hp_based_0hp_color;
	s_color_rgba hp100 = c_settings::visuals_glow_esp_hp_based_100hp_color;

	float f_scale = (float)player.m_i_health() / 100.f;
	s_color_rgba color;

	color.r = hp0.r + (hp100.r - hp0.r) * f_scale;
	color.g = hp0.g + (hp100.g - hp0.g) * f_scale;
	color.b = hp0.b + (hp100.b - hp0.b) * f_scale;
	color.a = hp0.a + (hp100.a - hp0.a) * f_scale;

	return color;
}

void c_visuals::loop() {
	if (g_engine.client_state->delta_tick() == -1 || g_engine.client_state->state() != en_client_states::InGame) {
		return;
	}

	for (const auto& glow_obj: g_client.glow_object_manager->array()) {
		auto entity = c_base_entity(glow_obj.first.base_entity);
		auto entity_class_id = entity.class_id();


		if (entity_class_id == en_class_id::CCSPlayer) {
			c_base_player player(entity);

			if (!player.get() || player.m_i_health() <= 0 || player.m_b_dormant()) {
				continue;
			}

			reset_render(player);
		}

		if (c_settings::visuals_glow_esp_enable) {
			if (entity_class_id == en_class_id::CC4) {
				if (c_settings::visuals_glow_esp_show_c4) {
					draw_entity(glow_obj, c_settings::visuals_glow_esp_c4_color, en_glow_style::FullBody);
				}
			}
			else if (entity_class_id == en_class_id::CPlantedC4) {
				if (c_settings::visuals_glow_esp_show_c4) {
					draw_entity(glow_obj, c_settings::visuals_glow_esp_c4_planted_color, en_glow_style::FullBody);
				}
			}
			else if (entity_class_id == en_class_id::CCSPlayer) {
				c_base_player player(entity);

				if (!player.get() || player.m_i_health() <= 0 || player.m_b_dormant()) {
					continue;
				}

				if (player.team_num() == g_client.local_player->team_num()) {
					if (c_settings::visuals_glow_esp_show_friends) {
						if (c_settings::visuals_glow_esp_mode == c_settings::en_visuals_glow_esp_mode::Color) {
							draw_entity(glow_obj, c_settings::visuals_glow_esp_friends_color, c_settings::visuals_glow_esp_style);
						}
						else {
							draw_entity(glow_obj, get_hp_based_color(player), c_settings::visuals_glow_esp_style);
						}

						if (c_settings::visuals_glow_esp_show_defusing) {
							if (player.m_b_is_defusing()) {
								draw_entity(glow_obj, c_settings::visuals_glow_esp_defusing_color, c_settings::visuals_glow_esp_style);
							}
						}
					}
				}
				else {
					if (c_settings::visuals_glow_esp_show_enemies) {
						if (c_settings::visuals_glow_esp_mode == c_settings::en_visuals_glow_esp_mode::Color) {
							bool b_is_visible = false;

							//visible check
							if (g_client.local_player->get() && !g_client.local_player->m_b_dormant() && g_client.local_player->m_i_health() > 0) {
								b_is_visible = g_client.local_player->can_see_player(player, -1, true);
							}
							else {
								b_is_visible = player.m_b_spotted();
							}

							draw_entity(
								glow_obj,
								(b_is_visible ?
								c_settings::visuals_glow_esp_enemy_visible_color :
								c_settings::visuals_glow_esp_enemy_invisible_color),
								c_settings::visuals_glow_esp_style
							);
						}
						else {
							draw_entity(glow_obj, get_hp_based_color(player), c_settings::visuals_glow_esp_style);
						}

						if (c_settings::visuals_glow_esp_show_defusing) {
							if (player.m_b_is_defusing()) {
								draw_entity(glow_obj, c_settings::visuals_glow_esp_defusing_color, c_settings::visuals_glow_esp_style);
							}
						}
					}
				}
			}
			else if (
				entity_class_id == en_class_id::CDecoyGrenade ||
				entity_class_id == en_class_id::CHEGrenade ||
				entity_class_id == en_class_id::CIncendiaryGrenade ||
				entity_class_id == en_class_id::CMolotovGrenade ||
				entity_class_id == en_class_id::CSmokeGrenade ||
				entity_class_id == en_class_id::CFlashbang
				) {
				if (c_settings::visuals_glow_esp_show_grenades) {
					draw_entity(glow_obj, c_settings::visuals_glow_esp_grenades_color, en_glow_style::FullBody);
				}
			}
		}

		if (c_settings::visuals_chams_enable) {
			if (entity_class_id == en_class_id::CCSPlayer) {
				c_base_player player(entity);

				if (!player.get() || player.m_i_health() <= 0 || player.m_b_dormant()) {
					continue;
				}

				if (player.team_num() == g_client.local_player->team_num()) {
					if (c_settings::visuals_chams_show_friends) {
						player.render(c_settings::visuals_chams_friends_color);
					}
				}
				else {
					if (c_settings::visuals_chams_show_enemies) {
						player.render(c_settings::visuals_chams_enemy_color);
					}
				}
			}
		}
	}
}