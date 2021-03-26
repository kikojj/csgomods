import React from "react";

import { DataContext, SettingsContext } from "@contexts";
import { WeaponSelect } from "@containers";
import { Group, CheckboxField, RangeField, SelectField, SelectItem, KeyInputField } from "@components";

import { TSettings, Weapon } from "@utils";
import { useStyles } from "./styles";

export const TriggerbotContent: React.FC = () => {
  const classes = useStyles();

  const { settings, updateValue } = React.useContext(SettingsContext);
  const { activeWeapon: gameActiveWeapon, getActiveWeapon } = React.useContext(DataContext);

  const [activeWeapon, setActiveWeapon] = React.useState<Weapon>(gameActiveWeapon);

  const triggerFields = {
    enable: `triggerbot_${activeWeapon.sectionName}_enable` as keyof TSettings,
  };

  React.useEffect(() => {
    getActiveWeapon();
  }, []);

  React.useEffect(() => {
    if (
      gameActiveWeapon.isPistol() ||
      gameActiveWeapon.isSMG() ||
      gameActiveWeapon.isHeavy() ||
      gameActiveWeapon.isShotgun() ||
      gameActiveWeapon.isRifle() ||
      gameActiveWeapon.isSnipers()
    ) {
      setActiveWeapon(gameActiveWeapon);
    }
  }, [gameActiveWeapon]);

  return (
    <div>
      <div className={classes.container}>
        <div>
          <Group label="Triggerbot">
            <CheckboxField
              label="Enable"
              checked={settings.triggerbot_enable}
              onChange={(v) => updateValue("triggerbot_enable", v)}
            />
            {settings.triggerbot_enable ? (
              <React.Fragment>
                <CheckboxField
                  label="Flash check"
                  helperText="Check if you are blinded"
                  checked={settings.triggerbot_flash_check}
                  onChange={(v) => updateValue("triggerbot_flash_check", v)}
                />
                <CheckboxField
                  label="Jump check"
                  helperText="Check if you are jumping"
                  checked={settings.triggerbot_jump_check}
                  onChange={(v) => updateValue("triggerbot_jump_check", v)}
                />
                <CheckboxField
                  label="Friendly fire"
                  helperText="Aim if player is teammates"
                  checked={settings.triggerbot_friendly_fire}
                  onChange={(v) => updateValue("triggerbot_friendly_fire", v)}
                />
                <RangeField
                  label={`Delay before: ${settings.triggerbot_delay_before_shoot}`}
                  helperText="Delay before shooting"
                  min={0}
                  max={2000}
                  step={10}
                  value={settings.triggerbot_delay_before_shoot}
                  onChange={(v) => updateValue("triggerbot_delay_before_shoot", v)}
                />
                <RangeField
                  label={`Delay after: ${settings.triggerbot_delay_after_shoot}`}
                  helperText="Delay after shooting"
                  min={0}
                  max={2000}
                  step={10}
                  value={settings.triggerbot_delay_after_shoot}
                  onChange={(v) => updateValue("triggerbot_delay_after_shoot", v)}
                />
                <SelectField
                  placeholder="Type"
                  helperText="Use key to activate aim"
                  value={settings.triggerbot_use_key ? "1" : "0"}
                  onChange={(v) => updateValue("triggerbot_use_key", v === "1")}
                >
                  <SelectItem value="0">Auto</SelectItem>
                  <SelectItem value="1">Key</SelectItem>
                </SelectField>
                {settings.triggerbot_use_key ? (
                  <KeyInputField value={settings.triggerbot_key} onChange={(v) => updateValue("triggerbot_key", v)} />
                ) : (
                  ""
                )}
              </React.Fragment>
            ) : (
              ""
            )}
          </Group>
        </div>
        {settings.triggerbot_enable ? (
          <div>
            <Group marginLeft={35} label="Weapon triggerbot">
              <WeaponSelect
                value={activeWeapon.itemDI.toString()}
                onChnage={(itemDI) => setActiveWeapon(new Weapon({ itemDI: +itemDI }))}
              />
              {activeWeapon.itemDI > 0 ? (
                <CheckboxField
                  label="Enable"
                  checked={settings[triggerFields.enable] as boolean}
                  onChange={(v) => updateValue(triggerFields.enable, v)}
                />
              ) : (
                ""
              )}
            </Group>
          </div>
        ) : (
          ""
        )}
      </div>
    </div>
  );
};
