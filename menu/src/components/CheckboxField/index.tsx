import React from "react";

import { Checkbox, CheckboxProps } from "@components";

import { useStyles } from "./styles";

export type CheckboxFieldProps = {
  label?: string;
  helperText?: string;
  marginTop?: number;
};
export const CheckboxField: React.FC<CheckboxFieldProps & CheckboxProps> = (props) => {
  const classes = useStyles();

  return (
    <div className={classes.container} style={{ marginTop: props.marginTop !== undefined ? props.marginTop : 20 }}>
      <div className={classes.containerCheckbox}>
        <h6 className={classes.label}>{props.label || "Label"}</h6>
        <Checkbox {...props} />
      </div>
      {props.helperText ? <p className={classes.helperText}>{props.helperText}</p> : ""}
    </div>
  );
};
