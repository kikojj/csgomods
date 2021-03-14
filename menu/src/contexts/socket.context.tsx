import React from "react";
import {
  TGetAllSettingsResponse,
  TGetConfigsListResponse,
  TConfigsListInput,
  TStopListeningInput,
  TUpdateSettingsInput,
  TSaveConfigInput,
  TDeleteConfigInput,
  TLoadConfigInput,
  TCloseMenuInput,
  TGetActiveWeaponResponse,
  TGetActiveWeaponInput,
  TFullForceUpdateInput,
  TGetAllSkinsInput,
  TGetAllSkinsResponse,
  TGetTeamInput,
  TGetTeamResponse,
} from "@ts/requests/";

const socket = new WebSocket("ws://localhost:2222");

type TMassage =
  | TGetAllSettingsResponse
  | TGetConfigsListResponse
  | TGetActiveWeaponResponse
  | TGetAllSkinsResponse
  | TGetTeamResponse;
type TMassageType = TMassage["type"];
type TMassageListener = { type: TMassageType; func: (message: any) => void };

type TSend =
  | TUpdateSettingsInput
  | TStopListeningInput
  | TConfigsListInput
  | TSaveConfigInput
  | TDeleteConfigInput
  | TLoadConfigInput
  | TCloseMenuInput
  | TGetActiveWeaponInput
  | TFullForceUpdateInput
  | TGetAllSkinsInput
  | TGetTeamInput;
type TSendType = TSend["type"];
type TSendMessage = TSend["message"];

const Socket = () => {
  const [connected, setConnected] = React.useState<boolean>(false);

  React.useEffect(() => {
    socket.onopen = function (e) {
      console.log("[WebSocket]: connected.");
      setConnected(true);
    };

    socket.onclose = function (event) {
      console.log("[WebSocket]: closed.");
      setConnected(false);
      setTimeout(() => {
        location.reload();
      }, 1000);
    };

    socket.onerror = function (error) {
      console.log("[WebSocket]: error.", error);
      setTimeout(() => {
        location.reload();
      }, 1000);
    };
  }, []);

  const addOnMessageListener = (type: TMassageType, func: TMassageListener["func"]) => {
    socket.addEventListener("message", (e) => {
      try {
        const data = JSON.parse(e.data) as TMassage;
        if (data && data.type === type) {
          func(data.message);
        }
      } catch (error) {
        console.log(error);
      }
    });
  };

  const send = (type: TSendType, message?: TSendMessage) => {
    socket.send(JSON.stringify({ type, message }));
  };

  return {
    connected,
    addOnMessageListener,
    send,
  };
};

const defaultValue: ReturnType<typeof Socket> = {
  connected: false,
  addOnMessageListener: () => 0,
  send: () => 0,
};

export const SocketContext = React.createContext<ReturnType<typeof Socket>>(defaultValue);
export const SocketContextProvider = (props: { children?: React.ReactNode }) => {
  return <SocketContext.Provider value={Socket()}>{props.children}</SocketContext.Provider>;
};
