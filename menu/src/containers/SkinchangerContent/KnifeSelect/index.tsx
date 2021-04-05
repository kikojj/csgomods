import React from "react";

import { DataContext, SettingsContext } from "@contexts";
import { Group, SkinchangerItem } from "@components";

import { getWeaponName, ISkinchangerWeapon, ItemDefinitionIndex, SkinRarity, TeamNum, Weapon } from "@utils";
import BackIcon from "../images/BackIcon.svg";
import { useStyles } from "../styles";

export type KnifeSelectProps = {
  activeTeam?: TeamNum;
  setActiveTeam: React.Dispatch<React.SetStateAction<TeamNum | undefined>>;
  activeWeapon?: Weapon;
  setActiveWeapon: React.Dispatch<React.SetStateAction<Weapon | undefined>>;
};
export const KnifeSelect: React.FC<KnifeSelectProps> = ({ activeTeam, setActiveTeam, setActiveWeapon }) => {
  const classes = useStyles();

  const { settings, setSettings } = React.useContext(SettingsContext);
  const { defaultSkins, skins, fullForceUpdate } = React.useContext(DataContext);

  const knifes = [ItemDefinitionIndex.WeaponKnifeT, ItemDefinitionIndex.WeaponKnifeCT2];

  const models = Object.keys(defaultSkins)
    .filter((k) => {
      const itemDI = parseInt(k);
      const weapon = new Weapon({ itemDI });

      return (
        itemDI !== NaN &&
        weapon.isKnife() &&
        weapon.itemDI !== ItemDefinitionIndex.WeaponKnifeCT2 &&
        weapon.itemDI !== ItemDefinitionIndex.WeaponKnifeT &&
        (activeTeam === TeamNum.Terrorist
          ? itemDI !== ItemDefinitionIndex.WeaponKnifeCT2
          : itemDI !== ItemDefinitionIndex.WeaponKnifeT)
      );
    })
    .map((k) => parseInt(k));

  function applyModel(itemDI: ItemDefinitionIndex) {
    if (activeTeam && (activeTeam === TeamNum.Terrorist || activeTeam === TeamNum.CounterTerrorist)) {
      setSettings({
        ...settings,
        skinchanger_knives: {
          ...settings.skinchanger_knives,
          [activeTeam]: {
            ...settings.skinchanger_knives[activeTeam],
            itemDI,
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
        activeTeam ? (
          <div className={classes.title_back}>
            <img src={BackIcon} alt="<-" onClick={() => setActiveTeam(undefined)} />
            Models
          </div>
        ) : (
          "Knives"
        )
      }
    >
      <div className={classes.items_containers}>
        {!activeTeam ? (
          <React.Fragment>
            {knifes
              .filter((itemDI) => defaultSkins[itemDI])
              .map((itemDI, key) => {
                const knife = new Weapon({ itemDI });
                let image = defaultSkins[itemDI] as string;

                const knifeSettings: ISkinchangerWeapon | undefined =
                  settings.skinchanger_knives[
                    itemDI === ItemDefinitionIndex.WeaponKnifeT ? TeamNum.Terrorist : TeamNum.CounterTerrorist
                  ];

                if (knifeSettings) {
                  let skin = skins.find(
                    (s) => +s.paintKit === +knifeSettings.paint_kit && +s.weaponDI === +knifeSettings.item_di
                  );
                  if (skin) {
                    image = skin.image;
                  }
                }

                return (
                  <SkinchangerItem
                    key={key}
                    image={image}
                    name={knife.itemDI === ItemDefinitionIndex.WeaponKnifeCT2 ? "Knife CT" : "Knife T"}
                    rarity={SkinRarity.RARITY_ANCIENT}
                    onClick={() =>
                      setActiveTeam(
                        itemDI === ItemDefinitionIndex.WeaponKnifeT ? TeamNum.Terrorist : TeamNum.CounterTerrorist
                      )
                    }
                  />
                );
              })}
          </React.Fragment>
        ) : (
          [
            activeTeam === TeamNum.Terrorist ? ItemDefinitionIndex.WeaponKnifeT : ItemDefinitionIndex.WeaponKnifeCT2,
            ...models.sort((m1, m2) => (getWeaponName(m1) > getWeaponName(m2) ? 1 : -1)),
          ].map((itemDI, key) => {
            const model: Weapon = new Weapon({ itemDI });

            return (
              <SkinchangerItem
                key={key}
                name={
                  model.itemDI === ItemDefinitionIndex.WeaponKnifeT ||
                  model.itemDI === ItemDefinitionIndex.WeaponKnifeCT2
                    ? "Default"
                    : model.name
                }
                image={defaultSkins[model.itemDI]!}
                rarity={SkinRarity.RARITY_ANCIENT}
                onClick={() => {
                  if (
                    model.itemDI !== ItemDefinitionIndex.WeaponKnifeT &&
                    model.itemDI !== ItemDefinitionIndex.WeaponKnifeCT2
                  ) {
                    setActiveWeapon(new Weapon({ itemDI: model.itemDI }));
                    applyModel(model.itemDI);
                  }
                }}
              />
            );
          })
        )}
      </div>
    </Group>
  );
};
