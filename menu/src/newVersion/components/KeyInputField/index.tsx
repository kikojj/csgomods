import React from "react";
import { KeyInput, KeyInputProps } from "../KeyInput";
import { useStyles } from "./styles";

export type KeyInputFieldProps = {
  helperText?: string;
  marginTop?: number;
};
export const KeyInputField: React.FC<KeyInputFieldProps & KeyInputProps> = (props) => {
  const classes = useStyles();
  return (
    <div className={classes.container} style={{ marginTop: props.marginTop !== undefined ? props.marginTop : 20 }}>
      <KeyInput {...(props as any)} />
      {props.helperText ? <div className={classes.helperText}>{props.helperText}</div> : ""}
    </div>
  );
};
