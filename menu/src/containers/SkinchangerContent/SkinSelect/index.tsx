import React from "react";

import { DataContext, SettingsContext } from "@contexts";
import { Group, SkinchangerItem } from "@components";

import { getDefaultSkin, ISkinchangerWeapon, TeamNum, Weapon } from "@utils";
import BackIcon from "../images/BackIcon.svg";
import { useStyles } from "../styles";

export type SkinSelectProps = {
  activeTeam?: TeamNum;
  activeWeapon: Weapon;
  setActiveWeapon: React.Dispatch<React.SetStateAction<Weapon | undefined>>;
};
export const SkinSelect: React.FC<SkinSelectProps> = ({ activeTeam, activeWeapon, setActiveWeapon }) => {
  const classes = useStyles();

  const { settings, setSettings } = React.useContext(SettingsContext);
  const { skins, defaultSkins, fullForceUpdate } = React.useContext(DataContext);

  const weaponSkins = [
    getDefaultSkin(activeWeapon.itemDI, defaultSkins[activeWeapon.itemDI] as string),
    ...skins.filter((skin) => +skin.weaponDI === +activeWeapon.itemDI).sort((s1, s2) => (s1.name > s2.name ? 1 : -1)),
  ];

  let weaponSettings: ISkinchangerWeapon | undefined = undefined;
  if (activeWeapon) {
    if (activeWeapon.isKnife() && activeTeam) {
      weaponSettings = settings.skinchanger_knives[activeTeam];
    } else {
      weaponSettings = settings.skinchanger_weapons[activeWeapon.itemDI];
    }
  }

  function applyPaintKit(paintKit: number) {
    if (activeWeapon.isKnife()) {
      if (activeTeam && (activeTeam === TeamNum.TERRORIST || activeTeam === TeamNum.COUNTER_TERRORIST)) {
        setSettings({
          ...settings,
          skinchanger_knives: {
            ...settings.skinchanger_knives,
            [activeTeam]: {
              ...settings.skinchanger_knives[activeTeam],
              paintKit,
            },
          },
        });
        fullForceUpdate();
      }
    } else {
      setSettings({
        ...settings,
        skinchanger_weapons: {
          ...settings.skinchanger_weapons,
          [activeWeapon.itemDI]: {
            ...settings.skinchanger_weapons[activeWeapon.itemDI],
            paintKit,
          },
        },
      });
      fullForceUpdate();
    }
  }

  return (
    <Group
      marginTop={35}
      width="100%"
      label={
        <div className={classes.title_back}>
          <img src={BackIcon} alt="<-" onClick={() => setActiveWeapon(undefined)} />
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
            active={weaponSettings && weaponSettings?.paintKit === skin.paintKit}
            onClick={() => applyPaintKit(skin.paintKit)}
          />
        ))}
      </div>
    </Group>
  );
};
