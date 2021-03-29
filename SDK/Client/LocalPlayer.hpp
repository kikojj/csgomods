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

class LocalPlayer : public BasePlayer {
//main methods
public:
	LocalPlayer() {}

	virtual int get(){
		return mem.read<int>(clientDll.dwBase + Offsets::signatures::dwLocalPlayer);
	}

//props
public:
	PROP(int,		m_iCrosshairId, get())	//entity in crosshair

	PROP(Vec3,	m_vecVelocity,	get())	//direction of movement of the player

//methods
public:
	bool canSeePlayer(BasePlayer player, int bone = -1, bool smokeCheck = true) {
		auto playerID = EntityList::getEntityID(player.get());
		return canSeePlayer({ player, playerID }, bone, smokeCheck);
	}
	bool canSeePlayer(EntityList::EntityObject entityObject, int bone = -1, bool smokeCheck = true) {
		auto playerID = entityObject.second;

		if (playerID < 0) {
			return false;
		}

		bool isVisible = false;

		if (bone <= 0) {
			isVisible = visibleCheck.isVisible(playerID);
		}
		else {
			isVisible = visibleCheck.isVisible(playerID, bone);
		}

		if (smokeCheck && isVisible) {
			auto myView = (Vector3(m_vecOrigin()) + Vector3(m_vecViewOffset())).toVec3();

			BasePlayer player(entityObject.first);
			auto playerBonePos = player.getBonePos(bone <= 0 ? Skeleton::CHEST : (Skeleton)bone).toVec3();

			if (!visibleCheck.lineGoesThroughSmoke(myView, playerBonePos)) {
				isVisible = true;
			}
			else {
				isVisible = false;
			}
		}

		return isVisible;
	}
};