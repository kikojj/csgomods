#pragma once

#include <vector>
#include <algorithm>
#include <iterator>

class c_item {
public:
  enum struct en_defenition_index : int {
    Invalid = 0,
    WeaponDesertEagle = 1,
    WeaponDualBerettas = 2,
    WeaponFiveSeven = 3,
    WeaponGlock18 = 4,
    WeaponAK47 = 7,
    WeaponAUG = 8,
    WeaponAWP = 9,
    WeaponFAMAS = 10,
    WeaponG3SG1 = 11,
    WeaponGalilAR = 13,
    WeaponM249 = 14,
    WeaponM4A4 = 16,
    WeaponMAC10 = 17,
    WeaponP90 = 19,
    ItemRepulsorDevice = 20,
    WeaponMP5SD = 23,
    WeaponUMP45 = 24,
    WeaponXM1014 = 25,
    WeaponPPBizon = 26,
    WeaponMAG7 = 27,
    WeaponNegev = 28,
    WeaponSawedOff = 29,
    WeaponTec9 = 30,
    WeaponZeusx27 = 31,
    WeaponP2000 = 32,
    WeaponMP7 = 33,
    WeaponMP9 = 34,
    WeaponNova = 35,
    WeaponP250 = 36,
    ItemBallisticShield = 37,
    WeaponSCAR20 = 38,
    WeaponSG553 = 39,
    WeaponSSG08 = 40,
    WeaponKnifeCT = 41,
    WeaponKnifeCT2 = 42,
    WeaponFlashbang = 43,
    WeaponHEGrenade = 44,
    WeaponSmokeGrenade = 45,
    WeaponMolotov = 46,
    WeaponDecoyGrenade = 47,
    WeaponIncendiaryGrenade = 48,
    ItemC4Explosive = 49,
    ItemKelvarVest = 50,
    ItemKelvar_Helmet = 51,
    ItemHeavyAssaultSuit = 52,
    Itemnvg = 54,
    ItemDefuseKit = 55,
    ItemRescueKit = 56,
    ItemMediShot = 57,
    ItemMusicKit = 58,
    WeaponKnifeT = 59,
    WeaponM4A1S = 60,
    WeaponUSPS = 61,
    ItemTradeUpContract = 62,
    WeaponCZ75Auto = 63,
    WeaponR8Revolver = 64,
    WeaponTacticalAwarenessGrenade = 68,
    ItemBareHands = 69,
    WeaponBreachCharge = 70,
    ItemTablet = 72,
    WeaponKnife = 74,
    WeaponAxe = 75,
    WeaponHammer = 76,
    WeaponWrench = 78,
    ItemSpectralShiv = 80,
    WeaponFireBomb = 81,
    WeaponDiversionDevice = 82,
    WeaponFragGrenade = 83,
    WeaponSnowball = 84,
    WeaponBumpMine = 85,
    WeaponBayonet = 500,
    WeaponClassicKnife = 503,
    WeaponFlipKnife = 505,
    WeaponGutKnife = 506,
    WeaponKarambit = 507,
    WeaponM9Bayonet = 508,
    WeaponHuntsmanKnife = 509,
    WeaponFlachionKnife = 512,
    WeaponBowieKnife = 514,
    WeaponButterflyKnife = 515,
    WeaponShadowDaggers = 516,
    WeaponParacordKnife = 517,
    WeaponSurvivalKnife = 518,
    WeaponUrsusKnife = 519,
    WeaponNavajaKnife = 520,
    WeaponNomadKnife = 521,
    WeaponStilettoKnife = 522,
    WeaponTalonKnife = 523,
    WeaponSkeletonKnife = 525,
    GloveStuddedBloodhound = 5027,
    GloveT = 5028,
    GloveCT = 5029,
    GloveSporty = 5030,
    GloveSlick = 5031,
    GloveLeatherWeap= 5032,
    GloveMotorcycle = 5033,
    GloveSpecialist = 5034,
    GloveHydra = 5035,
    InvalidLast
  };

  static std::vector<en_defenition_index> all() {
    return std::vector<en_defenition_index>{
      en_defenition_index::Invalid,
        en_defenition_index::WeaponDesertEagle,
        en_defenition_index::WeaponDualBerettas,
        en_defenition_index::WeaponFiveSeven,
        en_defenition_index::WeaponGlock18,
        en_defenition_index::WeaponAK47,
        en_defenition_index::WeaponAUG,
        en_defenition_index::WeaponAWP,
        en_defenition_index::WeaponFAMAS,
        en_defenition_index::WeaponG3SG1,
        en_defenition_index::WeaponGalilAR,
        en_defenition_index::WeaponM249,
        en_defenition_index::WeaponM4A4,
        en_defenition_index::WeaponMAC10,
        en_defenition_index::WeaponP90,
        en_defenition_index::ItemRepulsorDevice,
        en_defenition_index::WeaponMP5SD,
        en_defenition_index::WeaponUMP45,
        en_defenition_index::WeaponXM1014,
        en_defenition_index::WeaponPPBizon,
        en_defenition_index::WeaponMAG7,
        en_defenition_index::WeaponNegev,
        en_defenition_index::WeaponSawedOff,
        en_defenition_index::WeaponTec9,
        en_defenition_index::WeaponZeusx27,
        en_defenition_index::WeaponP2000,
        en_defenition_index::WeaponMP7,
        en_defenition_index::WeaponMP9,
        en_defenition_index::WeaponNova,
        en_defenition_index::WeaponP250,
        en_defenition_index::ItemBallisticShield,
        en_defenition_index::WeaponSCAR20,
        en_defenition_index::WeaponSG553,
        en_defenition_index::WeaponSSG08,
        en_defenition_index::WeaponKnifeCT,
        en_defenition_index::WeaponKnifeCT2,
        en_defenition_index::WeaponFlashbang,
        en_defenition_index::WeaponHEGrenade,
        en_defenition_index::WeaponSmokeGrenade,
        en_defenition_index::WeaponMolotov,
        en_defenition_index::WeaponDecoyGrenade,
        en_defenition_index::WeaponIncendiaryGrenade,
        en_defenition_index::ItemC4Explosive,
        en_defenition_index::ItemKelvarVest,
        en_defenition_index::ItemKelvar_Helmet,
        en_defenition_index::ItemHeavyAssaultSuit,
        en_defenition_index::Itemnvg,
        en_defenition_index::ItemDefuseKit,
        en_defenition_index::ItemRescueKit,
        en_defenition_index::ItemMediShot,
        en_defenition_index::ItemMusicKit,
        en_defenition_index::WeaponKnifeT,
        en_defenition_index::WeaponM4A1S,
        en_defenition_index::WeaponUSPS,
        en_defenition_index::ItemTradeUpContract,
        en_defenition_index::WeaponCZ75Auto,
        en_defenition_index::WeaponR8Revolver,
        en_defenition_index::WeaponTacticalAwarenessGrenade,
        en_defenition_index::ItemBareHands,
        en_defenition_index::WeaponBreachCharge,
        en_defenition_index::ItemTablet,
        en_defenition_index::WeaponKnife,
        en_defenition_index::WeaponAxe,
        en_defenition_index::WeaponHammer,
        en_defenition_index::WeaponWrench,
        en_defenition_index::ItemSpectralShiv,
        en_defenition_index::WeaponFireBomb,
        en_defenition_index::WeaponDiversionDevice,
        en_defenition_index::WeaponFragGrenade,
        en_defenition_index::WeaponSnowball,
        en_defenition_index::WeaponBumpMine,
        en_defenition_index::WeaponBayonet,
        en_defenition_index::WeaponClassicKnife,
        en_defenition_index::WeaponFlipKnife,
        en_defenition_index::WeaponGutKnife,
        en_defenition_index::WeaponKarambit,
        en_defenition_index::WeaponM9Bayonet,
        en_defenition_index::WeaponHuntsmanKnife,
        en_defenition_index::WeaponFlachionKnife,
        en_defenition_index::WeaponBowieKnife,
        en_defenition_index::WeaponButterflyKnife,
        en_defenition_index::WeaponShadowDaggers,
        en_defenition_index::WeaponParacordKnife,
        en_defenition_index::WeaponSurvivalKnife,
        en_defenition_index::WeaponUrsusKnife,
        en_defenition_index::WeaponNavajaKnife,
        en_defenition_index::WeaponNomadKnife,
        en_defenition_index::WeaponStilettoKnife,
        en_defenition_index::WeaponTalonKnife,
        en_defenition_index::WeaponSkeletonKnife
    };
  }
  static std::vector<en_defenition_index> knifes() {
    std::vector<en_defenition_index> all_items = all();
    std::vector<en_defenition_index> knifes;

    copy_if(all_items.begin(), all_items.end(), std::back_inserter(knifes), [](en_defenition_index& di) {
      return is_knife(di);
      });

    return knifes;
  }

  static bool is_pistol(en_defenition_index di) {
    if (
      di == en_defenition_index::WeaponDesertEagle ||
      di == en_defenition_index::WeaponDualBerettas ||
      di == en_defenition_index::WeaponFiveSeven ||
      di == en_defenition_index::WeaponGlock18 ||
      di == en_defenition_index::WeaponTec9 ||
      di == en_defenition_index::WeaponP2000 ||
      di == en_defenition_index::WeaponP250 ||
      di == en_defenition_index::WeaponUSPS ||
      di == en_defenition_index::WeaponCZ75Auto ||
      di == en_defenition_index::WeaponR8Revolver
      ) {
      return true;
    }
    return false;
  }
  static bool is_smg(en_defenition_index di) {
    if (
      di == en_defenition_index::WeaponMAC10 ||
      di == en_defenition_index::WeaponP90 ||
      di == en_defenition_index::WeaponMP5SD ||
      di == en_defenition_index::WeaponUMP45 ||
      di == en_defenition_index::WeaponMP7 ||
      di == en_defenition_index::WeaponMP9 ||
      di == en_defenition_index::WeaponPPBizon
      ) {
      return true;
    }
    return false;
  }
  static bool is_shotgun(en_defenition_index di) {
    if (
      di == en_defenition_index::WeaponXM1014 ||
      di == en_defenition_index::WeaponMAG7 ||
      di == en_defenition_index::WeaponSawedOff ||
      di == en_defenition_index::WeaponNova
      ) {
      return true;
    }
    return false;
  }
  static bool is_heavy(en_defenition_index di) {
    if (
      di == en_defenition_index::WeaponM249 ||
      di == en_defenition_index::WeaponNegev
      ) {
      return true;
    }
    return false;
  }
  static bool is_rifle(en_defenition_index di) {
    if (
      di == en_defenition_index::WeaponAK47 ||
      di == en_defenition_index::WeaponAUG ||
      di == en_defenition_index::WeaponFAMAS ||
      di == en_defenition_index::WeaponGalilAR ||
      di == en_defenition_index::WeaponM4A4 ||
      di == en_defenition_index::WeaponSG553 ||
      di == en_defenition_index::WeaponM4A1S
      ) {
      return true;
    }
    return false;
  }
  static bool is_snipers(en_defenition_index di) {
    if (
      di == en_defenition_index::WeaponAWP ||
      di == en_defenition_index::WeaponG3SG1 ||
      di == en_defenition_index::WeaponSCAR20 ||
      di == en_defenition_index::WeaponSSG08
      ) {
      return true;
    }
    return false;
  }
  static bool is_knife(en_defenition_index di) {
    if (
      di == en_defenition_index::WeaponKnife ||
      di == en_defenition_index::WeaponKnifeCT ||
      di == en_defenition_index::WeaponKnifeCT2 ||
      di == en_defenition_index::WeaponKnifeT ||
      di == en_defenition_index::WeaponBayonet ||
      di == en_defenition_index::WeaponClassicKnife ||
      di == en_defenition_index::WeaponFlipKnife ||
      di == en_defenition_index::WeaponGutKnife ||
      di == en_defenition_index::WeaponKarambit ||
      di == en_defenition_index::WeaponM9Bayonet ||
      di == en_defenition_index::WeaponHuntsmanKnife ||
      di == en_defenition_index::WeaponFlachionKnife ||
      di == en_defenition_index::WeaponBowieKnife ||
      di == en_defenition_index::WeaponButterflyKnife ||
      di == en_defenition_index::WeaponShadowDaggers ||
      di == en_defenition_index::WeaponParacordKnife ||
      di == en_defenition_index::WeaponSurvivalKnife ||
      di == en_defenition_index::WeaponUrsusKnife ||
      di == en_defenition_index::WeaponNavajaKnife ||
      di == en_defenition_index::WeaponNomadKnife ||
      di == en_defenition_index::WeaponStilettoKnife ||
      di == en_defenition_index::WeaponTalonKnife ||
      di == en_defenition_index::WeaponSkeletonKnife
      ) {
      return true;
    }
    return false;
  }
  static bool is_bomb(en_defenition_index di) {
    if (di == en_defenition_index::ItemC4Explosive) {
      return true;
    }
    return false;
  }
  static bool is_grenade(en_defenition_index di) {
    if (
      di == en_defenition_index::WeaponHEGrenade ||
      di == en_defenition_index::WeaponFlashbang ||
      di == en_defenition_index::WeaponMolotov ||
      di == en_defenition_index::WeaponSmokeGrenade ||
      di == en_defenition_index::WeaponIncendiaryGrenade ||
      di == en_defenition_index::WeaponDecoyGrenade
      ) {
      return true;
    }
    return false;
  }
  static bool is_zeusx27(en_defenition_index di) {
    if (
      di == en_defenition_index::WeaponZeusx27
      ) {
      return true;
    }
    return false;
  }
};