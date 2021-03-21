#pragma once

#include <iostream>

#include "BaseLocalPlayer.hpp"
#include "EntityList.hpp"
#include "GlowObjectManager.hpp"

#include "../Vars.hpp"

#include "../Utils/Defines.hpp"
#include "../Utils/IGlowObjectDefinition.hpp"
#include "../Utils/CInput.hpp"
#include "../Utils/KeyEvent.hpp"

#include "../../Utils/Memory/Memory.hpp"
#include "../../Utils/Memory/Modules.hpp"
#include "../../Utils/Offsets/Offsets.hpp"

class Client {
public:
	BaseLocalPlayer* localPlayer;
	EntityList* entityList;
	GlowObjectManager* glowObjectManager;

	Client();

	VAR_R_DEC(Input, dwInput)
	VAR_R_DEC(short, dwMouseEnable)
	VAR_R_DEC(int, hConfirmMatch)
	VAR_R_DEC(int, confirmReservationCallback)
	VAR_W_DEC(KeyEvent, dwForceJump)
	VAR_W_DEC(KeyEvent, dwForceAttack)
};

extern Client client;