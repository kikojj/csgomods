import React from "react";
import { ColorPicker, ColorPickerProps } from "..";
import { useStyles } from "./styles";

export type ColorPickerFieldProps = {
  label?: string;
  helperText?: string;
  marginTop?: number;
};
export const ColorPickerField: React.FC<ColorPickerFieldProps & ColorPickerProps> = (props) => {
  const classes = useStyles();

  return (
    <div className={classes.container} style={{ marginTop: props.marginTop !== undefined ? props.marginTop : 20 }}>
      <div className={classes.containerCheckbox}>
        <h6 className={classes.label}>{props.label || "Label"}</h6>
        <ColorPicker {...props} />
      </div>
      {props.helperText ? <p className={classes.helperText}>{props.helperText}</p> : ""}
    </div>
  );
};
