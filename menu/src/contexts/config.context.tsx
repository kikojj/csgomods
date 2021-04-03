import React from "react";
import { SocketContext } from ".";
import { TGetConfigsListResponse, GET_CONFIGS_LIST, SAVE_CONFIG, DELETE_CONFIG, LOAD_CONFIG } from "@ts/requests";

const Config = () => {
  const socket = React.useContext(SocketContext);

  const [configsList, setConfigsList] = React.useState<string[]>([]);

  React.useEffect(() => {
    socket.addOnMessageListener(GET_CONFIGS_LIST, onGetConfigsList);
  }, []);

  const onGetConfigsList = React.useCallback((message: TGetConfigsListResponse["message"]) => {
    setConfigsList(message.files);
  }, []);

  const getConfigsList = React.useCallback(() => {
    socket.send(GET_CONFIGS_LIST);
  }, []);

  const loadConfig = React.useCallback((fileName: string) => {
    socket.send(LOAD_CONFIG, { file_name: fileName });
  }, []);

  const saveConfig = React.useCallback((fileName: string) => {
    socket.send(SAVE_CONFIG, { file_name: fileName.split(".")[0] });
  }, []);

  const deleteConfig = React.useCallback((fileName: string) => {
    socket.send(DELETE_CONFIG, { file_name: fileName });
  }, []);

  return {
    configsList,
    getConfigsList,
    loadConfig,
    saveConfig,
    deleteConfig,
  };
};

const defaultValue: ReturnType<typeof Config> = {
  configsList: [],
  getConfigsList: () => 0,
  loadConfig: () => 0,
  saveConfig: () => 0,
  deleteConfig: () => 0,
};

export const ConfigContext = React.createContext<ReturnType<typeof Config>>(defaultValue);
export const ConfigContextProvider = (props: { children?: React.ReactNode }) => {
  return <ConfigContext.Provider value={Config()}>{props.children}</ConfigContext.Provider>;
};
