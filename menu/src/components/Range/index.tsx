import { Slider } from "@material-ui/core";
import { TMargin } from "@utils";
import React from "react";
import { useStyles } from "./styles";

export type RangeProps = {
  marginTop?: TMargin;
  label: string;
  min: number;
  max: number;
  step: number;
  value?: number | number[];
  onChange?: (e: React.ChangeEvent<{}>, v: number | number[]) => void;
};
export const Range: React.FC<RangeProps> = ({ marginTop, label, min, max, step, value, onChange }) => {
  const classes = useStyles({ marginTop });
  return (
    <div className={classes.range}>
      <h5 className={classes.range_label}>
        {label} {value}
      </h5>
      <Slider min={min} max={max} step={step} value={value} onChange={onChange} />
    </div>
  );
};
