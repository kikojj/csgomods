#include "Visuals.hpp"

c_visuals::c_visuals() {}

void c_visuals::draw_entity(c_glow_object_manager::t_glow_object glowObject, s_color_rgba color, en_glow_style style) {
	glowObject.first.color(color);
	glowObject.first.glow_style = (int)style;
	glowObject.first.render_when_occluded = true;
	g_mem.write<s_glow_object_definition>(g_client.glow_object_manager->get_object_base(glowObject), glowObject.first);
}

void c_visuals::reset_render(c_base_player& player) {
	player.render({ 255, 255, 255, 0 });
}

s_color_rgba c_visuals::get_hp_based_color(c_base_player& player){
	float scale = (float)player.m_i_health() / 100.f;
	s_color_rgba hp0 = { 255,0,0,255 };
	s_color_rgba hp100 = { 0,255,0,255 };
	s_color_rgba color;
	color.r = hp0.r + (hp100.r - hp0.r) * scale;
	color.g = hp0.g + (hp100.g - hp0.g) * scale;
	color.b = hp0.b + (hp100.b - hp0.b) * scale;
	color.a = 255;
	return color;
}

void c_visuals::loop() {
	if (g_engine.client_state->state() != en_client_states::InGame || g_engine.client_state->delta_tick() == -1) {
		return;
	}

	for (const auto& glowObject : g_client.glow_object_manager->array()) {
		auto entity = c_base_entity(glowObject.first.base_entity);
		auto entityClassID = entity.class_id();


		if (entityClassID == en_class_id::CCSPlayer) {
			c_base_player player(entity);

			if (!player.get() || player.m_i_health() <= 0 || player.m_b_dormant()) {
				continue;
			}

			reset_render(player);
		}

		if (c_settings::visuals_glow_esp_enable) {
			if (entityClassID == en_class_id::CC4) {
				if (c_settings::visuals_glow_esp_show_c4) {
					draw_entity(glowObject, c_settings::visuals_glow_esp_c4_color, en_glow_style::FullBody);
				}
			}
			else if (entityClassID == en_class_id::CPlantedC4) {
				if (c_settings::visuals_glow_esp_show_c4) {
					draw_entity(glowObject, c_settings::visuals_glow_esp_c4_planted_color, en_glow_style::FullBody);
				}
			}
			else if (entityClassID == en_class_id::CCSPlayer) {
				c_base_player player(entity);

				if (!player.get() || player.m_i_health() <= 0 || player.m_b_dormant()) {
					continue;
				}

				if (player.team_num() == g_client.local_player->team_num()) {
					if (c_settings::visuals_glow_esp_show_friends) {
						if (c_settings::visuals_glow_esp_mode == c_settings::en_visuals_glow_esp_mode::Color) {
							draw_entity(glowObject, c_settings::visuals_glow_esp_friends_color, c_settings::visuals_glow_esp_style);
						}
						else {
							draw_entity(glowObject, get_hp_based_color(player), c_settings::visuals_glow_esp_style);
						}

						if (c_settings::visuals_glow_esp_show_defusing) {
							if (player.m_b_is_defusing()) {
								draw_entity(glowObject, c_settings::visuals_glow_esp_defusing_color, c_settings::visuals_glow_esp_style);
							}
						}
					}
				}
				else {
					if (c_settings::visuals_glow_esp_show_enemies) {
						if (c_settings::visuals_glow_esp_mode == c_settings::en_visuals_glow_esp_mode::Color) {
							draw_entity(
								glowObject,

								//visible check
								g_client.local_player->can_see_player(player) ?
								c_settings::visuals_glow_esp_enemy_visible_color :
								c_settings::visuals_glow_esp_enemy_invisible_color,

								c_settings::visuals_glow_esp_style
							);
						}
						else {
							draw_entity(glowObject, get_hp_based_color(player), c_settings::visuals_glow_esp_style);
						}

						if (c_settings::visuals_glow_esp_show_defusing) {
							if (player.m_b_is_defusing()) {
								draw_entity(glowObject, c_settings::visuals_glow_esp_defusing_color, c_settings::visuals_glow_esp_style);
							}
						}
					}
				}
			}
			else if (
				entityClassID == en_class_id::CDecoyGrenade ||
				entityClassID == en_class_id::CHEGrenade ||
				entityClassID == en_class_id::CIncendiaryGrenade ||
				entityClassID == en_class_id::CMolotovGrenade ||
				entityClassID == en_class_id::CSmokeGrenade ||
				entityClassID == en_class_id::CFlashbang
				) {
				if (c_settings::visuals_glow_esp_show_grenades) {
					draw_entity(glowObject, c_settings::visuals_glow_esp_grenades_color, en_glow_style::FullBody);
				}
			}
		}

		if (c_settings::visuals_chams_enable) {
			if (entityClassID == en_class_id::CCSPlayer) {
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