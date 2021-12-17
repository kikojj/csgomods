import React from "react";

import { Range, RangeProps } from "@components";

import { useStyles } from "./styles";

export type RangeFieldProps = {
  label?: string;
  helperText?: string;
  marginTop?: number;
};
export const RangeField: React.FC<RangeFieldProps & RangeProps> = ({
  label = "Label",
  helperText,
  marginTop = 20,
  ...rangeProps
}) => {
  const classes = useStyles();

  return (
    <div className={classes.container} style={{ marginTop }}>
      <h6 className={classes.label}>{label}</h6>
      <Range {...rangeProps} />
      {helperText && <p className={classes.helperText}>{helperText}</p>}
    </div>
  );
};
