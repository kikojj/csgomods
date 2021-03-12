import React from "react";

import { SettingsContext } from "../../../contexts";

import { Group, CheckboxField, RangeField } from "../../components";
import { useStyles } from "./styles";

export const MiscContent: React.FC = () => {
  const classes = useStyles();

  const { settings, updateValue } = React.useContext(SettingsContext);

  return (
    <div className={classes.container}>
      <div>
        <Group label="Bhop">
          <CheckboxField
            label="Enable"
            checked={settings.misc_bhop_enable}
            onChange={(v) => updateValue("misc_bhop_enable", v)}
          />
        </Group>
        <Group marginTop={35} label="Auto pistols">
          <CheckboxField
            label="Enable"
            checked={settings.misc_autoPistols_enable}
            onChange={(v) => updateValue("misc_autoPistols_enable", v)}
          />
          {settings.misc_autoAccept_enable ? (
            <RangeField
              label={`Delay: ${settings.misc_autoPistols_delay}`}
              helperText="Delay between shoots"
              min={0}
              max={2000}
              step={10}
              value={settings.misc_autoPistols_delay}
              onChange={(v) => updateValue("misc_autoPistols_delay", v)}
            />
          ) : (
            ""
          )}
        </Group>
      </div>
      <div>
        <Group marginLeft={35} label="Auto accept">
          <CheckboxField
            label="Enable"
            checked={settings.misc_autoAccept_enable}
            onChange={(v) => updateValue("misc_autoAccept_enable", v)}
          />
        </Group>
        <Group marginTop={35} marginLeft={35} label="Ingame radar">
          <CheckboxField
            label="Enable"
            checked={settings.misc_ingameRadar_enable}
            onChange={(v) => updateValue("misc_ingameRadar_enable", v)}
          />
        </Group>
      </div>
    </div>
  );
};
