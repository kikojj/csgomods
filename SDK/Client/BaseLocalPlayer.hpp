#pragma once

#include <iostream>

#include "../../Utils/Memory/Memory.hpp"
#include "../../Utils/Memory/Modules.hpp"
#include "../../Utils/Offsets/Offsets.hpp"
#include "../../Utils/VisibleCheck/VisibleCheck.h"

#include "../Utils/Vector.hpp"
#include "../Utils/Skeleton.hpp"

#include "../Vars.hpp"

#include "BasePlayer.hpp"
#include "EntityList.hpp"

class BaseLocalPlayer : public BasePlayer {
//main methods
public:
	BaseLocalPlayer() {}

	virtual int get(){
		return mem.read<int>(clientDll.dwBase + Offsets::signatures::dwLocalPlayer);
	}

//props
public:
	PROP(int,		m_iCrosshairId, get())	//entity in crosshair

	PROP(Vec3,	m_vecVelocity,	get())	//direction of movement of the player

//methods
public:
	bool canSeePlayer(BasePlayer player, int bone = -1) {
		auto playerID = EntityList::getEntityID(player.get());
		return canSeePlayer({ player, playerID }, bone);
	}
	bool canSeePlayer(EntityList::EntityObject entityObject, int bone = -1) {
		auto playerID = entityObject.second;
		if (playerID == -1) {
			return false;
		}
		if (bone == -1) {
			return visibleCheck.isVisible(playerID);
		}
		else {
			return visibleCheck.isVisible(playerID, bone);
		}
	}
};