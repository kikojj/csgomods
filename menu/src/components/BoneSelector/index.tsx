import React from "react";
import { MenuItem, Select } from "@material-ui/core";
import { bones, Skeleton } from "@utils";

export type BoneSleectorProps = {
  value: number;
  onChange: (e: React.ChangeEvent<{ name?: string | undefined; value: unknown }>, child: React.ReactNode) => void;
};
export const BoneSleector: React.FC<BoneSleectorProps> = ({ value, onChange }) => {
  return (
    <Select placeholder="Bone" value={value} onChange={onChange}>
      {bones.map((bone, key) => (
        <MenuItem key={key} value={Skeleton[bone]}>
          {bone}
        </MenuItem>
      ))}
    </Select>
  );
};
