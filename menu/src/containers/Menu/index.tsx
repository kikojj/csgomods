import React from "react";

import { SocketContext } from "@contexts";
import { Menu as CMenu } from "@components";

import { ActiveTab } from "@utils";
import { SERVER_PORT } from "@utils/constants";
import { AimbotIcon, ConfigsIcon, MiscellaneousIcon, SkinchangerIcon, VisualsIcon, PlayersIcon } from "./images";

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
          iconUrl: VisualsIcon,
          active: activeTab === ActiveTab.TAB_VISUALS,
          onClick: () => setActiveTab(ActiveTab.TAB_VISUALS),
        },
        {
          title: "Aimbot",
          subtitle: "Legit, Weapon settings, Recoil control",
          iconUrl: AimbotIcon,
          active: activeTab === ActiveTab.TAB_AIMBOT,
          onClick: () => setActiveTab(ActiveTab.TAB_AIMBOT),
        },
        {
          title: "Triggerbot",
          subtitle: "Triggerbot, Weapon settings",
          iconUrl: AimbotIcon,
          active: activeTab === ActiveTab.TAB_TRIGGER,
          onClick: () => setActiveTab(ActiveTab.TAB_TRIGGER),
        },
        {
          title: "Skinchanger",
          subtitle: "Skins, knives",
          iconUrl: SkinchangerIcon,
          active: activeTab === ActiveTab.TAB_SKINCHANGER,
          onClick: () => setActiveTab(ActiveTab.TAB_SKINCHANGER),
        },
        {
          title: "Miscellaneous",
          subtitle: "Bhop, Auto pistols, Auto accept, Rank reveal",
          iconUrl: MiscellaneousIcon,
          active: activeTab === ActiveTab.TAB_MISC,
          onClick: () => setActiveTab(ActiveTab.TAB_MISC),
        },
        {
          title: "Configs",
          subtitle: "Configs list",
          iconUrl: ConfigsIcon,
          active: activeTab === ActiveTab.TAB_CONFIG,
          onClick: () => setActiveTab(ActiveTab.TAB_CONFIG),
        },
        {
          title: "Players List",
          iconUrl: PlayersIcon,
          active: activeTab === ActiveTab.TAB_PLAYERSLIST,
          onClick: () => setActiveTab(ActiveTab.TAB_PLAYERSLIST),
        },
      ]}
      onExit={() => {
        send("stop_listening");
        fetch(`http://localhost:${SERVER_PORT}/exit`, { method: "GET" });
      }}
    />
  );
};
