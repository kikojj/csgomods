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

  aimbot_pistols_enable: boolean;
  aimbot_pistols_fov: number;
  aimbot_pistols_bone: number;
  aimbot_pistols_smooth: number;
  aimbot_pistols_rcs_enable: boolean;
  aimbot_pistols_rcs_scale_x: number;
  aimbot_pistols_rcs_scale_y: number;

  aimbot_heavies_enable: boolean;
  aimbot_heavies_fov: number;
  aimbot_heavies_bone: number;
  aimbot_heavies_smooth: number;
  aimbot_heavies_rcs_enable: boolean;
  aimbot_heavies_rcs_scale_x: number;
  aimbot_heavies_rcs_scale_y: number;

  aimbot_shoutguns_enable: boolean;
  aimbot_shoutguns_fov: number;
  aimbot_shoutguns_bone: number;
  aimbot_shoutguns_smooth: number;
  aimbot_shoutguns_rcs_enable: boolean;
  aimbot_shoutguns_rcs_scale_x: number;
  aimbot_shoutguns_rcs_scale_y: number;

  aimbot_smgs_enable: boolean;
  aimbot_smgs_fov: number;
  aimbot_smgs_bone: number;
  aimbot_smgs_smooth: number;
  aimbot_smgs_rcs_enable: boolean;
  aimbot_smgs_rcs_scale_x: number;
  aimbot_smgs_rcs_scale_y: number;

  aimbot_rifles_enable: boolean;
  aimbot_rifles_fov: number;
  aimbot_rifles_bone: number;
  aimbot_rifles_smooth: number;
  aimbot_rifles_rcs_enable: boolean;
  aimbot_rifles_rcs_scale_x: number;
  aimbot_rifles_rcs_scale_y: number;

  aimbot_snipers_enable: boolean;
  aimbot_snipers_fov: number;
  aimbot_snipers_bone: number;
  aimbot_snipers_smooth: number;
  aimbot_snipers_rcs_enable: boolean;
  aimbot_snipers_rcs_scale_x: number;
  aimbot_snipers_rcs_scale_y: number;
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

  visuals_glowEsp_style: number;
  visuals_glowEsp_mode: number;

  visuals_glowEsp_enemy_visible_color: ColorRGBA;
  visuals_glowEsp_enemy_invisible_color: ColorRGBA;
  visuals_glowEsp_friends_color: ColorRGBA;
  visuals_glowEsp_c4_color: ColorRGBA;

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
  skinchanger_knifes: { [T in TeamNum]?: ISkinchangerWeapon };
  //

  ///MISC
  misc_ingameRadar_enable: boolean;
  misc_bhop_enable: boolean;
  misc_autoPistols_enable: boolean;
  misc_autoPistols_delay: number;
  misc_autoAccept_enable: boolean;
  misc_antiFlash_enable: boolean;
  misc_antiFlash_maxAlpha: number;
  ///
};

export const DEFAULT_SETTINGS: TSettings = {
  ///AIMBOT
  ///GLOBALS
  aimbot_enable: true,
  aimbot_use_key: true,
  aimbot_key: 1,
  aimbot_delay_enemy: 100,
  aimbot_visible_check: true,
  aimbot_flash_check: true,
  aimbot_jump_check: true,
  aimbot_friendly_fire: false,
  ///

  ///PISTOLS
  aimbot_pistols_enable: true,
  aimbot_pistols_fov: 2,
  aimbot_pistols_bone: 8,
  aimbot_pistols_smooth: 0,
  aimbot_pistols_rcs_enable: false,
  aimbot_pistols_rcs_scale_x: 0,
  aimbot_pistols_rcs_scale_y: 0,
  ///

  ///HEAVIES
  aimbot_heavies_enable: true,
  aimbot_heavies_fov: 8,
  aimbot_heavies_bone: 0,
  aimbot_heavies_smooth: 5,
  aimbot_heavies_rcs_enable: true,
  aimbot_heavies_rcs_scale_x: 100,
  aimbot_heavies_rcs_scale_y: 100,
  ///

  //SHOUTGUNS
  aimbot_shoutguns_enable: true,
  aimbot_shoutguns_fov: 15,
  aimbot_shoutguns_bone: 0,
  aimbot_shoutguns_smooth: 0,
  aimbot_shoutguns_rcs_enable: false,
  aimbot_shoutguns_rcs_scale_x: 0,
  aimbot_shoutguns_rcs_scale_y: 0,
  ///

  ///SMGS
  aimbot_smgs_enable: true,
  aimbot_smgs_fov: 5,
  aimbot_smgs_bone: 0,
  aimbot_smgs_smooth: 3,
  aimbot_smgs_rcs_enable: true,
  aimbot_smgs_rcs_scale_x: 90,
  aimbot_smgs_rcs_scale_y: 90,
  ///

  ///RIFLES
  aimbot_rifles_enable: true,
  aimbot_rifles_fov: 3,
  aimbot_rifles_bone: 0,
  aimbot_rifles_smooth: 0,
  aimbot_rifles_rcs_enable: true,
  aimbot_rifles_rcs_scale_x: 100,
  aimbot_rifles_rcs_scale_y: 100,
  ///

  ///SNIPERS
  aimbot_snipers_enable: true,
  aimbot_snipers_fov: 10,
  aimbot_snipers_bone: 0,
  aimbot_snipers_smooth: 0,
  aimbot_snipers_rcs_enable: false,
  aimbot_snipers_rcs_scale_x: 0,
  aimbot_snipers_rcs_scale_y: 0,
  ///
  ///

  ///TRIGGER
  triggerbot_enable: true,
  triggerbot_use_key: true,
  triggerbot_key: 17,
  triggerbot_friendly_fire: false,
  triggerbot_flash_check: false,
  triggerbot_jump_check: false,
  triggerbot_delay_before_shoot: 50,
  triggerbot_delay_after_shoot: 50,
  triggerbot_pistols_enable: false,
  triggerbot_heavies_enable: false,
  triggerbot_shoutguns_enable: false,
  triggerbot_smgs_enable: false,
  triggerbot_rifles_enable: false,
  triggerbot_snipers_enable: true,
  ///

  //VISUALS
  //GLOW ESP
  visuals_glowEsp_enable: true,

  visuals_glowEsp_show_enemies: true,
  visuals_glowEsp_show_friends: false,
  visuals_glowEsp_show_c4: true,

  visuals_glowEsp_style: 0,
  visuals_glowEsp_mode: 0,

  visuals_glowEsp_enemy_visible_color: { r: 0, g: 255, b: 0, a: 255 },
  visuals_glowEsp_enemy_invisible_color: { r: 255, g: 0, b: 0, a: 255 },
  visuals_glowEsp_friends_color: { r: 0, g: 255, b: 0, a: 255 },
  visuals_glowEsp_c4_color: { r: 0, g: 0, b: 255, a: 255 },

  visuals_glowEsp_hpBased_0hp_color: { r: 255, g: 0, b: 0, a: 255 },
  visuals_glowEsp_hpBased_100hp_color: { r: 0, g: 255, b: 0, a: 255 },
  ///

  //CHAMS
  visuals_chams_enable: true,

  visuals_chams_show_enemies: true,
  visuals_chams_show_friends: false,

  visuals_chams_enemy_color: { r: 0, g: 255, b: 0, a: 255 },
  visuals_chams_friends_color: { r: 0, g: 255, b: 0, a: 255 },
  ///
  ///

  //SKINCHANGER
  skinchanger_enable: true,
  skinchanger_weapons: {},
  skinchanger_knifes: {},
  //

  ///MISC
  misc_ingameRadar_enable: true,
  misc_bhop_enable: true,
  misc_autoPistols_enable: true,
  misc_autoPistols_delay: 50,
  misc_autoAccept_enable: true,
  misc_antiFlash_enable: false,
  misc_antiFlash_maxAlpha: 255,
  ///
};
