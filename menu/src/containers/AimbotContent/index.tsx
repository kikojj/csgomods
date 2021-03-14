import React from "react";

import { DataContext, SettingsContext } from "@contexts";
import { WeaponSelect, BoneSelect } from "@containers";
import { Group, CheckboxField, RangeField, SelectField, SelectItem, KeyInputField } from "@components";

import { TSettings, Weapon } from "@utils";
import { useStyles } from "./styles";

export const AimbotContent: React.FC = () => {
  const classes = useStyles();

  const { settings, updateValue } = React.useContext(SettingsContext);
  const { activeWeapon: gameActiveWeapon, getActiveWeapon } = React.useContext(DataContext);

  const [activeWeapon, setActiveWeapon] = React.useState<Weapon>(gameActiveWeapon);

  const legitbotFields = {
    enable: `aimbot_${activeWeapon.sectionName}_enable` as keyof TSettings,
    fov: `aimbot_${activeWeapon.sectionName}_fov` as keyof TSettings,
    bone: `aimbot_${activeWeapon.sectionName}_bone` as keyof TSettings,
    smooth: `aimbot_${activeWeapon.sectionName}_smooth` as keyof TSettings,
    rcs_enable: `aimbot_${activeWeapon.sectionName}_rcs_enable` as keyof TSettings,
    rcs_scale_x: `aimbot_${activeWeapon.sectionName}_rcs_scale_x` as keyof TSettings,
    rcs_scale_y: `aimbot_${activeWeapon.sectionName}_rcs_scale_y` as keyof TSettings,
  };

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
          <Group label="Legitbot">
            <CheckboxField
              label="Enable"
              checked={settings.aimbot_enable}
              onChange={(v) => updateValue("aimbot_enable", v)}
            />
            {settings.aimbot_enable ? (
              <React.Fragment>
                <CheckboxField
                  label="Visible check"
                  helperText="Check if player is visible"
                  checked={settings.aimbot_visible_check}
                  onChange={(v) => updateValue("aimbot_visible_check", v)}
                />
                <CheckboxField
                  label="Flash check"
                  helperText="Check if you are blinded"
                  checked={settings.aimbot_flash_check}
                  onChange={(v) => updateValue("aimbot_flash_check", v)}
                />
                <CheckboxField
                  label="Jump check"
                  helperText="Check if you are jumping"
                  checked={settings.aimbot_jump_check}
                  onChange={(v) => updateValue("aimbot_jump_check", v)}
                />
                <CheckboxField
                  label="Friendly fire"
                  helperText="Aim if player is teammates"
                  checked={settings.aimbot_friendly_fire}
                  onChange={(v) => updateValue("aimbot_friendly_fire", v)}
                />
                <RangeField
                  label={`Delay: ${settings.aimbot_delay_enemy}`}
                  helperText="Delay between aiming"
                  min={0}
                  max={2000}
                  step={10}
                  value={settings.aimbot_delay_enemy}
                  onChange={(v) => updateValue("aimbot_delay_enemy", v)}
                />
                <SelectField
                  placeholder="Type"
                  helperText={settings.aimbot_use_key ? "Use key to activate aim" : "Aim will always work"}
                  value={settings.aimbot_use_key ? "1" : "0"}
                  onChange={(v) => updateValue("aimbot_use_key", v === "1")}
                >
                  <SelectItem value="0">Auto</SelectItem>
                  <SelectItem value="1">Key</SelectItem>
                </SelectField>
                {settings.aimbot_use_key ? (
                  <KeyInputField value={settings.aimbot_key} onChange={(v) => updateValue("aimbot_key", v)} />
                ) : (
                  ""
                )}
              </React.Fragment>
            ) : (
              ""
            )}
          </Group>
        </div>
        {settings.aimbot_enable ? (
          <div>
            <Group marginLeft={35} label="Weapon legitbot">
              <WeaponSelect
                value={activeWeapon.itemDI.toString()}
                onChnage={(itemDI) => setActiveWeapon(new Weapon({ itemDI: +itemDI }))}
              />
              {activeWeapon.itemDI > 0 ? (
                <React.Fragment>
                  <CheckboxField
                    label="Enable"
                    checked={settings[legitbotFields.enable] as boolean}
                    onChange={(v) => updateValue(legitbotFields.enable, v)}
                  />
                  {(settings[legitbotFields.enable] as boolean) ? (
                    <React.Fragment>
                      <RangeField
                        label={`Fov: ${settings[legitbotFields.fov] as number}`}
                        min={0}
                        max={180}
                        step={1}
                        value={settings[legitbotFields.fov] as number}
                        onChange={(v) => updateValue(legitbotFields.fov, v)}
                      />
                      <BoneSelect
                        value={settings[legitbotFields.bone].toString()}
                        onChnage={(v) => updateValue(legitbotFields.fov, +v)}
                      />
                      <RangeField
                        label={`Smooth: ${settings[legitbotFields.smooth] as number}`}
                        helperText="Slowing down the movement of the aiming"
                        min={0}
                        max={100}
                        step={1}
                        value={settings[legitbotFields.smooth] as number}
                        onChange={(v) => updateValue(legitbotFields.smooth, v)}
                      />
                    </React.Fragment>
                  ) : (
                    ""
                  )}
                </React.Fragment>
              ) : (
                ""
              )}
            </Group>
            {settings.aimbot_enable ? (
              <Group marginTop={35} marginLeft={35} label="Weapon RCS">
                <WeaponSelect
                  value={activeWeapon.itemDI.toString()}
                  onChnage={(itemDI) => setActiveWeapon(new Weapon({ itemDI: +itemDI }))}
                />
                <CheckboxField
                  label="Enable"
                  checked={settings[legitbotFields.rcs_enable] as boolean}
                  onChange={(v) => updateValue(legitbotFields.rcs_enable, v)}
                />
                {(settings[legitbotFields.rcs_enable] as boolean) ? (
                  <React.Fragment>
                    <RangeField
                      label={`RCS X: ${settings[legitbotFields.rcs_scale_x].toString()}%`}
                      helperText="Horizontal recoil"
                      min={0}
                      max={100}
                      step={1}
                      value={settings[legitbotFields.rcs_scale_x] as number}
                      onChange={(v) => updateValue(legitbotFields.rcs_scale_x, v)}
                    />
                    <RangeField
                      label={`RCS Y: ${settings[legitbotFields.rcs_scale_y].toString()}%`}
                      helperText="Vertical recoil"
                      min={0}
                      max={100}
                      step={1}
                      value={settings[legitbotFields.rcs_scale_y] as number}
                      onChange={(v) => updateValue(legitbotFields.rcs_scale_y, v)}
                    />
                  </React.Fragment>
                ) : (
                  ""
                )}
              </Group>
            ) : (
              ""
            )}
          </div>
        ) : (
          ""
        )}
      </div>
      <div className={classes.container}>
        <div>
          <Group marginTop={35} label="Triggerbot">
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
            <Group marginTop={35} marginLeft={35} label="Weapon triggerbot">
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
