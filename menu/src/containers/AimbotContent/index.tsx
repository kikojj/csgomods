import React from "react";

import { DataContext, SettingsContext } from "@contexts";
import { BoneSelect } from "@containers";
import { Group, CheckboxField, RangeField, SelectField, SelectItem, KeyInputField, Button } from "@components";

import { capitalizeFirstLetter, DEFAULT_AIMBOT_SETTINGS, IAimbotSettings, TSettings, Weapon } from "@utils";
import { useStyles } from "./styles";

export const AimbotContent: React.FC = () => {
  const classes = useStyles();

  const { settings, updateValue } = React.useContext(SettingsContext);
  const { activeWeapon: gameActiveWeapon, getActiveWeapon } = React.useContext(DataContext);

  const [activeWeapon, setActiveWeapon] = React.useState<Weapon>(gameActiveWeapon);

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

  const weaponSettings: IAimbotSettings =
    settings.aimbot_weapons[activeWeapon.itemDI] && settings.aimbot_weapons[activeWeapon.itemDI]?.use
      ? (settings.aimbot_weapons[activeWeapon.itemDI] as IAimbotSettings)
      : (settings[`aimbot_${activeWeapon.sectionName}` as keyof TSettings] as IAimbotSettings).use
      ? (settings[`aimbot_${activeWeapon.sectionName}` as keyof TSettings] as IAimbotSettings)
      : settings.aimbot_global;

  function changeSettings(value: IAimbotSettings) {
    if (settings.aimbot_weapons[activeWeapon.itemDI] && settings.aimbot_weapons[activeWeapon.itemDI]?.use) {
      updateValue("aimbot_weapons", {
        ...settings.aimbot_weapons,
        [activeWeapon.itemDI]: {
          ...settings.aimbot_weapons[activeWeapon.itemDI],
          ...value,
        },
      });
    } else if ((settings[`aimbot_${activeWeapon.sectionName}` as keyof TSettings] as IAimbotSettings).use) {
      updateValue(`aimbot_${activeWeapon.sectionName}` as keyof TSettings, {
        ...(settings[`aimbot_${activeWeapon.sectionName}` as keyof TSettings] as IAimbotSettings),
        ...value,
      });
    } else {
      updateValue("aimbot_global", {
        ...settings.aimbot_global,
        ...value,
      });
    }
  }

  function addSectionSettings() {
    updateValue(`aimbot_${activeWeapon.sectionName}` as keyof TSettings, {
      ...DEFAULT_AIMBOT_SETTINGS,
      ...(settings[`aimbot_${activeWeapon.sectionName}` as keyof TSettings] as IAimbotSettings),
      use: true,
    });
  }

  function removeSectionSettings() {
    updateValue(`aimbot_${activeWeapon.sectionName}` as keyof TSettings, {
      ...DEFAULT_AIMBOT_SETTINGS,
      ...(settings[`aimbot_${activeWeapon.sectionName}` as keyof TSettings] as IAimbotSettings),
      use: false,
    });
  }

  function addWeaponSettings() {
    updateValue("aimbot_weapons", {
      ...settings.aimbot_weapons,
      [activeWeapon.itemDI]: {
        ...DEFAULT_AIMBOT_SETTINGS,
        ...settings.aimbot_weapons[activeWeapon.itemDI],
        use: true,
      },
    });
  }

  function removeWeaponSettings() {
    updateValue("aimbot_weapons", {
      ...settings.aimbot_weapons,
      [activeWeapon.itemDI]: {
        ...DEFAULT_AIMBOT_SETTINGS,
        ...settings.aimbot_weapons[activeWeapon.itemDI],
        use: false,
      },
    });
  }

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
                {settings.aimbot_visible_check ? (
                  <CheckboxField
                    label="Smoke check"
                    helperText="Check if player is behind the smoke"
                    checked={settings.aimbot_smoke_check}
                    onChange={(v) => updateValue("aimbot_smoke_check", v)}
                  />
                ) : (
                  ""
                )}
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
            <Group
              marginLeft={35}
              label={
                <React.Fragment>
                  {settings.aimbot_weapons[activeWeapon.itemDI] && settings.aimbot_weapons[activeWeapon.itemDI]?.use
                    ? "Weapon settings"
                    : (settings[`aimbot_${activeWeapon.sectionName}` as keyof TSettings] as IAimbotSettings).use
                    ? `${capitalizeFirstLetter(activeWeapon.sectionName)} settings`
                    : "Global settings"}
                </React.Fragment>
              }
            >
              <CheckboxField
                label="Enable"
                checked={weaponSettings.enable}
                onChange={(v) => changeSettings({ ...weaponSettings, enable: v })}
              />
              {weaponSettings.enable ? (
                <React.Fragment>
                  <CheckboxField
                    label="Perfect first"
                    helperText="First bullet will 100% hit the target"
                    checked={weaponSettings.first_perfect_shoot}
                    onChange={(v) => changeSettings({ ...weaponSettings, first_perfect_shoot: v })}
                  />
                  <RangeField
                    label={`Fov: ${weaponSettings.fov}`}
                    min={0}
                    max={180}
                    step={1}
                    value={weaponSettings.fov}
                    onChange={(v) => changeSettings({ ...weaponSettings, fov: v })}
                  />
                  <BoneSelect
                    value={weaponSettings.bone.toString()}
                    onChnage={(v) => changeSettings({ ...weaponSettings, bone: +v })}
                  />
                  {weaponSettings.bone === 0 ? (
                    <CheckboxField
                      label="Change bone"
                      helperText="Change the bone if it is not main(like shoulder, eblow, knee, etc.)"
                      checked={weaponSettings.change_after_nearest}
                      onChange={(v) => changeSettings({ ...weaponSettings, change_after_nearest: v })}
                    />
                  ) : (
                    ""
                  )}
                  <RangeField
                    label={`Smooth: ${weaponSettings.smooth}`}
                    helperText="Slowing down the movement of the aiming"
                    min={0}
                    max={100}
                    step={1}
                    value={weaponSettings.smooth}
                    onChange={(v) => changeSettings({ ...weaponSettings, smooth: v })}
                  />
                  <CheckboxField
                    label="RCS Enable"
                    checked={weaponSettings.rcs_enable}
                    onChange={(v) => changeSettings({ ...weaponSettings, rcs_enable: v })}
                  />
                  {weaponSettings.rcs_enable ? (
                    <React.Fragment>
                      <RangeField
                        label={`RCS X: ${weaponSettings.rcs_scale_x.toString()}%`}
                        helperText="Horizontal recoil"
                        min={0}
                        max={100}
                        step={1}
                        value={weaponSettings.rcs_scale_x}
                        onChange={(v) => changeSettings({ ...weaponSettings, rcs_scale_x: v })}
                      />
                      <RangeField
                        label={`RCS Y: ${weaponSettings.rcs_scale_y.toString()}%`}
                        helperText="Vertical recoil"
                        min={0}
                        max={100}
                        step={1}
                        value={weaponSettings.rcs_scale_y}
                        onChange={(v) => changeSettings({ ...weaponSettings, rcs_scale_y: v })}
                      />
                    </React.Fragment>
                  ) : (
                    ""
                  )}
                </React.Fragment>
              ) : (
                ""
              )}
              {settings.aimbot_weapons[activeWeapon.itemDI] && settings.aimbot_weapons[activeWeapon.itemDI]?.use ? (
                <Button onClick={removeWeaponSettings} color="#FF0000">
                  Remove {activeWeapon.name} settings
                </Button>
              ) : (settings[`aimbot_${activeWeapon.sectionName}` as keyof TSettings] as IAimbotSettings).use &&
                !activeWeapon.isKnife() ? (
                <React.Fragment>
                  <Button onClick={removeSectionSettings} color="#FF0000">
                    Remove {capitalizeFirstLetter(activeWeapon.sectionName)} settings
                  </Button>
                  <Button onClick={addWeaponSettings}>Add {activeWeapon.name} settings</Button>
                </React.Fragment>
              ) : !activeWeapon.isKnife() ? (
                <React.Fragment>
                  <Button onClick={addSectionSettings}>
                    Add {capitalizeFirstLetter(activeWeapon.sectionName)} settings
                  </Button>
                  <Button onClick={addWeaponSettings}>Add {activeWeapon.name} settings</Button>
                </React.Fragment>
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
