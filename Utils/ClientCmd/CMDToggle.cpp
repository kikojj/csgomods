#include "CMDToggle.hpp"

CMDToggle::CMDToggle(std::string toggle_on, std::string toggle_off): toggle_on(toggle_on), toggle_off(toggle_off) {}

void CMDToggle::toogle() {
	if (state) {
		off();
	}
	else {
		on();
	}
}

void CMDToggle::on() {
	g_client_cmd.execute(toggle_on.c_str());
	state = true;
}

void CMDToggle::off() {
	g_client_cmd.execute(toggle_off.c_str());
	state = false;
}