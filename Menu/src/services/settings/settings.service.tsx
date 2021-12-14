import { createStore, selectorFactory } from "okos";
import { send } from "@services";
import {
  DEFAULT_SETTINGS,
  ISkinchangerWeapon,
  ItemDefinitionIndex,
  TeamNum,
  TSettings,
} from "@utils";
import {
  CLOSE_MENU,
  TGetAllSettingsResponse,
  UPDATE_SETTINGS,
} from "@ts/requests";

export interface ISettingService {
  settings: TSettings;
}

export const SettingsService = createStore(
  { settings: { ...DEFAULT_SETTINGS } } as ISettingService,
  {
    updateValue: (
      state,
      payload: { name: keyof TSettings; value: TSettings[keyof TSettings] }
    ) => {
      (state.settings[payload.name] as TSettings[keyof TSettings]) =
        payload.value;
        
      send({ type: UPDATE_SETTINGS, message: state.settings });
    },
    closeMenu: () => {
      send({ type: CLOSE_MENU });
    },
    applyWeaponPaintKit: (
      state,
      payload: { itemDI: ItemDefinitionIndex; paintKit: number }
    ) => {
      state.settings.skinchanger_weapons = {
        ...state.settings.skinchanger_weapons,
        [payload.itemDI]: {
          ...state.settings.skinchanger_weapons[payload.itemDI],
          paint_kit: payload.paintKit,
        } as ISkinchangerWeapon,
      };
      
      send({ type: UPDATE_SETTINGS, message: state.settings });
    },
    applyKnifeModel: (
      state,
      payload: { activeTeam: TeamNum; itemDI: ItemDefinitionIndex }
    ) => {
      state.settings.skinchanger_knives = {
        ...state.settings.skinchanger_knives,
        [payload.activeTeam]: {
          ...state.settings.skinchanger_knives[payload.activeTeam],
          item_di: payload.itemDI,
        } as ISkinchangerWeapon,
      };
      
      send({ type: UPDATE_SETTINGS, message: state.settings });
    },
    applyKnifePaintKit: (
      state,
      payload: { activeTeam: TeamNum; paintKit: number }
    ) => {
      state.settings.skinchanger_knives = {
        ...state.settings.skinchanger_knives,
        [payload.activeTeam]: {
          ...state.settings.skinchanger_knives[payload.activeTeam],
          paint_kit: payload.paintKit,
        } as ISkinchangerWeapon,
      };
      
      send({ type: UPDATE_SETTINGS, message: state.settings });
    },
    onGetAllSettings: (state, message: TGetAllSettingsResponse["message"]) => {
      state.settings = message;
    },
  }
);

export const useSettingsSelector = selectorFactory(SettingsService.store);

export const {
  updateValue,
  closeMenu,
  applyWeaponPaintKit,
  applyKnifeModel,
  applyKnifePaintKit,
  onGetAllSettings,
} = SettingsService.actions;
