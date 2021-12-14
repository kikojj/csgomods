import React from "react";
import {
  fullForceUpdate,
  selectSettings,
  useSettingsSelector,
  updateValue,
} from "@services";
import { QualitySelect } from "@containers";
import {
  Group,
  CheckboxField,
  RangeField,
  TextField,
  Button,
} from "@components";
import {
  DEFAULT_WEAPON_SETTINGS,
  ISkinchangerWeapon,
  TeamNum,
  Weapon,
} from "@utils";

export type WeaponSettingsProps = {
  activeTeam?: TeamNum;
  activeWeapon?: Weapon;
};
export const WeaponSettings: React.FC<WeaponSettingsProps> = ({
  activeTeam,
  activeWeapon,
}) => {
  const settings = useSettingsSelector(selectSettings);

  let weaponSettings: ISkinchangerWeapon | undefined = undefined;
  if (activeTeam) {
    weaponSettings = settings.skinchanger_knives[activeTeam];
  }
  if (activeWeapon) {
    if (!activeWeapon.isKnife()) {
      weaponSettings = settings.skinchanger_weapons[activeWeapon.itemDI];
    }
  }

  const [props, setProps] = React.useState<ISkinchangerWeapon>({
    ...DEFAULT_WEAPON_SETTINGS,
    ...weaponSettings,
  });

  React.useEffect(() => {
    setProps({ ...DEFAULT_WEAPON_SETTINGS, ...weaponSettings });
  }, [weaponSettings]);

  function applyHandler() {
    if (activeWeapon) {
      if (activeWeapon.isKnife() && activeTeam) {
        updateValue({
          name: "skinchanger_knives",
          value: {
            ...settings.skinchanger_knives,
            [activeTeam]: {
              ...weaponSettings,
              ...props,
            },
          },
        });
        fullForceUpdate();
      } else if (!activeWeapon.isKnife()) {
        updateValue({
          name: "skinchanger_weapons",
          value: {
            ...settings.skinchanger_weapons,
            [activeWeapon.itemDI]: {
              ...weaponSettings,
              ...props,
            },
          },
        });
        fullForceUpdate();
      }
    }
  }

  if (!activeTeam && !activeWeapon) {
    return <React.Fragment />;
  }

  return (
    <Group width="100%" label="Weapon settings">
      <CheckboxField
        label="Enable"
        checked={props.enable}
        onChange={(v) => setProps({ ...props, enable: v })}
      />
      {props.enable ? (
        <div style={{ display: "flex", justifyContent: "space-between" }}>
          <div style={{ width: 280 }}>
            <RangeField
              label={`Wear: ${props.wear.toFixed(2)}`}
              min={0}
              max={1}
              step={0.01}
              value={parseFloat(props.wear.toFixed(2))}
              onChange={(v) => setProps({ ...props, wear: v })}
            />
            <RangeField
              label={`Seed: ${props.seed}`}
              min={-1}
              max={1000}
              step={1}
              value={props.seed}
              onChange={(v) => setProps({ ...props, seed: v })}
            />
            <TextField
              placeholder="Custom name"
              value={props.custom_name}
              onChange={(v) => setProps({ ...props, custom_name: v })}
            />
          </div>
          <div style={{ width: 280 }}>
            <QualitySelect
              marginTop={21}
              value={props.quality}
              onChnage={(v) => setProps({ ...props, quality: v })}
            />
            <CheckboxField
              marginTop={43}
              label="StatTrack"
              checked={props.stat_track >= 0}
              onChange={(v) => setProps({ ...props, stat_track: v ? 0 : -1 })}
            />
            {props.stat_track >= 0 ? (
              <TextField
                placeholder="StatTrack"
                value={props.stat_track.toString()}
                onChange={(v) => setProps({ ...props, stat_track: +v })}
              />
            ) : (
              ""
            )}
          </div>
        </div>
      ) : (
        ""
      )}

      <Button onClick={applyHandler}>Apply</Button>
    </Group>
  );
};
