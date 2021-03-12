import React from "react";

import { DataContext, SettingsContext } from "../../../contexts";
import { Items } from "@containers";

import { ItemDefinitionIndex, Weapon, ISkinchangerWeapon, TeamNum } from "@utils";
import { useStyles } from "../styles";

export type KnifeSelectProps = {
  setActiveTeam: React.Dispatch<React.SetStateAction<TeamNum | undefined>>;
};
export const KnifeSelect: React.FC<KnifeSelectProps> = ({ setActiveTeam }) => {
  const classes = useStyles();

  const { settings } = React.useContext(SettingsContext);
  const { skins, defaultSkins } = React.useContext(DataContext);

  const knifes = [ItemDefinitionIndex.WEAPON_KnifeT, ItemDefinitionIndex.WEAPON_KnifeCT2];

  return (
    <div className={classes.content}>
      <Items
        className={classes.cards}
        data={knifes
          .filter((itemDI) => defaultSkins[itemDI])
          .map((itemDI) => {
            const knife = new Weapon({ itemDI });
            let image = defaultSkins[itemDI] as string;

            const knifeSettings: ISkinchangerWeapon | undefined =
              settings.skinchanger_knifes[
                itemDI === ItemDefinitionIndex.WEAPON_KnifeT ? TeamNum.TERRORIST : TeamNum.COUNTER_TERRORIST
              ];

            if (knifeSettings) {
              let skin = skins.find(
                (s) => +s.paintKit === +knifeSettings.paintKit && +s.weaponDI === +knifeSettings.itemDI
              );
              if (skin) {
                image = skin.image;
              }
            }

            return {
              title: knife.itemDI === ItemDefinitionIndex.WEAPON_KnifeCT2 ? "CT Knife" : "T Knife",
              image: image,
              onClick: () =>
                setActiveTeam(
                  itemDI === ItemDefinitionIndex.WEAPON_KnifeT ? TeamNum.TERRORIST : TeamNum.COUNTER_TERRORIST
                ),
            };
          })}
      />
    </div>
  );
};
