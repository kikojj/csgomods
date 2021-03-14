import { ItemDefinitionIndex, Weapon } from "./weapon";

export type TSkinRarityText =
  | "Common"
  | "Uncommon"
  | "Rare"
  | "Mythical"
  | "Legendary"
  | "Ancient"
  | "Exceedingly rare"
  | "Immortal";

export enum SkinRarity {
  RARITY_COMMON = 1, //rgb - 175,175,175
  RARITY_UNCOMMON, //rgb - 135,199,255
  RARITY_RARE, //rgb - 17,85,221
  RARITY_MYTHICAL, //rgb - 136,71,255
  RARITY_LEGENDARY, //rgb - 211,44,230
  RARITY_ANCIENT, //rgb - 235,75,75
  RARITY_EXCEEDINGLY_RARE, //rgb - 202,171,5
  RARITY_IMMORTAL, //rgb - 242,188,75
}
export const rarityColors = {
  [SkinRarity.RARITY_COMMON]: "rgba(175,175,175)",
  [SkinRarity.RARITY_UNCOMMON]: "rgba(135,199,255)",
  [SkinRarity.RARITY_RARE]: "rgba(17,85,221)",
  [SkinRarity.RARITY_MYTHICAL]: "rgba(136,71,255)",
  [SkinRarity.RARITY_LEGENDARY]: "rgba(211,44,230)",
  [SkinRarity.RARITY_ANCIENT]: "rgba(235,75,75)",
  [SkinRarity.RARITY_EXCEEDINGLY_RARE]: "rgba(202,171,5)",
  [SkinRarity.RARITY_IMMORTAL]: "rgba(242,188,75)",
};

export class Skin {
  collections: string[] = [];
  collectionsImage: string[] = [];
  weapon: Weapon = new Weapon();
  weaponDI: ItemDefinitionIndex = ItemDefinitionIndex.INVALID_ITEM_DI;
  name: string = "";
  paintKit: number = 0;
  image: string = "";
  rarity: TSkinRarityText = "Common";
  rarityID: SkinRarity = SkinRarity.RARITY_COMMON;
  description: string = "";

  constructor(obj: any = {}) {
    if (obj.collections) {
      this.collections = obj.collections;
    }
    if (obj.collectionsImage) {
      this.collectionsImage = obj.collectionsImage;
    }
    if (obj.weaponDI) {
      this.weapon = new Weapon({ itemDI: obj.weaponDI });
      this.weaponDI = obj.weaponDI;
    }
    if (obj.name) {
      this.name = obj.name;
    }
    if (obj.paintKit) {
      this.paintKit = obj.paintKit;
    }
    if (obj.image) {
      this.image = obj.image;
    }
    if (obj.rarity) {
      this.rarity = obj.rarity;
    }
    if (obj.rarityID) {
      this.rarityID = obj.rarityID;
    }
    if (obj.description) {
      this.description = obj.description;
    }
  }
}

export const getDefaultSkin = (weaponDI: ItemDefinitionIndex, image: string) => {
  return new Skin({
    collections: [],
    collectionsImage: [],
    weapon: new Weapon({ itemDI: weaponDI }),
    weaponDI: weaponDI,
    name: "Default",
    paintKit: 0,
    image,
    rarity: "Common",
    rarityID: new Weapon({ itemDI: weaponDI }).isKnife() ? SkinRarity.RARITY_ANCIENT : SkinRarity.RARITY_COMMON,
    description: "",
  });
};

export const skinRaritiesText: { [T in SkinRarity]: TSkinRarityText } = {
  [SkinRarity.RARITY_COMMON]: "Common",
  [SkinRarity.RARITY_UNCOMMON]: "Uncommon",
  [SkinRarity.RARITY_RARE]: "Rare",
  [SkinRarity.RARITY_MYTHICAL]: "Mythical",
  [SkinRarity.RARITY_LEGENDARY]: "Legendary",
  [SkinRarity.RARITY_ANCIENT]: "Ancient",
  [SkinRarity.RARITY_EXCEEDINGLY_RARE]: "Exceedingly rare",
  [SkinRarity.RARITY_IMMORTAL]: "Immortal",
};

export type TSkin = {
  collections: string[];
  collectionsImage: string[];
  weapon: string;
  weaponDI: ItemDefinitionIndex;
  name: string;
  paintKit: number;
  image: string;
  rarity: TSkinRarityText;
  rarityID: SkinRarity;
  description: string;
};

export const SKIN: TSkin = {
  collections: [],
  collectionsImage: [],
  weapon: "",
  weaponDI: ItemDefinitionIndex.INVALID_ITEM_DI,
  name: "",
  paintKit: -1,
  image: "",
  rarity: "Common",
  rarityID: SkinRarity.RARITY_COMMON,
  description: "",
};

export const getRarity = (name: string): SkinRarity => {
  if (name.toLowerCase().includes("consumer")) {
    return SkinRarity.RARITY_COMMON;
  }
  if (name.toLowerCase().includes("industrial")) {
    return SkinRarity.RARITY_UNCOMMON;
  }
  if (name.toLowerCase().includes("mil-spec")) {
    return SkinRarity.RARITY_RARE;
  }
  if (name.toLowerCase().includes("restricted")) {
    return SkinRarity.RARITY_MYTHICAL;
  }
  if (name.toLowerCase().includes("classified")) {
    return SkinRarity.RARITY_LEGENDARY;
  }
  if (name.toLowerCase().includes("covert")) {
    return SkinRarity.RARITY_ANCIENT;
  }
  if (name.toLowerCase().includes("contraband ")) {
    return SkinRarity.RARITY_IMMORTAL;
  }
  return SkinRarity.RARITY_COMMON;
};
