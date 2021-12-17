import React from "react";
import { SelectField, SelectItem } from "@components";
import { bones, Skeleton } from "@utils";

export type BoneSelectProps = {
  value?: string;
  onChange?: (v: string) => void;
};
export const BoneSelect: React.FC<BoneSelectProps> = ({ value, onChange }) => {
  const bonesSelectItems = React.useMemo(
    () =>
      bones.map((bone) => (
        <SelectItem key={bone} value={Skeleton[bone].toString()}>
          {bone}
        </SelectItem>
      )),
    []
  );

  return (
    <SelectField placeholder="Bone" value={value} onChange={onChange}>
      {bonesSelectItems}
    </SelectField>
  );
};
