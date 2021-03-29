#pragma once

#include <iostream>

#include "../../Utils/Memory/Memory.hpp"
#include "../../Utils/Memory/Modules.hpp"
#include "../../Utils/Offsets/Offsets.hpp"

#include "../Utils/Defines.hpp"
#include "../Utils/IGlowObjectDefinition.hpp"
#include "../Utils/CInput.hpp"
#include "../Utils/KeyEvent.hpp"

#include "../Vars.hpp"

#include "LocalPlayer.hpp"
#include "EntityList.hpp"
#include "GlowObjectManager.hpp"
#include "GlobalVars.hpp"

class Client {
//main variables
public:
	LocalPlayer* localPlayer;
	EntityList* entityList;
	GlowObjectManager* glowObjectManager;
	GlobalVars* globalVars;

//main methods
public:
	Client() {
		localPlayer = new LocalPlayer();
		entityList = new EntityList();
		glowObjectManager = new GlowObjectManager();
		globalVars = new GlobalVars();
	}

//props
public:
	C_PROP_PTR(short,			dwMouseEnable)
	PROP_			(int,				confirmReservationCallback, mem.read<int>(clientDll.dwBase + Offsets::signatures::hConfirmMatch + 0x7), 0, int, value)

	C_PROP_PTR(Input,			dwInput)

	C_PROP_PTR(KeyEvent,	dwForceJump)
	C_PROP_PTR(KeyEvent,	dwForceAttack)

//methods
public:
	int hConfirmMatch() {
		return clientDll.dwBase + Offsets::signatures::hConfirmMatch;
	}
};

extern Client client;