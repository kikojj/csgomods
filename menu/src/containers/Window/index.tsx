import React from "react";
import { selectConnected, useSocketSelector } from "@services";
import {
  Menu,
  VisualsContent,
  AimbotContent,
  SkinchangerContent,
  MiscContent,
  ConfigsContent,
  LoadingContent,
  TriggerbotContent,
  PlayersListContent,
} from "@containers";
import { ActiveTab } from "@utils";
import { useStyles } from "./styles";

const LS_ACTIVE_TAB = "csgomods_active_tab";

export const Window = () => {
  const classes = useStyles();

  const connected = useSocketSelector(selectConnected);

  const [activeTab, _setActiveTab] = React.useState<ActiveTab>(
    localStorage.getItem(LS_ACTIVE_TAB) ? parseInt(localStorage.getItem(LS_ACTIVE_TAB)!) : ActiveTab.TAB_VISUALS
  );

  function setActiveTab(v: ActiveTab | ((prev: ActiveTab) => ActiveTab)) {
    const value = typeof v === "function" ? v(activeTab) : v;

    localStorage.setItem(LS_ACTIVE_TAB, value.toString());

    _setActiveTab(value);
  }

  return (
    <div className={classes.container}>
      <Menu activeTab={activeTab} setActiveTab={setActiveTab} />
      <div className={classes.content}>
        {!connected ? (
          <LoadingContent />
        ) : activeTab === ActiveTab.TAB_VISUALS ? (
          <VisualsContent />
        ) : activeTab === ActiveTab.TAB_AIMBOT ? (
          <AimbotContent />
        ) : activeTab === ActiveTab.TAB_TRIGGER ? (
          <TriggerbotContent />
        ) : activeTab === ActiveTab.TAB_SKINCHANGER ? (
          <SkinchangerContent />
        ) : activeTab === ActiveTab.TAB_MISC ? (
          <MiscContent />
        ) : activeTab === ActiveTab.TAB_CONFIG ? (
          <ConfigsContent />
        ) : activeTab === ActiveTab.TAB_PLAYERSLIST ? (
          <PlayersListContent />
        ) : (
          ""
        )}
      </div>
    </div>
  );
};
