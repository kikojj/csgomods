#pragma once

#include "Memory.hpp"
#include "Modules.hpp"
#include "Offsets.hpp"

#include "Vector.hpp"
#include "ClientStates.hpp"

class ClientState {
public:
	ClientState();

	/// <summary>
	/// get clientState address
	/// </summary>
	/// <returns>Address to clientState</returns>
	int get();

	/// <summary>
	/// get variable that stores vec2(x, y) the screen's center in the plane of the screen
	/// </summary>
	/// <returns>Vector2 class member</returns>
	Vector2 dwViewAngles();

	/// <summary>
	/// set variable that stores vec2(x, y) the screen's center in the plane of the screen
	/// </summary>
	/// <param name="vec">Vector2 class member</param>
	void dwViewAngles(Vector2);

	/// <summary>
	/// get the ID of localPlayer in entityList
	/// </summary>
	/// <returns>int ID of localPlayer</returns>
	int getLocalPlayer();

	/// <summary>
	/// get user state
	/// </summary>
	/// <returns>
	/// LOBBY = 0,
	/// LOADING = 1,
	/// CONNECTIONG = 2,
	/// CONNECTED = 5,
	/// INGAME = 6
	/// </returns>
	ClientStates state();

	/// <summary>
	/// get current map directory
	/// </summary>
	/// <returns></returns>
	std::array<char, 0x120> mapDirectory();

	int dwModelPrecache();

	void m_nDeltaTick(int);
};