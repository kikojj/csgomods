import React from "react";

import { DataContext, SettingsContext } from "@contexts";
import { Group, SkinchangerItem } from "@components";

import { getWeaponName, SkinRarity, unique, Weapon } from "@utils";
import { useStyles } from "../styles";

export type WeaponSelectProps = {
  setActiveWeapon: React.Dispatch<React.SetStateAction<Weapon | undefined>>;
};
export const WeaponSelect: React.FC<WeaponSelectProps> = ({ setActiveWeapon }) => {
  const classes = useStyles();

  const { settings } = React.useContext(SettingsContext);
  const { skins, defaultSkins } = React.useContext(DataContext);

  const weapons = skins
    .map((s) => {
      return s.weapon.itemDI;
    })
    .filter(unique)
    .filter((itemDI) => {
      const weapon = new Weapon({ itemDI });

      return (defaultSkins[itemDI] || defaultSkins[weapon.name]) && !weapon.isKnife();
    })
    .sort((itemDI1, itemDI2) => (getWeaponName(itemDI1) > getWeaponName(itemDI2) ? 1 : -1));

  return (
    <Group marginTop={35} width="100%" label="Weapons">
      <div className={classes.items_containers}>
        {weapons.map((itemDI, key) => {
          const weapon = new Weapon({ itemDI });
          let image = defaultSkins[itemDI] as string;
          let rarity = SkinRarity.RARITY_COMMON;

          if (settings.skinchanger_weapons[itemDI]) {
            let skin = skins.find(
              (s) =>
                +s.paintKit === +settings.skinchanger_weapons[itemDI]!.paintKit! &&
                settings.skinchanger_weapons[itemDI]?.enable
            );
            if (skin) {
              image = skin.image;
              rarity = skin.rarityID;
            }
          }

          return (
            <SkinchangerItem
              key={key}
              image={image}
              name={weapon.name}
              rarity={rarity}
              onClick={() => setActiveWeapon(new Weapon({ itemDI: weapon.itemDI }))}
            />
          );
        })}
      </div>
    </Group>
  );
};
