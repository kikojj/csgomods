#pragma once

#include "ClientCmdUD.hpp"

class CMDToggle {
private:
	std::string toggleOn;
	std::string toggleOff;
	bool state = false;

public:
	CMDToggle(std::string _toggleOn, std::string _toggleOff);
	void toogle();
	void on();
	void off();
};