import React from "react";

import { MenuItem, Select } from "@material-ui/core";

import { getWeaponName, ItemDefinitionIndex, TMargin, Weapon, weaponNames } from "@utils";
import { useStyles } from "./styles";

const defaultWeapons = weaponNames
  .filter((w) => {
    const weapon = new Weapon({ itemDI: w.idi });
    return (
      weapon.isPistol() ||
      weapon.isSMG() ||
      weapon.isHeavy() ||
      weapon.isShotgun() ||
      weapon.isRifle() ||
      weapon.isSnipers()
    );
  })
  .map((w) => new Weapon({ itemDI: w.idi }))
  .sort((w1, w2) => (w1.name > w2.name ? 1 : -1));

export type WeaponSelectProps = {
  className?: string;
  marginTop?: TMargin;
  weapons?: Weapon[];
  value: number;
  onChange: (v: number) => void;
};
export const WeaponSelect: React.FC<WeaponSelectProps> = ({
  className,
  marginTop,
  weapons = defaultWeapons,
  value,
  onChange,
}) => {
  const classes = useStyles();
  return (
    <div className={className} style={{ marginTop }}>
      <Select
        className={classes.select}
        value={value}
        onChange={(e, c) => onChange && onChange(e.target.value as number)}
        defaultValue={ItemDefinitionIndex.INVALID_ITEM_DI}
      >
        <MenuItem value={ItemDefinitionIndex.INVALID_ITEM_DI}>
          {getWeaponName(ItemDefinitionIndex.INVALID_ITEM_DI)}
        </MenuItem>
        {weapons.map((weapon, key) => (
          <MenuItem className={classes.select_item} key={key} value={weapon.itemDI}>
            {weapon.name}
          </MenuItem>
        ))}
      </Select>
    </div>
  );
};
