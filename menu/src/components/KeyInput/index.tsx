import React from "react";

import { TextField } from "@material-ui/core";
import { useStyles } from "./styles";
import { TMargin } from "@utils";

export type KeyInputProps = {
  label: string;
  marginTop?: TMargin;
  value?: number;
  onChange?: (v: number) => void;
};
export const KeyInput: React.FC<KeyInputProps> = ({ label, marginTop, value = 0, onChange }) => {
  const classes = useStyles({ marginTop });

  return (
    <div className={classes.keyInput} style={{ marginTop }}>
      <h5 className={classes.keyInput_label}>{label}</h5>
      <TextField
        className={classes.keyInput_input}
        value={value}
        onKeyDown={(e) => {
          onChange && onChange(e.keyCode);
        }}
        onMouseDown={(e) => {
          if (e.button === 0) {
            onChange && onChange(1);
          } else if (e.button === 2) {
            onChange && onChange(2);
          }
        }}
      />
    </div>
  );
};
