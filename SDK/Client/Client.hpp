#pragma once

#include <iostream>

#include "BaseLocalPlayer.hpp"
#include "EntityList.hpp"
#include "GlowObjectManager.hpp"

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

	/// <summary>
	/// set dwForceJump value
	/// </summary>
	/// <param name="value">KeyEvent</param>
	void dwForceJump(KeyEvent);

	/// <summary>
	/// set dwForceAttack value
	/// </summary>
	/// <param name="value">KeyEvent</param>
	void dwForceAttack(KeyEvent);

	/// <summary>
	/// get Input
	/// </summary>
	Input dwInput();

	short dwMouseEnable();

	int hConfirmMatch();

	int confirmReservationCallback();
};

extern Client client;