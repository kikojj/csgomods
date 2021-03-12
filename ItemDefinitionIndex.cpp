#include "ItemDefinitionIndex.hpp"

std::vector<ItemDefinitionIndex> ItemDefinition::all = {
	INVALID_ITEM_DI,
	WEAPON_DesertEagle,
	WEAPON_DualBerettas,
	WEAPON_FiveSeven,
	WEAPON_Glock18,
	WEAPON_AK47,
	WEAPON_AUG,
	WEAPON_AWP,
	WEAPON_FAMAS,
	WEAPON_G3SG1,
	WEAPON_GalilAR,
	WEAPON_M249,
	WEAPON_M4A4,
	WEAPON_MAC10,
	WEAPON_P90,
	ITEM_RepulsorDevice,
	WEAPON_MP5SD,
	WEAPON_UMP45,
	WEAPON_XM1014,
	WEAPON_PPBizon,
	WEAPON_MAG7,
	WEAPON_Negev,
	WEAPON_SawedOff,
	WEAPON_Tec9,
	WEAPON_Zeusx27,
	WEAPON_P2000,
	WEAPON_MP7,
	WEAPON_MP9,
	WEAPON_Nova,
	WEAPON_P250,
	ITEM_BallisticShield,
	WEAPON_SCAR20,
	WEAPON_SG553,
	WEAPON_SSG08,
	WEAPON_KnifeCT,
	WEAPON_KnifeCT2,
	WEAPON_Flashbang,
	WEAPON_HEGrenade,
	WEAPON_SmokeGrenade,
	WEAPON_Molotov,
	WEAPON_DecoyGrenade,
	WEAPON_IncendiaryGrenade,
	ITEM_C4Explosive,
	ITEM_KelvarVest,
	ITEM_Kelvar_Helmet,
	ITEM_HeavyAssaultSuit,
	ITEM_nvg,
	ITEM_DefuseKit,
	ITEM_RescueKit,
	ITEM_MediShot,
	ITEM_MusicKit,
	WEAPON_KnifeT,
	WEAPON_M4A1S,
	WEAPON_USPS,
	ITEM_TradeUpContract,
	WEAPON_CZ75Auto,
	WEAPON_R8Revolver,
	WEAPON_TacticalAwarenessGrenade,
	ITEM_BareHands,
	WEAPON_BreachCharge,
	ITEM_Tablet,
	WEAPON_Knife,
	WEAPON_Axe,
	WEAPON_Hammer,
	WEAPON_Wrench,
	ITEM_SpectralShiv,
	WEAPON_FireBomb,
	WEAPON_DiversionDevice,
	WEAPON_FragGrenade,
	WEAPON_Snowball,
	WEAPON_BumpMine,
	WEAPON_Bayonet,
	WEAPON_ClassicKnife,
	WEAPON_FlipKnife,
	WEAPON_GutKnife,
	WEAPON_Karambit,
	WEAPON_M9Bayonet,
	WEAPON_HuntsmanKnife,
	WEAPON_FlachionKnife,
	WEAPON_BowieKnife,
	WEAPON_ButterflyKnife,
	WEAPON_ShadowDaggers,
	WEAPON_ParacordKnife,
	WEAPON_SurvivalKnife,
	WEAPON_UrsusKnife,
	WEAPON_NavajaKnife,
	WEAPON_NomadKnife,
	WEAPON_StilettoKnife,
	WEAPON_TalonKnife,
	WEAPON_SkeletonKnife
};

std::vector<ItemDefinitionIndex> ItemDefinition::knifes(){
	std::vector<ItemDefinitionIndex> knifes;
	std::copy_if(all.begin(), all.end(), std::back_inserter(knifes), [](ItemDefinitionIndex& itemDI) {
		return isKnife(itemDI);
	});
	return knifes;
}

bool ItemDefinition::isPistol(ItemDefinitionIndex itemDI) {
	if (
		itemDI == WEAPON_DesertEagle ||
		itemDI == WEAPON_DualBerettas ||
		itemDI == WEAPON_FiveSeven ||
		itemDI == WEAPON_Glock18 ||
		itemDI == WEAPON_Tec9 ||
		itemDI == WEAPON_P2000 ||
		itemDI == WEAPON_P250 ||
		itemDI == WEAPON_USPS ||
		itemDI == WEAPON_CZ75Auto ||
		itemDI == WEAPON_R8Revolver
		) {
		return true;
	}
	return false;
}

bool ItemDefinition::isSMG(ItemDefinitionIndex itemDI) {
	if (
		itemDI == WEAPON_MAC10 ||
		itemDI == WEAPON_P90 ||
		itemDI == WEAPON_MP5SD ||
		itemDI == WEAPON_UMP45 ||
		itemDI == WEAPON_MP7 ||
		itemDI == WEAPON_MP9 ||
		itemDI == WEAPON_PPBizon
		) {
		return true;
	}
	return false;
}

bool ItemDefinition::isHeavy(ItemDefinitionIndex itemDI) {
	if (
		itemDI == WEAPON_M249 ||
		itemDI == WEAPON_Negev
		) {
		return true;
	}
	return false;
}

bool ItemDefinition::isShotgun(ItemDefinitionIndex itemDI) {
	if (
		itemDI == WEAPON_XM1014 ||
		itemDI == WEAPON_MAG7 ||
		itemDI == WEAPON_SawedOff ||
		itemDI == WEAPON_Nova
		) {
		return true;
	}
	return false;
}

bool ItemDefinition::isRifle(ItemDefinitionIndex itemDI) {
	if (
		itemDI == WEAPON_AK47 ||
		itemDI == WEAPON_AUG ||
		itemDI == WEAPON_FAMAS ||
		itemDI == WEAPON_GalilAR ||
		itemDI == WEAPON_M4A4 ||
		itemDI == WEAPON_SG553 ||
		itemDI == WEAPON_M4A1S
		) {
		return true;
	}
	return false;
}

bool ItemDefinition::isSnipers(ItemDefinitionIndex itemDI) {
	if (
		itemDI == WEAPON_AWP ||
		itemDI == WEAPON_G3SG1 ||
		itemDI == WEAPON_SCAR20 ||
		itemDI == WEAPON_SSG08
		) {
		return true;
	}
	return false;
}

bool ItemDefinition::isKnife(ItemDefinitionIndex itemDI) {
	if (
		itemDI == WEAPON_Knife ||
		itemDI == WEAPON_KnifeCT ||
		itemDI == WEAPON_KnifeCT2 ||
		itemDI == WEAPON_KnifeT ||
		itemDI == WEAPON_Bayonet ||
		itemDI == WEAPON_ClassicKnife ||
		itemDI == WEAPON_FlipKnife ||
		itemDI == WEAPON_GutKnife ||
		itemDI == WEAPON_Karambit ||
		itemDI == WEAPON_M9Bayonet ||
		itemDI == WEAPON_HuntsmanKnife ||
		itemDI == WEAPON_FlachionKnife ||
		itemDI == WEAPON_BowieKnife ||
		itemDI == WEAPON_ButterflyKnife ||
		itemDI == WEAPON_ShadowDaggers ||
		itemDI == WEAPON_ParacordKnife ||
		itemDI == WEAPON_SurvivalKnife ||
		itemDI == WEAPON_UrsusKnife ||
		itemDI == WEAPON_NavajaKnife ||
		itemDI == WEAPON_NomadKnife ||
		itemDI == WEAPON_StilettoKnife ||
		itemDI == WEAPON_TalonKnife ||
		itemDI == WEAPON_SkeletonKnife
		) {
		return true;
	}
	return false;
}

bool ItemDefinition::isBomb(ItemDefinitionIndex itemDI) {
	if (itemDI == ITEM_C4Explosive) {
		return true;
	}
	return false;
}

bool ItemDefinition::isGrenade(ItemDefinitionIndex itemDI) {
	if (
		itemDI == WEAPON_HEGrenade ||
		itemDI == WEAPON_Flashbang ||
		itemDI == WEAPON_Molotov ||
		itemDI == WEAPON_SmokeGrenade ||
		itemDI == WEAPON_IncendiaryGrenade ||
		itemDI == WEAPON_DecoyGrenade
		) {
		return true;
	}
	return false;
}