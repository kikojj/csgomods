import React from "react";
import { join, useProvidableState } from "@components/utils";
import { emptyHandler } from "@utils";
import { MouseIcon, KeyboardIcon } from "./images";
import { useStyles } from "./styles";

export type KeyInputProps = {
  value?: number;
  className?: string;
  onChange?: (v: number) => void;
};
export const KeyInput: React.FC<KeyInputProps> = ({
  className,
  value: _value,
  onChange: _onChange,
}) => {
  const classes = useStyles();

  const [value, onChange] = useProvidableState(1, _value, _onChange);

  const onKeyDown = React.useCallback(
    // TODO: Check @deprecated keyCode and remove it
    (event: React.KeyboardEvent<HTMLInputElement>) => onChange(event.keyCode),
    [onChange]
  );

  const onMouseDown = React.useCallback(
    (event: React.MouseEvent<HTMLInputElement, MouseEvent>) => {
      if (event.button === 0) {
        onChange(1);
      } else if (event.button === 2) {
        onChange(2);
      }
    },
    [onChange]
  );

  return (
    <div className={join(classes.container, className)}>
      <span className={classes.icons}>
        <img className={classes.icon} src={KeyboardIcon} alt="keyboard" />
        <img src={MouseIcon} alt="mouse" />
      </span>
      <input
        className={classes.input}
        value={value.toString()}
        onKeyDown={onKeyDown}
        onMouseDown={onMouseDown}
        onChange={emptyHandler}
      />
    </div>
  );
};
