#include "BaseLocalPlayer.hpp"

BaseLocalPlayer::BaseLocalPlayer() {
	this->dwBase = 0;
};

int BaseLocalPlayer::get() {
	//std::cout << "BaseLocalPlayer::get()" << std::endl;
	return mem.read<int>(clientDll.dwBase + Offsets::signatures::dwLocalPlayer);
}

Vector3 BaseLocalPlayer::m_vecVelocity(){
	auto vec = Vector3(mem.read<Vec3>(get() + Offsets::netvars::m_vecVelocity));
	//std::cout << "BaseLocalPlayer::m_vecVelocity(): (" << vec.x << ", " << vec.y << ", " << vec.z << ")" << std::endl;
	return vec;
}

int BaseLocalPlayer::m_iCrosshairId(){
	return mem.read<int>(get() + Offsets::netvars::m_iCrosshairId);
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
