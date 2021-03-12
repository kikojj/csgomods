#include "GlowEsp.hpp"

GlowEsp::GlowEsp() {}

void GlowEsp::drawEntity(std::pair<int, IGlowObjectDefinition> glowObject, colorRGBA color, GlowStyle style) {
	glowObject.second.color(color);
	glowObject.second.glowStyle = style;
	glowObject.second.renderWhenOccluded = true;
	mem.Write<IGlowObjectDefinition>(glowObject.first, glowObject.second);
}

colorRGBA GlowEsp::getHpBasedColor(BasePlayer& player){
	float scale = (float)player.m_iHealth() / 100.f;
	colorRGBA hp0 = { 255,0,0,255 };
	colorRGBA hp100 = { 0,255,0,255 };
	colorRGBA color;
	color.r = hp0.r + (hp100.r - hp0.r) * scale;
	color.g = hp0.g + (hp100.g - hp0.g) * scale;
	color.b = hp0.b + (hp100.b - hp0.b) * scale;
	color.a = 255;
	return color;
}

void GlowEsp::loop() {
	if (!Settings::visuals_glowEsp_enable && !Settings::visuals_chams_enable) {
		return;
	}

	if (engine.clientState->state() != INGAME) {
		return;
	}

	for (auto glowObject : client.glowObjectManager->array()) {
		auto entity = BaseEntity(glowObject.second.dwBaseEntity);

		auto entityClassID = entity.m_iClassID();
		if (entityClassID != CCSPlayer && entityClassID != CC4 && entityClassID != CPlantedC4) {
			continue;
		}

		if (Settings::visuals_glowEsp_enable && Settings::visuals_glowEsp_show_c4 && entityClassID == CC4) {
			drawEntity(glowObject, Settings::visuals_glowEsp_c4_color, GLOW_STYLE_FULL_BODY);
			continue;
		}

		if (Settings::visuals_glowEsp_enable && Settings::visuals_glowEsp_show_c4 && entityClassID == CPlantedC4) {
			drawEntity(glowObject, Settings::visuals_glowEsp_c4_planted_color, GLOW_STYLE_FULL_BODY);
			continue;
		}

		if (entityClassID == CCSPlayer &&
			(
				Settings::visuals_glowEsp_show_enemies || Settings::visuals_glowEsp_show_friends ||
				Settings::visuals_chams_show_enemies || Settings::visuals_chams_show_friends
				)
			) {
			BasePlayer player(entity);

			if (player.m_iHealth() <= 0) {
				continue;
			}

			if (player.m_iTeamNum() == client.localPlayer->m_iTeamNum()) {
				if (Settings::visuals_glowEsp_enable && Settings::visuals_glowEsp_show_friends) {
					if (Settings::visuals_glowEsp_mode == VISUALS_GLOWESP_MODE_COLOR) {
						drawEntity(glowObject, Settings::visuals_glowEsp_friends_color, Settings::visuals_glowEsp_style);
					}
					else {
						drawEntity(glowObject, getHpBasedColor(player), Settings::visuals_glowEsp_style);
					}
				}
				if (Settings::visuals_chams_enable && Settings::visuals_chams_show_friends) {
					player.m_clrRender(Settings::visuals_chams_friends_color);
				}
				continue;
			}

			if (Settings::visuals_glowEsp_enable && Settings::visuals_glowEsp_show_enemies) {
				if (Settings::visuals_glowEsp_mode == VISUALS_GLOWESP_MODE_COLOR) {
					//auto spottedByMask = player.m_bSpottedByMask(engine.clientState->getLocalPlayer());
					//drawEntity(glowObject, spottedByMask ? Settings::visuals_glowEsp_enemy_visible_color : Settings::visuals_glowEsp_enemy_invisible_color, GLOW_STYLE_FULL_BODY);

					auto isVisible = player.isBspVisibleFrom(client.localPlayer->m_vecOrigin() + client.localPlayer->m_vecViewOffset());
					drawEntity(glowObject, isVisible ? Settings::visuals_glowEsp_enemy_visible_color : Settings::visuals_glowEsp_enemy_invisible_color, Settings::visuals_glowEsp_style);
				}
				else {
					drawEntity(glowObject, getHpBasedColor(player), Settings::visuals_glowEsp_style);
				}
				
			}
			if (Settings::visuals_chams_enable && Settings::visuals_chams_show_enemies) {
				player.m_clrRender(Settings::visuals_chams_enemy_color);
			}
		}
	}
}