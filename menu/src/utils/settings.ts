import { ColorRGBA } from "@components";
import { ItemDefinitionIndex } from "./weapon";

export enum EntityQuality {
  QUALITY_NORMAL,
  QUALITY_GENUINE,
  QUALITY_VINTAGE,
  QUALITY_UNUSUAL,
  QUALITY_COMMUNITY = 5,
  QUALITY_DEVELOPER,
  QUALITY_SELF_MADE,
  QUALITY_CUSTOMIZED,
  QUALITY_STRANGE,
  QUALITY_COMPLETED,
  QUALITY_TOURNAMENT = 12,
}

export interface ISkinchangerWeapon {
  enable: boolean;
  paintKit: number;
  quality: EntityQuality;
  wear: number;
  customName: string;
  statTrack: number;
  seed: number;
  itemDI: ItemDefinitionIndex;
}

export const DEFAULT_WEAPON_SETTINGS: ISkinchangerWeapon = {
  enable: true,
  paintKit: -1,
  quality: EntityQuality.QUALITY_NORMAL,
  wear: 0.00001,
  customName: "",
  statTrack: -1,
  seed: 0,
  itemDI: ItemDefinitionIndex.INVALID_ITEM_DI,
};

export enum TeamNum {
  NO_TEAM = -1,
  SPECTATOR = 1,
  TERRORIST = 2,
  COUNTER_TERRORIST = 3,
}

export interface IAimbotSettings {
  use: boolean;
  enable: boolean;
  firstPerfectShoot: boolean;
  fov: number;
  bone: number;
  changeAfterNearest: boolean;
  smooth: number;
  rcs_enable: boolean;
  rcs_scale_x: number;
  rcs_scale_y: number;
}

export const DEFAULT_AIMBOT_SETTINGS: IAimbotSettings = {
  use: false,
  enable: false,
  firstPerfectShoot: false,
  fov: 0,
  bone: 0,
  changeAfterNearest: false,
  smooth: 0,
  rcs_enable: false,
  rcs_scale_x: 0,
  rcs_scale_y: 0,
};

export type TSettings = {
  //AIMBOT
  aimbot_enable: boolean;
  aimbot_use_key: boolean;
  aimbot_key: number;
  aimbot_delay_enemy: number;
  aimbot_visible_check: boolean;
  aimbot_flash_check: boolean;
  aimbot_jump_check: boolean;
  aimbot_friendly_fire: boolean;

  aimbot_global: IAimbotSettings;
  aimbot_pistols: IAimbotSettings;
  aimbot_heavies: IAimbotSettings;
  aimbot_shoutguns: IAimbotSettings;
  aimbot_smgs: IAimbotSettings;
  aimbot_rifles: IAimbotSettings;
  aimbot_snipers: IAimbotSettings;

  aimbot_weapons: { [T in ItemDefinitionIndex]?: IAimbotSettings };
  ///

  ///TRIGGER
  triggerbot_enable: boolean;
  triggerbot_use_key: boolean;
  triggerbot_key: number;
  triggerbot_friendly_fire: boolean;
  triggerbot_flash_check: boolean;
  triggerbot_jump_check: boolean;
  triggerbot_delay_before_shoot: number;
  triggerbot_delay_after_shoot: number;
  triggerbot_pistols_enable: boolean;
  triggerbot_heavies_enable: boolean;
  triggerbot_shoutguns_enable: boolean;
  triggerbot_smgs_enable: boolean;
  triggerbot_rifles_enable: boolean;
  triggerbot_snipers_enable: boolean;
  ///

  //VISUALS
  //GLOW ESP
  visuals_glowEsp_enable: boolean;

  visuals_glowEsp_show_enemies: boolean;
  visuals_glowEsp_show_friends: boolean;
  visuals_glowEsp_show_c4: boolean;
  visuals_glowEsp_show_defusing: boolean;
  visuals_glowEsp_show_grenades: boolean;

  visuals_glowEsp_style: number;
  visuals_glowEsp_mode: number;

  visuals_glowEsp_enemy_visible_color: ColorRGBA;
  visuals_glowEsp_enemy_invisible_color: ColorRGBA;
  visuals_glowEsp_friends_color: ColorRGBA;
  visuals_glowEsp_c4_color: ColorRGBA;
  visuals_glowEsp_defusing_color: ColorRGBA;
  visuals_glowEsp_grenades_color: ColorRGBA;

  visuals_glowEsp_hpBased_0hp_color: ColorRGBA;
  visuals_glowEsp_hpBased_100hp_color: ColorRGBA;
  ///

  //CHAMS
  visuals_chams_enable: boolean;
  visuals_chams_show_enemies: boolean;
  visuals_chams_show_friends: boolean;
  visuals_chams_enemy_color: ColorRGBA;
  visuals_chams_friends_color: ColorRGBA;
  ///
  ///

  //SKINCHANGER
  skinchanger_enable: boolean;
  skinchanger_weapons: { [T in ItemDefinitionIndex]?: ISkinchangerWeapon };
  skinchanger_knives: { [T in TeamNum]?: ISkinchangerWeapon };
  //

  ///MISC
  misc_ingameRadar_enable: boolean;
  misc_bhop_enable: boolean;
  misc_autoPistols_enable: boolean;
  misc_autoPistols_delay: number;
  misc_autoAccept_enable: boolean;
  misc_antiFlash_enable: boolean;
  misc_antiFlash_maxAlpha: number;
  misc_rankReveal_enable: boolean;
  ///
};

export const DEFAULT_SETTINGS: TSettings = {
  ///AIMBOT
  ///GLOBALS
  aimbot_enable: false,
  aimbot_use_key: false,
  aimbot_key: 0,
  aimbot_delay_enemy: 0,
  aimbot_visible_check: false,
  aimbot_flash_check: false,
  aimbot_jump_check: false,
  aimbot_friendly_fire: false,
  ///

  aimbot_global: { ...DEFAULT_AIMBOT_SETTINGS },

  aimbot_pistols: { ...DEFAULT_AIMBOT_SETTINGS },
  aimbot_heavies: { ...DEFAULT_AIMBOT_SETTINGS },
  aimbot_shoutguns: { ...DEFAULT_AIMBOT_SETTINGS },
  aimbot_smgs: { ...DEFAULT_AIMBOT_SETTINGS },
  aimbot_rifles: { ...DEFAULT_AIMBOT_SETTINGS },
  aimbot_snipers: { ...DEFAULT_AIMBOT_SETTINGS },

  aimbot_weapons: {},
  ///

  ///TRIGGER
  triggerbot_enable: false,
  triggerbot_use_key: false,
  triggerbot_key: 0,
  triggerbot_friendly_fire: false,
  triggerbot_flash_check: false,
  triggerbot_jump_check: false,
  triggerbot_delay_before_shoot: 0,
  triggerbot_delay_after_shoot: 0,
  triggerbot_pistols_enable: false,
  triggerbot_heavies_enable: false,
  triggerbot_shoutguns_enable: false,
  triggerbot_smgs_enable: false,
  triggerbot_rifles_enable: false,
  triggerbot_snipers_enable: false,
  ///

  //VISUALS
  //GLOW ESP
  visuals_glowEsp_enable: false,

  visuals_glowEsp_show_enemies: false,
  visuals_glowEsp_show_friends: false,
  visuals_glowEsp_show_c4: false,
  visuals_glowEsp_show_defusing: false,
  visuals_glowEsp_show_grenades: false,

  visuals_glowEsp_style: 0,
  visuals_glowEsp_mode: 0,

  visuals_glowEsp_enemy_visible_color: { r: 0, g: 0, b: 0, a: 0 },
  visuals_glowEsp_enemy_invisible_color: { r: 0, g: 0, b: 0, a: 0 },
  visuals_glowEsp_friends_color: { r: 0, g: 0, b: 0, a: 0 },
  visuals_glowEsp_c4_color: { r: 0, g: 0, b: 0, a: 0 },
  visuals_glowEsp_defusing_color: { r: 0, g: 0, b: 0, a: 0 },
  visuals_glowEsp_grenades_color: { r: 0, g: 0, b: 0, a: 0 },

  visuals_glowEsp_hpBased_0hp_color: { r: 0, g: 0, b: 0, a: 0 },
  visuals_glowEsp_hpBased_100hp_color: { r: 0, g: 0, b: 0, a: 0 },
  ///

  //CHAMS
  visuals_chams_enable: false,

  visuals_chams_show_enemies: false,
  visuals_chams_show_friends: false,

  visuals_chams_enemy_color: { r: 0, g: 0, b: 0, a: 0 },
  visuals_chams_friends_color: { r: 0, g: 0, b: 0, a: 0 },
  ///
  ///

  //SKINCHANGER
  skinchanger_enable: false,
  skinchanger_weapons: {},
  skinchanger_knives: {},
  //

  ///MISC
  misc_ingameRadar_enable: false,
  misc_bhop_enable: false,
  misc_autoPistols_enable: false,
  misc_autoPistols_delay: 0,
  misc_autoAccept_enable: false,
  misc_antiFlash_enable: false,
  misc_antiFlash_maxAlpha: 255,
  misc_rankReveal_enable: false,
  ///
};
