import React from "react";
import { ColorRGBA, RangeField } from "@components";
import { rgbToHex } from "@utils";

export type PickerProps = {
  color: ColorRGBA;
  onChange: (v: ColorRGBA) => void;
};
export const Picker: React.FC<PickerProps> = ({ color, onChange }) => (
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
