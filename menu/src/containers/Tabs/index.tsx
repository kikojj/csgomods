import React from "react";
import { SettingsContext } from "../../contexts";
import { Tab } from "../../components";
import { useStyles } from "./styles";
import { ActiveTab } from "@utils";

export type TabsProps = {
  activeTab: ActiveTab;
  setActiveTab: React.Dispatch<React.SetStateAction<ActiveTab>>;
};
export const Tabs: React.FC<TabsProps> = ({ activeTab, setActiveTab }) => {
  const classes = useStyles();
  const { settings } = React.useContext(SettingsContext);

  return (
    <div className={classes.tabs}>
      <Tab
        title="Visuals"
        active={activeTab === ActiveTab.TAB_VISUALS}
        enable={settings.visuals_glowEsp_enable || settings.visuals_chams_enable}
        onClick={() => setActiveTab(ActiveTab.TAB_VISUALS)}
      />
      <Tab
        title="Aimbot"
        active={activeTab === ActiveTab.TAB_AIMBOT}
        enable={settings.aimbot_enable}
        onClick={() => setActiveTab(ActiveTab.TAB_AIMBOT)}
      />
      <Tab
        title="Trigger"
        active={activeTab === ActiveTab.TAB_TRIGGER}
        enable={settings.triggerbot_enable}
        onClick={() => setActiveTab(ActiveTab.TAB_TRIGGER)}
      />
      <Tab
        title="Skinchanger"
        active={activeTab === ActiveTab.TAB_SKINCHANGER}
        enable={false}
        onClick={() => setActiveTab(ActiveTab.TAB_SKINCHANGER)}
      />
      <Tab
        title="Misc"
        active={activeTab === ActiveTab.TAB_MISC}
        enable={settings.misc_autoPistols_enable || settings.misc_bhop_enable || settings.misc_ingameRadar_enable}
        onClick={() => setActiveTab(ActiveTab.TAB_MISC)}
      />
      <Tab
        title="Config"
        active={activeTab === ActiveTab.TAB_CONFIG}
        onClick={() => setActiveTab(ActiveTab.TAB_CONFIG)}
      />
    </div>
  );
};
