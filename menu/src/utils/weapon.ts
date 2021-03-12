export enum ItemDefinitionIndex {
  INVALID_ITEM_DI = 0,
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
}

export const weaponNames = [
  { idi: ItemDefinitionIndex.WEAPON_DesertEagle, name: "Desert Eagle" },
  { idi: ItemDefinitionIndex.WEAPON_DualBerettas, name: "Dual Berettas" },
  { idi: ItemDefinitionIndex.WEAPON_FiveSeven, name: "Five-Seven" },
  { idi: ItemDefinitionIndex.WEAPON_Glock18, name: "Glock-18" },
  { idi: ItemDefinitionIndex.WEAPON_AK47, name: "AK-47" },
  { idi: ItemDefinitionIndex.WEAPON_AUG, name: "AUG" },
  { idi: ItemDefinitionIndex.WEAPON_AWP, name: "AWP" },
  { idi: ItemDefinitionIndex.WEAPON_FAMAS, name: "FAMAS" },
  { idi: ItemDefinitionIndex.WEAPON_G3SG1, name: "G3SG1" },
  { idi: ItemDefinitionIndex.WEAPON_GalilAR, name: "Galil AR" },
  { idi: ItemDefinitionIndex.WEAPON_M249, name: "M249" },
  { idi: ItemDefinitionIndex.WEAPON_M4A4, name: "M4A4" },
  { idi: ItemDefinitionIndex.WEAPON_MAC10, name: "MAC-10" },
  { idi: ItemDefinitionIndex.WEAPON_P90, name: "P90" },
  { idi: ItemDefinitionIndex.WEAPON_MP5SD, name: "MP5-SD" },
  { idi: ItemDefinitionIndex.WEAPON_UMP45, name: "UMP-45" },
  { idi: ItemDefinitionIndex.WEAPON_XM1014, name: "XM1014" },
  { idi: ItemDefinitionIndex.WEAPON_PPBizon, name: "PP-Bizon" },
  { idi: ItemDefinitionIndex.WEAPON_MAG7, name: "MAG-7" },
  { idi: ItemDefinitionIndex.WEAPON_Negev, name: "Negev" },
  { idi: ItemDefinitionIndex.WEAPON_SawedOff, name: "Sawed-Off" },
  { idi: ItemDefinitionIndex.WEAPON_Tec9, name: "Tec-9" },
  { idi: ItemDefinitionIndex.WEAPON_Zeusx27, name: "Zeus x27" },
  { idi: ItemDefinitionIndex.WEAPON_P2000, name: "P2000" },
  { idi: ItemDefinitionIndex.WEAPON_MP7, name: "MP7" },
  { idi: ItemDefinitionIndex.WEAPON_MP9, name: "MP9" },
  { idi: ItemDefinitionIndex.WEAPON_Nova, name: "Nova" },
  { idi: ItemDefinitionIndex.WEAPON_P250, name: "P250" },
  { idi: ItemDefinitionIndex.WEAPON_SCAR20, name: "SCAR-20" },
  { idi: ItemDefinitionIndex.WEAPON_SG553, name: "SG 553" },
  { idi: ItemDefinitionIndex.WEAPON_SSG08, name: "SSG 08" },
  { idi: ItemDefinitionIndex.WEAPON_KnifeCT, name: "KnifeCT" },
  { idi: ItemDefinitionIndex.WEAPON_KnifeCT2, name: "KnifeCT2" },
  { idi: ItemDefinitionIndex.WEAPON_Flashbang, name: "Flashbang" },
  { idi: ItemDefinitionIndex.WEAPON_HEGrenade, name: "HE" },
  { idi: ItemDefinitionIndex.WEAPON_SmokeGrenade, name: "Smoke" },
  { idi: ItemDefinitionIndex.WEAPON_Molotov, name: "Molotov" },
  { idi: ItemDefinitionIndex.WEAPON_DecoyGrenade, name: "Decoy" },
  { idi: ItemDefinitionIndex.WEAPON_IncendiaryGrenade, name: "Incendiary" },
  { idi: ItemDefinitionIndex.WEAPON_KnifeT, name: "KnifeT" },
  { idi: ItemDefinitionIndex.WEAPON_M4A1S, name: "M4A1S" },
  { idi: ItemDefinitionIndex.WEAPON_USPS, name: "USP-S" },
  { idi: ItemDefinitionIndex.WEAPON_CZ75Auto, name: "CZ75-Auto" },
  { idi: ItemDefinitionIndex.WEAPON_R8Revolver, name: "R8 Revolver" },
  { idi: ItemDefinitionIndex.WEAPON_TacticalAwarenessGrenade, name: "TacticalAwareness" },
  { idi: ItemDefinitionIndex.WEAPON_BreachCharge, name: "BreachCharge" },
  { idi: ItemDefinitionIndex.WEAPON_Knife, name: "Knife" },
  { idi: ItemDefinitionIndex.WEAPON_Axe, name: "Axe" },
  { idi: ItemDefinitionIndex.WEAPON_Hammer, name: "Hammer" },
  { idi: ItemDefinitionIndex.WEAPON_Wrench, name: "Wrench" },
  { idi: ItemDefinitionIndex.WEAPON_FireBomb, name: "FireBomb" },
  { idi: ItemDefinitionIndex.WEAPON_DiversionDevice, name: "DiversionDevice" },
  { idi: ItemDefinitionIndex.WEAPON_FragGrenade, name: "Frag" },
  { idi: ItemDefinitionIndex.WEAPON_Snowball, name: "Snowball" },
  { idi: ItemDefinitionIndex.WEAPON_BumpMine, name: "BumpMine" },
  { idi: ItemDefinitionIndex.WEAPON_Bayonet, name: "Bayonet" },
  { idi: ItemDefinitionIndex.WEAPON_ClassicKnife, name: "Classic Knife" },
  { idi: ItemDefinitionIndex.WEAPON_FlipKnife, name: "Flip Knife" },
  { idi: ItemDefinitionIndex.WEAPON_GutKnife, name: "Gut Knife" },
  { idi: ItemDefinitionIndex.WEAPON_Karambit, name: "Karambit" },
  { idi: ItemDefinitionIndex.WEAPON_M9Bayonet, name: "M9 Bayonet" },
  { idi: ItemDefinitionIndex.WEAPON_HuntsmanKnife, name: "Huntsman Knife" },
  { idi: ItemDefinitionIndex.WEAPON_FlachionKnife, name: "Flachion Knife" },
  { idi: ItemDefinitionIndex.WEAPON_BowieKnife, name: "Bowie Knife" },
  { idi: ItemDefinitionIndex.WEAPON_ButterflyKnife, name: "Butterfly Knife" },
  { idi: ItemDefinitionIndex.WEAPON_ShadowDaggers, name: "Shadow Daggers" },
  { idi: ItemDefinitionIndex.WEAPON_ParacordKnife, name: "Paracord Knife" },
  { idi: ItemDefinitionIndex.WEAPON_SurvivalKnife, name: "Survival Knife" },
  { idi: ItemDefinitionIndex.WEAPON_UrsusKnife, name: "Ursus Knife" },
  { idi: ItemDefinitionIndex.WEAPON_NavajaKnife, name: "Navaja Knife" },
  { idi: ItemDefinitionIndex.WEAPON_NomadKnife, name: "Nomad Knife" },
  { idi: ItemDefinitionIndex.WEAPON_StilettoKnife, name: "Stiletto Knife" },
  { idi: ItemDefinitionIndex.WEAPON_TalonKnife, name: "Talon Knife" },
  { idi: ItemDefinitionIndex.WEAPON_SkeletonKnife, name: "Skeleton Knife" },
];

export const getWeaponName = (idi: ItemDefinitionIndex): string => {
  const weapon = weaponNames.find((w) => w.idi === idi);
  if (weapon) {
    return weapon.name;
  }
  return "Unknown weapon";
};

export const getWeaponIDI = (name: string): ItemDefinitionIndex => {
  const weapon = weaponNames.find((w) => w.name === name);
  if (weapon) {
    return weapon.idi;
  }
  return ItemDefinitionIndex.INVALID_ITEM_DI;
};

export class Weapon {
  itemDI: ItemDefinitionIndex = ItemDefinitionIndex.INVALID_ITEM_DI;
  name: string = "Unknown weapon";

  constructor(data?: { itemDI?: ItemDefinitionIndex; name?: string }) {
    if (data && data.itemDI) {
      this.itemDI = data.itemDI;
      this.name = getWeaponName(data.itemDI);
    } else if (data && data.name) {
      this.itemDI = getWeaponIDI(data.name);
      this.name = data.name;
    }
  }

  isPistol = (): boolean => {
    if (
      this.itemDI == ItemDefinitionIndex.WEAPON_DesertEagle ||
      this.itemDI == ItemDefinitionIndex.WEAPON_DualBerettas ||
      this.itemDI == ItemDefinitionIndex.WEAPON_FiveSeven ||
      this.itemDI == ItemDefinitionIndex.WEAPON_Glock18 ||
      this.itemDI == ItemDefinitionIndex.WEAPON_Tec9 ||
      this.itemDI == ItemDefinitionIndex.WEAPON_P2000 ||
      this.itemDI == ItemDefinitionIndex.WEAPON_P250 ||
      this.itemDI == ItemDefinitionIndex.WEAPON_USPS ||
      this.itemDI == ItemDefinitionIndex.WEAPON_CZ75Auto ||
      this.itemDI == ItemDefinitionIndex.WEAPON_R8Revolver
    ) {
      return true;
    }
    return false;
  };

  isSMG = (): boolean => {
    if (
      this.itemDI == ItemDefinitionIndex.WEAPON_MAC10 ||
      this.itemDI == ItemDefinitionIndex.WEAPON_P90 ||
      this.itemDI == ItemDefinitionIndex.WEAPON_MP5SD ||
      this.itemDI == ItemDefinitionIndex.WEAPON_UMP45 ||
      this.itemDI == ItemDefinitionIndex.WEAPON_MP7 ||
      this.itemDI == ItemDefinitionIndex.WEAPON_MP9 ||
      this.itemDI == ItemDefinitionIndex.WEAPON_PPBizon
    ) {
      return true;
    }
    return false;
  };

  isHeavy = (): boolean => {
    if (this.itemDI == ItemDefinitionIndex.WEAPON_M249 || this.itemDI == ItemDefinitionIndex.WEAPON_Negev) {
      return true;
    }
    return false;
  };

  isShotgun = (): boolean => {
    if (
      this.itemDI == ItemDefinitionIndex.WEAPON_XM1014 ||
      this.itemDI == ItemDefinitionIndex.WEAPON_MAG7 ||
      this.itemDI == ItemDefinitionIndex.WEAPON_SawedOff ||
      this.itemDI == ItemDefinitionIndex.WEAPON_Nova
    ) {
      return true;
    }
    return false;
  };

  isRifle = (): boolean => {
    if (
      this.itemDI == ItemDefinitionIndex.WEAPON_AK47 ||
      this.itemDI == ItemDefinitionIndex.WEAPON_AUG ||
      this.itemDI == ItemDefinitionIndex.WEAPON_FAMAS ||
      this.itemDI == ItemDefinitionIndex.WEAPON_GalilAR ||
      this.itemDI == ItemDefinitionIndex.WEAPON_M4A4 ||
      this.itemDI == ItemDefinitionIndex.WEAPON_SG553 ||
      this.itemDI == ItemDefinitionIndex.WEAPON_M4A1S
    ) {
      return true;
    }
    return false;
  };

  isSnipers = (): boolean => {
    if (
      this.itemDI == ItemDefinitionIndex.WEAPON_AWP ||
      this.itemDI == ItemDefinitionIndex.WEAPON_G3SG1 ||
      this.itemDI == ItemDefinitionIndex.WEAPON_SCAR20 ||
      this.itemDI == ItemDefinitionIndex.WEAPON_SSG08
    ) {
      return true;
    }
    return false;
  };

  isKnife = (): boolean => {
    if (
      this.itemDI == ItemDefinitionIndex.WEAPON_Knife ||
      this.itemDI == ItemDefinitionIndex.WEAPON_KnifeCT ||
      this.itemDI == ItemDefinitionIndex.WEAPON_KnifeCT2 ||
      this.itemDI == ItemDefinitionIndex.WEAPON_KnifeT ||
      this.itemDI == ItemDefinitionIndex.WEAPON_Bayonet ||
      this.itemDI == ItemDefinitionIndex.WEAPON_ClassicKnife ||
      this.itemDI == ItemDefinitionIndex.WEAPON_FlipKnife ||
      this.itemDI == ItemDefinitionIndex.WEAPON_GutKnife ||
      this.itemDI == ItemDefinitionIndex.WEAPON_Karambit ||
      this.itemDI == ItemDefinitionIndex.WEAPON_M9Bayonet ||
      this.itemDI == ItemDefinitionIndex.WEAPON_HuntsmanKnife ||
      this.itemDI == ItemDefinitionIndex.WEAPON_FlachionKnife ||
      this.itemDI == ItemDefinitionIndex.WEAPON_BowieKnife ||
      this.itemDI == ItemDefinitionIndex.WEAPON_ButterflyKnife ||
      this.itemDI == ItemDefinitionIndex.WEAPON_ShadowDaggers ||
      this.itemDI == ItemDefinitionIndex.WEAPON_ParacordKnife ||
      this.itemDI == ItemDefinitionIndex.WEAPON_SurvivalKnife ||
      this.itemDI == ItemDefinitionIndex.WEAPON_UrsusKnife ||
      this.itemDI == ItemDefinitionIndex.WEAPON_NavajaKnife ||
      this.itemDI == ItemDefinitionIndex.WEAPON_NomadKnife ||
      this.itemDI == ItemDefinitionIndex.WEAPON_StilettoKnife ||
      this.itemDI == ItemDefinitionIndex.WEAPON_TalonKnife ||
      this.itemDI == ItemDefinitionIndex.WEAPON_SkeletonKnife
    ) {
      return true;
    }
    return false;
  };

  get sectionName() {
    if (this.isPistol()) {
      return "pistols";
    }
    if (this.isSMG()) {
      return "smgs";
    }
    if (this.isHeavy()) {
      return "heavies";
    }
    if (this.isShotgun()) {
      return "shoutguns";
    }
    if (this.isRifle()) {
      return "rifles";
    }
    return "snipers";
  }
}
