import React from "react";
import { join } from "../utils";
import { useNumberHandler, usePhoneHandler } from "./utils";
import { useStyles } from "./styles";

export type TextFieldProps = {
  className?: string;
  placeholder?: string;
  value?: string;
  helperText?: string;
  onChange?: (v: string) => void;
  marginTop?: number;
  marginRight?: number;
};
export function TextField({
  className,
  placeholder,
  value: _value,
  helperText = "",
  onChange: _onChange,
  marginTop = 20,
  marginRight,
}: TextFieldProps) {
  const classes = useStyles();
  const ref = React.createRef<HTMLInputElement>();

  const [focus, setFocus] = React.useState<boolean>(false);
  const [__value, __onChange] = React.useState<string>("");

  const value =
    _value !== undefined && _onChange !== undefined ? _value : __value;
  const onChange =
    _value !== undefined && _onChange !== undefined ? _onChange : __onChange;

  function changeHandler(e: React.ChangeEvent<HTMLInputElement>) {
    const value = e.target.value;
    onChange(value);
  }

  return (
    <div
      className={join(classes.preContainer, className)}
      style={{ marginTop, marginRight }}
    >
      <div className={classes.container}>
        {placeholder && (
          <span
            className={join(
              classes.placeholder,
              focus || (value && ` ${classes.placeholder}-focus`)
            )}
            onClick={() => {
              ref.current?.focus();
            }}
          >
            {placeholder}
          </span>
        )}
        <input
          ref={ref}
          className={classes.input}
          type={"text"}
          value={value}
          onChange={changeHandler}
          onFocus={() => setFocus(true)}
          onBlur={() => setFocus(false)}
        />
      </div>
      <div
        className={join(
          classes.helperText,
          helperText && ` ${classes.helperText}-show`
        )}
      >
        {helperText}
      </div>
    </div>
  );
}
