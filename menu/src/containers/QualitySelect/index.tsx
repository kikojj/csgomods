import React from "react";
import { SelectField, SelectItem } from "@components";
import { EntityQuality, GenericObject } from "@utils";

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
  onChange?: (v: number) => void;
  marginTop?: number;
};
export const QualitySelect: React.FC<QualitySelectProps> = ({
  marginTop,
  value,
  onChange,
}) => {
  const qualityItems = React.useMemo(
    () =>
      GenericObject.keys(qualities).map((qualityKey) => (
        <SelectItem key={qualityKey} value={qualityKey.toString()}>
          {qualities[qualityKey]}
        </SelectItem>
      )),
    []
  );

  return (
    <SelectField
      placeholder="Quality"
      value={value?.toString()}
      onChange={(v) => onChange && onChange(+v)}
      marginTop={marginTop}
    >
      {qualityItems}
    </SelectField>
  );
};
