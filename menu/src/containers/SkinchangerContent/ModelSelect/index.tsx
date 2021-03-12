import React from "react";

import { DataContext, SettingsContext } from "../../../contexts";
import { Items } from "@containers";

import { ArrowBack as IconArrowBack } from "@material-ui/icons";
import { IconButton } from "@material-ui/core";

import { ItemDefinitionIndex, Weapon, TeamNum, getDefaultSkin, Skin, getWeaponName } from "@utils";
import { useStyles } from "../styles";

export type ModelSelectProps = {
  activeTeam: TeamNum;
  setActiveWeapon: React.Dispatch<React.SetStateAction<Weapon | undefined>>;
  setActiveSkin: React.Dispatch<React.SetStateAction<Skin | undefined>>;

  onBack: () => void;
};
export const ModelSelect: React.FC<ModelSelectProps> = ({ activeTeam, setActiveWeapon, setActiveSkin, onBack }) => {
  const classes = useStyles();

  const { setSettings, settings } = React.useContext(SettingsContext);
  const { defaultSkins } = React.useContext(DataContext);

  const models = Object.keys(defaultSkins)
    .filter((k) => {
      const itemDI = parseInt(k);
      const weapon = new Weapon({ itemDI });

      return (
        itemDI !== NaN &&
        weapon.isKnife() &&
        weapon.itemDI !== ItemDefinitionIndex.WEAPON_KnifeCT2 &&
        weapon.itemDI !== ItemDefinitionIndex.WEAPON_KnifeT &&
        (activeTeam === TeamNum.TERRORIST
          ? itemDI !== ItemDefinitionIndex.WEAPON_KnifeCT2
          : itemDI !== ItemDefinitionIndex.WEAPON_KnifeT)
      );
    })
    .map((k) => parseInt(k));

  return (
    <div className={classes.content + ` ${classes.content}-btn`}>
      <IconButton className={classes.btn_back} onClick={onBack} color="primary">
        <IconArrowBack />
      </IconButton>
      <Items
        className={classes.cards}
        data={[
          activeTeam === TeamNum.TERRORIST ? ItemDefinitionIndex.WEAPON_KnifeT : ItemDefinitionIndex.WEAPON_KnifeCT2,
          ...models.sort((m1, m2) => (getWeaponName(m1) > getWeaponName(m2) ? 1 : -1)),
        ].map((itemDI) => {
          const model: Weapon = new Weapon({ itemDI });

          return {
            title:
              model.itemDI === ItemDefinitionIndex.WEAPON_KnifeT || model.itemDI === ItemDefinitionIndex.WEAPON_KnifeCT2
                ? "Default"
                : model.name,
            image: defaultSkins[model.itemDI]!,
            onClick: () => {
              if (model.itemDI === ItemDefinitionIndex.WEAPON_KnifeT) {
                setActiveSkin(
                  getDefaultSkin(
                    ItemDefinitionIndex.WEAPON_KnifeT,
                    defaultSkins[ItemDefinitionIndex.WEAPON_KnifeT] as string
                  )
                );
              } else if (model.itemDI === ItemDefinitionIndex.WEAPON_KnifeCT2) {
                setActiveSkin(
                  getDefaultSkin(
                    ItemDefinitionIndex.WEAPON_KnifeCT2,
                    defaultSkins[ItemDefinitionIndex.WEAPON_KnifeCT2] as string
                  )
                );
              }
              setActiveWeapon(model);
            },
          };
        })}
      />
    </div>
  );
};
