#pragma once

#include <algorithm>

#include "Overlay.hpp"
#include "Render.hpp"
#include "SDK/Client/Client.hpp"
#include "SDK/Client/BaseEntity.hpp"
#include "SDK/Client/BasePlayer.hpp"
#include "SDK/Engine/Engine.hpp"
#include "SDK/Utils/ColorRGBA.hpp"
#include "SDK/Utils/GlowObjectDefinition.hpp"

#include "Utils/VisibleCheck/VisibleCheck.hpp"
#include "Utils/Settings/Settings.hpp"
#include "Utils/Helpers/Helpers.hpp"

class c_visuals {
private:
	void draw_entity(c_glow_object_manager::t_glow_object, s_color_rgba, en_glow_style&);
	void reset_render(c_base_player&);
	s_color_rgba get_hp_based_color(c_base_player&, c_settings::s_glow_esp_settings&);
	bool get_entity_glow_settings(c_base_entity&, s_color_rgba*, en_glow_style*);
	bool get_entity_chams_settings(c_base_entity&, s_color_rgba*);

public:
	c_visuals();
	void loop();
	
	void render(c_overlay*, c_render*);

private:
	struct s_draw_player_options {
	
	};

public:
	void draw_player_box(s_draw_player_options);
};