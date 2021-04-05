import React from "react";

import { SocketContext } from "@contexts";
import { Menu as CMenu } from "@components";

import { ActiveTab } from "@utils";
import * as icons from "./images";

export type MenuProps = {
  activeTab: ActiveTab;
  setActiveTab: React.Dispatch<React.SetStateAction<ActiveTab>>;
};
export const Menu: React.FC<MenuProps> = ({ activeTab, setActiveTab }) => {
  const { send } = React.useContext(SocketContext);

  return (
    <CMenu
      tabs={[
        {
          title: "Visuals",
          subtitle: "Glow ESP, Chams",
          iconUrl: icons.VisualsIcon,
          active: activeTab === ActiveTab.TAB_VISUALS,
          onClick: () => setActiveTab(ActiveTab.TAB_VISUALS),
        },
        {
          title: "Aimbot",
          subtitle: "Legit, Weapon settings, Recoil control",
          iconUrl: icons.MouseIcon,
          active: activeTab === ActiveTab.TAB_AIMBOT,
          onClick: () => setActiveTab(ActiveTab.TAB_AIMBOT),
        },
        {
          title: "Triggerbot",
          subtitle: "Triggerbot, Weapon settings",
          iconUrl: icons.AimIcon,
          active: activeTab === ActiveTab.TAB_TRIGGER,
          onClick: () => setActiveTab(ActiveTab.TAB_TRIGGER),
        },
        {
          title: "Skinchanger",
          subtitle: "Skins, knives",
          iconUrl: icons.SkinchangerIcon,
          active: activeTab === ActiveTab.TAB_SKINCHANGER,
          onClick: () => setActiveTab(ActiveTab.TAB_SKINCHANGER),
        },
        {
          title: "Miscellaneous",
          subtitle: "Bhop, Auto pistols, Auto accept, Rank reveal",
          iconUrl: icons.MiscellaneousIcon,
          active: activeTab === ActiveTab.TAB_MISC,
          onClick: () => setActiveTab(ActiveTab.TAB_MISC),
        },
        {
          title: "Players List",
          subtitle: "Statistics, Ranks, Personal settings",
          iconUrl: icons.PlayersIcon,
          active: activeTab === ActiveTab.TAB_PLAYERSLIST,
          onClick: () => setActiveTab(ActiveTab.TAB_PLAYERSLIST),
        },
        {
          title: "Configs",
          subtitle: "Configs list",
          iconUrl: icons.ConfigsIcon,
          active: activeTab === ActiveTab.TAB_CONFIG,
          onClick: () => setActiveTab(ActiveTab.TAB_CONFIG),
        },
      ]}
      onExit={() => {
        send("stop_listening");
      }}
    />
  );
};
