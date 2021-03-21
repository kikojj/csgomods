import React from "react";

import { DataContext, SettingsContext } from "@contexts";
import { QualitySelect } from "@containers";
import { Group, CheckboxField, RangeField, TextField, Button } from "@components";

import { DEFAULT_WEAPON_SETTINGS, ISkinchangerWeapon, TeamNum, Weapon } from "@utils";

export type WeaponSettingsProps = {
  activeTeam?: TeamNum;
  activeWeapon?: Weapon;
};
export const WeaponSettings: React.FC<WeaponSettingsProps> = ({ activeTeam, activeWeapon }) => {
  const { settings, updateValue } = React.useContext(SettingsContext);
  const { fullForceUpdate } = React.useContext(DataContext);

  let weaponSettings: ISkinchangerWeapon | undefined = undefined;
  if (activeTeam) {
    weaponSettings = settings.skinchanger_knives[activeTeam];
  }
  if (activeWeapon) {
    if (!activeWeapon.isKnife()) {
      weaponSettings = settings.skinchanger_weapons[activeWeapon.itemDI];
    }
  }

  const [props, setProps] = React.useState<ISkinchangerWeapon>({ ...DEFAULT_WEAPON_SETTINGS, ...weaponSettings });

  React.useEffect(() => {
    setProps({ ...DEFAULT_WEAPON_SETTINGS, ...weaponSettings });
  }, [weaponSettings]);

  function applyHandler() {
    if (activeWeapon) {
      if (activeWeapon.isKnife() && activeTeam) {
        updateValue("skinchanger_knives", {
          ...settings.skinchanger_knives,
          [activeTeam]: {
            ...weaponSettings,
            ...props,
          },
        });
        fullForceUpdate();
      } else if (!activeWeapon.isKnife()) {
        updateValue("skinchanger_weapons", {
          ...settings.skinchanger_weapons,
          [activeWeapon.itemDI]: {
            ...weaponSettings,
            ...props,
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
      <CheckboxField label="Enable" checked={props.enable} onChange={(v) => setProps({ ...props, enable: v })} />
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
              value={props.customName}
              onChange={(v) => setProps({ ...props, customName: v })}
            />
          </div>
          <div style={{ width: 280 }}>
            <QualitySelect marginTop={21} value={props.quality} onChnage={(v) => setProps({ ...props, quality: v })} />
            <CheckboxField
              marginTop={43}
              label="StatTrack"
              checked={props.statTrack >= 0}
              onChange={(v) => setProps({ ...props, statTrack: v ? 0 : -1 })}
            />
            {props.statTrack >= 0 ? (
              <TextField
                placeholder="StatTrack"
                value={props.statTrack.toString()}
                onChange={(v) => setProps({ ...props, statTrack: +v })}
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
