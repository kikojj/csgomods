import { ColorRGBA } from "@components";
import { ItemDefinitionIndex } from "./weapon";

export enum EntityQuality {
  Invalid = -1,
  Normal,
  Genuine,
  Vintage,
  Unusual,
  Community = 5,
  Developer,
  SelftMade,
  Customized,
  Strange,
  Completed,
  Tournament = 12,
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
  quality: EntityQuality.Normal,
  wear: 0.00001,
  custom_name: "",
  stat_track: -1,
  seed: 0,
  item_di: ItemDefinitionIndex.Invalid,
};

export enum TeamNum {
  Invalid = 0,
  Spectator = 1,
  Terrorist = 2,
  CounterTerrorist = 3,
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

export interface IGlowESPSettings {
  enable: boolean;
  mode: number;
  style: number;
  visible_color: ColorRGBA;
  invisible_color: ColorRGBA;
  hp_based_0hp_color: ColorRGBA;
  hp_based_100hp_color: ColorRGBA;
}

export const DEFAULT_GLOW_ESP_SETTINGS: IGlowESPSettings = {
  enable: false,
  mode: 0,
  style: 0,
  visible_color: { r: 0, g: 0, b: 0, a: 0 },
  invisible_color: { r: 0, g: 0, b: 0, a: 0 },
  hp_based_0hp_color: { r: 0, g: 0, b: 0, a: 0 },
  hp_based_100hp_color: { r: 0, g: 0, b: 0, a: 0 },
};

export interface IChamsSettings {
  enable: boolean;
  color: ColorRGBA;
}

export const DEFAULT_CHAMS_SETTINGS: IChamsSettings = {
  enable: false,
  color: { r: 0, g: 0, b: 0, a: 0 },
};

export interface IPersonalSettings {
  enable: boolean;
  glow_settings: IGlowESPSettings;
  chams_settings: IChamsSettings;
}

export const DEFAULT_PERSONAL_SETTINGS: IPersonalSettings = {
  enable: false,
  glow_settings: { ...DEFAULT_GLOW_ESP_SETTINGS },
  chams_settings: { ...DEFAULT_CHAMS_SETTINGS },
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
  visuals_glow_esp_enemies: IGlowESPSettings;
  visuals_glow_esp_friends: IGlowESPSettings;
  visuals_glow_esp_c4: IGlowESPSettings;
  visuals_glow_esp_defusing: IGlowESPSettings;
  visuals_glow_esp_grenades: IGlowESPSettings;
  ///

  //CHAMS
  visuals_chams_enable: boolean;
  visuals_chams_enemies: IChamsSettings;
  visuals_chams_friends: IChamsSettings;
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

  ///PERSONAL SETTINGS
  personal_settings: { [T in number]?: IPersonalSettings };
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
  visuals_glow_esp_enemies: { ...DEFAULT_GLOW_ESP_SETTINGS },
  visuals_glow_esp_friends: { ...DEFAULT_GLOW_ESP_SETTINGS },
  visuals_glow_esp_defusing: { ...DEFAULT_GLOW_ESP_SETTINGS },
  visuals_glow_esp_grenades: { ...DEFAULT_GLOW_ESP_SETTINGS },
  visuals_glow_esp_c4: { ...DEFAULT_GLOW_ESP_SETTINGS },
  ///

  //CHAMS
  visuals_chams_enable: false,
  visuals_chams_enemies: { ...DEFAULT_CHAMS_SETTINGS },
  visuals_chams_friends: { ...DEFAULT_CHAMS_SETTINGS },
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

  ///PERSONAL SETTINGS
  personal_settings: {},
  ///
};
