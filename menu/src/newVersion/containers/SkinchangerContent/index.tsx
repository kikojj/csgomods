import React from "react";

import {
  Group,
  CheckboxField,
  FiltersField,
  RangeField,
  SelectField,
  SelectItem,
  ColorPickerField,
  TextField,
  Button,
} from "../../components";
import { QualitySelect } from "../";
import { useStyles } from "./styles";
import { DataContext, SettingsContext } from "../../../contexts";
import { DEFAULT_WEAPON_SETTINGS, EntityQuality, ISkinchangerWeapon, TeamNum, Weapon } from "@utils";

export const SkinchangerContent: React.FC = () => {
  const classes = useStyles();

  const { settings, updateValue } = React.useContext(SettingsContext);
  const { activeWeapon: gameActiveWeapon, getActiveWeapon, team: gameActiveTeam, fullForceUpdate } = React.useContext(
    DataContext
  );

  const [activeWeapon, setActiveWeapon] = React.useState<Weapon>(gameActiveWeapon);
  const [type, setType] = React.useState<number>(0);
  const [activeTeam, setActiveTeam] = React.useState<TeamNum>(gameActiveTeam);

  const weaponSettings = activeWeapon.isKnife()
    ? settings.skinchanger_knifes[activeTeam]
    : settings.skinchanger_weapons[activeWeapon.itemDI]
    ? settings.skinchanger_weapons[activeWeapon.itemDI]
    : undefined;

  const [props, setProps] = React.useState<ISkinchangerWeapon>({ ...DEFAULT_WEAPON_SETTINGS, ...weaponSettings });

  function applyHandler() {
    if (activeWeapon.isKnife() && activeTeam) {
      updateValue("skinchanger_knifes", {
        ...settings.skinchanger_knifes,
        [activeTeam]: {
          ...weaponSettings,
          ...props,
          itemDI: activeWeapon.itemDI,
        },
      });
    } else if (!activeWeapon.isKnife()) {
      updateValue("skinchanger_weapons", {
        ...settings.skinchanger_weapons,
        [activeWeapon.itemDI]: {
          ...weaponSettings,
          ...props,
        },
      });
    }
    fullForceUpdate();
  }

  return (
    <div className={classes.container}>
      <div>
        <Group width={300} label="Skinchanger">
          {/* <CheckboxField label="Enable" /> */}
          <SelectField placeholder="Type" value={type.toString()} onChange={(v) => setType(+v)}>
            <SelectItem value="0">Weapons</SelectItem>
            <SelectItem value="1">Inventory</SelectItem>
          </SelectField>
        </Group>
        {weaponSettings && weaponSettings.paintKit > 0 ? (
          <Group marginTop={35} width={300} label="Weapon settings">
            <CheckboxField label="Enable" checked={props.enable} onChange={(v) => setProps({ ...props, enable: v })} />
            <RangeField
              label={`Wear: ${props.wear}`}
              min={0}
              max={1}
              step={0.1}
              value={props.wear}
              onChange={(v) => setProps({ ...props, wear: v })}
            />
            <RangeField
              label={`Seed: ${props.seed}`}
              min={0}
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
            <QualitySelect value={props.quality} onChnage={(v) => setProps({ ...props, quality: v })} />
            <CheckboxField
              label="StatTrack"
              checked={props.statTrack >= 0}
              onChange={(v) => setProps({ ...props, statTrack: v ? 0 : -1 })}
            />
            <TextField
              placeholder="StatTrack"
              value={props.statTrack.toString()}
              onChange={(v) => setProps({ ...props, statTrack: +v })}
            />
            <Button onClick={applyHandler}>Apply</Button>
          </Group>
        ) : (
          ""
        )}
      </div>
      <div style={{ flex: 1 }}>
        <Group marginLeft={35} width="calc(100% - 35px)" label="Knives"></Group>
        <Group marginTop={35} marginLeft={35} width="calc(100% - 35px)" label="Weapons"></Group>
      </div>
    </div>
  );
};
