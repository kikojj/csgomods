import React from "react";
import {
  getActiveWeapon,
  selectActiveWeapon,
  selectSettings,
  updateValue,
  useDataSelector,
  useSettingsSelector,
} from "@services";
import { WeaponSelect } from "@containers";
import {
  Group,
  CheckboxField,
  RangeField,
  SelectField,
  SelectItem,
  KeyInputField,
} from "@components";
import { TSettings, Weapon } from "@utils";
import { useStyles } from "./styles";

export const TriggerbotContent: React.FC = () => {
  const classes = useStyles();

  const settings = useSettingsSelector(selectSettings);
  const gameActiveWeapon = useDataSelector(selectActiveWeapon);

  const [activeWeapon, setActiveWeapon] =
    React.useState<Weapon>(gameActiveWeapon);

  const triggerFields = {
    enable: `triggerbot_${activeWeapon.sectionName}_enable` as keyof TSettings,
  };

  React.useEffect(() => {
    getActiveWeapon();
  }, []);

  React.useEffect(() => {
    if (
      gameActiveWeapon.isPistol ||
      gameActiveWeapon.isSMG ||
      gameActiveWeapon.isHeavy ||
      gameActiveWeapon.isShotgun ||
      gameActiveWeapon.isRifle ||
      gameActiveWeapon.isSnipers
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
              onChange={(v) =>
                updateValue({ name: "triggerbot_enable", value: v })
              }
            />
            {settings.triggerbot_enable ? (
              <React.Fragment>
                <CheckboxField
                  label="Flash check"
                  helperText="Check if you are blinded"
                  checked={settings.triggerbot_flash_check}
                  onChange={(v) =>
                    updateValue({ name: "triggerbot_flash_check", value: v })
                  }
                />
                <CheckboxField
                  label="Jump check"
                  helperText="Check if you are jumping"
                  checked={settings.triggerbot_jump_check}
                  onChange={(v) =>
                    updateValue({ name: "triggerbot_jump_check", value: v })
                  }
                />
                <CheckboxField
                  label="Friendly fire"
                  helperText="Aim if player is teammates"
                  checked={settings.triggerbot_friendly_fire}
                  onChange={(v) =>
                    updateValue({ name: "triggerbot_friendly_fire", value: v })
                  }
                />
                <RangeField
                  label={`Delay before: ${settings.triggerbot_delay_before_shoot}`}
                  helperText="Delay before shooting"
                  min={0}
                  max={2000}
                  step={10}
                  value={settings.triggerbot_delay_before_shoot}
                  onChange={(v) =>
                    updateValue({
                      name: "triggerbot_delay_before_shoot",
                      value: v,
                    })
                  }
                />
                <RangeField
                  label={`Delay after: ${settings.triggerbot_delay_after_shoot}`}
                  helperText="Delay after shooting"
                  min={0}
                  max={2000}
                  step={10}
                  value={settings.triggerbot_delay_after_shoot}
                  onChange={(v) =>
                    updateValue({
                      name: "triggerbot_delay_after_shoot",
                      value: v,
                    })
                  }
                />
                <SelectField
                  placeholder="Type"
                  helperText="Use key to activate aim"
                  value={settings.triggerbot_use_key ? "1" : "0"}
                  onChange={(v) =>
                    updateValue({
                      name: "triggerbot_use_key",
                      value: v === "1",
                    })
                  }
                >
                  <SelectItem value="0">Auto</SelectItem>
                  <SelectItem value="1">Key</SelectItem>
                </SelectField>
                {settings.triggerbot_use_key ? (
                  <KeyInputField
                    value={settings.triggerbot_key}
                    onChange={(v) =>
                      updateValue({ name: "triggerbot_key", value: v })
                    }
                  />
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
                onChange={(itemDI) =>
                  setActiveWeapon(new Weapon({ itemDI: +itemDI }))
                }
              />
              {activeWeapon.itemDI > 0 ? (
                <CheckboxField
                  label="Enable"
                  checked={settings[triggerFields.enable] as boolean}
                  onChange={(v) =>
                    updateValue({ name: triggerFields.enable, value: v })
                  }
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
