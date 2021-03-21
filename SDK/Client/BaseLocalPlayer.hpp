#pragma once

#include <iostream>

#include "BasePlayer.hpp"

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

	int get();

	/// <summary>
	/// get direction of movement of the player
	/// </summary>
	/// <returns>vec3(x,y,z) direction</returns>
	Vector3 m_vecVelocity();

	/// <summary>
	/// check if entity in crosshair
	/// </summary>
	/// <returns></returns>
	int m_iCrosshairId();

	bool canSeePlayer(BasePlayer, int = -1);
};