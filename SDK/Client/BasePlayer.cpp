#include "BasePlayer.hpp"

BasePlayer::BasePlayer() {}
BasePlayer::BasePlayer(BaseEntity entity){
	this->dwBase = entity.dwBase;
}
BasePlayer::BasePlayer(int _dwBase) {
	this->dwBase = _dwBase;
};

TeamNum BasePlayer::m_iTeamNum() {
	auto team = mem.read<int>(get() + Offsets::netvars::m_iTeamNum);
	//std::cout << "BasePlayer::m_iTeamNum(): " << team << std::endl;
	if (team == 1 || team == 2 || team == 3) {
		return TeamNum(team);
	};
	return NO_TEAM;
}
VAR_R_DEF(int, m_iHealth, BasePlayer, get(), netvars)
VAR_R_DEF(int, m_dwBoneMatrix, BasePlayer, get(), netvars)
Vector3 BasePlayer::getBonePos(Skeleton bone) {
	auto bonePos = Vector3(mem.read<BoneVector>(m_dwBoneMatrix() + 0x30 * bone + 0x0C));
	return bonePos;
}
VAR_R_DEF(Vector3, m_vecOrigin, BasePlayer, get(), netvars)
VAR_R_DEF(Vector3, m_vecViewOffset, BasePlayer, get(), netvars)
VAR_R_DEF(int, m_bSpottedByMask, BasePlayer, get(), netvars)
bool BasePlayer::isBspVisibleFrom(Vector3 origin) {
	for (auto bone : ALL_BONES) {
		if (bsp_parser.is_visible(origin.toMatrix(), getBonePos(bone).toMatrix())) {
			return true;
		}
	}
	return false;
}
VAR_R_DEF(bool, m_bSpotted, BasePlayer, get(), netvars)
bool BasePlayer::m_bSpottedByMask(int id) {
	return m_bSpottedByMask() & (1 << id);
}
VAR_R_DEF(int, m_iShotsFired, BasePlayer, get(), netvars)
VAR_R_DEF(Vector2, m_viewPunchAngle, BasePlayer, get(), netvars)
VAR_R_DEF(int, m_hActiveWeapon, BasePlayer, get(), netvars)
VAR_R_DEF(int, m_fFlags, BasePlayer, get(), netvars)
VAR_R_DEF(bool, m_bIsDefusing, BasePlayer, get(), netvars)
VAR_R_DEF(int, m_ArmorValue, BasePlayer, get(), netvars)
VAR_R_DEF(int, m_iCompetitiveWins, BasePlayer, get(), netvars)
VAR_R_DEF(bool, m_bHasDefuser, BasePlayer, get(), netvars)
VAR_R_DEF(bool, m_bIsScoped, BasePlayer, get(), netvars)
VAR_R_DEF(bool, m_bHasHelmet, BasePlayer, get(), netvars)
VAR_R_DEF(int, m_nTickBase, BasePlayer, get(), netvars)
LifeState BasePlayer::m_lifeState() {
	auto lifeState = mem.read<int>(get() + Offsets::netvars::m_lifeState);
	if (lifeState >= 0 && lifeState <= 2) {
		return LifeState(lifeState);
	}
	return INVALID_LIFESTATE;
}
VAR_R_DEF(float, m_flFlashDuration, BasePlayer, get(), netvars)
VAR_R_DEF(float, m_flFlashAlpha, BasePlayer, get(), netvars)
VAR_R_DEF(int, m_hViewModel, BasePlayer, get(), netvars)
std::vector<int> BasePlayer::myWeapons() {
	std::vector<int> weapons;
	for (int i = 0; i < 8; i++) {
		int weaponID = myWeaponByID(i) & 0xfff;
		weapons.push_back(weaponID);
	}
	return weapons;
}
VAR_R_DEF(bool, m_bDormant, BasePlayer, get(), netvars)
int BasePlayer::myWeaponByID(int id) {
	return mem.read<int>(get() + Offsets::netvars::m_hMyWeapons + id * 0x4);
}
void BasePlayer::m_clrRender(colorRGBA color) {
	//std::cout << "m_clrRender()" << std::endl;
	struct SClrColor { BYTE r; BYTE g; BYTE b; BYTE a; } clrColor;
	clrColor.r = color.r;
	clrColor.g = color.g;
	clrColor.b = color.b;
	clrColor.a = color.a;
	mem.write(get() + Offsets::netvars::m_clrRender, clrColor);
}
VAR_W_DEF(bool, m_bSpotted, BasePlayer, get(), netvars)
VAR_W_DEF(Vector2&, m_viewPunchAngle, BasePlayer, get(), netvars)
VAR_RW_DEF(Vector2, m_aimPunchAngle, BasePlayer, get(), netvars)
VAR_RW_DEF(float, m_flFlashMaxAlpha, BasePlayer, get(), netvars)
VAR_RW_DEF(int, m_iObserverMode, BasePlayer, get(), netvars)

int BasePlayer::get() {
	return this->dwBase;
}
void BasePlayer::operator=(BasePlayer entity) {
	this->dwBase = entity.dwBase;
}