import React from "react";
import { BrowserRouter, Switch, Route } from "react-router-dom";
import {
  addMessageListener,
  connect,
  disconnect,
  onGetConfigsList,
  reconnect,
  selectConnected,
  selectSocket,
  useSocketSelector,
  onGetActiveWeapon,
  onGetAllSkins,
  onGetTeam,
  onGetRadarData,
  onGetMapName,
  onGetAllSettings,
} from "@services";
import { Window } from "@containers";
import { useGlobalStyles } from "./utils";
import {
  GET_ACTIVE_WEAPON,
  GET_ALL_SETTINGS,
  GET_ALL_SKINS,
  GET_CONFIGS_LIST,
  GET_MAP_NAME,
  GET_RADAR_DATA,
  GET_TEAM,
} from "@ts/requests";

export const App = () => {
  useGlobalStyles();

  const socket = useSocketSelector(selectSocket);
  const connected = useSocketSelector(selectConnected);

  React.useEffect(() => {
    socket.onopen = function () {
      console.log("[WebSocket]: connected.");
      connect();
    };

    socket.onclose = function () {
      console.log("[WebSocket]: closed.");
      disconnect();
    };

    socket.onerror = function (error) {
      setInterval(reconnect, 1000);
      console.log("[WebSocket]: error.", error);
    };
  }, []);

  React.useEffect(() => {
    if (!connected) {
      return;
    }

    // from config service
    addMessageListener({ type: GET_CONFIGS_LIST, callback: onGetConfigsList });

    // from data service
    addMessageListener({
      type: GET_ACTIVE_WEAPON,
      callback: onGetActiveWeapon,
    });
    addMessageListener({ type: GET_ALL_SKINS, callback: onGetAllSkins });
    addMessageListener({ type: GET_TEAM, callback: onGetTeam });
    addMessageListener({ type: GET_RADAR_DATA, callback: onGetRadarData });
    addMessageListener({ type: GET_MAP_NAME, callback: onGetMapName });

    // from settings service
    addMessageListener({ type: GET_ALL_SETTINGS, callback: onGetAllSettings });
  }, [connected]);

  return (
    <BrowserRouter>
      <Switch>
        <Route path="/">
          <Window />
        </Route>
      </Switch>
    </BrowserRouter>
  );
};
