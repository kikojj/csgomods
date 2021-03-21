#pragma once

#include <iostream>

#include "BasePlayer.hpp"

#include "../Vars.hpp"

#include "../Utils/Vector.hpp"
#include "../Utils/Skeleton.hpp"

#include "../../Utils/Memory/Memory.hpp"
#include "../../Utils/Memory/Modules.hpp"
#include "../../Utils/Offsets/Offsets.hpp"
#include "../../Utils/VisibleCheck/VisibleCheck.h"

class BaseLocalPlayer : public BasePlayer {
private:
public:
	BaseLocalPlayer();

	/// <summary>get direction of movement of the player</summary>
	VAR_R_DEC(Vector3, m_vecVelocity)
	/// <summary>check if entity in crosshair</summary>
	VAR_R_DEC(int, m_iCrosshairId)

	int get();
	bool canSeePlayer(BasePlayer, int = -1);
};