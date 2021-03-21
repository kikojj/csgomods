#include "BaseLocalPlayer.hpp"

BaseLocalPlayer::BaseLocalPlayer() {
	this->dwBase = 0;
};

Vector3 BaseLocalPlayer::m_vecVelocity(){
	auto vec = Vector3(mem.read<Vec3>(get() + Offsets::netvars::m_vecVelocity));
	//std::cout << "BaseLocalPlayer::m_vecVelocity(): (" << vec.x << ", " << vec.y << ", " << vec.z << ")" << std::endl;
	return vec;
}
VAR_R_DEF(int, m_iCrosshairId, BaseLocalPlayer, get(), netvars)

int BaseLocalPlayer::get() {
	//std::cout << "BaseLocalPlayer::get()" << std::endl;
	return mem.read<int>(clientDll.dwBase + Offsets::signatures::dwLocalPlayer);
}
bool BaseLocalPlayer::canSeePlayer(BasePlayer player, int bone){
	auto playerID = player.getEntityID();
	if (playerID == -1) {
		return false;
	}
	if (bone == -1) {
		return visibleCheck.isVisible(playerID);
	}
	else {
		return visibleCheck.isVisible(playerID, bone);
	}
}
