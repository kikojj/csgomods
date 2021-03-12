import React from "react";

import { DataContext, SettingsContext } from "../../../contexts";

import {
  IconButton,
  Typography,
  Accordion,
  AccordionSummary,
  AccordionDetails,
  TextField,
  Button,
} from "@material-ui/core";
import { ArrowBack as IconArrowBack, ExpandMore as ExpandMoreIcon } from "@material-ui/icons";
import { ItemCard, Switch, QualitySelect } from "@components";

import { Skin, ISkinchangerWeapon, TeamNum, Weapon, DEFAULT_WEAPON_SETTINGS, EntityQuality } from "@utils";
import { useStyles } from "../styles";

export type TSkinViewProps = {
  activeTeam?: TeamNum;
  activeSkin: Skin;
  activeWeapon: Weapon;
  onBack: () => void;
};
export const SkinView: React.FC<TSkinViewProps> = ({ activeTeam, activeSkin, activeWeapon, onBack }) => {
  const classes = useStyles();

  const { settings, updateValue } = React.useContext(SettingsContext);
  const { fullForceUpdate } = React.useContext(DataContext);

  const [props, setProps] = React.useState<ISkinchangerWeapon>({ ...DEFAULT_WEAPON_SETTINGS });

  const weaponSettings =
    activeTeam && activeSkin?.weapon?.isKnife()
      ? settings.skinchanger_knifes[activeTeam]
      : !activeSkin?.weapon?.isKnife()
      ? settings.skinchanger_weapons[activeSkin.weaponDI]
      : undefined;

  if (!weaponSettings) {
    return (
      <IconButton className={classes.btn_back} onClick={onBack} color="primary">
        <IconArrowBack />
      </IconButton>
    );
  }

  function applyHandler() {
    if (activeWeapon.isKnife() && activeTeam) {
      updateValue("skinchanger_knifes", {
        ...settings.skinchanger_knifes,
        [activeTeam]: {
          ...weaponSettings,
          ...props,
          paintKit: activeSkin.paintKit,
          itemDI: activeWeapon.itemDI,
        },
      });
    } else if (!activeWeapon.isKnife()) {
      updateValue("skinchanger_weapons", {
        ...settings.skinchanger_weapons,
        [activeSkin.weaponDI]: {
          ...weaponSettings,
          ...props,
          paintKit: activeSkin.paintKit,
        },
      });
    }
    fullForceUpdate();
  }

  return (
    <div className={classes.content + ` ${classes.content}-btn`}>
      <IconButton className={classes.btn_back} onClick={onBack} color="primary">
        <IconArrowBack />
      </IconButton>
      <div style={{ width: "calc(100% - 65px)" }}>
        <div className={classes.skin_view_main}>
          <ItemCard
            className={classes.skin_view_main_skin}
            image={activeSkin?.image || "a"}
            title={activeSkin?.name || ""}
          />
          <div className={classes.skin_view_main_props}>
            <Switch label="Enable" checked={props.enable} onChange={(e, v) => setProps({ ...props, enable: v })} />
            {weaponSettings.enable ? (
              <React.Fragment>
                <TextField
                  placeholder="Wear"
                  type="number"
                  fullWidth
                  value={(props.wear * 1000).toFixed(0)}
                  onChange={(e) =>
                    setProps({ ...props, wear: Math.abs(Math.min(1000, parseInt(e.target.value))) / 1000 })
                  }
                />
                <TextField
                  margin="normal"
                  placeholder="Seed"
                  type="number"
                  fullWidth
                  value={props.seed}
                  onChange={(e) => setProps({ ...props, seed: Math.abs(parseInt(e.target.value)) })}
                />
                <TextField
                  margin="normal"
                  placeholder="Custom name"
                  fullWidth
                  value={props.customName}
                  onChange={(e) => setProps({ ...props, customName: e.target.value })}
                />
                <QualitySelect
                  marginTop={15}
                  value={props.quality < 0 ? EntityQuality.QUALITY_NORMAL : props.quality}
                  onChange={(v) => setProps({ ...props, quality: v })}
                />
                <Switch
                  label="StatTrack"
                  marginTop={10}
                  checked={props.statTrack !== -1}
                  onChange={(e, v) => setProps({ ...props, statTrack: v ? 1 : -1 })}
                />
                {props.statTrack >= 0 ? (
                  <TextField
                    placeholder="StatTrack"
                    type="number"
                    fullWidth
                    value={props.statTrack}
                    onChange={(e) => setProps({ ...props, statTrack: Math.abs(parseInt(e.target.value)) })}
                  />
                ) : (
                  ""
                )}
              </React.Fragment>
            ) : (
              ""
            )}
            <Button
              className={classes.skin_view_main_props_apply}
              variant="contained"
              color="primary"
              onClick={applyHandler}
            >
              Apply
            </Button>
          </div>
        </div>
        <div className={classes.skin_view_info}>
          {activeSkin?.description ? (
            <Accordion defaultExpanded={true}>
              <AccordionSummary expandIcon={<ExpandMoreIcon />}>
                <Typography>Description</Typography>
              </AccordionSummary>
              <AccordionDetails>
                <Typography>{activeSkin?.description}</Typography>
              </AccordionDetails>
            </Accordion>
          ) : (
            ""
          )}
          {activeSkin?.collections && activeSkin?.collections.length > 0 ? (
            <Accordion defaultExpanded={true}>
              <AccordionSummary expandIcon={<ExpandMoreIcon />}>
                <Typography>Collections</Typography>
              </AccordionSummary>
              <AccordionDetails>
                {activeSkin?.collections.map((c, key) => (
                  <div className={classes.skin_view_info_collection} key={key}>
                    <img src={activeSkin.collectionsImage[key]} alt="" />
                    <Typography key={key} variant="body2" align="center">
                      {c}
                    </Typography>
                  </div>
                ))}
              </AccordionDetails>
            </Accordion>
          ) : (
            ""
          )}
        </div>
      </div>
    </div>
  );
};
