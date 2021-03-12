import React from "react";
import { SectionTitle, Switch, Group, Radio, ColorPicker } from "@components";

import { WindowContent } from "../Window/Content";
import { RadioGroup } from "@material-ui/core";
import { useStyles } from "./styles";
import { SettingsContext } from "../../contexts";

export const VisualsContent = () => {
  const classes = useStyles();
  const { settings, updateValue } = React.useContext(SettingsContext);

  return (
    <WindowContent>
      <div className={classes.glowEsp}>
        <SectionTitle text="GlowESP" />
        <Switch
          label="Enable"
          marginTop={28}
          checked={settings.visuals_glowEsp_enable}
          onChange={(e, v) => updateValue("visuals_glowEsp_enable", v)}
        />
        {settings.visuals_glowEsp_enable ? (
          <React.Fragment>
            <Group title="Filters" marginTop={28}>
              <Switch
                label="Enemy"
                marginTop={10}
                checked={settings.visuals_glowEsp_show_enemies}
                onChange={(e, v) => updateValue("visuals_glowEsp_show_enemies", v)}
              />
              <Switch
                label="Teammates"
                checked={settings.visuals_glowEsp_show_friends}
                onChange={(e, v) => updateValue("visuals_glowEsp_show_friends", v)}
              />
              <Switch
                label="C4"
                checked={settings.visuals_glowEsp_show_c4}
                onChange={(e, v) => updateValue("visuals_glowEsp_show_c4", v)}
              />
              <Group title="Glow style" marginTop={28}>
                <RadioGroup
                  row
                  style={{ marginTop: 10 }}
                  value={settings.visuals_glowEsp_style}
                  onChange={(e, v) => updateValue("visuals_glowEsp_style", +v)}
                >
                  <Radio label="Full body" value="0" checked={settings.visuals_glowEsp_style === 0} />
                  <Radio label="Inline" value="2" checked={settings.visuals_glowEsp_style === 2} />
                  <Radio label="Flicker" value="3" checked={settings.visuals_glowEsp_style === 3} />
                  <Radio label="Inline flicker" value="1" checked={settings.visuals_glowEsp_style === 1} />
                </RadioGroup>
              </Group>
            </Group>
            {settings.visuals_glowEsp_show_enemies || settings.visuals_glowEsp_show_friends ? (
              <Group title="Glow mode" marginTop={28}>
                <RadioGroup
                  row
                  style={{ marginTop: 10 }}
                  value={settings.visuals_glowEsp_mode}
                  onChange={(e, v) => updateValue("visuals_glowEsp_mode", +v)}
                >
                  <Radio label="Color" value="0" checked={settings.visuals_glowEsp_mode === 0} />
                  <Radio label="Hp based" value="1" checked={settings.visuals_glowEsp_mode === 1} />
                </RadioGroup>
              </Group>
            ) : (
              ""
            )}
            {settings.visuals_glowEsp_show_enemies ||
            settings.visuals_glowEsp_show_friends ||
            settings.visuals_glowEsp_show_c4 ? (
              <Group title="Colors" marginTop={28}>
                {settings.visuals_glowEsp_mode === 0 ? (
                  <React.Fragment>
                    {settings.visuals_glowEsp_show_enemies ? (
                      <React.Fragment>
                        <ColorPicker
                          label="Enemy visible"
                          marginTop={10}
                          value={settings.visuals_glowEsp_enemy_visible_color}
                          onChange={(v) => updateValue("visuals_glowEsp_enemy_visible_color", v as any)}
                        />
                        <ColorPicker
                          label="Enemy invisible"
                          marginTop={15}
                          value={settings.visuals_glowEsp_enemy_invisible_color}
                          onChange={(v) => updateValue("visuals_glowEsp_enemy_invisible_color", v as any)}
                        />
                      </React.Fragment>
                    ) : (
                      ""
                    )}
                    {settings.visuals_glowEsp_show_friends ? (
                      <React.Fragment>
                        <ColorPicker
                          label="Teammate visible"
                          marginTop={10}
                          value={settings.visuals_glowEsp_friends_color}
                          onChange={(v) => updateValue("visuals_glowEsp_friends_color", v as any)}
                        />
                      </React.Fragment>
                    ) : (
                      ""
                    )}
                  </React.Fragment>
                ) : (
                  <React.Fragment>
                    {settings.visuals_glowEsp_show_enemies || settings.visuals_glowEsp_show_friends ? (
                      <React.Fragment>
                        <ColorPicker
                          label="0 hp"
                          marginTop={10}
                          value={settings.visuals_glowEsp_hpBased_0hp_color}
                          onChange={(v) => updateValue("visuals_glowEsp_hpBased_0hp_color", v as any)}
                        />
                        <ColorPicker
                          label="100 hp"
                          marginTop={15}
                          value={settings.visuals_glowEsp_hpBased_100hp_color}
                          onChange={(v) => updateValue("visuals_glowEsp_hpBased_100hp_color", v as any)}
                        />
                      </React.Fragment>
                    ) : (
                      ""
                    )}
                  </React.Fragment>
                )}
                {settings.visuals_glowEsp_show_c4 ? (
                  <React.Fragment>
                    <ColorPicker
                      label="C4"
                      marginTop={15}
                      value={settings.visuals_glowEsp_c4_color}
                      onChange={(v) => {
                        updateValue("visuals_glowEsp_c4_color", v as any);
                      }}
                    />
                  </React.Fragment>
                ) : (
                  ""
                )}
              </Group>
            ) : (
              ""
            )}
          </React.Fragment>
        ) : (
          ""
        )}
      </div>
      <div className={classes.chams}>
        <SectionTitle text="Chams" />
        <Switch
          label="Enable"
          marginTop={28}
          checked={settings.visuals_chams_enable}
          onChange={(e, v) => updateValue("visuals_chams_enable", v)}
        />
        {settings.visuals_chams_enable ? (
          <React.Fragment>
            <Group title="Filters" marginTop={28}>
              <Switch
                label="Enemy"
                marginTop={10}
                checked={settings.visuals_chams_show_enemies}
                onChange={(e, v) => updateValue("visuals_chams_show_enemies", v)}
              />
              <Switch
                label="Teammates"
                checked={settings.visuals_chams_show_friends}
                onChange={(e, v) => updateValue("visuals_chams_show_friends", v)}
              />
            </Group>
            {settings.visuals_chams_show_enemies || settings.visuals_chams_show_friends ? (
              <Group title="Colors" marginTop={28}>
                {settings.visuals_chams_show_enemies ? (
                  <ColorPicker
                    label="Enemy"
                    marginTop={10}
                    value={settings.visuals_chams_enemy_color}
                    onChange={(v) => updateValue("visuals_chams_enemy_color", v as any)}
                  />
                ) : (
                  ""
                )}
                {settings.visuals_chams_show_friends ? (
                  <ColorPicker
                    label="Teammates"
                    marginTop={10}
                    value={settings.visuals_chams_friends_color}
                    onChange={(v) => updateValue("visuals_chams_friends_color", v as any)}
                  />
                ) : (
                  ""
                )}
              </Group>
            ) : (
              ""
            )}
          </React.Fragment>
        ) : (
          ""
        )}
      </div>
    </WindowContent>
  );
};
