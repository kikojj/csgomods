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
  paint_kit: number;
  quality: EntityQuality;
  wear: number;
  custom_name: string;
  stat_track: number;
  seed: number;
  item_di: ItemDefinitionIndex;
}

export const DEFAULT_WEAPON_SETTINGS: ISkinchangerWeapon = {
  enable: true,
  paint_kit: -1,
  quality: EntityQuality.QUALITY_NORMAL,
  wear: 0.00001,
  custom_name: "",
  stat_track: -1,
  seed: 0,
  item_di: ItemDefinitionIndex.INVALID_ITEM_DI,
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
  first_perfect_shoot: boolean;
  fov: number;
  bone: number;
  change_after_nearest: boolean;
  smooth: number;
  rcs_enable: boolean;
  rcs_scale_x: number;
  rcs_scale_y: number;
}

export const DEFAULT_AIMBOT_SETTINGS: IAimbotSettings = {
  use: false,
  enable: false,
  first_perfect_shoot: false,
  fov: 0,
  bone: 0,
  change_after_nearest: false,
  smooth: 0,
  rcs_enable: false,
  rcs_scale_x: 100,
  rcs_scale_y: 100,
};

export type TSettings = {
  //AIMBOT
  aimbot_enable: boolean;
  aimbot_use_key: boolean;
  aimbot_key: number;
  aimbot_delay_enemy: number;
  aimbot_visible_check: boolean;
  aimbot_smoke_check: boolean;
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
  visuals_glow_esp_enable: boolean;

  visuals_glow_esp_show_enemies: boolean;
  visuals_glow_esp_show_friends: boolean;
  visuals_glow_esp_show_c4: boolean;
  visuals_glow_esp_show_defusing: boolean;
  visuals_glow_esp_show_grenades: boolean;

  visuals_glow_esp_style: number;
  visuals_glow_esp_mode: number;

  visuals_glow_esp_enemy_visible_color: ColorRGBA;
  visuals_glow_esp_enemy_invisible_color: ColorRGBA;
  visuals_glow_esp_friends_color: ColorRGBA;
  visuals_glow_esp_c4_color: ColorRGBA;
  visuals_glow_esp_defusing_color: ColorRGBA;
  visuals_glow_esp_grenades_color: ColorRGBA;

  visuals_glow_esp_hp_based_0hp_color: ColorRGBA;
  visuals_glow_esp_hp_based_100hp_color: ColorRGBA;
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
  misc_ingame_radar_enable: boolean;
  misc_bhop_enable: boolean;
  misc_auto_pistols_enable: boolean;
  misc_auto_pistols_delay: number;
  misc_auto_accept_enable: boolean;
  misc_anti_flash_enable: boolean;
  misc_anti_flash_max_alpha: number;
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
  aimbot_smoke_check: false,
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
  visuals_glow_esp_enable: false,

  visuals_glow_esp_show_enemies: false,
  visuals_glow_esp_show_friends: false,
  visuals_glow_esp_show_c4: false,
  visuals_glow_esp_show_defusing: false,
  visuals_glow_esp_show_grenades: false,

  visuals_glow_esp_style: 0,
  visuals_glow_esp_mode: 0,

  visuals_glow_esp_enemy_visible_color: { r: 0, g: 0, b: 0, a: 0 },
  visuals_glow_esp_enemy_invisible_color: { r: 0, g: 0, b: 0, a: 0 },
  visuals_glow_esp_friends_color: { r: 0, g: 0, b: 0, a: 0 },
  visuals_glow_esp_c4_color: { r: 0, g: 0, b: 0, a: 0 },
  visuals_glow_esp_defusing_color: { r: 0, g: 0, b: 0, a: 0 },
  visuals_glow_esp_grenades_color: { r: 0, g: 0, b: 0, a: 0 },

  visuals_glow_esp_hp_based_0hp_color: { r: 0, g: 0, b: 0, a: 0 },
  visuals_glow_esp_hp_based_100hp_color: { r: 0, g: 0, b: 0, a: 0 },
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
  misc_ingame_radar_enable: false,
  misc_bhop_enable: false,
  misc_auto_pistols_enable: false,
  misc_auto_pistols_delay: 0,
  misc_auto_accept_enable: false,
  misc_anti_flash_enable: false,
  misc_anti_flash_max_alpha: 255,
  ///
};
