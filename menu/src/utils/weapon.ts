export enum ItemDefinitionIndex {
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
  WeaponFalchionKnife = 512,
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
}

export const weaponNames = [
  { idi: ItemDefinitionIndex.WeaponDesertEagle, name: "Desert Eagle" },
  { idi: ItemDefinitionIndex.WeaponDualBerettas, name: "Dual Berettas" },
  { idi: ItemDefinitionIndex.WeaponFiveSeven, name: "Five-SeveN" },
  { idi: ItemDefinitionIndex.WeaponGlock18, name: "Glock-18" },
  { idi: ItemDefinitionIndex.WeaponAK47, name: "AK-47" },
  { idi: ItemDefinitionIndex.WeaponAUG, name: "AUG" },
  { idi: ItemDefinitionIndex.WeaponAWP, name: "AWP" },
  { idi: ItemDefinitionIndex.WeaponFAMAS, name: "FAMAS" },
  { idi: ItemDefinitionIndex.WeaponG3SG1, name: "G3SG1" },
  { idi: ItemDefinitionIndex.WeaponGalilAR, name: "Galil AR" },
  { idi: ItemDefinitionIndex.WeaponM249, name: "M249" },
  { idi: ItemDefinitionIndex.WeaponM4A4, name: "M4A4" },
  { idi: ItemDefinitionIndex.WeaponMAC10, name: "MAC-10" },
  { idi: ItemDefinitionIndex.WeaponP90, name: "P90" },
  { idi: ItemDefinitionIndex.WeaponMP5SD, name: "MP5-SD" },
  { idi: ItemDefinitionIndex.WeaponUMP45, name: "UMP-45" },
  { idi: ItemDefinitionIndex.WeaponXM1014, name: "XM1014" },
  { idi: ItemDefinitionIndex.WeaponPPBizon, name: "PP-Bizon" },
  { idi: ItemDefinitionIndex.WeaponMAG7, name: "MAG-7" },
  { idi: ItemDefinitionIndex.WeaponNegev, name: "Negev" },
  { idi: ItemDefinitionIndex.WeaponSawedOff, name: "Sawed-Off" },
  { idi: ItemDefinitionIndex.WeaponTec9, name: "Tec-9" },
  { idi: ItemDefinitionIndex.WeaponZeusx27, name: "Zeus x27" },
  { idi: ItemDefinitionIndex.WeaponP2000, name: "P2000" },
  { idi: ItemDefinitionIndex.WeaponMP7, name: "MP7" },
  { idi: ItemDefinitionIndex.WeaponMP9, name: "MP9" },
  { idi: ItemDefinitionIndex.WeaponNova, name: "Nova" },
  { idi: ItemDefinitionIndex.WeaponP250, name: "P250" },
  { idi: ItemDefinitionIndex.WeaponSCAR20, name: "SCAR-20" },
  { idi: ItemDefinitionIndex.WeaponSG553, name: "SG 553" },
  { idi: ItemDefinitionIndex.WeaponSSG08, name: "SSG 08" },
  { idi: ItemDefinitionIndex.WeaponKnifeCT, name: "KnifeCT" },
  { idi: ItemDefinitionIndex.WeaponKnifeCT2, name: "KnifeCT2" },
  { idi: ItemDefinitionIndex.WeaponFlashbang, name: "Flashbang" },
  { idi: ItemDefinitionIndex.WeaponHEGrenade, name: "HE" },
  { idi: ItemDefinitionIndex.WeaponSmokeGrenade, name: "Smoke" },
  { idi: ItemDefinitionIndex.WeaponMolotov, name: "Molotov" },
  { idi: ItemDefinitionIndex.WeaponDecoyGrenade, name: "Decoy" },
  { idi: ItemDefinitionIndex.WeaponIncendiaryGrenade, name: "Incendiary" },
  { idi: ItemDefinitionIndex.WeaponKnifeT, name: "KnifeT" },
  { idi: ItemDefinitionIndex.WeaponM4A1S, name: "M4A1-S" },
  { idi: ItemDefinitionIndex.WeaponUSPS, name: "USP-S" },
  { idi: ItemDefinitionIndex.WeaponCZ75Auto, name: "CZ75-Auto" },
  { idi: ItemDefinitionIndex.WeaponR8Revolver, name: "R8 Revolver" },
  { idi: ItemDefinitionIndex.WeaponTacticalAwarenessGrenade, name: "TacticalAwareness" },
  { idi: ItemDefinitionIndex.WeaponBreachCharge, name: "BreachCharge" },
  { idi: ItemDefinitionIndex.WeaponKnife, name: "Knife" },
  { idi: ItemDefinitionIndex.WeaponAxe, name: "Axe" },
  { idi: ItemDefinitionIndex.WeaponHammer, name: "Hammer" },
  { idi: ItemDefinitionIndex.WeaponWrench, name: "Wrench" },
  { idi: ItemDefinitionIndex.WeaponFireBomb, name: "FireBomb" },
  { idi: ItemDefinitionIndex.WeaponDiversionDevice, name: "DiversionDevice" },
  { idi: ItemDefinitionIndex.WeaponFragGrenade, name: "Frag" },
  { idi: ItemDefinitionIndex.WeaponSnowball, name: "Snowball" },
  { idi: ItemDefinitionIndex.WeaponBumpMine, name: "BumpMine" },
  { idi: ItemDefinitionIndex.WeaponBayonet, name: "Bayonet" },
  { idi: ItemDefinitionIndex.WeaponClassicKnife, name: "Classic Knife" },
  { idi: ItemDefinitionIndex.WeaponFlipKnife, name: "Flip Knife" },
  { idi: ItemDefinitionIndex.WeaponGutKnife, name: "Gut Knife" },
  { idi: ItemDefinitionIndex.WeaponKarambit, name: "Karambit" },
  { idi: ItemDefinitionIndex.WeaponM9Bayonet, name: "M9 Bayonet" },
  { idi: ItemDefinitionIndex.WeaponHuntsmanKnife, name: "Huntsman Knife" },
  { idi: ItemDefinitionIndex.WeaponFalchionKnife, name: "Falchion Knife" },
  { idi: ItemDefinitionIndex.WeaponBowieKnife, name: "Bowie Knife" },
  { idi: ItemDefinitionIndex.WeaponButterflyKnife, name: "Butterfly Knife" },
  { idi: ItemDefinitionIndex.WeaponShadowDaggers, name: "Shadow Daggers" },
  { idi: ItemDefinitionIndex.WeaponParacordKnife, name: "Paracord Knife" },
  { idi: ItemDefinitionIndex.WeaponSurvivalKnife, name: "Survival Knife" },
  { idi: ItemDefinitionIndex.WeaponUrsusKnife, name: "Ursus Knife" },
  { idi: ItemDefinitionIndex.WeaponNavajaKnife, name: "Navaja Knife" },
  { idi: ItemDefinitionIndex.WeaponNomadKnife, name: "Nomad Knife" },
  { idi: ItemDefinitionIndex.WeaponStilettoKnife, name: "Stiletto Knife" },
  { idi: ItemDefinitionIndex.WeaponTalonKnife, name: "Talon Knife" },
  { idi: ItemDefinitionIndex.WeaponSkeletonKnife, name: "Skeleton Knife" },
];

export const getWeaponName = (idi: ItemDefinitionIndex): string => {
  const weapon = weaponNames.find((w) => w.idi === idi);
  if (weapon) {
    return weapon.name;
  }
  return "Unknown weapon";
};

export const getWeaponDI = (name: string): ItemDefinitionIndex => {
  const weapon = weaponNames.find((w) => w.name === name);
  if (weapon) {
    return weapon.idi;
  }
  return ItemDefinitionIndex.Invalid;
};

export class Weapon {
  itemDI: ItemDefinitionIndex = ItemDefinitionIndex.Invalid;
  name: string = "Unknown weapon";

  constructor(data?: { itemDI?: ItemDefinitionIndex; name?: string }) {
    if (data && data.itemDI) {
      this.itemDI = data.itemDI;
      this.name = getWeaponName(data.itemDI);
    } else if (data && data.name) {
      this.itemDI = getWeaponDI(data.name);
      this.name = data.name;
    }
  }

  get isWeapon (): boolean {
    return (
      this.isPistol ||
      this.isSMG ||
      this.isShotgun ||
      this.isRifle ||
      this.isHeavy ||
      this.isSnipers ||
      this.isKnife
    );
  };

  get isPistol (): boolean  {
    if (
      this.itemDI == ItemDefinitionIndex.WeaponDesertEagle ||
      this.itemDI == ItemDefinitionIndex.WeaponDualBerettas ||
      this.itemDI == ItemDefinitionIndex.WeaponFiveSeven ||
      this.itemDI == ItemDefinitionIndex.WeaponGlock18 ||
      this.itemDI == ItemDefinitionIndex.WeaponTec9 ||
      this.itemDI == ItemDefinitionIndex.WeaponP2000 ||
      this.itemDI == ItemDefinitionIndex.WeaponP250 ||
      this.itemDI == ItemDefinitionIndex.WeaponUSPS ||
      this.itemDI == ItemDefinitionIndex.WeaponCZ75Auto ||
      this.itemDI == ItemDefinitionIndex.WeaponR8Revolver
    ) {
      return true;
    }
    return false;
  };

  get isSMG(): boolean  {
    if (
      this.itemDI == ItemDefinitionIndex.WeaponMAC10 ||
      this.itemDI == ItemDefinitionIndex.WeaponP90 ||
      this.itemDI == ItemDefinitionIndex.WeaponMP5SD ||
      this.itemDI == ItemDefinitionIndex.WeaponUMP45 ||
      this.itemDI == ItemDefinitionIndex.WeaponMP7 ||
      this.itemDI == ItemDefinitionIndex.WeaponMP9 ||
      this.itemDI == ItemDefinitionIndex.WeaponPPBizon
    ) {
      return true;
    }
    return false;
  };

  get isHeavy (): boolean  {
    if (this.itemDI == ItemDefinitionIndex.WeaponM249 || this.itemDI == ItemDefinitionIndex.WeaponNegev) {
      return true;
    }
    return false;
  };

  get isShotgun (): boolean {
    if (
      this.itemDI == ItemDefinitionIndex.WeaponXM1014 ||
      this.itemDI == ItemDefinitionIndex.WeaponMAG7 ||
      this.itemDI == ItemDefinitionIndex.WeaponSawedOff ||
      this.itemDI == ItemDefinitionIndex.WeaponNova
    ) {
      return true;
    }
    return false;
  };

  get isRifle (): boolean {
    if (
      this.itemDI == ItemDefinitionIndex.WeaponAK47 ||
      this.itemDI == ItemDefinitionIndex.WeaponAUG ||
      this.itemDI == ItemDefinitionIndex.WeaponFAMAS ||
      this.itemDI == ItemDefinitionIndex.WeaponGalilAR ||
      this.itemDI == ItemDefinitionIndex.WeaponM4A4 ||
      this.itemDI == ItemDefinitionIndex.WeaponSG553 ||
      this.itemDI == ItemDefinitionIndex.WeaponM4A1S
    ) {
      return true;
    }
    return false;
  };

  get isSnipers (): boolean {
    if (
      this.itemDI == ItemDefinitionIndex.WeaponAWP ||
      this.itemDI == ItemDefinitionIndex.WeaponG3SG1 ||
      this.itemDI == ItemDefinitionIndex.WeaponSCAR20 ||
      this.itemDI == ItemDefinitionIndex.WeaponSSG08
    ) {
      return true;
    }
    return false;
  };

  get isKnife (): boolean {
    if (
      this.itemDI == ItemDefinitionIndex.WeaponKnife ||
      this.itemDI == ItemDefinitionIndex.WeaponKnifeCT ||
      this.itemDI == ItemDefinitionIndex.WeaponKnifeCT2 ||
      this.itemDI == ItemDefinitionIndex.WeaponKnifeT ||
      this.itemDI == ItemDefinitionIndex.WeaponBayonet ||
      this.itemDI == ItemDefinitionIndex.WeaponClassicKnife ||
      this.itemDI == ItemDefinitionIndex.WeaponFlipKnife ||
      this.itemDI == ItemDefinitionIndex.WeaponGutKnife ||
      this.itemDI == ItemDefinitionIndex.WeaponKarambit ||
      this.itemDI == ItemDefinitionIndex.WeaponM9Bayonet ||
      this.itemDI == ItemDefinitionIndex.WeaponHuntsmanKnife ||
      this.itemDI == ItemDefinitionIndex.WeaponFalchionKnife ||
      this.itemDI == ItemDefinitionIndex.WeaponBowieKnife ||
      this.itemDI == ItemDefinitionIndex.WeaponButterflyKnife ||
      this.itemDI == ItemDefinitionIndex.WeaponShadowDaggers ||
      this.itemDI == ItemDefinitionIndex.WeaponParacordKnife ||
      this.itemDI == ItemDefinitionIndex.WeaponSurvivalKnife ||
      this.itemDI == ItemDefinitionIndex.WeaponUrsusKnife ||
      this.itemDI == ItemDefinitionIndex.WeaponNavajaKnife ||
      this.itemDI == ItemDefinitionIndex.WeaponNomadKnife ||
      this.itemDI == ItemDefinitionIndex.WeaponStilettoKnife ||
      this.itemDI == ItemDefinitionIndex.WeaponTalonKnife ||
      this.itemDI == ItemDefinitionIndex.WeaponSkeletonKnife
    ) {
      return true;
    }
    return false;
  };

  get sectionName() {
    if (this.isPistol) {
      return "pistols";
    }
    if (this.isSMG) {
      return "smgs";
    }
    if (this.isHeavy) {
      return "heavies";
    }
    if (this.isShotgun) {
      return "shoutguns";
    }
    if (this.isRifle) {
      return "rifles";
    }
    return "snipers";
  }
}
