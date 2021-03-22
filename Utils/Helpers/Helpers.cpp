#include "Helpers.hpp"

void Helpers::shoot() {
	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
	Sleep(10);
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
}

void Helpers::jump(){
	client.dwForceJump(KeyEvent::KEY_DOWN);
	Sleep(10);
	client.dwForceJump(KeyEvent::KEY_UP);
}

void Helpers::keyboardPressKey(int key){
	keybd_event(key, 0, 0, 0);
	Sleep(10);
	keybd_event(key, 0, KEYEVENTF_KEYUP, 0);
}

void Helpers::toggleSteamOverlay(){
	keybd_event(VK_TAB, 0, 0, 0);
	keybd_event(VK_SHIFT, 0, 0, 0);
	Sleep(10);
	keybd_event(VK_TAB, 0, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0);
}

bool Helpers::isMouseActive(){
	return (client.dwInput().mouseActive && (client.dwMouseEnable() ^ (short)Offsets::signatures::dwMouseEnablePtr) && !engine.isOverlayActive());
}

bool Helpers::isFlashed(float flash){
	return flash > 120.f ? true : false;
}

void Helpers::exit(){
	mem.exit();
	std::exit(0);
}

int Helpers::getModelIndex(std::string name) {
	int dwModelPrecache = engine.clientState->dwModelPrecache();
	int modelBase = mem.read<int>(mem.read<int>(dwModelPrecache + 0x40) + 0xC) + 0xC;

	for (int i = 0; i < 1024; i++) {
		int model = mem.read<int>(modelBase + (i * 0x34));

		std::string modelString = std::string(mem.read<std::array<char, 128>>(model).data());
		if (modelString.find(name) != std::string::npos) {
			return i;
		}
	}

	return -1;
}

int Helpers::getModelIndex(ItemDefinitionIndex itemDI) {
	switch (itemDI)
	{
	case ItemDefinitionIndex::WEAPON_Knife:
		return Helpers::getModelIndex("models/weapons/v_knife_default_ct.mdl");
		break;
	case ItemDefinitionIndex::WEAPON_KnifeT:
		return Helpers::getModelIndex("models/weapons/v_knife_default_t.mdl");
		break;
	case ItemDefinitionIndex::WEAPON_Bayonet:
		return Helpers::getModelIndex("models/weapons/v_knife_bayonet.mdl");
		break;
	case ItemDefinitionIndex::WEAPON_FlipKnife:
		return Helpers::getModelIndex("models/weapons/v_knife_flip.mdl");
		break;
	case ItemDefinitionIndex::WEAPON_GutKnife:
		return Helpers::getModelIndex("models/weapons/v_knife_gut.mdl");
		break;
	case ItemDefinitionIndex::WEAPON_Karambit:
		return Helpers::getModelIndex("models/weapons/v_knife_karam.mdl");
		break;
	case ItemDefinitionIndex::WEAPON_M9Bayonet:
		return Helpers::getModelIndex("models/weapons/v_knife_m9_bay.mdl");
		break;
	case ItemDefinitionIndex::WEAPON_HuntsmanKnife:
		return Helpers::getModelIndex("models/weapons/v_knife_tactical.mdl");
		break;
	case ItemDefinitionIndex::WEAPON_FlachionKnife:
		return Helpers::getModelIndex("models/weapons/v_knife_falchion_advanced.mdl");
		break;
	case ItemDefinitionIndex::WEAPON_BowieKnife:
		return Helpers::getModelIndex("models/weapons/v_knife_survival_bowie.mdl");
		break;
	case ItemDefinitionIndex::WEAPON_ButterflyKnife:
		return Helpers::getModelIndex("models/weapons/v_knife_butterfly.mdl");
		break;
	case ItemDefinitionIndex::WEAPON_ShadowDaggers:
		return Helpers::getModelIndex("models/weapons/v_knife_push.mdl");
		break;
	case ItemDefinitionIndex::WEAPON_UrsusKnife:
		return Helpers::getModelIndex("models/weapons/v_knife_ursus.mdl");
		break;
	case ItemDefinitionIndex::WEAPON_NavajaKnife:
		return Helpers::getModelIndex("models/weapons/v_knife_gypsy_jackknife.mdl");
		break;
	case ItemDefinitionIndex::WEAPON_StilettoKnife:
		return Helpers::getModelIndex("models/weapons/v_knife_stiletto.mdl");
		break;
	case  ItemDefinitionIndex::WEAPON_TalonKnife:
		return Helpers::getModelIndex("models/weapons/v_knife_widowmaker.mdl");
		break;
	case ItemDefinitionIndex::WEAPON_ClassicKnife:
		return Helpers::getModelIndex("models/weapons/v_knife_css.mdl");
		break;
	case ItemDefinitionIndex::WEAPON_ParacordKnife:
		return Helpers::getModelIndex("models/weapons/v_knife_cord.mdl");
		break;
	case ItemDefinitionIndex::WEAPON_SurvivalKnife:
		return Helpers::getModelIndex("models/weapons/v_knife_canis.mdl");
		break;
	case ItemDefinitionIndex::WEAPON_NomadKnife:
		return Helpers::getModelIndex("models/weapons/v_knife_outdoor.mdl");
		break;
	case ItemDefinitionIndex::WEAPON_SkeletonKnife:
		return Helpers::getModelIndex("models/weapons/v_knife_skeleton.mdl");
		break;
	default:
		return -1;
		break;
	}
}

void Helpers::updateModelIndexes(){
	if (engine.clientState->state() != ClientStates::INGAME) {
		return;
	}

	auto knifes = ItemDefinition::knifes();
	std::for_each(knifes.begin(), knifes.end(), [](ItemDefinitionIndex& itemDI) {
		modelIndexes[itemDI] = getModelIndex(itemDI);
	});
}

void Helpers::fullForceUpdate(){
	engine.clientState->m_nDeltaTick(-1);
}