#pragma once

enum struct en_client_states: int {
	Invalid = -1,
	Lobby = 0,
	Loading = 1,
	Connecting = 2,
	Connected = 5,
	InGame = 6,
	InvalidLast,
};