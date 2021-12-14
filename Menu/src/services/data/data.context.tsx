import { send } from "@services";
import { isObjectsEqual, Skin, TeamNum, Weapon } from "@utils";
import {
  TGetActiveWeaponResponse,
  GET_ACTIVE_WEAPON,
  GAME_FULL_FORCE_UPDATE,
  GET_ALL_SKINS,
  TGetTeamResponse,
  GET_TEAM,
  TGetRadarDataResponse,
  IRadarData,
  TGetMapNameResponse,
  TGetAllSkinsResponse,
} from "@ts/requests";
import { createStore, selectorFactory } from "okos";

export interface IDataService {
  activeWeapon: Weapon;
  team: TeamNum;
  skins: Skin[];
  defaultSkins: TGetAllSkinsResponse["message"]["default"];
  radarData: IRadarData[];
  mapName: string;
}

const DataService = createStore(
  {
    activeWeapon: new Weapon(),
    team: TeamNum.Invalid,
    skins: [],
    defaultSkins: {},
    radarData: [],
    mapName: "",
  } as IDataService,
  {
    getActiveWeapon: (_state) => {
      send({ type: GET_ACTIVE_WEAPON });
    },
    fullForceUpdate: (_state) => {
      send({ type: GAME_FULL_FORCE_UPDATE });
    },
    getAllSkins: () => {
      send({ type: GET_ALL_SKINS });
    },
    onGetTeam: (state, message: TGetTeamResponse["message"]) => {
      state.team = message.team;
    },
    getTeam: () => {
      send({ type: GET_TEAM });
    },
    onGetActiveWeapon: (
      state,
      message: TGetActiveWeaponResponse["message"]
    ) => {
      state.activeWeapon = new Weapon({ itemDI: message.active_weapon });
    },
    onGetAllSkins: (state, message: TGetAllSkinsResponse["message"]) => {
      if (message && message.skins) {
        state.skins = message?.skins?.map((s) => new Skin(s));
        state.defaultSkins = message.default;
      }
    },
    onGetRadarData: (state, message: TGetRadarDataResponse["message"]) => {
      let wasChanged = false;

      message.forEach((d) => {
        const dataUser = state.radarData.find((d_) => {
          return d_.user_id === d.user_id;
        });

        if (dataUser && !isObjectsEqual(dataUser, d)) {
          wasChanged = true;
        } else if (!dataUser) {
          wasChanged = true;
        }
      });

      if (wasChanged) {
        state.radarData = message;
      }

      state.radarData = state.radarData;
    },
    onGetMapName: (state, message: TGetMapNameResponse["message"]) => {
      state.mapName = message;
    },
  }
);

export const useDataSelector = selectorFactory(DataService.store);

export const {
  fullForceUpdate,
  getActiveWeapon,
  getAllSkins,
  getTeam,
  onGetActiveWeapon,
  onGetAllSkins,
  onGetMapName,
  onGetRadarData,
  onGetTeam,
} = DataService.actions;
