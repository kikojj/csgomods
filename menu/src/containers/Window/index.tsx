import React from "react";

import { ConfigContext, DataContext, SocketContext } from "../../contexts";
import { Header, Tabs } from "../";
import {
  LoadingContent,
  VisualsContent,
  TriggerContent,
  MiscContent,
  AimbotContent,
  ConfigContent,
  SkinchangerContent,
} from "@containers";

import { ActiveTab, getWeaponName } from "@utils";
import { useStyles } from "./styles";

export type TWindowSize = "default" | "full";
export const Window = () => {
  const { connected } = React.useContext(SocketContext);
  const { skins } = React.useContext(DataContext);

  const [activeTab, setActiveTab] = React.useState<ActiveTab>(ActiveTab.TAB_VISUALS);
  const [windowSize, setWindowSize] = React.useState<TWindowSize>("default");

  const classes = useStyles({ windowSize });

  return (
    <div className={classes.bg}>
      <div className={classes.window}>
        <Header onOptions={() => setWindowSize(windowSize === "default" ? "full" : "default")} />
        <Tabs activeTab={activeTab} setActiveTab={setActiveTab} />
        {!connected || skins.length <= 0 ? (
          <LoadingContent />
        ) : activeTab === ActiveTab.TAB_VISUALS ? (
          <VisualsContent />
        ) : activeTab === ActiveTab.TAB_AIMBOT ? (
          <AimbotContent />
        ) : activeTab === ActiveTab.TAB_TRIGGER ? (
          <TriggerContent />
        ) : activeTab === ActiveTab.TAB_SKINCHANGER ? (
          <SkinchangerContent />
        ) : activeTab === ActiveTab.TAB_MISC ? (
          <MiscContent />
        ) : activeTab === ActiveTab.TAB_CONFIG ? (
          <ConfigContent />
        ) : (
          ""
        )}
      </div>
    </div>
  );
};
