import React from "react";

import { ColorPicker, ColorPickerProps } from "@components";

import { useStyles } from "./styles";

export type ColorPickerFieldProps = ColorPickerProps & {
  label?: string;
  helperText?: string;
  marginTop?: number;
};
export const ColorPickerField: React.FC<ColorPickerFieldProps> = ({
  label = "Label",
  helperText,
  marginTop = 20,
  ...colorPickerProps
}) => {
  const classes = useStyles();

  return (
    <div className={classes.container} style={{ marginTop }}>
      <div className={classes.containerCheckbox}>
        <h6 className={classes.label}>{label}</h6>
        <ColorPicker {...colorPickerProps} />
      </div>
      {helperText && <p className={classes.helperText}>{helperText}</p>}
    </div>
  );
};
