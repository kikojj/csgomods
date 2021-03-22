#include "ItemDefinitionIndex.hpp"

std::vector<ItemDefinitionIndex> ItemDefinition::all = {
	ItemDefinitionIndex::Invalid,
	ItemDefinitionIndex::WEAPON_DesertEagle,
	ItemDefinitionIndex::WEAPON_DualBerettas,
	ItemDefinitionIndex::WEAPON_FiveSeven,
	ItemDefinitionIndex::WEAPON_Glock18,
	ItemDefinitionIndex::WEAPON_AK47,
	ItemDefinitionIndex::WEAPON_AUG,
	ItemDefinitionIndex::WEAPON_AWP,
	ItemDefinitionIndex::WEAPON_FAMAS,
	ItemDefinitionIndex::WEAPON_G3SG1,
	ItemDefinitionIndex::WEAPON_GalilAR,
	ItemDefinitionIndex::WEAPON_M249,
	ItemDefinitionIndex::WEAPON_M4A4,
	ItemDefinitionIndex::WEAPON_MAC10,
	ItemDefinitionIndex::WEAPON_P90,
	ItemDefinitionIndex::ITEM_RepulsorDevice,
	ItemDefinitionIndex::WEAPON_MP5SD,
	ItemDefinitionIndex::WEAPON_UMP45,
	ItemDefinitionIndex::WEAPON_XM1014,
	ItemDefinitionIndex::WEAPON_PPBizon,
	ItemDefinitionIndex::WEAPON_MAG7,
	ItemDefinitionIndex::WEAPON_Negev,
	ItemDefinitionIndex::WEAPON_SawedOff,
	ItemDefinitionIndex::WEAPON_Tec9,
	ItemDefinitionIndex::WEAPON_Zeusx27,
	ItemDefinitionIndex::WEAPON_P2000,
	ItemDefinitionIndex::WEAPON_MP7,
	ItemDefinitionIndex::WEAPON_MP9,
	ItemDefinitionIndex::WEAPON_Nova,
	ItemDefinitionIndex::WEAPON_P250,
	ItemDefinitionIndex::ITEM_BallisticShield,
	ItemDefinitionIndex::WEAPON_SCAR20,
	ItemDefinitionIndex::WEAPON_SG553,
	ItemDefinitionIndex::WEAPON_SSG08,
	ItemDefinitionIndex::WEAPON_KnifeCT,
	ItemDefinitionIndex::WEAPON_KnifeCT2,
	ItemDefinitionIndex::WEAPON_Flashbang,
	ItemDefinitionIndex::WEAPON_HEGrenade,
	ItemDefinitionIndex::WEAPON_SmokeGrenade,
	ItemDefinitionIndex::WEAPON_Molotov,
	ItemDefinitionIndex::WEAPON_DecoyGrenade,
	ItemDefinitionIndex::WEAPON_IncendiaryGrenade,
	ItemDefinitionIndex::ITEM_C4Explosive,
	ItemDefinitionIndex::ITEM_KelvarVest,
	ItemDefinitionIndex::ITEM_Kelvar_Helmet,
	ItemDefinitionIndex::ITEM_HeavyAssaultSuit,
	ItemDefinitionIndex::ITEM_nvg,
	ItemDefinitionIndex::ITEM_DefuseKit,
	ItemDefinitionIndex::ITEM_RescueKit,
	ItemDefinitionIndex::ITEM_MediShot,
	ItemDefinitionIndex::ITEM_MusicKit,
	ItemDefinitionIndex::WEAPON_KnifeT,
	ItemDefinitionIndex::WEAPON_M4A1S,
	ItemDefinitionIndex::WEAPON_USPS,
	ItemDefinitionIndex::ITEM_TradeUpContract,
	ItemDefinitionIndex::WEAPON_CZ75Auto,
	ItemDefinitionIndex::WEAPON_R8Revolver,
	ItemDefinitionIndex::WEAPON_TacticalAwarenessGrenade,
	ItemDefinitionIndex::ITEM_BareHands,
	ItemDefinitionIndex::WEAPON_BreachCharge,
	ItemDefinitionIndex::ITEM_Tablet,
	ItemDefinitionIndex::WEAPON_Knife,
	ItemDefinitionIndex::WEAPON_Axe,
	ItemDefinitionIndex::WEAPON_Hammer,
	ItemDefinitionIndex::WEAPON_Wrench,
	ItemDefinitionIndex::ITEM_SpectralShiv,
	ItemDefinitionIndex::WEAPON_FireBomb,
	ItemDefinitionIndex::WEAPON_DiversionDevice,
	ItemDefinitionIndex::WEAPON_FragGrenade,
	ItemDefinitionIndex::WEAPON_Snowball,
	ItemDefinitionIndex::WEAPON_BumpMine,
	ItemDefinitionIndex::WEAPON_Bayonet,
	ItemDefinitionIndex::WEAPON_ClassicKnife,
	ItemDefinitionIndex::WEAPON_FlipKnife,
	ItemDefinitionIndex::WEAPON_GutKnife,
	ItemDefinitionIndex::WEAPON_Karambit,
	ItemDefinitionIndex::WEAPON_M9Bayonet,
	ItemDefinitionIndex::WEAPON_HuntsmanKnife,
	ItemDefinitionIndex::WEAPON_FlachionKnife,
	ItemDefinitionIndex::WEAPON_BowieKnife,
	ItemDefinitionIndex::WEAPON_ButterflyKnife,
	ItemDefinitionIndex::WEAPON_ShadowDaggers,
	ItemDefinitionIndex::WEAPON_ParacordKnife,
	ItemDefinitionIndex::WEAPON_SurvivalKnife,
	ItemDefinitionIndex::WEAPON_UrsusKnife,
	ItemDefinitionIndex::WEAPON_NavajaKnife,
	ItemDefinitionIndex::WEAPON_NomadKnife,
	ItemDefinitionIndex::WEAPON_StilettoKnife,
	ItemDefinitionIndex::WEAPON_TalonKnife,
	ItemDefinitionIndex::WEAPON_SkeletonKnife
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
		itemDI == ItemDefinitionIndex::WEAPON_DesertEagle ||
		itemDI == ItemDefinitionIndex::WEAPON_DualBerettas ||
		itemDI == ItemDefinitionIndex::WEAPON_FiveSeven ||
		itemDI == ItemDefinitionIndex::WEAPON_Glock18 ||
		itemDI == ItemDefinitionIndex::WEAPON_Tec9 ||
		itemDI == ItemDefinitionIndex::WEAPON_P2000 ||
		itemDI == ItemDefinitionIndex::WEAPON_P250 ||
		itemDI == ItemDefinitionIndex::WEAPON_USPS ||
		itemDI == ItemDefinitionIndex::WEAPON_CZ75Auto ||
		itemDI == ItemDefinitionIndex::WEAPON_R8Revolver
		) {
		return true;
	}
	return false;
}

bool ItemDefinition::isSMG(ItemDefinitionIndex itemDI) {
	if (
		itemDI == ItemDefinitionIndex::WEAPON_MAC10 ||
		itemDI == ItemDefinitionIndex::WEAPON_P90 ||
		itemDI == ItemDefinitionIndex::WEAPON_MP5SD ||
		itemDI == ItemDefinitionIndex::WEAPON_UMP45 ||
		itemDI == ItemDefinitionIndex::WEAPON_MP7 ||
		itemDI == ItemDefinitionIndex::WEAPON_MP9 ||
		itemDI == ItemDefinitionIndex::WEAPON_PPBizon
		) {
		return true;
	}
	return false;
}

bool ItemDefinition::isHeavy(ItemDefinitionIndex itemDI) {
	if (
		itemDI == ItemDefinitionIndex::WEAPON_M249 ||
		itemDI == ItemDefinitionIndex::WEAPON_Negev
		) {
		return true;
	}
	return false;
}

bool ItemDefinition::isShotgun(ItemDefinitionIndex itemDI) {
	if (
		itemDI == ItemDefinitionIndex::WEAPON_XM1014 ||
		itemDI == ItemDefinitionIndex::WEAPON_MAG7 ||
		itemDI == ItemDefinitionIndex::WEAPON_SawedOff ||
		itemDI == ItemDefinitionIndex::WEAPON_Nova
		) {
		return true;
	}
	return false;
}

bool ItemDefinition::isRifle(ItemDefinitionIndex itemDI) {
	if (
		itemDI == ItemDefinitionIndex::WEAPON_AK47 ||
		itemDI == ItemDefinitionIndex::WEAPON_AUG ||
		itemDI == ItemDefinitionIndex::WEAPON_FAMAS ||
		itemDI == ItemDefinitionIndex::WEAPON_GalilAR ||
		itemDI == ItemDefinitionIndex::WEAPON_M4A4 ||
		itemDI == ItemDefinitionIndex::WEAPON_SG553 ||
		itemDI == ItemDefinitionIndex::WEAPON_M4A1S
		) {
		return true;
	}
	return false;
}

bool ItemDefinition::isSnipers(ItemDefinitionIndex itemDI) {
	if (
		itemDI == ItemDefinitionIndex::WEAPON_AWP ||
		itemDI == ItemDefinitionIndex::WEAPON_G3SG1 ||
		itemDI == ItemDefinitionIndex::WEAPON_SCAR20 ||
		itemDI == ItemDefinitionIndex::WEAPON_SSG08
		) {
		return true;
	}
	return false;
}

bool ItemDefinition::isKnife(ItemDefinitionIndex itemDI) {
	if (
		itemDI == ItemDefinitionIndex::WEAPON_Knife ||
		itemDI == ItemDefinitionIndex::WEAPON_KnifeCT ||
		itemDI == ItemDefinitionIndex::WEAPON_KnifeCT2 ||
		itemDI == ItemDefinitionIndex::WEAPON_KnifeT ||
		itemDI == ItemDefinitionIndex::WEAPON_Bayonet ||
		itemDI == ItemDefinitionIndex::WEAPON_ClassicKnife ||
		itemDI == ItemDefinitionIndex::WEAPON_FlipKnife ||
		itemDI == ItemDefinitionIndex::WEAPON_GutKnife ||
		itemDI == ItemDefinitionIndex::WEAPON_Karambit ||
		itemDI == ItemDefinitionIndex::WEAPON_M9Bayonet ||
		itemDI == ItemDefinitionIndex::WEAPON_HuntsmanKnife ||
		itemDI == ItemDefinitionIndex::WEAPON_FlachionKnife ||
		itemDI == ItemDefinitionIndex::WEAPON_BowieKnife ||
		itemDI == ItemDefinitionIndex::WEAPON_ButterflyKnife ||
		itemDI == ItemDefinitionIndex::WEAPON_ShadowDaggers ||
		itemDI == ItemDefinitionIndex::WEAPON_ParacordKnife ||
		itemDI == ItemDefinitionIndex::WEAPON_SurvivalKnife ||
		itemDI == ItemDefinitionIndex::WEAPON_UrsusKnife ||
		itemDI == ItemDefinitionIndex::WEAPON_NavajaKnife ||
		itemDI == ItemDefinitionIndex::WEAPON_NomadKnife ||
		itemDI == ItemDefinitionIndex::WEAPON_StilettoKnife ||
		itemDI == ItemDefinitionIndex::WEAPON_TalonKnife ||
		itemDI == ItemDefinitionIndex::WEAPON_SkeletonKnife
		) {
		return true;
	}
	return false;
}

bool ItemDefinition::isBomb(ItemDefinitionIndex itemDI) {
	if (itemDI == ItemDefinitionIndex::ITEM_C4Explosive) {
		return true;
	}
	return false;
}

bool ItemDefinition::isGrenade(ItemDefinitionIndex itemDI) {
	if (
		itemDI == ItemDefinitionIndex::WEAPON_HEGrenade ||
		itemDI == ItemDefinitionIndex::WEAPON_Flashbang ||
		itemDI == ItemDefinitionIndex::WEAPON_Molotov ||
		itemDI == ItemDefinitionIndex::WEAPON_SmokeGrenade ||
		itemDI == ItemDefinitionIndex::WEAPON_IncendiaryGrenade ||
		itemDI == ItemDefinitionIndex::WEAPON_DecoyGrenade
		) {
		return true;
	}
	return false;
}