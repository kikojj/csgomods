import React from "react";

import { join } from "../utils";

import { MouseIcon, KeyboardIcon } from "./images";
import { useStyles } from "./styles";

export type KeyInputProps = {
  className?: string;
  value?: number;
  onChange?: (v: number) => void;
};
export const KeyInput: React.FC<KeyInputProps> = ({ className, value: _value, onChange: _onChange }) => {
  const classes = useStyles();

  const [__value, __onChange] = React.useState<number>(1);

  const value = _value !== undefined && _onChange !== undefined ? _value : __value;
  const onChange = _value !== undefined && _onChange !== undefined ? _onChange : __onChange;

  return (
    <div className={join(classes.container, className)}>
      <span className={classes.icons}>
        <img className={classes.icon} src={KeyboardIcon} alt="keyboard" />
        <img src={MouseIcon} alt="mouse" />
      </span>
      <input
        className={classes.input}
        value={value.toString()}
        onKeyDown={(e) => {
          onChange(e.keyCode);
        }}
        onMouseDown={(e) => {
          if (e.button === 0) {
            onChange(1);
          } else if (e.button === 2) {
            onChange(2);
          }
        }}
        onChange={() => 0}
      />
    </div>
  );
};
