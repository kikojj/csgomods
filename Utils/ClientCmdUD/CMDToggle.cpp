#include "CMDToggle.hpp"

CMDToggle::CMDToggle(std::string _toggleOn, std::string _toggleOff) : toggleOn(_toggleOn), toggleOff(_toggleOff) {}

void CMDToggle::toogle() {
	if (state) {
		off();
	}
	else {
		on();
	}
}

void CMDToggle::on() {
	clientCmdUD.execute(toggleOn.c_str());
	state = true;
}

void CMDToggle::off() {
	clientCmdUD.execute(toggleOff.c_str());
	state = false;
}
