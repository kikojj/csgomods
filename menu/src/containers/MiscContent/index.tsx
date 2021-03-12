import React from "react";

import { SettingsContext } from "../../contexts";

import { SectionTitle, Switch, Group, Range } from "@components";
import { WindowContent } from "../Window/Content";

import { useStyles } from "./styles";

export const MiscContent = () => {
  const classes = useStyles();
  const { settings, updateValue } = React.useContext(SettingsContext);

  return (
    <WindowContent>
      <SectionTitle text="Misc" />
      <Group title="Bhop" marginTop={28}>
        <Switch
          label="Enable"
          marginTop={10}
          checked={settings.misc_bhop_enable}
          onChange={(e, v) => updateValue("misc_bhop_enable", v)}
        />
      </Group>
      <Group title="Autopistols" marginTop={28}>
        <Switch
          label="Enable"
          marginTop={10}
          checked={settings.misc_autoPistols_enable}
          onChange={(e, v) => updateValue("misc_autoPistols_enable", v)}
        />
        <Range
          marginTop={10}
          label="Delay"
          min={0}
          max={1000}
          value={settings.misc_autoPistols_delay}
          onChange={(e, v) => (typeof v === "number" ? updateValue("misc_autoPistols_delay", v) : 0)}
          step={1}
        />
      </Group>
      <Group title="Ingame radar" marginTop={28}>
        <Switch
          label="Enable"
          marginTop={10}
          checked={settings.misc_ingameRadar_enable}
          onChange={(e, v) => updateValue("misc_ingameRadar_enable", v)}
        />
      </Group>
      <Group title="Auto accept" marginTop={28}>
        <Switch
          label="Enable"
          marginTop={10}
          checked={settings.misc_autoAccept_enable}
          onChange={(e, v) => updateValue("misc_autoAccept_enable", v)}
        />
      </Group>
    </WindowContent>
  );
};
