import React from "react";

import { DataContext, SocketContext } from "@contexts";
import {
  Menu,
  VisualsContent,
  AimbotContent,
  SkinchangerContent,
  MiscContent,
  ConfigsContent,
  LoadingContent,
} from "@containers";

import { ActiveTab } from "@utils";
import { useStyles } from "./styles";

export const Window = () => {
  const classes = useStyles();

  const { connected } = React.useContext(SocketContext);
  const { skins } = React.useContext(DataContext);

  const [activeTab, setActiveTab] = React.useState<ActiveTab>(ActiveTab.TAB_VISUALS);

  return (
    <div className={classes.container}>
      <Menu activeTab={activeTab} setActiveTab={setActiveTab} />
      <div className={classes.content}>
        {!connected || skins.length <= 0 ? (
          <LoadingContent />
        ) : activeTab === ActiveTab.TAB_VISUALS ? (
          <VisualsContent />
        ) : activeTab === ActiveTab.TAB_AIMBOT ? (
          <AimbotContent />
        ) : activeTab === ActiveTab.TAB_SKINCHANGER ? (
          <SkinchangerContent />
        ) : activeTab === ActiveTab.TAB_MISC ? (
          <MiscContent />
        ) : activeTab === ActiveTab.TAB_CONFIG ? (
          <ConfigsContent />
        ) : (
          ""
        )}
      </div>
    </div>
  );
};
