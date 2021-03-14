import React from "react";

import { Range, RangeProps } from "@components";

import { useStyles } from "./styles";

export type RangeFieldProps = {
  label?: string;
  helperText?: string;
  marginTop?: number;
};
export const RangeField: React.FC<RangeFieldProps & RangeProps> = (props) => {
  const classes = useStyles();

  return (
    <div className={classes.container} style={{ marginTop: props.marginTop !== undefined ? props.marginTop : 20 }}>
      <h6 className={classes.label}>{props.label || "Label"}</h6>
      <Range {...props} />
      {props.helperText ? <p className={classes.helperText}>{props.helperText}</p> : ""}
    </div>
  );
};
