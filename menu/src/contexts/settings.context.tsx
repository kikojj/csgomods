import React from "react";
import { SocketContext } from "./";
import { DEFAULT_SETTINGS, TSettings } from "@utils";
import { CLOSE_MENU, GET_ALL_SETTINGS, TGetAllSettingsResponse, UPDATE_SETTINGS } from "@ts/requests";

const Settings = () => {
  const socket = React.useContext(SocketContext);

  const [settings, _setSettings] = React.useState<TSettings>({ ...DEFAULT_SETTINGS });

  React.useEffect(() => {
    socket.addOnMessageListener(GET_ALL_SETTINGS, onGetAllSettings);
  }, []);

  const onGetAllSettings = React.useCallback((message: TGetAllSettingsResponse["message"]) => {
    _setSettings(message);
  }, []);

  const setSettings = React.useCallback((state: TSettings) => {
    socket.send(UPDATE_SETTINGS, state);
    _setSettings(state);
  }, []);

  const updateValue = React.useCallback(
    (name: keyof TSettings, value: TSettings[keyof TSettings]) => {
      setSettings({ ...settings, [name]: value });
    },
    [settings]
  );

  const closeMenu = React.useCallback(() => {
    socket.send(CLOSE_MENU);
  }, []);

  return {
    settings,
    setSettings,
    updateValue,
    closeMenu,
  };
};

const defaultValue: ReturnType<typeof Settings> = {
  settings: { ...DEFAULT_SETTINGS },
  setSettings: () => 0,
  updateValue: () => 0,
  closeMenu: () => 0,
};

export const SettingsContext = React.createContext<ReturnType<typeof Settings>>(defaultValue);
export const SettingsContextProvider = (props: { children?: React.ReactNode }) => {
  return <SettingsContext.Provider value={Settings()}>{props.children}</SettingsContext.Provider>;
};
