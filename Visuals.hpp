#pragma once

#include <algorithm>

#include "SDK/Client/Client.hpp"
#include "SDK/Client/BaseEntity.hpp"
#include "SDK/Client/BasePlayer.hpp"
#include "SDK/Engine/Engine.hpp"
#include "SDK/Utils/ColorRGBA.hpp"
#include "SDK/Utils/GlowObjectDefinition.hpp"

#include "Utils/VisibleCheck/VisibleCheck.hpp"
#include "Utils/Settings/Settings.hpp"

class c_visuals {
private:
	void draw_entity(c_glow_object_manager::t_glow_object, s_color_rgba, en_glow_style);
	void reset_render(c_base_player&);
	s_color_rgba get_hp_based_color(c_base_player&);

public:
	c_visuals();
	void loop();
};