import React from "react";
import { selectRadarData, selectSettings, selectTeam, updateValue, useDataSelector, useSettingsSelector } from "@services";
import { CheckboxField, ColorPickerField, Group, List } from "@components";
import { GlowStyle } from "@containers/VisualsContent/GlowStyle";
import { GlowMode } from "@containers/VisualsContent/GlowMode";
import {
  DEFAULT_PERSONAL_SETTINGS,
  IPersonalSettings,
  TeamNum,
} from "@utils";
import { IRadarData } from "@ts/requests";
import { Player } from "./Player";
import { Average } from "./Average";
import { useStyles } from "./styles";

const Header: React.FC = () => {
  const classes = useStyles();

  return (
    <div className={classes.player}>
      <div className={classes.player_info}>
        <div className={classes.player_stat}>Ping</div>
        <div className={classes.player_name}>Name</div>
        <div className={classes.player_rank}>Rank</div>
        <div className={classes.player_wins}>Wins</div>
      </div>
      <div className={classes.player_stats}>
        <div className={classes.player_money}>Money</div>
        <div className={classes.player_stat}>K</div>
        <div className={classes.player_stat}>A</div>
        <div className={classes.player_stat}>D</div>
        <div className={classes.player_mvps}>MVP</div>
        <div className={classes.player_stat} style={{ marginRight: 0 }}>
          S
        </div>
      </div>
    </div>
  );
};

export const PlayersListContent: React.FC = () => {
  const myTeam = useDataSelector(selectTeam);
  const radarData = useDataSelector(selectRadarData);
  const settings = useSettingsSelector(selectSettings);

  const [selectedPlayer, setSelectedPlayer] = React.useState<IRadarData>();

  const Ts = radarData
    .filter((d) => d.team_num === TeamNum.Terrorist)
    .sort((d1, d2) => d2.score - d1.score);
  const CTs = radarData
    .filter((d) => d.team_num === TeamNum.CounterTerrorist)
    .sort((d1, d2) => d2.score - d1.score);

  const personalSettings = selectedPlayer
    ? settings.personal_settings[selectedPlayer.user_id] || {
        ...DEFAULT_PERSONAL_SETTINGS,
      }
    : { ...DEFAULT_PERSONAL_SETTINGS };

  const TList: React.FC = React.useCallback(() => {
    return (
      <List
        items={[
          {
            content: <Header />,
          },
          ...Ts.map((data) => {
            return {
              content: <Player playerData={data} />,
              onClick: () => setSelectedPlayer(data),
              selected: selectedPlayer?.user_id === data.user_id,
            };
          }),
          {
            content: <Average data={Ts} />,
          },
        ]}
      />
    );
  }, [Ts]);

  const CTList: React.FC = React.useCallback(() => {
    return (
      <List
        items={[
          {
            content: <Header />,
          },
          ...CTs.map((data) => {
            return {
              content: <Player playerData={data} />,
              onClick: () => setSelectedPlayer(data),
              selected: selectedPlayer?.user_id === data.user_id,
            };
          }),
          {
            content: <Average data={CTs} />,
          },
        ]}
      />
    );
  }, [CTs]);

  function updatePersonalSettings(
    field: keyof IPersonalSettings,
    value: IPersonalSettings[keyof IPersonalSettings]
  ) {
    if (selectedPlayer) {
      updateValue({name: "personal_settings", value: {
        ...settings.personal_settings,
        [selectedPlayer.user_id]: {
          ...personalSettings,
          [field]: value,
        },
      }});
    }
  }

  function updatePersonalGlowSettings(
    field: keyof IPersonalSettings["glow_settings"],
    value: IPersonalSettings["glow_settings"][keyof IPersonalSettings["glow_settings"]]
  ) {
    if (selectedPlayer) {
      updatePersonalSettings("glow_settings", {
        ...personalSettings.glow_settings,
        [field]: value,
      });
    }
  }

  return (
    <div>
      <div>
        <Group width="100%" label="Players list">
          <TList />
          <CTList />
        </Group>
        {selectedPlayer && (
          <Group
            marginTop={35}
            label={`Personal settings for ${selectedPlayer.name}`}
          >
            <CheckboxField
              label="Enable"
              checked={personalSettings.enable}
              onChange={(v) => updatePersonalSettings("enable", v)}
            />
          </Group>
        )}
        {selectedPlayer && personalSettings && personalSettings.enable && (
          <Group marginTop={35} label="Glow ESP">
            <CheckboxField
              label="Enable"
              checked={personalSettings.glow_settings.enable}
              onChange={(v) => updatePersonalGlowSettings("enable", v)}
            />
            {personalSettings.glow_settings.enable && (
              <React.Fragment>
                <GlowStyle
                  value={personalSettings.glow_settings.style.toString()}
                  onChange={(v) => updatePersonalGlowSettings("style", +v)}
                />
                {selectedPlayer.team_num === myTeam ? (
                  <React.Fragment>
                    <ColorPickerField
                      label="Color"
                      color={personalSettings.glow_settings.visible_color}
                      onChange={(v) =>
                        updatePersonalGlowSettings("visible_color", v)
                      }
                    />
                  </React.Fragment>
                ) : (
                  <React.Fragment>
                    <GlowMode
                      value={personalSettings.glow_settings.mode.toString()}
                      onChange={(v) => updatePersonalGlowSettings("mode", +v)}
                    />
                    {personalSettings.glow_settings.mode === 0 ? (
                      <React.Fragment key={0}>
                        <ColorPickerField
                          label="Visible color"
                          color={personalSettings.glow_settings.visible_color}
                          onChange={(v) =>
                            updatePersonalGlowSettings("visible_color", v)
                          }
                        />
                        <ColorPickerField
                          label="Invisible color"
                          color={personalSettings.glow_settings.invisible_color}
                          onChange={(v) =>
                            updatePersonalGlowSettings("invisible_color", v)
                          }
                        />
                      </React.Fragment>
                    ) : (
                      <React.Fragment key={1}>
                        <ColorPickerField
                          label="0hp color"
                          color={
                            personalSettings.glow_settings.hp_based_0hp_color
                          }
                          onChange={(v) =>
                            updatePersonalGlowSettings("hp_based_0hp_color", v)
                          }
                        />
                        <ColorPickerField
                          label="100hp color"
                          color={
                            personalSettings.glow_settings.hp_based_100hp_color
                          }
                          onChange={(v) =>
                            updatePersonalGlowSettings(
                              "hp_based_100hp_color",
                              v
                            )
                          }
                        />
                      </React.Fragment>
                    )}
                  </React.Fragment>
                )}
              </React.Fragment>
            )}
          </Group>
        )}
      </div>
    </div>
  );
};
