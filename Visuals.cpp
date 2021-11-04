#include "Visuals.hpp"

c_visuals::c_visuals() {}

void c_visuals::draw_entity(c_glow_object_manager::t_glow_object glowObject, s_color_rgba color, en_glow_style& style) {
	glowObject.first.color(color);
	glowObject.first.style = (int)style;
	glowObject.first.render_when_occluded = true;
	//glowObject.first.full_bloom_render = true; can use it to make it like a chams
	g_mem.write<s_glow_object_definition>(g_client.glow_object_manager->get_object_base(glowObject), glowObject.first);
}

void c_visuals::reset_render(c_base_player& player) {
	player.render({ 255, 255, 255, 0 });
}

s_color_rgba c_visuals::get_hp_based_color(c_base_player& player, c_settings::s_glow_esp_settings& settings){
	s_color_rgba hp0 = settings.hp_based_0hp_color;
	s_color_rgba hp100 = settings.hp_based_100hp_color;

	float f_scale = (float)player.m_i_health() / 100.f;
	s_color_rgba color;

	color.r = hp0.r + (hp100.r - hp0.r) * f_scale;
	color.g = hp0.g + (hp100.g - hp0.g) * f_scale;
	color.b = hp0.b + (hp100.b - hp0.b) * f_scale;
	color.a = hp0.a + (hp100.a - hp0.a) * f_scale;

	return color;
}

bool c_visuals::get_entity_glow_settings(c_base_entity& entity, s_color_rgba* color, en_glow_style* style){
	auto entity_class_id = entity.class_id();

	if (entity_class_id == en_class_id::CC4) {
		if (c_settings::visuals_glow_esp_c4.enable) {
			*color = c_settings::visuals_glow_esp_c4.visible_color;
			*style = c_settings::visuals_glow_esp_c4.style;
			return true;
		}
	}
	else if (entity_class_id == en_class_id::CPlantedC4) {
		if (c_settings::visuals_glow_esp_c4.enable) {
			*color = c_settings::visuals_glow_esp_c4.visible_color;
			*style = c_settings::visuals_glow_esp_c4.style;
			return true;
		}
	}
	else if (entity_class_id == en_class_id::CCSPlayer) {
		c_base_player player(entity);

		if (!player.get() || player.m_i_health() <= 0 || player.m_b_dormant()) {
			return false;
		}

		auto i_player_user_id = player.info().user_id;

		if (player.team_num() == g_client.local_player->team_num()) {
			if (c_settings::visuals_glow_esp_friends.enable) {
				if (c_settings::visuals_glow_esp_friends.mode == c_settings::en_glow_mode::Color) {
					*color = c_settings::visuals_glow_esp_friends.visible_color;
					*style = c_settings::visuals_glow_esp_friends.style;
				}
				else {
					*color = get_hp_based_color(player, c_settings::visuals_glow_esp_friends);
					*style = c_settings::visuals_glow_esp_friends.style;
				}

				if (c_settings::visuals_glow_esp_defusing.enable) {
					if (player.m_b_is_defusing()) {
						*color = c_settings::visuals_glow_esp_defusing.visible_color;
						*style = c_settings::visuals_glow_esp_defusing.style;
					}
				}

				if (c_settings::personal_settings[i_player_user_id].glow_settings.enable) {
					auto player_glow_settings = c_settings::personal_settings[i_player_user_id].glow_settings;
					if (player_glow_settings.mode == c_settings::en_glow_mode::Color) {
						*color = player_glow_settings.visible_color;
						*style = player_glow_settings.style;
					}
					else {
						*color = get_hp_based_color(player, player_glow_settings);
						*style = player_glow_settings.style;
					}
				}

				return true;
			}
			else {
				return false;
			}
		}
		else {
			if (c_settings::visuals_glow_esp_enemies.enable) {
				if (c_settings::visuals_glow_esp_enemies.mode == c_settings::en_glow_mode::Color) {
					bool b_is_visible = false;

					//visible check
					if (g_client.local_player->get() && !g_client.local_player->m_b_dormant() && g_client.local_player->m_i_health() > 0) {
						b_is_visible = g_client.local_player->can_see_player(player, -1, true);
					}
					else {
						b_is_visible = player.m_b_spotted();
					}

					*color = (b_is_visible ? c_settings::visuals_glow_esp_enemies.visible_color : c_settings::visuals_glow_esp_enemies.invisible_color);
					*style = c_settings::visuals_glow_esp_enemies.style;
				}
				else {
					*color = get_hp_based_color(player, c_settings::visuals_glow_esp_enemies);
					*style = c_settings::visuals_glow_esp_enemies.style;
				}

				if (c_settings::visuals_glow_esp_defusing.enable) {
					if (player.m_b_is_defusing()) {
						*color = c_settings::visuals_glow_esp_defusing.visible_color;
						*style = c_settings::visuals_glow_esp_defusing.style;
					}
				}

				if (c_settings::personal_settings[i_player_user_id].glow_settings.enable) {
					auto player_glow_settings = c_settings::personal_settings[i_player_user_id].glow_settings;

					if (player_glow_settings.mode == c_settings::en_glow_mode::Color) {
						bool b_is_visible = false;

						//visible check
						if (g_client.local_player->get() && !g_client.local_player->m_b_dormant() && g_client.local_player->m_i_health() > 0) {
							b_is_visible = g_client.local_player->can_see_player(player, -1, true);
						}
						else {
							b_is_visible = player.m_b_spotted();
						}

						*color = (b_is_visible ? player_glow_settings.visible_color : player_glow_settings.invisible_color);
						* style = player_glow_settings.style;
					}
					else {
						*color = get_hp_based_color(player, player_glow_settings);
						*style = player_glow_settings.style;
					}
				}

				return true;
			}
			else {
				return false;
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
		if (c_settings::visuals_glow_esp_grenades.enable) {
			*color = c_settings::visuals_glow_esp_grenades.visible_color;
			*style = c_settings::visuals_glow_esp_grenades.style;
		}
	}

	return false;
}

bool c_visuals::get_entity_chams_settings(c_base_entity& entity, s_color_rgba* color){
	auto entity_class_id = entity.class_id();

	if (entity_class_id == en_class_id::CCSPlayer) {
		c_base_player player(entity);

		if (!player.get() || player.m_i_health() <= 0 || player.m_b_dormant()) {
			return false;
		}

		if (player.team_num() == g_client.local_player->team_num()) {
			if (c_settings::visuals_chams_friends.enable) {
				*color = c_settings::visuals_chams_friends.color;
				return true;
			}
			else {
				return false;
			}
		}
		else {
			if (c_settings::visuals_chams_enemies.enable) {
				*color = c_settings::visuals_chams_enemies.color;
				return true;
			}
			else {
				return false;
			}
		}
	}
	
	return false;	
}

void c_visuals::loop() {
	if (g_engine.client_state->delta_tick() == -1 || g_engine.client_state->state() != en_client_states::InGame) {
		return;
	}

	for (const auto& glow_obj : g_client.glow_object_manager->array()) {
		auto entity = c_base_entity(glow_obj.first.base_entity);
		auto entity_class_id = entity.class_id();


		if (entity_class_id == en_class_id::CCSPlayer) {
			c_base_player player(entity);

			if (!player.get() || player.m_i_health() <= 0 || player.m_b_dormant()) {
				continue;
			}

			reset_render(player);
		}

		s_color_rgba glow_color, chams_color;
		en_glow_style glow_style;

		if (c_settings::visuals_glow_esp_enable && get_entity_glow_settings(entity, &glow_color, &glow_style)) {
			draw_entity(glow_obj, glow_color, glow_style);
		}

		if (c_settings::visuals_chams_enable && get_entity_chams_settings(entity, &chams_color)) {
			c_base_player player(entity);
			player.render(chams_color);
		}
	}
}

void c_visuals::render(c_overlay* overlay, c_render* render) {
	if (g_engine.client_state->delta_tick() == -1 || g_engine.client_state->state() != en_client_states::InGame || !c_helpers::is_mouse_active()) {
		return;
	}

	for (const auto& glow_obj : g_client.glow_object_manager->array()) {
		auto entity = c_base_entity(glow_obj.first.base_entity);
		auto entity_class_id = entity.class_id();
		c_base_player player(entity);

		if (entity_class_id != en_class_id::CCSPlayer || !player.get() || player.m_i_health() <= 0 || player.m_b_dormant()) {
			continue;
		}

		if (player.team_num() == g_client.local_player->team_num()) {
			continue;
		}

		D3DXVECTOR2 player_origin_screen(0, 0);
		D3DXVECTOR2 player_origin_top_screen(0, 0);

		auto player_origin = c_vector3(player.m_vec3_origin());
		auto player_origin_top = player.get_bone_pos(en_skeleton::Head) + c_vector3(0, 0, 8);

		auto view_matrix = g_client.dw_view_matrix().data;

		if (
			!c_helpers::world_to_screen(player_origin.to_d3dx_vec3(), player_origin_screen, overlay->desktop_rect, view_matrix) ||
			!c_helpers::world_to_screen(player_origin_top.to_d3dx_vec3(), player_origin_top_screen, overlay->desktop_rect, view_matrix)
			) {
			continue;
		}

		auto box_height = abs(player_origin_top_screen.y - player_origin_screen.y);
		auto box_width = box_height / 2;
		auto box_x = player_origin_screen.x - box_width / 2;
		auto box_y = player_origin_top_screen.y;

		//box
		c_render::s_rect_styles box_styles;
		box_styles.x = box_x;
		box_styles.y = box_y;
		box_styles.width = box_width;
		box_styles.height = box_height;
		box_styles.fill = true;
		box_styles.fill_color = D3DCOLOR_ARGB(50, 255, 255, 255);
		box_styles.border = true;

		//visible check
		bool b_is_visible = false;
		if (g_client.local_player->get() && !g_client.local_player->m_b_dormant() && g_client.local_player->m_i_health() > 0) {
			b_is_visible = g_client.local_player->can_see_player(player, -1, true);
		}
		else {
			b_is_visible = player.m_b_spotted();
		}

		box_styles.border_color = b_is_visible ? D3DCOLOR_ARGB(200, 0, 255, 0) : D3DCOLOR_ARGB(200, 255, 0, 0);

		box_styles.border_width = 1;
		render->rect(box_styles);

		//health bar
		c_render::s_rect_styles health_bar_background_styles;
		health_bar_background_styles.x = box_styles.x + box_styles.width;
		health_bar_background_styles.y = box_styles.y;
		health_bar_background_styles.width = 2/* my width */ + 2 * 1 /* for border */;
		health_bar_background_styles.height = box_styles.height;
		health_bar_background_styles.fill = true;
		health_bar_background_styles.fill_color = D3DCOLOR_ARGB(200, 255, 0, 0);
		health_bar_background_styles.border = true;
		health_bar_background_styles.border_color = D3DCOLOR_ARGB(200, 0, 0, 0);
		health_bar_background_styles.border_width = 1;
		render->rect(health_bar_background_styles);

		c_render::s_rect_styles health_bar_styles;
		health_bar_styles.x = health_bar_background_styles.x + health_bar_background_styles.border_width;
		health_bar_styles.y = health_bar_background_styles.y + health_bar_background_styles.border_width + (box_styles.height - 2 * health_bar_background_styles.border_width) / 100 * (100 - player.m_i_health());
		health_bar_styles.width = health_bar_background_styles.width - 2 * health_bar_background_styles.border_width;
		health_bar_styles.height = (box_styles.height - 2 * health_bar_background_styles.border_width) / 100 * player.m_i_health();
		health_bar_styles.fill = true;
		health_bar_styles.fill_color = D3DCOLOR_ARGB(200, 0, 255, 0);
		render->rect(health_bar_styles);
		const auto HEALTH_BAR_WIDTH = health_bar_background_styles.width;

		//armor bar
		c_render::s_rect_styles armor_bar_background_styles;
		armor_bar_background_styles.x = box_styles.x + box_styles.width + HEALTH_BAR_WIDTH;
		armor_bar_background_styles.y = box_styles.y;
		armor_bar_background_styles.width = 2/* my width */ + 2 * 1 /* for border */;
		armor_bar_background_styles.height = box_styles.height;
		armor_bar_background_styles.fill = true;
		armor_bar_background_styles.fill_color = D3DCOLOR_ARGB(122, 255, 255, 255);
		armor_bar_background_styles.border = true;
		armor_bar_background_styles.border_color = D3DCOLOR_ARGB(200, 0, 0, 0);
		armor_bar_background_styles.border_width = 1;
		render->rect(armor_bar_background_styles);

		c_render::s_rect_styles armor_bar_styles;
		armor_bar_styles.x = armor_bar_background_styles.x + armor_bar_background_styles.border_width;
		armor_bar_styles.y = armor_bar_background_styles.y + armor_bar_background_styles.border_width + (box_styles.height - 2 * health_bar_background_styles.border_width) / 100 * (100 - player.m_armor_value());
		armor_bar_styles.width = armor_bar_background_styles.width - 2 * armor_bar_background_styles.border_width;
		armor_bar_styles.height = (box_styles.height - 2 * armor_bar_background_styles.border_width) / 100 * player.m_armor_value();
		armor_bar_styles.fill = true;
		armor_bar_styles.fill_color = D3DCOLOR_ARGB(200, 0, 0, 255);
		render->rect(armor_bar_styles);
		const auto ARMOR_BAR_WIDTH = armor_bar_background_styles.width;

		//name
		auto player_info = player.info();
		auto player_name = player_info.is_fake_player ? "BOT " + std::string(player_info.name): player_info.name;
		auto player_name_width = render->get_text_width(player_name, c_render::en_font_type::ROBOTO_12);
		auto player_name_height = render->get_text_height(player_name, c_render::en_font_type::ROBOTO_12);
		auto player_name_x = box_x + box_width / 2 - player_name_width / 2;

		c_render::s_text_styles name_styles;
		name_styles.x = player_name_x;
		name_styles.y = player_origin_top_screen.y - player_name_height;
		name_styles.color = D3DCOLOR_ARGB(255, 255, 255, 255);
		name_styles.outline = true;
		name_styles.font_type = c_render::en_font_type::ROBOTO_12;
		render->text(player_name, name_styles);

		//hp text
		auto player_hp_text = "HP: " + std::to_string(player.m_i_health());
		auto player_hp_text_width = render->get_text_width(player_hp_text, c_render::en_font_type::ROBOTO_10);
		auto player_hp_text_height = render->get_text_height(player_hp_text, c_render::en_font_type::ROBOTO_10);

		c_render::s_text_styles hp_text_styles;
		hp_text_styles.x = box_x - player_hp_text_width;
		hp_text_styles.y = box_y;
		hp_text_styles.color = D3DCOLOR_ARGB(255, 255, 255, 255);
		hp_text_styles.outline = true;
		hp_text_styles.font_type = c_render::en_font_type::ROBOTO_10;
		render->text(player_hp_text, hp_text_styles);
		const auto HP_TEXT_HEIGHT = player_hp_text_height;

		//armor text
		auto player_armor_text = "Armor: " + std::to_string(player.m_armor_value());
		auto player_armor_text_width = render->get_text_width(player_armor_text, c_render::en_font_type::ROBOTO_10);
		auto player_armor_text_height = render->get_text_height(player_armor_text, c_render::en_font_type::ROBOTO_10);

		c_render::s_text_styles armor_text_styles;
		armor_text_styles.x = box_x - player_armor_text_width;
		armor_text_styles.y = box_y + HP_TEXT_HEIGHT;
		armor_text_styles.color = D3DCOLOR_ARGB(255, 255, 255, 255);
		armor_text_styles.outline = true;
		armor_text_styles.font_type = c_render::en_font_type::ROBOTO_10;
		render->text(player_armor_text, armor_text_styles);
		const auto ARMOR_TEXT_HEIGHT = player_armor_text_height;

		//has defuse kit text
		auto player_defuse_kit_text = player.m_b_has_defuser() ? "Has defuse kit" : "";
		auto player_defuse_kit_text_width = render->get_text_width(player_defuse_kit_text, c_render::en_font_type::ROBOTO_10);
		auto player_defuse_kit_text_height = render->get_text_height(player_defuse_kit_text, c_render::en_font_type::ROBOTO_10);

		c_render::s_text_styles defuse_kit_text_styles;
		defuse_kit_text_styles.x = box_x - player_defuse_kit_text_width;
		defuse_kit_text_styles.y = box_y + HP_TEXT_HEIGHT + ARMOR_TEXT_HEIGHT;
		defuse_kit_text_styles.color = D3DCOLOR_ARGB(255, 255, 255, 255);
		defuse_kit_text_styles.outline = true;
		defuse_kit_text_styles.font_type = c_render::en_font_type::ROBOTO_10;
		render->text(player_defuse_kit_text, defuse_kit_text_styles);
	}
}