#pragma once

#include <algorithm>

#include "Client.hpp"
#include "Engine.hpp"
#include "Settings.hpp"

#include "BaseEntity.hpp"
#include "BasePlayer.hpp"

#include "ColorRGBA.hpp"
#include "IGlowObjectDefinition.hpp"

class GlowEsp {
private:
	void drawEntity(std::pair<int, IGlowObjectDefinition>, colorRGBA, GlowStyle);
	colorRGBA getHpBasedColor(BasePlayer&);

public:
	GlowEsp();
	void loop();
};