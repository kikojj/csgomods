import React from "react";
import {
  applyKnifePaintKit,
  applyWeaponPaintKit,
  fullForceUpdate,
  selectDefaultSkins,
  selectSettings,
  selectSkins,
  useDataSelector,
  useSettingsSelector,
} from "@services";
import { Group, SkinchangerItem } from "@components";
import { getDefaultSkin, ISkinchangerWeapon, TeamNum, Weapon } from "@utils";
import BackIcon from "../images/BackIcon.svg";
import { useStyles } from "../styles";

export type SkinSelectProps = {
  activeTeam?: TeamNum;
  activeWeapon: Weapon;
  setActiveWeapon: React.Dispatch<React.SetStateAction<Weapon | undefined>>;
};
export const SkinSelect: React.FC<SkinSelectProps> = ({
  activeTeam,
  activeWeapon,
  setActiveWeapon,
}) => {
  const classes = useStyles();

  const skins = useDataSelector(selectSkins);
  const settings = useSettingsSelector(selectSettings);
  const defaultSkins = useDataSelector(selectDefaultSkins);

  const weaponSkins = [
    getDefaultSkin(
      activeWeapon.itemDI,
      defaultSkins[activeWeapon.itemDI] as string
    ),
    ...skins
      .filter((skin) => +skin.weaponDI === +activeWeapon.itemDI)
      .sort((s1, s2) => (s1.name > s2.name ? 1 : -1)),
  ];

  let weaponSettings: ISkinchangerWeapon | undefined = undefined;
  if (activeWeapon) {
    if (activeWeapon.isKnife && activeTeam) {
      weaponSettings = settings.skinchanger_knives[activeTeam];
    } else {
      weaponSettings = settings.skinchanger_weapons[activeWeapon.itemDI];
    }
  }

  function applyPaintKit(paintKit: number) {
    if (activeWeapon.isKnife) {
      if (
        activeTeam &&
        (activeTeam === TeamNum.Terrorist ||
          activeTeam === TeamNum.CounterTerrorist)
      ) {
        applyKnifePaintKit({ activeTeam, paintKit });
        fullForceUpdate();
      }
    } else {
      applyWeaponPaintKit({ itemDI: activeWeapon.itemDI, paintKit });
      fullForceUpdate();
    }
  }

  return (
    <Group
      marginTop={35}
      width="100%"
      label={
        <div className={classes.title_back}>
          <img
            src={BackIcon}
            alt="<-"
            onClick={() => setActiveWeapon(undefined)}
          />
          Skins
        </div>
      }
    >
      <div className={classes.items_containers}>
        {weaponSkins.map((skin, key) => (
          <SkinchangerItem
            key={key}
            image={skin.image}
            name={`${activeWeapon.name} | ${skin.name}`}
            rarity={skin.rarityID}
            active={
              weaponSettings && weaponSettings?.paint_kit === skin.paintKit
            }
            onClick={() => applyPaintKit(skin.paintKit)}
          />
        ))}
      </div>
    </Group>
  );
};
