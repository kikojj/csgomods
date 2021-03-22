#pragma once

enum struct ClientStates : int {
	Invalid = -1,
	LOBBY = 0,
	LOADING = 1,
	CONNECTING = 2,
	CONNECTED = 5,
	INGAME = 6
};