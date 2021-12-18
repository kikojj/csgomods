import React from "react";
import { Checkbox, CheckboxProps } from "@components";
import { useStyles } from "./styles";

export type CheckboxFieldProps = CheckboxProps & {
  label?: string;
  helperText?: string;
  marginTop?: number;
};
export const CheckboxField: React.FC<CheckboxFieldProps> = ({
  label = "Label",
  helperText,
  marginTop = 20,
  ...checkboxProps
}) => {
  const classes = useStyles();

  return (
    <div className={classes.container} style={{ marginTop }}>
      <div className={classes.containerCheckbox}>
        <h6 className={classes.label}>{label}</h6>
        <Checkbox {...checkboxProps} />
      </div>
      {helperText && <p className={classes.helperText}>{helperText}</p>}
    </div>
  );
};
