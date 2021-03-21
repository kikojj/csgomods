#pragma once

#include <algorithm>

#include "SDK/Client/Client.hpp"
#include "SDK/Client/BaseEntity.hpp"
#include "SDK/Client/BasePlayer.hpp"
#include "SDK/Engine/Engine.hpp"
#include "SDK/Utils/ColorRGBA.hpp"
#include "SDK/Utils/IGlowObjectDefinition.hpp"

#include "Utils/VisibleCheck/VisibleCheck.h"
#include "Utils/Settings/Settings.hpp"

class Visuals {
private:
	void drawEntity(std::pair<int, IGlowObjectDefinition>, colorRGBA, GlowStyle);
	colorRGBA getHpBasedColor(BasePlayer&);

public:
	Visuals();
	void loop();
};