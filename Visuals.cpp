#include "Visuals.hpp"

Visuals::Visuals() {}

void Visuals::drawEntity(std::pair<int, IGlowObjectDefinition> glowObject, colorRGBA color, GlowStyle style) {
	glowObject.second.color(color);
	glowObject.second.glowStyle = (int)style;
	glowObject.second.renderWhenOccluded = true;
	mem.write<IGlowObjectDefinition>(glowObject.first, glowObject.second);
}

colorRGBA Visuals::getHpBasedColor(BasePlayer& player){
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

void Visuals::loop() {
	if (!Settings::visuals_glowEsp_enable && !Settings::visuals_chams_enable) {
		return;
	}

	if (engine.clientState->state() != ClientStates::INGAME || engine.clientState->m_nDeltaTick() == -1) {
		return;
	}

	for (auto glowObject : client.glowObjectManager->array()) {
		auto entity = BaseEntity(glowObject.second.dwBaseEntity);
		auto entityClassID = entity.m_iClassID();

		if (Settings::visuals_glowEsp_enable) {
			if (entityClassID == ClassID::CC4) {
				if (Settings::visuals_glowEsp_show_c4) {
					drawEntity(glowObject, Settings::visuals_glowEsp_c4_color, GlowStyle::GLOW_STYLE_FULL_BODY);
				}
			}
			else if (entityClassID == ClassID::CPlantedC4) {
				if (Settings::visuals_glowEsp_show_c4) {
					drawEntity(glowObject, Settings::visuals_glowEsp_c4_planted_color, GlowStyle::GLOW_STYLE_FULL_BODY);
				}
			}
			else if (entityClassID == ClassID::CCSPlayer) {
				BasePlayer player(entity);

				if (!player.dwBase || player.m_iHealth() <= 0 || player.m_bDormant()) {
					continue;
				}

				if (player.m_iTeamNum() == client.localPlayer->m_iTeamNum()) {
					if (Settings::visuals_glowEsp_show_friends) {
						if (Settings::visuals_glowEsp_mode == VISUALS_GLOWESP_MODE_COLOR) {
							drawEntity(glowObject, Settings::visuals_glowEsp_friends_color, Settings::visuals_glowEsp_style);
						}
						else {
							drawEntity(glowObject, getHpBasedColor(player), Settings::visuals_glowEsp_style);
						}
					}
				}
				else {
					if (Settings::visuals_glowEsp_show_enemies) {
						if (Settings::visuals_glowEsp_mode == VISUALS_GLOWESP_MODE_COLOR) {
							drawEntity(
								glowObject,

								//visible check
								client.localPlayer->canSeePlayer(player) ?
								Settings::visuals_glowEsp_enemy_visible_color :
								Settings::visuals_glowEsp_enemy_invisible_color,

								Settings::visuals_glowEsp_style
							);
						}
						else {
							drawEntity(glowObject, getHpBasedColor(player), Settings::visuals_glowEsp_style);
						}
					}
				}

				if (Settings::visuals_glowEsp_show_defusing) {
					if (player.m_bIsDefusing()) {
						drawEntity(glowObject, Settings::visuals_glowEsp_defusing_color, Settings::visuals_glowEsp_style);
					}
				}
			}
			else if (
				entityClassID == ClassID::CDecoyGrenade ||
				entityClassID == ClassID::CHEGrenade ||
				entityClassID == ClassID::CIncendiaryGrenade ||
				entityClassID == ClassID::CMolotovGrenade ||
				entityClassID == ClassID::CSmokeGrenade ||
				entityClassID == ClassID::CFlashbang
				) {
				if (Settings::visuals_glowEsp_show_grenades) {
					drawEntity(glowObject, Settings::visuals_glowEsp_grenades_color, GlowStyle::GLOW_STYLE_FULL_BODY);
				}
			}
		}

		if (Settings::visuals_chams_enable) {
			if (entityClassID == ClassID::CCSPlayer) {
				BasePlayer player(entity);

				if (!player.dwBase || player.m_iHealth() <= 0 || player.m_bDormant()) {
					continue;
				}

				if (player.m_iTeamNum() == client.localPlayer->m_iTeamNum()) {
					if (Settings::visuals_chams_show_friends) {
						player.m_clrRender(Settings::visuals_chams_friends_color);
					}
				}
				else {
					if (Settings::visuals_chams_show_enemies) {
						player.m_clrRender(Settings::visuals_chams_enemy_color);
					}
				}
			}
		}
	}
}