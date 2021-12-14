import React from "react";
import {
  fullForceUpdate,
  getActiveWeapon,
  selectActiveWeapon,
  selectSettings,
  selectSkins,
  selectTeam,
  updateValue,
  useDataSelector,
  useSettingsSelector,
} from "@services";
import { LoadingContent } from "@containers";
import { Group, CheckboxField } from "@components";
import { TeamNum, Weapon } from "@utils";
import { KnifeSelect } from "./KnifeSelect";
import { WeaponSelect } from "./WeaponSelect";
import { SkinSelect } from "./SkinSelect";
import { WeaponSettings } from "./WeaponSettings";

export const SkinchangerContent: React.FC = () => {
  const skins = useDataSelector(selectSkins);
  const gameActiveTeam = useDataSelector(selectTeam);
  const settings = useSettingsSelector(selectSettings);
  const gameActiveWeapon = useDataSelector(selectActiveWeapon);

  const [activeWeapon, setActiveWeapon] = React.useState<Weapon | undefined>(
    undefined
  );
  const [activeTeam, setActiveTeam] = React.useState<TeamNum | undefined>(
    undefined
  );

  React.useEffect(() => {
    getActiveWeapon();
  }, []);

  React.useEffect(() => {
    if (
      settings.skinchanger_enable &&
      gameActiveWeapon.itemDI > 0 &&
      gameActiveWeapon.isWeapon()
    ) {
      setActiveWeapon(new Weapon({ itemDI: gameActiveWeapon.itemDI }));

      if (gameActiveWeapon.isKnife()) {
        if (
          gameActiveTeam === TeamNum.Terrorist ||
          gameActiveTeam === TeamNum.CounterTerrorist
        ) {
          setActiveTeam(gameActiveTeam);
        }
      } else {
        setActiveTeam(undefined);
      }
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
              updateValue({ name: "skinchanger_enable", value: v });
              fullForceUpdate();
            }}
          />
          {/*
            TODO: Add inventory feature: we cant store in in local storage, fox example

            <SelectField placeholder="Type">
            <SelectItem value="0">Weapons</SelectItem>
            <SelectItem value="1">Inventory</SelectItem>
          </SelectField>
          */}
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
            <SkinSelect
              activeTeam={activeTeam}
              activeWeapon={activeWeapon}
              setActiveWeapon={setActiveWeapon}
            />
          )}
        </React.Fragment>
      ) : (
        ""
      )}
    </div>
  );
};
