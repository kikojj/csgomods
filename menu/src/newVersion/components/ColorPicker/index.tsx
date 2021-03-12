import React from "react";
import { RangeField } from "../RangeField";
import { useStyles } from "./styles";
import { rgbToHex } from "@utils";
import { ClickAwayListener } from "@material-ui/core";

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
export const ColorPicker: React.FC<ColorPickerProps> = ({ color: _color, onChnage: _onChange }) => {
  const [show, setShow] = React.useState<boolean>(false);
  const [__color, __onChange] = React.useState<ColorRGBA>({ r: 0, g: 0, b: 0, a: 255 });

  const color = _color !== undefined && _onChange !== undefined ? _color : __color;
  const onChange = _color !== undefined && _onChange !== undefined ? _onChange : __onChange;

  const classes = useStyles({ color });

  return (
    <div className={classes.container}>
      <div className={classes.colorContainer} onClick={() => setShow(true)} />
      {show ? (
        <ClickAwayListener onClickAway={() => setShow(false)}>
          <div className={classes.pickerContainer}>
            <Picker color={color} onChange={onChange} />
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
  const classes = useStyles({ color });

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
