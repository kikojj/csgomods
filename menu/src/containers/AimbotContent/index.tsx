import React from "react";
import {
  getActiveWeapon,
  selectActiveWeapon,
  selectSettings,
  useDataSelector,
  useSettingsSelector,
  updateValue,
} from "@services";
import { BoneSelect } from "@containers";
import {
  Group,
  CheckboxField,
  RangeField,
  SelectField,
  SelectItem,
  KeyInputField,
  Button,
} from "@components";
import {
  capitalizeFirstLetter,
  DEFAULT_AIMBOT_SETTINGS,
  IAimbotSettings,
  selectWeaponAimbotSettings,
  TSettings,
  Weapon,
} from "@utils";
import { useStyles } from "./styles";

export const AimbotContent: React.FC = () => {
  const classes = useStyles();

  const settings = useSettingsSelector(selectSettings);
  const gameActiveWeapon = useDataSelector(selectActiveWeapon);

  const [activeWeapon, setActiveWeapon] =
    React.useState<Weapon>(gameActiveWeapon);

  const activeWeaponSettings = selectWeaponAimbotSettings(
    settings,
    activeWeapon.itemDI,
    activeWeapon.sectionName
  );

  const activeWeaponAimbotSettings =
    settings.aimbot_weapons[activeWeapon.itemDI];
  const hasUsedActiveWeaponAimbotSettings =
    activeWeaponAimbotSettings && activeWeaponAimbotSettings.use;

  const activeWeaponSectionKey =
    `aimbot_${activeWeapon.sectionName}` as keyof TSettings;
  const activeWeaponSectionAimbotSettings = settings[
    activeWeaponSectionKey
  ] as IAimbotSettings;
  const hasUsedActiveWeaponSectionAimbotSettings =
    activeWeaponSectionAimbotSettings && activeWeaponSectionAimbotSettings.use;

  React.useEffect(() => {
    getActiveWeapon();
  }, []);

  React.useEffect(() => {
    if (gameActiveWeapon.isWeapon && !gameActiveWeapon.isKnife) {
      setActiveWeapon(gameActiveWeapon);
    }
  }, [gameActiveWeapon]);

  const changeSettings = React.useCallback(
    (value: IAimbotSettings) => {
      if (hasUsedActiveWeaponAimbotSettings) {
        return updateValue({
          name: "aimbot_weapons",
          value: {
            ...settings.aimbot_weapons,
            [activeWeapon.itemDI]: {
              ...activeWeaponAimbotSettings,
              ...value,
            },
          },
        });
      }

      if (hasUsedActiveWeaponSectionAimbotSettings) {
        return updateValue({
          name: activeWeaponSectionKey,
          value: {
            ...activeWeaponSectionAimbotSettings,
            ...value,
          },
        });
      }

      updateValue({
        name: "aimbot_global",
        value: {
          ...settings.aimbot_global,
          ...value,
        },
      });
    },
    [
      settings,
      activeWeaponAimbotSettings,
      hasUsedActiveWeaponAimbotSettings,
      activeWeaponSectionKey,
      activeWeaponSectionAimbotSettings,
      hasUsedActiveWeaponSectionAimbotSettings,
    ]
  );

  const addSectionSettings = React.useCallback(() => {
    updateValue({
      name: activeWeaponSectionKey,
      value: {
        ...DEFAULT_AIMBOT_SETTINGS,
        ...activeWeaponSectionAimbotSettings,
        use: true,
      },
    });
  }, [settings, activeWeaponSectionKey, activeWeaponSectionAimbotSettings]);

  const removeSectionSettings = React.useCallback(() => {
    updateValue({
      name: activeWeaponSectionKey,
      value: {
        ...DEFAULT_AIMBOT_SETTINGS,
        ...activeWeaponSectionAimbotSettings,
        use: false,
      },
    });
  }, [settings, activeWeaponSectionKey, activeWeaponSectionAimbotSettings]);

  const addWeaponSettings = React.useCallback(() => {
    updateValue({
      name: "aimbot_weapons",
      value: {
        ...settings.aimbot_weapons,
        [activeWeapon.itemDI]: {
          ...DEFAULT_AIMBOT_SETTINGS,
          ...activeWeaponSettings,
          use: true,
        },
      },
    });
  }, [settings, activeWeaponSettings]);

  const removeWeaponSettings = React.useCallback(() => {
    updateValue({
      name: "aimbot_weapons",
      value: {
        ...settings.aimbot_weapons,
        [activeWeapon.itemDI]: {
          ...DEFAULT_AIMBOT_SETTINGS,
          ...activeWeaponSettings,
          use: false,
        },
      },
    });
  }, [settings, activeWeaponSettings]);

  return (
    <div>
      <div className={classes.container}>
        <div>
          <Group label="Legitbot">
            <CheckboxField
              label="Enable"
              checked={settings.aimbot_enable}
              onChange={(v) => updateValue({ name: "aimbot_enable", value: v })}
            />
            {settings.aimbot_enable && (
              <React.Fragment>
                <CheckboxField
                  label="Visible check"
                  helperText="Check if player is visible"
                  checked={settings.aimbot_visible_check}
                  onChange={(v) =>
                    updateValue({ name: "aimbot_visible_check", value: v })
                  }
                />
                {settings.aimbot_visible_check && (
                  <CheckboxField
                    label="Smoke check"
                    helperText="Check if player is behind the smoke"
                    checked={settings.aimbot_smoke_check}
                    onChange={(v) =>
                      updateValue({ name: "aimbot_smoke_check", value: v })
                    }
                  />
                )}
                <CheckboxField
                  label="Flash check"
                  helperText="Check if you are blinded"
                  checked={settings.aimbot_flash_check}
                  onChange={(v) =>
                    updateValue({ name: "aimbot_flash_check", value: v })
                  }
                />
                <CheckboxField
                  label="Jump check"
                  helperText="Check if you are jumping"
                  checked={settings.aimbot_jump_check}
                  onChange={(v) =>
                    updateValue({ name: "aimbot_jump_check", value: v })
                  }
                />
                <CheckboxField
                  label="Friendly fire"
                  helperText="Aim if player is teammates"
                  checked={settings.aimbot_friendly_fire}
                  onChange={(v) =>
                    updateValue({ name: "aimbot_friendly_fire", value: v })
                  }
                />
                <RangeField
                  label={`Delay: ${settings.aimbot_delay_enemy}`}
                  helperText="Delay between aiming"
                  min={0}
                  max={2000}
                  step={10}
                  value={settings.aimbot_delay_enemy}
                  onChange={(v) =>
                    updateValue({ name: "aimbot_delay_enemy", value: v })
                  }
                />
                <SelectField
                  placeholder="Type"
                  helperText={
                    settings.aimbot_use_key
                      ? "Use key to activate aim"
                      : "Aim will always work"
                  }
                  value={settings.aimbot_use_key ? "1" : "0"}
                  onChange={(v) =>
                    updateValue({ name: "aimbot_use_key", value: v === "1" })
                  }
                >
                  <SelectItem value="0">Auto</SelectItem>
                  <SelectItem value="1">Key</SelectItem>
                </SelectField>
                {settings.aimbot_use_key && (
                  <KeyInputField
                    value={settings.aimbot_key}
                    onChange={(v) =>
                      updateValue({ name: "aimbot_key", value: v })
                    }
                  />
                )}
              </React.Fragment>
            )}
          </Group>
        </div>
        {settings.aimbot_enable && (
          <div>
            <Group
              marginLeft={35}
              label={
                hasUsedActiveWeaponAimbotSettings
                  ? "Weapon settings"
                  : hasUsedActiveWeaponSectionAimbotSettings
                  ? `${capitalizeFirstLetter(
                      activeWeapon.sectionName
                    )} settings`
                  : "Global settings"
              }
            >
              <CheckboxField
                label="Enable"
                checked={activeWeaponSettings.enable}
                onChange={(v) =>
                  changeSettings({ ...activeWeaponSettings, enable: v })
                }
              />
              {activeWeaponSettings.enable && (
                <React.Fragment>
                  <CheckboxField
                    label="Perfect first"
                    helperText="First bullet will 100% hit the target"
                    checked={activeWeaponSettings.first_perfect_shoot}
                    onChange={(v) =>
                      changeSettings({
                        ...activeWeaponSettings,
                        first_perfect_shoot: v,
                      })
                    }
                  />
                  <RangeField
                    label={`Fov: ${activeWeaponSettings.fov}`}
                    min={0}
                    max={180}
                    step={1}
                    value={activeWeaponSettings.fov}
                    onChange={(v) =>
                      changeSettings({ ...activeWeaponSettings, fov: v })
                    }
                  />
                  <BoneSelect
                    value={activeWeaponSettings.bone.toString()}
                    onChange={(v) =>
                      changeSettings({ ...activeWeaponSettings, bone: +v })
                    }
                  />
                  {!activeWeaponSettings.bone && (
                    <CheckboxField
                      label="Change bone"
                      helperText="Change the bone if it is not main(like shoulder, eblow, knee, etc.)"
                      checked={activeWeaponSettings.change_after_nearest}
                      onChange={(v) =>
                        changeSettings({
                          ...activeWeaponSettings,
                          change_after_nearest: v,
                        })
                      }
                    />
                  )}
                  <RangeField
                    label={`Smooth: ${activeWeaponSettings.smooth}`}
                    helperText="Slowing down the movement of the aiming"
                    min={0}
                    max={100}
                    step={1}
                    value={activeWeaponSettings.smooth}
                    onChange={(v) =>
                      changeSettings({ ...activeWeaponSettings, smooth: v })
                    }
                  />
                  <CheckboxField
                    label="RCS Enable"
                    checked={activeWeaponSettings.rcs_enable}
                    onChange={(v) =>
                      changeSettings({ ...activeWeaponSettings, rcs_enable: v })
                    }
                  />
                  {activeWeaponSettings.rcs_enable && (
                    <React.Fragment>
                      <RangeField
                        label={`RCS X: ${activeWeaponSettings.rcs_scale_x.toString()}%`}
                        helperText="Horizontal recoil"
                        min={0}
                        max={100}
                        step={1}
                        value={activeWeaponSettings.rcs_scale_x}
                        onChange={(v) =>
                          changeSettings({
                            ...activeWeaponSettings,
                            rcs_scale_x: v,
                          })
                        }
                      />
                      <RangeField
                        label={`RCS Y: ${activeWeaponSettings.rcs_scale_y.toString()}%`}
                        helperText="Vertical recoil"
                        min={0}
                        max={100}
                        step={1}
                        value={activeWeaponSettings.rcs_scale_y}
                        onChange={(v) =>
                          changeSettings({
                            ...activeWeaponSettings,
                            rcs_scale_y: v,
                          })
                        }
                      />
                    </React.Fragment>
                  )}
                </React.Fragment>
              )}
              {hasUsedActiveWeaponAimbotSettings ? (
                <Button onClick={removeWeaponSettings} color="#FF0000">
                  Remove {activeWeapon.name} settings
                </Button>
              ) : hasUsedActiveWeaponSectionAimbotSettings ? (
                <React.Fragment>
                  <Button onClick={removeSectionSettings} color="#FF0000">
                    Remove {capitalizeFirstLetter(activeWeapon.sectionName)}{" "}
                    settings
                  </Button>
                  <Button onClick={addWeaponSettings}>
                    Add {activeWeapon.name} settings
                  </Button>
                </React.Fragment>
              ) : (
                <React.Fragment>
                  <Button onClick={addSectionSettings}>
                    Add {capitalizeFirstLetter(activeWeapon.sectionName)}{" "}
                    settings
                  </Button>
                  <Button onClick={addWeaponSettings}>
                    Add {activeWeapon.name} settings
                  </Button>
                </React.Fragment>
              )}
            </Group>
          </div>
        )}
      </div>
    </div>
  );
};
