import React from "react";
import {
  SectionTitle,
  Switch,
  Group,
  Radio,
  ColorPicker,
  Range,
  KeyInput,
  BoneSleector,
  WeaponSelect,
} from "@components";

import { WindowContent } from "../Window/Content";
import { RadioGroup } from "@material-ui/core";
import { useStyles } from "./styles";
import { DataContext, SettingsContext } from "../../contexts";
import { ItemDefinitionIndex, TSettings, Weapon } from "@utils";

export const AimbotContent = () => {
  const classes = useStyles();
  const { settings, updateValue } = React.useContext(SettingsContext);
  const data = React.useContext(DataContext);

  const [activeWeapon, setActiveWeapon] = React.useState<Weapon>(data.activeWeapon);

  const fields = {
    enable: `aimbot_${activeWeapon.sectionName}_enable` as keyof TSettings,
    fov: `aimbot_${activeWeapon.sectionName}_fov` as keyof TSettings,
    bone: `aimbot_${activeWeapon.sectionName}_bone` as keyof TSettings,
    smooth: `aimbot_${activeWeapon.sectionName}_smooth` as keyof TSettings,
    rcs_enable: `aimbot_${activeWeapon.sectionName}_rcs_enable` as keyof TSettings,
    rcs_scale_x: `aimbot_${activeWeapon.sectionName}_rcs_scale_x` as keyof TSettings,
    rcs_scale_y: `aimbot_${activeWeapon.sectionName}_rcs_scale_y` as keyof TSettings,
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
          checked={settings.aimbot_enable}
          onChange={(e, v) => updateValue("aimbot_enable", v)}
        />
        {settings.aimbot_enable ? (
          <React.Fragment>
            <Switch
              label="Visible check"
              checked={settings.aimbot_visible_check}
              onChange={(e, v) => updateValue("aimbot_visible_check", v)}
            />
            <Switch
              label="Flash check"
              checked={settings.aimbot_flash_check}
              onChange={(e, v) => updateValue("aimbot_flash_check", v)}
            />
            <Switch
              label="Jump check"
              checked={settings.aimbot_jump_check}
              onChange={(e, v) => updateValue("aimbot_jump_check", v)}
            />
            <Switch
              label="Friendly fire"
              checked={settings.aimbot_friendly_fire}
              onChange={(e, v) => updateValue("aimbot_friendly_fire", v)}
            />
            <Range
              marginTop={10}
              label="Delay"
              min={0}
              max={2000}
              value={settings.aimbot_delay_enemy}
              onChange={(e, v) => (typeof v === "number" ? updateValue("aimbot_delay_enemy", v) : 0)}
              step={1}
            />
            <RadioGroup
              row
              value={settings.aimbot_use_key}
              onChange={(e, v) => updateValue("aimbot_use_key", Boolean(+v))}
            >
              <Radio label="Auto" value="0" checked={settings.aimbot_use_key === false} />
              <Radio label="Key" value="1" checked={settings.aimbot_use_key === true} />
            </RadioGroup>
            {settings.aimbot_use_key ? (
              <KeyInput
                marginTop={10}
                label="Activate key"
                value={settings.aimbot_key}
                onChange={(v) => updateValue("aimbot_key", v)}
              />
            ) : (
              ""
            )}
          </React.Fragment>
        ) : (
          ""
        )}
      </div>
      {settings.aimbot_enable ? (
        <React.Fragment>
          <div className={classes.weapon}>
            <SectionTitle text="Weapon" />
            <WeaponSelect
              value={activeWeapon.itemDI}
              onChange={(v) => setActiveWeapon(new Weapon({ itemDI: v }))}
              marginTop={28}
            />
            {activeWeapon.itemDI !== ItemDefinitionIndex.INVALID_ITEM_DI ? (
              <React.Fragment>
                <Switch
                  marginTop={10}
                  label="Enable"
                  checked={settings[fields.enable] as boolean}
                  onChange={(e, v) => updateValue(fields.enable, v)}
                />
                {settings[fields.enable] ? (
                  <React.Fragment>
                    <Range
                      marginTop={10}
                      label="Fov"
                      min={0}
                      max={180}
                      step={1}
                      value={settings[fields.fov] as number}
                      onChange={(e, v) => (typeof v === "number" ? updateValue(fields.fov, v) : 0)}
                    />
                    <BoneSleector
                      value={settings[fields.bone] as number}
                      onChange={(v, c) => updateValue(fields.bone, v.target.value as number)}
                    />
                    <Range
                      marginTop={10}
                      label="Smooth"
                      min={0}
                      max={100}
                      step={1}
                      value={settings[fields.smooth] as number}
                      onChange={(e, v) => (typeof v === "number" ? updateValue(fields.smooth, v) : 0)}
                    />
                    <Switch
                      label="RCS enable"
                      checked={settings[fields.rcs_enable] as boolean}
                      onChange={(e, v) => updateValue(fields.rcs_enable, v)}
                    />
                    {settings[fields.rcs_enable] ? (
                      <React.Fragment>
                        <Range
                          marginTop={10}
                          label="RCS X"
                          min={0}
                          max={100}
                          step={1}
                          value={settings[fields.rcs_scale_x] as number}
                          onChange={(e, v) => (typeof v === "number" ? updateValue(fields.rcs_scale_x, v) : 0)}
                        />
                        <Range
                          marginTop={10}
                          label="RCS Y"
                          min={0}
                          max={100}
                          step={1}
                          value={settings[fields.rcs_scale_y] as number}
                          onChange={(e, v) => (typeof v === "number" ? updateValue(fields.rcs_scale_y, v) : 0)}
                        />
                      </React.Fragment>
                    ) : (
                      ""
                    )}
                  </React.Fragment>
                ) : (
                  ""
                )}
              </React.Fragment>
            ) : (
              ""
            )}
          </div>
        </React.Fragment>
      ) : (
        ""
      )}
    </WindowContent>
  );
};
