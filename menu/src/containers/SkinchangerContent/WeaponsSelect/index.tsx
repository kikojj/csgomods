import React from "react";

import { DataContext, SettingsContext } from "../../../contexts";
import { Items } from "@containers";
import { getWeaponName, unique, Weapon } from "@utils";

import { useStyles } from "../styles";

export type WeaponsSelectProps = {
  setActiveWeapon: React.Dispatch<React.SetStateAction<Weapon | undefined>>;
};
export const WeaponsSelect: React.FC<WeaponsSelectProps> = ({ setActiveWeapon }) => {
  const classes = useStyles();

  const { settings } = React.useContext(SettingsContext);
  const { skins, defaultSkins } = React.useContext(DataContext);

  const weapons = skins
    .map((s) => s.weapon.itemDI)
    .filter(unique)
    .filter((itemDI) => {
      const weapon = new Weapon({ itemDI });

      return (defaultSkins[itemDI] || defaultSkins[weapon.name]) && !weapon.isKnife();
    })
    .sort((itemDI1, itemDI2) => (getWeaponName(itemDI1) > getWeaponName(itemDI2) ? 1 : -1));

  return (
    <div className={classes.content}>
      <Items
        className={classes.cards}
        data={weapons.map((itemDI) => {
          const weapon = new Weapon({ itemDI });
          let image = defaultSkins[itemDI] as string;

          if (settings.skinchanger_weapons[itemDI]) {
            let skin = skins.find(
              (s) =>
                +s.paintKit === +settings.skinchanger_weapons[itemDI]!.paintKit! &&
                settings.skinchanger_weapons[itemDI]?.enable
            );
            if (skin) {
              image = skin.image;
            }
          }

          return {
            title: weapon.name,
            image: image,
            onClick: () => setActiveWeapon(weapon),
          };
        })}
      />
    </div>
  );
};
