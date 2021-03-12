import React from "react";

import { DataContext } from "../../../contexts";
import { Items } from "@containers";

import { IconButton } from "@material-ui/core";
import { ArrowBack as IconArrowBack } from "@material-ui/icons";

import { Skin, Weapon, TeamNum, getDefaultSkin } from "@utils";
import { useStyles } from "../styles";

export type TSkinsSelectProps = {
  activeTeam?: TeamNum;
  activeWeapon: Weapon;
  setActiveSkin: React.Dispatch<React.SetStateAction<Skin | undefined>>;
  onBack: () => void;
};
export const SkinsSelect: React.FC<TSkinsSelectProps> = ({ activeWeapon, setActiveSkin, onBack }) => {
  const classes = useStyles();

  const { skins, defaultSkins } = React.useContext(DataContext);

  return (
    <div className={classes.content + ` ${classes.content}-btn`}>
      <IconButton className={classes.btn_back} onClick={onBack} color="primary">
        <IconArrowBack />
      </IconButton>
      <Items
        className={classes.cards}
        data={[
          getDefaultSkin(activeWeapon.itemDI, defaultSkins[activeWeapon.itemDI] as string),
          ...skins
            .filter((skin) => +skin.weaponDI === +activeWeapon.itemDI)
            .sort((s1, s2) => (s1.name > s2.name ? 1 : -1)),
        ].map((skin) => ({
          image: skin.image,
          title: `${activeWeapon.name} | ${skin.name}`,
          onClick: () => {
            setActiveSkin(skin);
          },
        }))}
      />
    </div>
  );
};
