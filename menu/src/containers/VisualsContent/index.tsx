import React from "react";

import { SettingsContext } from "@contexts";
import { Group, CheckboxField, FiltersField, SelectField, SelectItem, ColorPickerField } from "@components";

import { useStyles } from "./styles";

export const VisualsContent: React.FC = () => {
  const classes = useStyles();

  const { settings, updateValue } = React.useContext(SettingsContext);

  const glowFilters: string[] = [];
  if (settings.visuals_glowEsp_show_friends) {
    glowFilters.push("Teammates");
  }
  if (settings.visuals_glowEsp_show_enemies) {
    glowFilters.push("Enemies");
  }
  if (settings.visuals_glowEsp_show_c4) {
    glowFilters.push("C4");
  }

  function changeGlowFiltersHandler(v: string[]) {
    if (!glowFilters.includes("Teammates") && v.includes("Teammates")) {
      updateValue("visuals_glowEsp_show_friends", true);
    } else if (glowFilters.includes("Teammates") && !v.includes("Teammates")) {
      updateValue("visuals_glowEsp_show_friends", false);
    }
    if (!glowFilters.includes("Enemies") && v.includes("Enemies")) {
      updateValue("visuals_glowEsp_show_enemies", true);
    } else if (glowFilters.includes("Enemies") && !v.includes("Enemies")) {
      updateValue("visuals_glowEsp_show_enemies", false);
    }
    if (!glowFilters.includes("C4") && v.includes("C4")) {
      updateValue("visuals_glowEsp_show_c4", true);
    } else if (glowFilters.includes("C4") && !v.includes("C4")) {
      updateValue("visuals_glowEsp_show_c4", false);
    }
  }

  const chamsFilters: string[] = [];
  if (settings.visuals_chams_show_friends) {
    chamsFilters.push("Teammates");
  }
  if (settings.visuals_chams_show_enemies) {
    chamsFilters.push("Enemies");
  }

  function changeChamsFiltersHandler(v: string[]) {
    if (!chamsFilters.includes("Teammates") && v.includes("Teammates")) {
      updateValue("visuals_chams_show_friends", true);
    } else if (chamsFilters.includes("Teammates") && !v.includes("Teammates")) {
      updateValue("visuals_chams_show_friends", false);
    }
    if (!chamsFilters.includes("Enemies") && v.includes("Enemies")) {
      updateValue("visuals_chams_show_enemies", true);
    } else if (chamsFilters.includes("Enemies") && !v.includes("Enemies")) {
      updateValue("visuals_chams_show_enemies", false);
    }
  }

  return (
    <div className={classes.container}>
      <div>
        <Group label="Glow ESP">
          <CheckboxField
            label="Enable"
            checked={settings.visuals_glowEsp_enable}
            onChange={(v) => updateValue("visuals_glowEsp_enable", v)}
          />
          {settings.visuals_glowEsp_enable ? (
            <React.Fragment>
              <FiltersField
                label="Filters:"
                helperText="Filter entities for display"
                filters={["Teammates", "Enemies", "C4"]}
                values={glowFilters}
                onChange={changeGlowFiltersHandler}
              />
              <SelectField
                placeholder="Style"
                helperText={
                  settings.visuals_glowEsp_style === 0
                    ? "Outline full body(works through the walls)"
                    : settings.visuals_glowEsp_style === 1
                    ? "All body contours and flicker of glow"
                    : settings.visuals_glowEsp_style === 2
                    ? "All body contours"
                    : "Flicker of glow"
                }
                value={settings.visuals_glowEsp_style.toString()}
                onChange={(v) => updateValue("visuals_glowEsp_style", +v)}
              >
                <SelectItem value="0">Full body</SelectItem>
                <SelectItem value="2">Inline</SelectItem>
                <SelectItem value="3">Flicker</SelectItem>
                <SelectItem value="1">Inline flicker</SelectItem>
              </SelectField>
              <SelectField
                placeholder="Mode"
                helperText={settings.visuals_glowEsp_mode === 0 ? "Use color for glow" : "Show health in color"}
                value={settings.visuals_glowEsp_mode.toString()}
                onChange={(v) => updateValue("visuals_glowEsp_mode", +v)}
              >
                <SelectItem value="0">Color</SelectItem>
                <SelectItem value="1">HP based</SelectItem>
              </SelectField>
            </React.Fragment>
          ) : (
            ""
          )}
        </Group>
        {settings.visuals_glowEsp_enable &&
        (settings.visuals_glowEsp_show_enemies ||
          settings.visuals_glowEsp_show_friends ||
          settings.visuals_glowEsp_show_c4) ? (
          <React.Fragment>
            <Group marginTop={35} label="Glow colors">
              {settings.visuals_glowEsp_mode === 0 ? (
                <React.Fragment>
                  {settings.visuals_glowEsp_show_friends ? (
                    <ColorPickerField
                      label="Teammates"
                      color={settings.visuals_glowEsp_friends_color}
                      onChnage={(c) => updateValue("visuals_glowEsp_friends_color", c)}
                    />
                  ) : (
                    ""
                  )}
                  {settings.visuals_glowEsp_show_enemies ? (
                    <React.Fragment>
                      <ColorPickerField
                        label="Enemies visible"
                        color={settings.visuals_glowEsp_enemy_visible_color}
                        onChnage={(c) => updateValue("visuals_glowEsp_enemy_visible_color", c)}
                      />
                      <ColorPickerField
                        label="Enemies invisible"
                        color={settings.visuals_glowEsp_enemy_invisible_color}
                        onChnage={(c) => updateValue("visuals_glowEsp_enemy_invisible_color", c)}
                      />
                    </React.Fragment>
                  ) : (
                    ""
                  )}
                </React.Fragment>
              ) : (
                <React.Fragment>
                  <ColorPickerField
                    label="0 hp"
                    color={settings.visuals_glowEsp_hpBased_0hp_color}
                    onChnage={(c) => updateValue("visuals_glowEsp_hpBased_0hp_color", c)}
                  />
                  <ColorPickerField
                    label="100 hp"
                    color={settings.visuals_glowEsp_hpBased_100hp_color}
                    onChnage={(c) => updateValue("visuals_glowEsp_hpBased_100hp_color", c)}
                  />
                </React.Fragment>
              )}
              {settings.visuals_glowEsp_show_c4 ? (
                <ColorPickerField
                  label="C4"
                  color={settings.visuals_glowEsp_c4_color}
                  onChnage={(c) => updateValue("visuals_glowEsp_c4_color", c)}
                />
              ) : (
                ""
              )}
            </Group>
          </React.Fragment>
        ) : (
          ""
        )}
      </div>
      <div>
        <Group marginLeft={35} label="Chams">
          <CheckboxField
            label="Enable"
            checked={settings.visuals_chams_enable}
            onChange={(v) => updateValue("visuals_chams_enable", v)}
          />
          {settings.visuals_chams_enable ? (
            <FiltersField
              label="Filters:"
              helperText="Filter entities for display"
              filters={["Teammates", "Enemies"]}
              values={chamsFilters}
              onChange={changeChamsFiltersHandler}
            />
          ) : (
            ""
          )}
        </Group>
        {settings.visuals_chams_enable &&
        (settings.visuals_chams_show_enemies || settings.visuals_chams_show_friends) ? (
          <React.Fragment>
            <Group marginTop={35} marginLeft={35} label="Chams colors">
              {settings.visuals_chams_show_friends ? (
                <ColorPickerField
                  label="Teammates"
                  color={settings.visuals_chams_friends_color}
                  onChnage={(c) => updateValue("visuals_chams_friends_color", c)}
                />
              ) : (
                ""
              )}
              {settings.visuals_chams_show_enemies ? (
                <React.Fragment>
                  <ColorPickerField
                    label="Enemies"
                    color={settings.visuals_chams_enemy_color}
                    onChnage={(c) => updateValue("visuals_chams_enemy_color", c)}
                  />
                </React.Fragment>
              ) : (
                ""
              )}
            </Group>
          </React.Fragment>
        ) : (
          ""
        )}
      </div>
    </div>
  );
};
