import React from "react";

import { SelectField, SelectItem } from "@components";

export type GlowModeProps = {
  value: string;
  onChange: (v: string) => void;
};
export const GlowMode: React.FC<GlowModeProps> = ({ value, onChange }) => {
  return (
    <SelectField
      placeholder="Mode"
      helperText={value === "0" ? "Use color for glow" : "Show health in color"}
      value={value}
      onChange={onChange}
    >
      <SelectItem value="0">Color</SelectItem>
      <SelectItem value="1">HP based</SelectItem>
    </SelectField>
  );
};
