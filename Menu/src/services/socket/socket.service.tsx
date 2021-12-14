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
  TGetRadarDataResponse,
  TGetMapNameResponse,
} from "@ts/requests/";
import { WEBSOCKET_PORT } from "@utils/constants";
import { createStore, selectorFactory } from "okos";

const SOCKET_URL = `ws://localhost:${WEBSOCKET_PORT}`;

type TMassage =
  | TGetAllSettingsResponse
  | TGetConfigsListResponse
  | TGetActiveWeaponResponse
  | TGetAllSkinsResponse
  | TGetTeamResponse
  | TGetRadarDataResponse
  | TGetMapNameResponse;
type TMassageType = TMassage["type"];
type TMassageListener = { type: TMassageType; callback: (message: any) => void };

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

export interface ISocketService {
  readonly socket: WebSocket;
  connected: boolean;
}

const SocketService = createStore(
  { socket: new WebSocket(SOCKET_URL), connected: false },
  {
    connect: (state) => {
      state.connected = true;
    },
    disconnect: (state) => {
      state.connected = false;
    },
    reconnect: (state) => {
      state.socket = new WebSocket(SOCKET_URL);
      state.socket.onopen = () => location.reload();
    },
    addMessageListener: (
      state,
      payload: { type: TMassageType; callback: TMassageListener["callback"] }
    ) => {
      state.socket.addEventListener("message", (e) => {
        try {
          const data = JSON.parse(e.data) as TMassage;
          if (data && data.type === payload.type) {
            payload.callback(data.message);
          }
        } catch (error) {
          console.log(error);
        }
      });
    },

    send: (state, payload: { type: TSendType; message?: TSendMessage }) => {
      state.socket.send(JSON.stringify(payload));
    },
  }
);

export const useSocketSelector = selectorFactory(SocketService.store);

export const { connect, disconnect, reconnect, addMessageListener, send } =
  SocketService.actions;
