import React from "react";
import { SectionTitle, Switch, Radio, Range, KeyInput, WeaponSelect } from "@components";

import { WindowContent } from "../Window/Content";
import { RadioGroup } from "@material-ui/core";
import { useStyles } from "./styles";
import { DataContext, SettingsContext } from "../../contexts";
import { ItemDefinitionIndex, TSettings, Weapon } from "@utils";

export const TriggerContent = () => {
  const classes = useStyles();
  const { settings, updateValue } = React.useContext(SettingsContext);
  const data = React.useContext(DataContext);

  const [activeWeapon, setActiveWeapon] = React.useState<Weapon>(data.activeWeapon);

  const fields = {
    enable: `triggerbot_${activeWeapon.sectionName}_enable` as keyof TSettings,
  };

  React.useEffect(() => {
    data.getActiveWeapon();
  }, []);

  React.useEffect(() => {
    if (
      data.activeWeapon.isPistol() ||
      data.activeWeapon.isSMG() ||
      data.activeWeapon.isHeavy() ||
      data.activeWeapon.isShotgun() ||
      data.activeWeapon.isRifle() ||
      data.activeWeapon.isSnipers()
    ) {
      setActiveWeapon(data.activeWeapon);
    }
  }, [data, data.activeWeapon]);

  return (
    <WindowContent>
      <div className={classes.global}>
        <SectionTitle text="General" />
        <Switch
          label="Enable"
          marginTop={28}
          checked={settings.triggerbot_enable}
          onChange={(e, v) => updateValue("triggerbot_enable", v)}
        />
        {settings.triggerbot_enable ? (
          <React.Fragment>
            <Switch
              label="Friendly fire"
              checked={settings.triggerbot_friendly_fire}
              onChange={(e, v) => updateValue("triggerbot_friendly_fire", v)}
            />
            <Switch
              label="Flash check"
              checked={settings.triggerbot_flash_check}
              onChange={(e, v) => updateValue("triggerbot_flash_check", v)}
            />
            <Switch
              label="Jump check"
              checked={settings.triggerbot_jump_check}
              onChange={(e, v) => updateValue("triggerbot_jump_check", v)}
            />
            <Range
              marginTop={10}
              label="Delay before shoot"
              min={0}
              max={2000}
              value={settings.triggerbot_delay_before_shoot}
              onChange={(e, v) => (typeof v === "number" ? updateValue("triggerbot_delay_before_shoot", v) : 0)}
              step={1}
            />
            <Range
              marginTop={10}
              label="Delay after shoot"
              min={0}
              max={2000}
              value={settings.triggerbot_delay_after_shoot}
              onChange={(e, v) => (typeof v === "number" ? updateValue("triggerbot_delay_after_shoot", v) : 0)}
              step={1}
            />
            <RadioGroup
              row
              value={settings.triggerbot_use_key}
              onChange={(e, v) => updateValue("triggerbot_use_key", Boolean(+v))}
            >
              <Radio label="Auto" value="0" checked={settings.triggerbot_use_key === false} />
              <Radio label="Key" value="1" checked={settings.triggerbot_use_key === true} />
            </RadioGroup>
            {settings.triggerbot_use_key === true ? (
              <KeyInput
                marginTop={10}
                label="Activate key"
                value={settings.triggerbot_key}
                onChange={(v) => updateValue("triggerbot_key", v)}
              />
            ) : (
              ""
            )}
          </React.Fragment>
        ) : (
          ""
        )}
      </div>
      {settings.triggerbot_enable ? (
        <div className={classes.weapons}>
          <SectionTitle text="Weapon" />
          <WeaponSelect
            value={activeWeapon.itemDI}
            onChange={(v) => setActiveWeapon(new Weapon({ itemDI: v }))}
            marginTop={28}
          />
          {activeWeapon.itemDI !== ItemDefinitionIndex.INVALID_ITEM_DI ? (
            <Switch
              label="Enable"
              marginTop={28}
              checked={settings[fields.enable] as boolean}
              onChange={(e, v) => updateValue(fields.enable, v)}
            />
          ) : (
            ""
          )}
        </div>
      ) : (
        ""
      )}
    </WindowContent>
  );
};
