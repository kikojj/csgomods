import React from "react";
import { MenuItem, Select } from "@material-ui/core";
import { TMargin, EntityQuality } from "@utils";
import { useStyles } from "./styles";

const defaultQualities: { [T in EntityQuality]?: string } = {
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
  className?: string;
  marginTop?: TMargin;
  qualities?: typeof defaultQualities;
  value?: number;
  onChange?: (v: number) => void;
};
export const QualitySelect: React.FC<QualitySelectProps> = ({
  className,
  marginTop,
  qualities = { ...defaultQualities },
  value,
  onChange,
}) => {
  const classes = useStyles();
  return (
    <div className={className} style={{ marginTop }}>
      <Select
        className={classes.select}
        placeholder="Quality"
        value={value}
        onChange={(e, c) => onChange && onChange(parseInt(e.target.value as string))}
        defaultValue={EntityQuality.QUALITY_NORMAL}
      >
        {Object.keys(qualities).map((key) => (
          <MenuItem className={classes.select_item} key={key} value={key}>
            {qualities[(key as any) as EntityQuality]}
          </MenuItem>
        ))}
      </Select>
    </div>
  );
};
