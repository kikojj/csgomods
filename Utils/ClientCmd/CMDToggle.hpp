#pragma once

#include "ClientCmd.hpp"

class CMDToggle {
private:
	std::string toggle_on;
	std::string toggle_off;
	bool state = false;

public:
	CMDToggle(std::string toggle_on, std::string toggle_off);
	void toogle();
	void on();
	void off();
};