import React from "react";
import { selectSettings, updateValue, useSettingsSelector } from "@services";
import { Group, CheckboxField, RangeField } from "@components";
import { useStyles } from "./styles";

export const MiscContent: React.FC = () => {
  const classes = useStyles();

  const settings = useSettingsSelector(selectSettings);

  return (
    <div className={classes.container}>
      <div>
        <Group label="Bhop">
          <CheckboxField
            label="Enable"
            checked={settings.misc_bhop_enable}
            onChange={(v) =>
              updateValue({ name: "misc_bhop_enable", value: v })
            }
          />
        </Group>
        <Group marginTop={35} label="Auto pistols">
          <CheckboxField
            label="Enable"
            checked={settings.misc_auto_pistols_enable}
            onChange={(v) =>
              updateValue({ name: "misc_auto_pistols_enable", value: v })
            }
          />
          {settings.misc_auto_accept_enable && (
            <RangeField
              label={`Delay: ${settings.misc_auto_pistols_delay}`}
              helperText="Delay between shoots"
              min={0}
              max={2000}
              step={10}
              value={settings.misc_auto_pistols_delay}
              onChange={(v) =>
                updateValue({ name: "misc_auto_pistols_delay", value: v })
              }
            />
          )}
        </Group>
        <Group marginTop={35} label="Anti flash">
          <CheckboxField
            label="Enable"
            checked={settings.misc_anti_flash_enable}
            onChange={(v) =>
              updateValue({ name: "misc_anti_flash_enable", value: v })
            }
          />
          {settings.misc_anti_flash_enable && (
            <RangeField
              label={`Max alpha: ${settings.misc_anti_flash_max_alpha}`}
              min={0}
              max={255}
              step={1}
              value={settings.misc_anti_flash_max_alpha}
              onChange={(v) =>
                updateValue({ name: "misc_anti_flash_max_alpha", value: v })
              }
            />
          )}
        </Group>
      </div>
      <div>
        <Group marginLeft={35} label="Auto accept">
          <CheckboxField
            label="Enable"
            checked={settings.misc_auto_accept_enable}
            onChange={(v) =>
              updateValue({ name: "misc_auto_accept_enable", value: v })
            }
          />
        </Group>
        <Group marginTop={35} marginLeft={35} label="Ingame radar">
          <CheckboxField
            label="Enable"
            checked={settings.misc_ingame_radar_enable}
            onChange={(v) =>
              updateValue({ name: "misc_ingame_radar_enable", value: v })
            }
          />
        </Group>
      </div>
    </div>
  );
};
