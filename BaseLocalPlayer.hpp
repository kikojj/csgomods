#pragma once

#include <iostream>

#include "Memory.hpp"
#include "Modules.hpp"
#include "Offsets.hpp"

#include "BasePlayer.hpp"
#include "Vector.hpp"
#include "Skeleton.hpp"
#include "visibleCheck/VisibleCheck.h"

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