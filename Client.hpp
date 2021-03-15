#pragma once

#include <iostream>

#include "Defines.hpp"
#include "Memory.hpp"
#include "Modules.hpp"
#include "Offsets.hpp"

#include "BaseLocalPlayer.hpp"
#include "EntityList.hpp"
#include "GlowObjectManager.hpp"

#include "IGlowObjectDefinition.hpp"
#include "CInput.hpp"
#include "KeyEvent.hpp"

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