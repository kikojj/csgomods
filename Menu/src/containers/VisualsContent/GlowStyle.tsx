import React from "react";

import { SelectField, SelectItem } from "@components";

export type GlowStyleProps = {
  value: string;
  onChange: (v: string) => void;
};
export const GlowStyle: React.FC<GlowStyleProps> = ({ value, onChange }) => {
  return (
    <SelectField
      placeholder="Style"
      helperText={
        value === "0"
          ? "Outline full body(works through the walls)"
          : value === "1"
          ? "All body contours and flicker of glow"
          : value === "2"
          ? "All body contours"
          : "Flicker of glow"
      }
      value={value}
      onChange={onChange}
    >
      <SelectItem value="0">Full body</SelectItem>
      <SelectItem value="2">Inline</SelectItem>
      <SelectItem value="3">Flicker</SelectItem>
      <SelectItem value="1">Inline flicker</SelectItem>
    </SelectField>
  );
};
