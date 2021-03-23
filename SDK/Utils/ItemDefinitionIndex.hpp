#pragma once

#include <vector>
#include <algorithm>
#include <iterator>

enum struct ItemDefinitionIndex : int {
  Invalid = 0,
  WEAPON_DesertEagle = 1,
  WEAPON_DualBerettas = 2,
  WEAPON_FiveSeven = 3,
  WEAPON_Glock18 = 4,
  WEAPON_AK47 = 7,
  WEAPON_AUG = 8,
  WEAPON_AWP = 9,
  WEAPON_FAMAS = 10,
  WEAPON_G3SG1 = 11,
  WEAPON_GalilAR = 13,
  WEAPON_M249 = 14,
  WEAPON_M4A4 = 16,
  WEAPON_MAC10 = 17,
  WEAPON_P90 = 19,
  ITEM_RepulsorDevice = 20,
  WEAPON_MP5SD = 23,
  WEAPON_UMP45 = 24,
  WEAPON_XM1014 = 25,
  WEAPON_PPBizon = 26,
  WEAPON_MAG7 = 27,
  WEAPON_Negev = 28,
  WEAPON_SawedOff = 29,
  WEAPON_Tec9 = 30,
  WEAPON_Zeusx27 = 31,
  WEAPON_P2000 = 32,
  WEAPON_MP7 = 33,
  WEAPON_MP9 = 34,
  WEAPON_Nova = 35,
  WEAPON_P250 = 36,
  ITEM_BallisticShield = 37,
  WEAPON_SCAR20 = 38,
  WEAPON_SG553 = 39,
  WEAPON_SSG08 = 40,
  WEAPON_KnifeCT = 41,
  WEAPON_KnifeCT2 = 42,
  WEAPON_Flashbang = 43,
  WEAPON_HEGrenade = 44,
  WEAPON_SmokeGrenade = 45,
  WEAPON_Molotov = 46,
  WEAPON_DecoyGrenade = 47,
  WEAPON_IncendiaryGrenade = 48,
  ITEM_C4Explosive = 49,
  ITEM_KelvarVest = 50,
  ITEM_Kelvar_Helmet = 51,
  ITEM_HeavyAssaultSuit = 52,
  ITEM_nvg = 54,
  ITEM_DefuseKit = 55,
  ITEM_RescueKit = 56,
  ITEM_MediShot = 57,
  ITEM_MusicKit = 58,
  WEAPON_KnifeT = 59,
  WEAPON_M4A1S = 60,
  WEAPON_USPS = 61,
  ITEM_TradeUpContract = 62,
  WEAPON_CZ75Auto = 63,
  WEAPON_R8Revolver = 64,
  WEAPON_TacticalAwarenessGrenade = 68,
  ITEM_BareHands = 69,
  WEAPON_BreachCharge = 70,
  ITEM_Tablet = 72,
  WEAPON_Knife = 74,
  WEAPON_Axe = 75,
  WEAPON_Hammer = 76,
  WEAPON_Wrench = 78,
  ITEM_SpectralShiv = 80,
  WEAPON_FireBomb = 81,
  WEAPON_DiversionDevice = 82,
  WEAPON_FragGrenade = 83,
  WEAPON_Snowball = 84,
  WEAPON_BumpMine = 85,
  WEAPON_Bayonet = 500,
  WEAPON_ClassicKnife = 503,
  WEAPON_FlipKnife = 505,
  WEAPON_GutKnife = 506,
  WEAPON_Karambit = 507,
  WEAPON_M9Bayonet = 508,
  WEAPON_HuntsmanKnife = 509,
  WEAPON_FlachionKnife = 512,
  WEAPON_BowieKnife = 514,
  WEAPON_ButterflyKnife = 515,
  WEAPON_ShadowDaggers = 516,
  WEAPON_ParacordKnife = 517,
  WEAPON_SurvivalKnife = 518,
  WEAPON_UrsusKnife = 519,
  WEAPON_NavajaKnife = 520,
  WEAPON_NomadKnife = 521,
  WEAPON_StilettoKnife = 522,
  WEAPON_TalonKnife = 523,
  WEAPON_SkeletonKnife = 525,
  InvalidLast
};

class ItemDefinition {
public:
  static std::vector<ItemDefinitionIndex> all;
  static std::vector<ItemDefinitionIndex> knifes();

  static bool isPistol(ItemDefinitionIndex);
  static bool isSMG(ItemDefinitionIndex);
  static bool isShotgun(ItemDefinitionIndex);
  static bool isHeavy(ItemDefinitionIndex);
  static bool isRifle(ItemDefinitionIndex);
  static bool isSnipers(ItemDefinitionIndex);
  static bool isKnife(ItemDefinitionIndex);
  static bool isBomb(ItemDefinitionIndex);
  static bool isGrenade(ItemDefinitionIndex);
  static bool isZeusX27(ItemDefinitionIndex);
};