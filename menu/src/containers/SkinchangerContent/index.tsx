import React from "react";

import { DataContext, SettingsContext } from "@contexts";
import { KnifeSelect } from "./KnifeSelect";
import { WeaponSelect } from "./WeaponSelect";
import { SkinSelect } from "./SkinSelect";
import { WeaponSettings } from "./WeaponSettings";

import { TeamNum, Weapon } from "@utils";
import { useStyles } from "./styles";

export const SkinchangerContent: React.FC = () => {
  const classes = useStyles();

  const { settings } = React.useContext(SettingsContext);
  const { activeWeapon: gameActiveWeapon, getActiveWeapon, team: gameActiveTeam } = React.useContext(DataContext);

  const [activeWeapon, setActiveWeapon] = React.useState<Weapon | undefined>(undefined);
  const [activeTeam, setActiveTeam] = React.useState<TeamNum | undefined>(undefined);

  React.useEffect(() => {
    getActiveWeapon();
  }, []);

  React.useEffect(() => {
    if (gameActiveWeapon.itemDI > 0 && gameActiveWeapon.isWeapon()) {
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

  return (
    <div>
      {/* <Group width={300} label="Skinchanger">
        <CheckboxField label="Enable" />
        <SelectField placeholder="Type">
          <SelectItem value="0">Weapons</SelectItem>
          <SelectItem value="1">Inventory</SelectItem>
        </SelectField>
      </Group> */}
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
    </div>
  );
};
