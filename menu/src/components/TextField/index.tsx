import React from "react";
import { join, useProvidableState } from "../utils";
import { useStyles } from "./styles";

export type TextFieldProps = {
  className?: string;
  placeholder?: string;
  value?: string;
  helperText?: string;
  marginTop?: number;
  marginRight?: number;
  onChange?: (v: string) => void;
};
export function TextField({
  className,
  placeholder,
  value: _value,
  helperText = "",
  marginTop = 20,
  marginRight,
  onChange: _onChange,
}: TextFieldProps) {
  const classes = useStyles({ marginTop, marginRight });
  const inputRef = React.createRef<HTMLInputElement>();

  const [focus, setFocus] = React.useState<boolean>(false);
  const [value, setValue] = useProvidableState("", _value, _onChange);

  const onPlaceholderClick = React.useCallback(
    () => inputRef.current?.focus(),
    [inputRef]
  );

  const onChange = React.useCallback(
    (event: React.ChangeEvent<HTMLInputElement>) =>
      setValue(event.target.value),
    [setValue]
  );

  const onFocus = React.useCallback(() => setFocus(true), [setFocus]);

  const onBlur = React.useCallback(() => setFocus(false), [setFocus]);

  return (
    <div className={join(classes.preContainer, className)}>
      <div className={classes.container}>
        {placeholder && (
          <span
            className={join(
              classes.placeholder,
              (focus || value) && ` ${classes.placeholder}-focus`
            )}
            onClick={onPlaceholderClick}
          >
            {placeholder}
          </span>
        )}
        <input
          ref={inputRef}
          className={classes.input}
          type="text"
          value={value}
          onChange={onChange}
          onFocus={onFocus}
          onBlur={onBlur}
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
