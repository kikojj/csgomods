import React from "react";
import { SocketContext } from ".";
import {
  TGetActiveWeaponResponse,
  GET_ACTIVE_WEAPON,
  GAME_FULL_FORCE_UPDATE,
  GET_ALL_SKINS,
  TGetTeamResponse,
  GET_TEAM,
  TGetRadarDataResponse,
  GET_RADAR_DATA,
  IRadarData,
  TGetMapNameResponse,
  GET_MAP_NAME,
} from "@ts/requests";
import { isObjectsEqual, Skin, TeamNum, Weapon } from "@utils";
import { TGetAllSkinsResponse } from "@ts/requests";

const Data = () => {
  const socket = React.useContext(SocketContext);

  const [activeWeapon, setActiveWeapon] = React.useState<Weapon>(new Weapon());
  const [team, setTeam] = React.useState<TeamNum>(TeamNum.Invalid);
  const [skins, setSkins] = React.useState<Skin[]>([]);
  const [defaultSkins, setDefaultSkins] = React.useState<TGetAllSkinsResponse["message"]["default"]>({});
  const [radarData, setRadarData] = React.useState<IRadarData[]>([]);
  const [mapName, setMapName] = React.useState<string>("");

  React.useEffect(() => {
    socket.addOnMessageListener(GET_ACTIVE_WEAPON, onGetActiveWeapon);
    socket.addOnMessageListener(GET_ALL_SKINS, onGetAllSkins);
    socket.addOnMessageListener(GET_TEAM, onGetTeam);
    socket.addOnMessageListener(GET_RADAR_DATA, onGetRadarData);
    socket.addOnMessageListener(GET_MAP_NAME, onGetMapName);
  }, []);

  const onGetActiveWeapon = React.useCallback((message: TGetActiveWeaponResponse["message"]) => {
    setActiveWeapon(new Weapon({ itemDI: message.active_weapon }));
  }, []);

  const getActiveWeapon = React.useCallback(() => {
    socket.send(GET_ACTIVE_WEAPON);
  }, []);

  const fullForceUpdate = React.useCallback(() => {
    socket.send(GAME_FULL_FORCE_UPDATE);
  }, []);

  const onGetAllSkins = React.useCallback((message: TGetAllSkinsResponse["message"]) => {
    if (message && message.skins) {
      setSkins(message?.skins?.map((s) => new Skin(s)));
      setDefaultSkins(message.default);
    }
  }, []);

  const getAllSkins = React.useCallback(() => {
    socket.send(GET_ALL_SKINS);
  }, []);

  const onGetTeam = React.useCallback((message: TGetTeamResponse["message"]) => {
    setTeam(message.team);
  }, []);

  const getTeam = React.useCallback(() => {
    socket.send(GET_TEAM);
  }, []);

  const onGetRadarData = React.useCallback((message: TGetRadarDataResponse["message"]) => {
    setRadarData((radarData) => {
      let wasChanged = false;
      message.forEach((d) => {
        const dataUser = radarData.find((d_) => {
          return d_.user_id === d.user_id;
        });
        if (dataUser && !isObjectsEqual(dataUser, d)) {
          wasChanged = true;
        } else if (!dataUser) {
          wasChanged = true;
        }
      });

      if (wasChanged) {
        return message;
      }
      return radarData;
    });
  }, []);

  const onGetMapName = React.useCallback((message: TGetMapNameResponse["message"]) => {
    setMapName(message);
  }, []);

  return {
    activeWeapon,
    getActiveWeapon,
    fullForceUpdate,
    skins,
    getAllSkins,
    defaultSkins,
    team,
    getTeam,
    radarData,
  };
};

const defaultValue: ReturnType<typeof Data> = {
  activeWeapon: new Weapon(),
  getActiveWeapon: () => 0,
  fullForceUpdate: () => 0,
  skins: [],
  getAllSkins: () => 0,
  defaultSkins: {},
  team: TeamNum.Invalid,
  getTeam: () => 0,
  radarData: [],
};

export const DataContext = React.createContext<ReturnType<typeof Data>>(defaultValue);
export const DataContextProvider = (props: { children?: React.ReactNode }) => {
  return <DataContext.Provider value={Data()}>{props.children}</DataContext.Provider>;
};
