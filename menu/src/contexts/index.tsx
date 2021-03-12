import React from "react";
import { SettingsContextProvider } from "./settings.context";
import { SocketContextProvider } from "./socket.context";
import { ConfigContextProvider } from "./config.context";
import { DataContextProvider } from "./data.context";

export const Context = (props: { children: React.ReactNode }) => {
  return (
    <SocketContextProvider>
      <SettingsContextProvider>
        <DataContextProvider>
          <ConfigContextProvider>{props.children}</ConfigContextProvider>
        </DataContextProvider>
      </SettingsContextProvider>
    </SocketContextProvider>
  );
};

export { SettingsContext } from "./settings.context";
export { SocketContext } from "./socket.context";
export { ConfigContext } from "./config.context";
export { DataContext } from "./data.context";
