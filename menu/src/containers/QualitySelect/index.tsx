import React from "react";
import { SelectField, SelectItem } from "@components";
import { EntityQuality } from "@utils";

const qualities: { [T in EntityQuality]: string } = {
  [EntityQuality.Invalid]: "Invalid",
  [EntityQuality.Normal]: "Default",
  [EntityQuality.Genuine]: "Genuine",
  [EntityQuality.Vintage]: "Vintage",
  [EntityQuality.Unusual]: "Unusual",
  [EntityQuality.Community]: "Community",
  [EntityQuality.Developer]: "Developer",
  [EntityQuality.SelftMade]: "Self made",
  [EntityQuality.Customized]: "Customized",
  [EntityQuality.Strange]: "Strange",
  [EntityQuality.Completed]: "Completed",
  [EntityQuality.Tournament]: "Tournament",
};

export type QualitySelectProps = {
  value?: number;
  onChnage?: (v: number) => void;
  marginTop?: number;
};
export const QualitySelect: React.FC<QualitySelectProps> = ({ marginTop, value, onChnage }) => {
  return (
    <SelectField
      placeholder="Quality"
      value={value?.toString()}
      onChange={onChnage ? (v) => onChnage(+v) : undefined}
      marginTop={marginTop}
    >
      {Object.keys(qualities).map((key) => (
        <SelectItem key={key} value={key.toString()}>
          {qualities[(key as any) as EntityQuality]}
        </SelectItem>
      ))}
    </SelectField>
  );
};
