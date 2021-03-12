import React from "react";
import { SelectField, SelectItem } from "../../components";
import { bones, Skeleton } from "@utils";

export type BoneSelectProps = {
  value?: string;
  onChnage?: (v: string) => void;
};
export const BoneSelect: React.FC<BoneSelectProps> = ({ value, onChnage }) => {
  return (
    <SelectField placeholder="Bone" value={value} onChange={onChnage}>
      {bones.map((bone, key) => (
        <SelectItem key={key} value={Skeleton[bone].toString()}>
          {bone}
        </SelectItem>
      ))}
    </SelectField>
  );
};
