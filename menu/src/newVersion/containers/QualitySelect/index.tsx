import React from "react";
import { SelectField, SelectItem } from "../../components";
import { EntityQuality } from "@utils";

const qualities: { [T in EntityQuality]: string } = {
  [EntityQuality.QUALITY_NORMAL]: "Default",
  [EntityQuality.QUALITY_GENUINE]: "Genuine",
  [EntityQuality.QUALITY_VINTAGE]: "Vintage",
  [EntityQuality.QUALITY_UNUSUAL]: "Unusual",
  [EntityQuality.QUALITY_COMMUNITY]: "Community",
  [EntityQuality.QUALITY_DEVELOPER]: "Developer",
  [EntityQuality.QUALITY_SELF_MADE]: "Self made",
  [EntityQuality.QUALITY_CUSTOMIZED]: "Customized",
  [EntityQuality.QUALITY_STRANGE]: "Strange",
  [EntityQuality.QUALITY_COMPLETED]: "Completed",
  [EntityQuality.QUALITY_TOURNAMENT]: "Tournament",
};

export type QualitySelectProps = {
  value?: number;
  onChnage?: (v: number) => void;
};
export const QualitySelect: React.FC<QualitySelectProps> = ({ value, onChnage }) => {
  return (
    <SelectField placeholder="Quality" value={value?.toString()} onChange={onChnage ? (v) => onChnage(+v) : undefined}>
      {Object.keys(qualities).map((key) => (
        <SelectItem key={key} value={key.toString()}>
          {qualities[(key as any) as EntityQuality]}
        </SelectItem>
      ))}
    </SelectField>
  );
};
