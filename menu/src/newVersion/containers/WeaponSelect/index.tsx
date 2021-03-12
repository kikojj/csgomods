import { Weapon, weaponNames } from "@utils";
import React from "react";
import { SelectField, SelectFieldProps, SelectItem } from "../../components";

export type WeaponSelectProps = {
  usePistols?: boolean;
  useSMGs?: boolean;
  useHeavies?: boolean;
  useShotguns?: boolean;
  useRifles?: boolean;
  useSnipers?: boolean;
  useKnives?: boolean;
  value?: string;
  onChnage?: (v: string) => void;
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
  onChnage,
}) => {
  const weapons = weaponNames
    .map((w) => new Weapon({ itemDI: w.idi }))
    .filter((weapon) => {
      return (
        (usePistols && weapon.isPistol()) ||
        (useSMGs && weapon.isSMG()) ||
        (useHeavies && weapon.isHeavy()) ||
        (useShotguns && weapon.isShotgun()) ||
        (useRifles && weapon.isRifle()) ||
        (useSnipers && weapon.isSnipers()) ||
        (useKnives && weapon.isKnife())
      );
    })
    .sort((w1, w2) => (w1.name > w2.name ? 1 : -1));

  return (
    <SelectField placeholder="Weapon" value={value} onChange={onChnage}>
      {weapons.map((weapon, key) => (
        <SelectItem key={key} value={weapon.itemDI.toString()}>
          {weapon.name}
        </SelectItem>
      ))}
    </SelectField>
  );
};
