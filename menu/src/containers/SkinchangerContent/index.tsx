import React from "react";

import { DataContext, SettingsContext } from "@contexts";
import { LoadingContent } from "@containers";
import { Group, CheckboxField } from "@components";

import { KnifeSelect } from "./KnifeSelect";
import { WeaponSelect } from "./WeaponSelect";
import { SkinSelect } from "./SkinSelect";
import { WeaponSettings } from "./WeaponSettings";

import { TeamNum, Weapon } from "@utils";
import { useStyles } from "./styles";

export const SkinchangerContent: React.FC = () => {
  const classes = useStyles();

  const { settings, updateValue } = React.useContext(SettingsContext);
  const {
    activeWeapon: gameActiveWeapon,
    getActiveWeapon,
    team: gameActiveTeam,
    skins,
    fullForceUpdate,
  } = React.useContext(DataContext);

  const [activeWeapon, setActiveWeapon] = React.useState<Weapon | undefined>(undefined);
  const [activeTeam, setActiveTeam] = React.useState<TeamNum | undefined>(undefined);

  React.useEffect(() => {
    getActiveWeapon();
  }, []);

  React.useEffect(() => {
    if (settings.skinchanger_enable && gameActiveWeapon.itemDI > 0 && gameActiveWeapon.isWeapon()) {
      setActiveWeapon(new Weapon({ itemDI: gameActiveWeapon.itemDI }));

      if (gameActiveWeapon.isKnife()) {
        if (gameActiveTeam >= TeamNum.TERRORIST) {
          setActiveTeam(gameActiveTeam);
        }
      } else {
        setActiveTeam(undefined);
      }
    } else {
      setActiveWeapon(undefined);
      setActiveTeam(undefined);
    }
  }, [gameActiveWeapon, gameActiveTeam]);

  if (skins.length <= 0) {
    return <LoadingContent />;
  }

  return (
    <div>
      {!activeWeapon && !activeTeam ? (
        <Group width={300} label="Skinchanger">
          <CheckboxField
            label="Enable"
            checked={settings.skinchanger_enable}
            onChange={(v) => {
              updateValue("skinchanger_enable", v);
              fullForceUpdate();
            }}
          />
          {/* <SelectField placeholder="Type">
          <SelectItem value="0">Weapons</SelectItem>
          <SelectItem value="1">Inventory</SelectItem>
        </SelectField> */}
        </Group>
      ) : (
        ""
      )}
      {settings.skinchanger_enable ? (
        <React.Fragment>
          <WeaponSettings activeTeam={activeTeam} activeWeapon={activeWeapon} />
          {!activeWeapon && !activeTeam ? (
            <React.Fragment>
              <KnifeSelect
                activeTeam={activeTeam}
                setActiveTeam={setActiveTeam}
                activeWeapon={activeWeapon}
                setActiveWeapon={setActiveWeapon}
              />
              <WeaponSelect setActiveWeapon={setActiveWeapon} />
            </React.Fragment>
          ) : !activeWeapon ? (
            <KnifeSelect
              activeTeam={activeTeam}
              setActiveTeam={setActiveTeam}
              activeWeapon={activeWeapon}
              setActiveWeapon={setActiveWeapon}
            />
          ) : (
            <SkinSelect activeTeam={activeTeam} activeWeapon={activeWeapon} setActiveWeapon={setActiveWeapon} />
          )}
        </React.Fragment>
      ) : (
        ""
      )}
    </div>
  );
};
