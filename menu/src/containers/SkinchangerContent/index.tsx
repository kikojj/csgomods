import React from "react";

import { Group, SectionTitle } from "@components";
import { WindowContent } from "../Window/Content";
import { WeaponsSelect } from "./WeaponsSelect";
import { SkinsSelect } from "./SkinSelect";
import { SkinView } from "./SkinView";
import { KnifeSelect } from "./KnifeSelect";
import { ModelSelect } from "./ModelSelect";

import { Skin, Weapon, TeamNum, ItemDefinitionIndex, ISkinchangerWeapon, getDefaultSkin } from "@utils";
import { useStyles } from "./styles";
import { DataContext, SettingsContext } from "../../contexts";

export const SkinchangerContent = () => {
  const classes = useStyles();

  const { settings } = React.useContext(SettingsContext);
  const { activeWeapon: gameActiveWeapon, skins, team, defaultSkins } = React.useContext(DataContext);

  const [activeTeam, setActiveTeam] = React.useState<TeamNum | undefined>();
  const [activeWeapon, setActiveWeapon] = React.useState<Weapon | undefined>();
  const [activeSkin, setActiveSkin] = React.useState<Skin | undefined>();

  React.useEffect(() => {
    if (gameActiveWeapon.isKnife() && (team === TeamNum.TERRORIST || team === TeamNum.COUNTER_TERRORIST)) {
      setActiveTeam(team);
    } else {
      setActiveTeam(undefined);
    }

    if (gameActiveWeapon.itemDI !== ItemDefinitionIndex.INVALID_ITEM_DI && gameActiveWeapon.name !== "") {
      setActiveWeapon(new Weapon({ itemDI: gameActiveWeapon.itemDI }));

      let weaponSettings: ISkinchangerWeapon | undefined = undefined;

      if (gameActiveWeapon.isKnife() && (team === TeamNum.TERRORIST || team === TeamNum.COUNTER_TERRORIST)) {
        weaponSettings = settings.skinchanger_knifes[team];
      } else {
        weaponSettings = settings.skinchanger_weapons[gameActiveWeapon.itemDI];
      }

      if (weaponSettings && weaponSettings.enable && weaponSettings.paintKit > 0) {
        const skin = skins.find(
          (s) =>
            s.weaponDI === (gameActiveWeapon.isKnife() ? weaponSettings : gameActiveWeapon)!.itemDI &&
            s.paintKit === weaponSettings!.paintKit
        );

        if (skin) {
          setActiveSkin(skin);
        } else {
          setActiveSkin(undefined);
        }
      } else if (weaponSettings && weaponSettings.enable && weaponSettings.paintKit === 0) {
        setActiveSkin(getDefaultSkin(gameActiveWeapon.itemDI, defaultSkins[gameActiveWeapon.itemDI] as string));
      } else {
        setActiveSkin(undefined);
      }
    } else {
      setActiveWeapon(undefined);
      setActiveSkin(undefined);
    }
  }, [gameActiveWeapon, skins, team]);

  const Title: React.FC = () => <SectionTitle text="Skinchanger" />;

  if (!activeWeapon && !activeTeam) {
    return (
      <WindowContent key={0}>
        <Title />
        <Group title="Knifes" marginTop={28}>
          <KnifeSelect setActiveTeam={setActiveTeam} />
        </Group>
        <Group title="Weapons" marginTop={28}>
          <WeaponsSelect setActiveWeapon={setActiveWeapon} />
        </Group>
      </WindowContent>
    );
  }

  if (!activeWeapon) {
    return (
      <WindowContent key={1}>
        <Title />
        <ModelSelect
          activeTeam={activeTeam!}
          setActiveWeapon={setActiveWeapon}
          setActiveSkin={setActiveSkin}
          onBack={() => setActiveTeam(undefined)}
        />
      </WindowContent>
    );
  }

  if (!activeSkin) {
    return (
      <WindowContent key={2}>
        <Title />
        <SkinsSelect
          activeTeam={activeTeam}
          activeWeapon={activeWeapon}
          setActiveSkin={setActiveSkin}
          onBack={() => setActiveWeapon(undefined)}
        />
      </WindowContent>
    );
  }

  return (
    <WindowContent key={3}>
      <Title />
      <SkinView
        activeTeam={activeTeam}
        activeSkin={activeSkin}
        activeWeapon={activeWeapon}
        onBack={() => {
          if (
            activeSkin.weaponDI === ItemDefinitionIndex.WEAPON_KnifeCT2 ||
            activeSkin.weaponDI === ItemDefinitionIndex.WEAPON_KnifeT
          ) {
            setActiveWeapon(undefined);
          }
          setActiveSkin(undefined);
        }}
      />
    </WindowContent>
  );
};
