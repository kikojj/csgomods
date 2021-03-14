import React from "react";

import { Select, SelectProps } from "@components";

import { useStyles } from "./styles";

export type SelectFieldProps = {
  helperText?: string;
  marginTop?: number;
};
export const SelectField: React.FC<SelectFieldProps & SelectProps> = (props) => {
  const classes = useStyles();
  return (
    <div className={classes.container} style={{ marginTop: props.marginTop !== undefined ? props.marginTop : 20 }}>
      <Select {...(props as any)} />
      {props.helperText ? <div className={classes.helperText}>{props.helperText}</div> : ""}
    </div>
  );
};
