import React from "react";
import { SocketContext } from ".";
import {
  TGetActiveWeaponResponse,
  GET_ACTIVE_WEAPON,
  GAME_FULL_FORCE_UPDATE,
  GET_ALL_SKINS,
  TGetTeamResponse,
  GET_TEAM,
} from "@ts/requests";
import { Skin, TeamNum, Weapon } from "@utils";
import { TGetAllSkinsResponse } from "@ts/requests";

const Data = () => {
  const socket = React.useContext(SocketContext);

  const [activeWeapon, setActiveWeapon] = React.useState<Weapon>(new Weapon());
  const [team, setTeam] = React.useState<TeamNum>(TeamNum.NO_TEAM);
  const [skins, setSkins] = React.useState<Skin[]>([]);
  const [defaultSkins, setDefaultSkins] = React.useState<TGetAllSkinsResponse["message"]["default"]>({});

  React.useEffect(() => {
    socket.addOnMessageListener(GET_ACTIVE_WEAPON, onGetActiveWeapon);
    socket.addOnMessageListener(GET_ALL_SKINS, onGetAllSkins);
    socket.addOnMessageListener(GET_TEAM, onGetTeam);
  }, []);

  const onGetActiveWeapon = React.useCallback((message: TGetActiveWeaponResponse["message"]) => {
    setActiveWeapon(new Weapon({ itemDI: message.activeWeapon }));
  }, []);

  const getActiveWeapon = React.useCallback(() => {
    socket.send(GET_ACTIVE_WEAPON);
  }, []);

  const fullForceUpdate = React.useCallback(() => {
    socket.send(GAME_FULL_FORCE_UPDATE);
  }, []);

  const onGetAllSkins = React.useCallback((message: TGetAllSkinsResponse["message"]) => {
    setSkins(message.skins.map((s) => new Skin(s)));
    setDefaultSkins(message.default);
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

  return {
    activeWeapon,
    getActiveWeapon,
    fullForceUpdate,
    skins,
    getAllSkins,
    defaultSkins,
    team,
    getTeam,
  };
};

const defaultValue: ReturnType<typeof Data> = {
  activeWeapon: new Weapon(),
  getActiveWeapon: () => 0,
  fullForceUpdate: () => 0,
  skins: [],
  getAllSkins: () => 0,
  defaultSkins: {},
  team: TeamNum.NO_TEAM,
  getTeam: () => 0,
};

export const DataContext = React.createContext<ReturnType<typeof Data>>(defaultValue);
export const DataContextProvider = (props: { children?: React.ReactNode }) => {
  return <DataContext.Provider value={Data()}>{props.children}</DataContext.Provider>;
};
