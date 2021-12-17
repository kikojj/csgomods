import React from "react";
import { SelectField, SelectItem } from "@components";
import { Weapon, weaponNames } from "@utils";

export type WeaponSelectProps = {
  usePistols?: boolean;
  useSMGs?: boolean;
  useHeavies?: boolean;
  useShotguns?: boolean;
  useRifles?: boolean;
  useSnipers?: boolean;
  useKnives?: boolean;
  value?: string;
  onChange?: (v: string) => void;
};
export const WeaponSelect: React.FC<WeaponSelectProps> = ({
  usePistols = true,
  useSMGs = true,
  useHeavies = true,
  useShotguns = true,
  useRifles = true,
  useSnipers = true,
  useKnives = false,
  value,
  onChange,
}) => {
  const weapons = weaponNames
    .map((w) => new Weapon({ itemDI: w.idi }))
    .filter((weapon) => {
      return (
        (usePistols && weapon.isPistol) ||
        (useSMGs && weapon.isSMG) ||
        (useHeavies && weapon.isHeavy) ||
        (useShotguns && weapon.isShotgun) ||
        (useRifles && weapon.isRifle) ||
        (useSnipers && weapon.isSnipers) ||
        (useKnives && weapon.isKnife)
      );
    })
    .sort((w1, w2) => (w1.name > w2.name ? 1 : -1));

  return (
    <SelectField placeholder="Weapon" value={value} onChange={onChange}>
      {weapons.map((weapon) => (
        <SelectItem key={weapon.itemDI} value={weapon.itemDI.toString()}>
          {weapon.name}
        </SelectItem>
      ))}
    </SelectField>
  );
};
