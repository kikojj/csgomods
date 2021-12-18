import React from "react";
import { Select, SelectProps } from "@components";
import { useStyles } from "./styles";

export type SelectFieldProps = {
  helperText?: string;
  marginTop?: number;
};
export const SelectField: React.FC<SelectFieldProps & SelectProps> = ({
  helperText,
  marginTop = 20,
  ...selectProps
}) => {
  const classes = useStyles();

  return (
    <div className={classes.container} style={{ marginTop }}>
      <Select {...selectProps} />
      {helperText && <div className={classes.helperText}>{helperText}</div>}
    </div>
  );
};
