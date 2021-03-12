#include "BasePlayer.hpp"

BasePlayer::BasePlayer() {}

BasePlayer::BasePlayer(BaseEntity entity){
	this->dwBase = entity.dwBase;
}

BasePlayer::BasePlayer(int _dwBase) {
	this->dwBase = _dwBase;
};

void BasePlayer::operator=(BasePlayer entity) {
	this->dwBase = entity.dwBase;
}

int BasePlayer::get(){
	return this->dwBase;
}

TeamNum BasePlayer::m_iTeamNum() {
	auto team = mem.Read<int>(get() + Offsets::netvars::m_iTeamNum);
	//std::cout << "BasePlayer::m_iTeamNum(): " << team << std::endl;
	if (team == 1 || team == 2 || team == 3) {
		return TeamNum(team);
	};
	return NO_TEAM;
}

int BasePlayer::m_iHealth() {
	auto health = mem.Read<int>(get() + Offsets::netvars::m_iHealth);
	//std::cout << "BasePlayer::m_iHealth(): " << health << std::endl;
	return health;
}

int BasePlayer::m_dwBoneMatrix() {
	//std::cout << "BasePlayer::m_dwBoneMatrix()" << std::endl;
	return mem.Read<int>(get() + Offsets::netvars::m_dwBoneMatrix);
}

Vector3 BasePlayer::getBonePos(Skeleton bone){
	auto bonePos = Vector3(mem.Read<BoneVector>(m_dwBoneMatrix() + 0x30 * bone + 0x0C));
	return bonePos;
}

Vector3 BasePlayer::m_vecOrigin() {
	auto vec = Vector3(mem.Read<Vec3>(get() + Offsets::netvars::m_vecOrigin));
	//std::cout << "BasePlayer::m_vecOrigin(): (" << vec << ")\n";
	return vec;
}

Vector3 BasePlayer::m_vecViewOffset() {
	auto vec = Vector3(mem.Read<Vec3>(get() + Offsets::netvars::m_vecViewOffset));
	//std::cout << "BasePlayer::m_vecViewOffset(): (" << vec << ")\n";
	return vec;
}

int BasePlayer::m_bSpottedByMask() {
	auto spottedByMask = mem.Read<int>(get() + Offsets::netvars::m_bSpottedByMask);
	//std::cout << "BasePlayer::m_bSpottedByMask(): " << std::bitset<sizeof spottedByMask>(spottedByMask) << std::endl;
	return spottedByMask;
}

bool BasePlayer::isBspVisibleFrom(Vector3 origin){
	for (auto bone: ALL_BONES){
		if (bsp_parser.is_visible(origin.toMatrix(), getBonePos(bone).toMatrix())) {
			return true;
		}
	}
	return false;
}

bool BasePlayer::m_bSpotted() {
	auto spotted = (bool)mem.Read<BOOL>(get() + Offsets::netvars::m_bSpotted);
	//std::cout << "BasePlayer::m_bSpotted(): " << spotted << std::endl;
	return spotted;
}

void BasePlayer::m_bSpotted(bool value) {
	mem.Write(get() + Offsets::netvars::m_bSpotted, BOOL(value));
}

bool BasePlayer::m_bSpottedByMask(int id) {
	return m_bSpottedByMask() & (1 << id);
}

int BasePlayer::m_iShotsFired() {
	auto shotsFired = mem.Read<int>(get() + Offsets::netvars::m_iShotsFired);
	//std::cout << "BasePlayer::m_iShotsFired(): " << shotsFired << std::endl;
	return shotsFired;
}

Vector2 BasePlayer::m_aimPunchAngle() {
	auto vec = Vector2(mem.Read<Vec2>(get() + Offsets::netvars::m_aimPunchAngle));;
	//std::cout << "BasePlayer::m_aimPunchAngle(): (" << vec << ")\n";
	return vec;
}

void BasePlayer::m_aimPunchAngle(Vector2& ang) {
	//std::cout << "m_aimPunchAngle()" << std::endl;
	mem.Write(get() + Offsets::netvars::m_aimPunchAngle, ang.toVec2());
}

Vector2 BasePlayer::m_viewPunchAngle() {
	auto vec = Vector2(mem.Read<Vec2>(get() + Offsets::netvars::m_viewPunchAngle));;
	//std::cout << "BasePlayer::m_viewPunchAngle(): (" << vec << ")\n";
	return vec;
}

void BasePlayer::m_viewPunchAngle(Vector2& ang) {
	//std::cout << "m_viewPunchAngle()" << std::endl;
	mem.Write(get() + Offsets::netvars::m_viewPunchAngle, ang.toVec2());
}

int BasePlayer::m_hActiveWeapon() {
	auto activeWeapon = mem.Read<int>(get() + Offsets::netvars::m_hActiveWeapon);
	//std::cout << "BasePlayer::m_hActiveWeapon(): " << activeWeapon << std::endl;
	return activeWeapon;
}

int BasePlayer::m_fFlags(){
	return mem.Read<int>(get() + Offsets::netvars::m_fFlags);
}

void BasePlayer::m_clrRender(colorRGBA color) {
	//std::cout << "m_clrRender()" << std::endl;
	struct { BYTE r; BYTE g; BYTE b; BYTE a; } clrColor;
	clrColor.r = color.r;
	clrColor.g = color.g;
	clrColor.b = color.b;
	clrColor.a = color.a;
	mem.Write(get() + Offsets::netvars::m_clrRender, clrColor);
}

bool BasePlayer::m_bIsDefusing(){
	return mem.Read<bool>(get() + Offsets::netvars::m_bIsDefusing);
}

int BasePlayer::m_ArmorValue(){
	return mem.Read<int>(get() + Offsets::netvars::m_ArmorValue);
}

int BasePlayer::m_iCompetitiveWins(){
	return mem.Read<int>(get() + Offsets::netvars::m_iCompetitiveWins);
}

bool BasePlayer::m_bHasDefuser(){
	return mem.Read<bool>(get() + Offsets::netvars::m_bHasDefuser);
}

bool BasePlayer::m_bIsScoped(){
	return mem.Read<bool>(get() + Offsets::netvars::m_bIsScoped);
}

bool BasePlayer::m_bHasHelmet(){
	return mem.Read<bool>(get() + Offsets::netvars::m_bHasHelmet);
}

int BasePlayer::m_nTickBase(){
	return mem.Read<int>(get() + Offsets::netvars::m_nTickBase);
}

LifeState BasePlayer::m_lifeState(){
	auto lifeState = mem.Read<int>(get() + Offsets::netvars::m_lifeState);
	if (lifeState >= 0 && lifeState <= 2) {
		return LifeState(lifeState);
	}
	return INVALID_LIFESTATE;
}

float BasePlayer::m_flFlashMaxAlpha() {
	auto flashMaxAlpha = mem.Read<float>(get() + Offsets::netvars::m_flFlashMaxAlpha);
	return flashMaxAlpha;
}

void BasePlayer::m_flFlashMaxAlpha(float v){
	mem.Write(get() + Offsets::netvars::m_flFlashMaxAlpha, v);
}

float BasePlayer::m_flFlashDuration() {
	auto m_flFlashDuration = mem.Read<float>(get() + Offsets::netvars::m_flFlashDuration);
	return m_flFlashDuration;
}

float BasePlayer::m_flFlashAlpha() {
	auto m_flFlashAlpha = mem.Read<float>(get() + Offsets::netvars::m_flFlashMaxAlpha - 0xC);
	return m_flFlashAlpha;
}

int BasePlayer::m_hViewModel(){
	return mem.Read<int>(get() + Offsets::netvars::m_hViewModel);
}

std::vector<int> BasePlayer::myWeapons(){
	std::vector<int> weapons;
	for (int i = 0; i < 8; i++){
		int weaponID = myWeaponByID(i) & 0xfff;
		weapons.push_back(weaponID);
	}
	return weapons;
}

int BasePlayer::myWeaponByID(int id) {
	return mem.Read<int>(get() + Offsets::netvars::m_hMyWeapons + id * 0x4);
}

int BasePlayer::m_iObserverMode(){
	return mem.Read<int>(get() + Offsets::netvars::m_iObserverMode);
}

void BasePlayer::m_iObserverMode(int v){
	mem.Write(get() + Offsets::netvars::m_iObserverMode, v);
}

