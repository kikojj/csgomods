import React from "react";
import ClickAwayListener from "react-click-away-listener";

import { RangeField } from "@components";
import { rgbToHex } from "@utils";

import { useStyles } from "./styles";

export type ColorRGBA = {
  r: number;
  g: number;
  b: number;
  a: number;
};

export type ColorPickerProps = {
  color?: ColorRGBA;
  onChnage?: (v: ColorRGBA) => void;
};
export const ColorPicker: React.FC<ColorPickerProps> = ({ color: _color, onChnage: onChange }) => {
  const [show, setShow] = React.useState<boolean>(false);
  const [color, setColor] = React.useState<ColorRGBA>({ r: 0, g: 0, b: 0, a: 255, ..._color });

  const classes = useStyles({ color });

  return (
    <div className={classes.container}>
      <div className={classes.colorContainer} onClick={() => setShow(true)} />
      {show ? (
        <ClickAwayListener
          onClickAway={() => {
            setShow(false);
            onChange && onChange({ ...color });
          }}
        >
          <div className={classes.pickerContainer}>
            <Picker color={color} onChange={setColor} />
          </div>
        </ClickAwayListener>
      ) : (
        ""
      )}
    </div>
  );
};

export type PickerProps = {
  color: ColorRGBA;
  onChange: (v: ColorRGBA) => void;
};
export const Picker: React.FC<PickerProps> = ({ color, onChange }) => {
  return (
    <div>
      <RangeField
        marginTop={0}
        label={`Red: ${color.r}`}
        value={color.r}
        onChange={(v) => onChange({ ...color, r: v })}
        min={0}
        max={255}
        step={1}
        color="#FF0000"
      />
      <RangeField
        marginTop={15}
        label={`Green: ${color.g}`}
        value={color.g}
        onChange={(v) => onChange({ ...color, g: v })}
        min={0}
        max={255}
        step={1}
        color="#00FF00"
      />
      <RangeField
        marginTop={15}
        label={`Blue: ${color.b}`}
        value={color.b}
        onChange={(v) => onChange({ ...color, b: v })}
        min={0}
        max={255}
        step={1}
        color="#0000FF"
      />
      <RangeField
        marginTop={15}
        label={`Alpha: ${color.a}`}
        value={color.a}
        onChange={(v) => onChange({ ...color, a: v })}
        min={0}
        max={255}
        step={1}
        color={rgbToHex(color.r, color.g, color.b)}
      />
    </div>
  );
};
