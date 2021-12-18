import React from "react";
import { selectSettings, updateValue, useSettingsSelector } from "@services";
import {
  Group,
  CheckboxField,
  FiltersField,
  ColorPickerField,
} from "@components";
import { GlowStyle } from "./GlowStyle";
import { GlowMode } from "./GlowMode";
import { useStyles } from "./styles";

export const VisualsContent: React.FC = () => {
  const classes = useStyles();

  const settings = useSettingsSelector(selectSettings);

  const glowFilters: string[] = [];
  if (settings.visuals_glow_esp_friends.enable) {
    glowFilters.push("Teammates");
  }
  if (settings.visuals_glow_esp_enemies.enable) {
    glowFilters.push("Enemies");
  }
  if (settings.visuals_glow_esp_c4.enable) {
    glowFilters.push("C4");
  }
  if (settings.visuals_glow_esp_defusing.enable) {
    glowFilters.push("Defusing");
  }
  if (settings.visuals_glow_esp_grenades.enable) {
    glowFilters.push("Grenades");
  }

  function changeGlowFiltersHandler(v: string[]) {
    if (!glowFilters.includes("Teammates") && v.includes("Teammates")) {
      updateValue({
        name: "visuals_glow_esp_friends",
        value: { ...settings.visuals_glow_esp_friends, enable: true },
      });
    } else if (glowFilters.includes("Teammates") && !v.includes("Teammates")) {
      updateValue({
        name: "visuals_glow_esp_friends",
        value: { ...settings.visuals_glow_esp_friends, enable: false },
      });
    }
    if (!glowFilters.includes("Enemies") && v.includes("Enemies")) {
      updateValue({
        name: "visuals_glow_esp_enemies",
        value: { ...settings.visuals_glow_esp_enemies, enable: true },
      });
    } else if (glowFilters.includes("Enemies") && !v.includes("Enemies")) {
      updateValue({
        name: "visuals_glow_esp_enemies",
        value: { ...settings.visuals_glow_esp_enemies, enable: false },
      });
    }
    if (!glowFilters.includes("C4") && v.includes("C4")) {
      updateValue({
        name: "visuals_glow_esp_c4",
        value: { ...settings.visuals_glow_esp_c4, enable: true },
      });
    } else if (glowFilters.includes("C4") && !v.includes("C4")) {
      updateValue({
        name: "visuals_glow_esp_c4",
        value: { ...settings.visuals_glow_esp_c4, enable: false },
      });
    }
    if (!glowFilters.includes("Defusing") && v.includes("Defusing")) {
      updateValue({
        name: "visuals_glow_esp_defusing",
        value: { ...settings.visuals_glow_esp_defusing, enable: true },
      });
    } else if (glowFilters.includes("Defusing") && !v.includes("Defusing")) {
      updateValue({
        name: "visuals_glow_esp_defusing",
        value: { ...settings.visuals_glow_esp_defusing, enable: false },
      });
    }
    if (!glowFilters.includes("Grenades") && v.includes("Grenades")) {
      updateValue({
        name: "visuals_glow_esp_grenades",
        value: { ...settings.visuals_glow_esp_grenades, enable: true },
      });
    } else if (glowFilters.includes("Grenades") && !v.includes("Grenades")) {
      updateValue({
        name: "visuals_glow_esp_grenades",
        value: { ...settings.visuals_glow_esp_grenades, enable: false },
      });
    }
  }

  const chamsFilters: string[] = [];
  if (settings.visuals_chams_friends.enable) {
    chamsFilters.push("Teammates");
  }
  if (settings.visuals_chams_enemies.enable) {
    chamsFilters.push("Enemies");
  }

  function changeChamsFiltersHandler(v: string[]) {
    if (!chamsFilters.includes("Teammates") && v.includes("Teammates")) {
      updateValue({
        name: "visuals_chams_friends",
        value: {
          ...settings.visuals_chams_friends,
          enable: true,
        },
      });
    } else if (chamsFilters.includes("Teammates") && !v.includes("Teammates")) {
      updateValue({
        name: "visuals_chams_friends",
        value: {
          ...settings.visuals_chams_friends,
          enable: false,
        },
      });
    }
    if (!chamsFilters.includes("Enemies") && v.includes("Enemies")) {
      updateValue({
        name: "visuals_chams_enemies",
        value: {
          ...settings.visuals_chams_enemies,
          enable: true,
        },
      });
    } else if (chamsFilters.includes("Enemies") && !v.includes("Enemies")) {
      updateValue({
        name: "visuals_chams_enemies",
        value: {
          ...settings.visuals_chams_enemies,
          enable: false,
        },
      });
    }
  }

  return (
    <div className={classes.container}>
      <div>
        <Group label="Glow ESP">
          <CheckboxField
            label="Enable"
            checked={settings.visuals_glow_esp_enable}
            onChange={(v) =>
              updateValue({ name: "visuals_glow_esp_enable", value: v })
            }
          />
          {settings.visuals_glow_esp_enable ? (
            <React.Fragment>
              <FiltersField
                label="Filters:"
                helperText="Filter entities for display"
                filters={["Teammates", "Enemies", "C4", "Defusing", "Grenades"]}
                values={glowFilters}
                onChange={changeGlowFiltersHandler}
              />
            </React.Fragment>
          ) : (
            ""
          )}
        </Group>
        {settings.visuals_glow_esp_enable &&
        settings.visuals_glow_esp_friends.enable ? (
          <Group marginTop={35} label="Teammates">
            <GlowStyle
              value={settings.visuals_glow_esp_friends.style.toString()}
              onChange={(v) =>
                updateValue({
                  name: "visuals_glow_esp_friends",
                  value: {
                    ...settings.visuals_glow_esp_friends,
                    style: +v,
                  },
                })
              }
            />
            <GlowMode
              value={settings.visuals_glow_esp_friends.mode.toString()}
              onChange={(v) =>
                updateValue({
                  name: "visuals_glow_esp_friends",
                  value: {
                    ...settings.visuals_glow_esp_friends,
                    mode: +v,
                  },
                })
              }
            />
            {settings.visuals_glow_esp_friends.mode === 0 ? (
              <React.Fragment key={0}>
                <ColorPickerField
                  label="Color"
                  color={settings.visuals_glow_esp_friends.visible_color}
                  onChange={(v) =>
                    updateValue({
                      name: "visuals_glow_esp_friends",
                      value: {
                        ...settings.visuals_glow_esp_friends,
                        visible_color: v,
                      },
                    })
                  }
                />
              </React.Fragment>
            ) : (
              <React.Fragment key={1}>
                <ColorPickerField
                  label="0hp color"
                  color={settings.visuals_glow_esp_friends.hp_based_0hp_color}
                  onChange={(v) =>
                    updateValue({
                      name: "visuals_glow_esp_friends",
                      value: {
                        ...settings.visuals_glow_esp_friends,
                        hp_based_0hp_color: v,
                      },
                    })
                  }
                />
                <ColorPickerField
                  label="100hp color"
                  color={settings.visuals_glow_esp_friends.hp_based_100hp_color}
                  onChange={(v) =>
                    updateValue({
                      name: "visuals_glow_esp_friends",
                      value: {
                        ...settings.visuals_glow_esp_friends,
                        hp_based_100hp_color: v,
                      },
                    })
                  }
                />
              </React.Fragment>
            )}
          </Group>
        ) : (
          ""
        )}
        {settings.visuals_glow_esp_enable &&
        settings.visuals_glow_esp_enemies.enable ? (
          <Group marginTop={35} label="Enemies">
            <GlowStyle
              value={settings.visuals_glow_esp_enemies.style.toString()}
              onChange={(v) =>
                updateValue({
                  name: "visuals_glow_esp_enemies",
                  value: {
                    ...settings.visuals_glow_esp_enemies,
                    style: +v,
                  },
                })
              }
            />
            <GlowMode
              value={settings.visuals_glow_esp_enemies.mode.toString()}
              onChange={(v) =>
                updateValue({
                  name: "visuals_glow_esp_enemies",
                  value: {
                    ...settings.visuals_glow_esp_enemies,
                    mode: +v,
                  },
                })
              }
            />
            {settings.visuals_glow_esp_enemies.mode === 0 ? (
              <React.Fragment key={0}>
                <ColorPickerField
                  label="Visible color"
                  color={settings.visuals_glow_esp_enemies.visible_color}
                  onChange={(v) =>
                    updateValue({
                      name: "visuals_glow_esp_enemies",
                      value: {
                        ...settings.visuals_glow_esp_enemies,
                        visible_color: v,
                      },
                    })
                  }
                />
                <ColorPickerField
                  label="Invisible color"
                  color={settings.visuals_glow_esp_enemies.invisible_color}
                  onChange={(v) =>
                    updateValue({
                      name: "visuals_glow_esp_enemies",
                      value: {
                        ...settings.visuals_glow_esp_enemies,
                        invisible_color: v,
                      },
                    })
                  }
                />
              </React.Fragment>
            ) : (
              <React.Fragment key={1}>
                <ColorPickerField
                  label="0hp color"
                  color={settings.visuals_glow_esp_enemies.hp_based_0hp_color}
                  onChange={(v) =>
                    updateValue({
                      name: "visuals_glow_esp_enemies",
                      value: {
                        ...settings.visuals_glow_esp_enemies,
                        hp_based_0hp_color: v,
                      },
                    })
                  }
                />
                <ColorPickerField
                  label="100hp color"
                  color={settings.visuals_glow_esp_enemies.hp_based_100hp_color}
                  onChange={(v) =>
                    updateValue({
                      name: "visuals_glow_esp_enemies",
                      value: {
                        ...settings.visuals_glow_esp_enemies,
                        hp_based_100hp_color: v,
                      },
                    })
                  }
                />
              </React.Fragment>
            )}
          </Group>
        ) : (
          ""
        )}
        {settings.visuals_glow_esp_enable &&
        settings.visuals_glow_esp_c4.enable ? (
          <Group marginTop={35} label="C4">
            <GlowStyle
              value={settings.visuals_glow_esp_c4.style.toString()}
              onChange={(v) =>
                updateValue({
                  name: "visuals_glow_esp_c4",
                  value: {
                    ...settings.visuals_glow_esp_c4,
                    style: +v,
                  },
                })
              }
            />
            <ColorPickerField
              label="Color"
              color={settings.visuals_glow_esp_c4.visible_color}
              onChange={(v) =>
                updateValue({
                  name: "visuals_glow_esp_c4",
                  value: {
                    ...settings.visuals_glow_esp_c4,
                    visible_color: v,
                  },
                })
              }
            />
          </Group>
        ) : (
          ""
        )}
        {settings.visuals_glow_esp_enable &&
        settings.visuals_glow_esp_defusing.enable ? (
          <Group marginTop={35} label="Defusing">
            <GlowStyle
              value={settings.visuals_glow_esp_defusing.style.toString()}
              onChange={(v) =>
                updateValue({
                  name: "visuals_glow_esp_defusing",
                  value: {
                    ...settings.visuals_glow_esp_defusing,
                    style: +v,
                  },
                })
              }
            />
            <ColorPickerField
              label="Color"
              color={settings.visuals_glow_esp_defusing.visible_color}
              onChange={(v) =>
                updateValue({
                  name: "visuals_glow_esp_defusing",
                  value: {
                    ...settings.visuals_glow_esp_defusing,
                    visible_color: v,
                  },
                })
              }
            />
          </Group>
        ) : (
          ""
        )}
        {settings.visuals_glow_esp_enable &&
        settings.visuals_glow_esp_grenades.enable ? (
          <Group marginTop={35} label="Grenades">
            <GlowStyle
              value={settings.visuals_glow_esp_grenades.style.toString()}
              onChange={(v) =>
                updateValue({
                  name: "visuals_glow_esp_grenades",
                  value: {
                    ...settings.visuals_glow_esp_grenades,
                    style: +v,
                  },
                })
              }
            />
            <ColorPickerField
              label="Color"
              color={settings.visuals_glow_esp_grenades.visible_color}
              onChange={(v) =>
                updateValue({
                  name: "visuals_glow_esp_grenades",
                  value: {
                    ...settings.visuals_glow_esp_grenades,
                    visible_color: v,
                  },
                })
              }
            />
          </Group>
        ) : (
          ""
        )}
      </div>
      <div>
        <Group marginLeft={35} label="Chams">
          <CheckboxField
            label="Enable"
            checked={settings.visuals_chams_enable}
            onChange={(v) =>
              updateValue({ name: "visuals_chams_enable", value: v })
            }
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
        settings.visuals_chams_friends.enable ? (
          <Group marginTop={35} marginLeft={35} label="Teammates">
            <ColorPickerField
              label="Color"
              color={settings.visuals_chams_friends.color}
              onChange={(v) =>
                updateValue({
                  name: "visuals_chams_friends",
                  value: {
                    ...settings.visuals_chams_friends,
                    color: v,
                  },
                })
              }
            />
          </Group>
        ) : (
          ""
        )}
        {settings.visuals_chams_enable &&
        settings.visuals_chams_enemies.enable ? (
          <Group marginTop={35} marginLeft={35} label="Enemies">
            <ColorPickerField
              label="Color"
              color={settings.visuals_chams_enemies.color}
              onChange={(v) =>
                updateValue({
                  name: "visuals_chams_enemies",
                  value: {
                    ...settings.visuals_chams_enemies,
                    color: v,
                  },
                })
              }
            />
          </Group>
        ) : (
          ""
        )}
      </div>
    </div>
  );
};
