import React from "react";
import { useStyles } from "./styles";

export type CheckboxProps = {
  checked?: boolean;
  onChange?: (v: boolean) => void;
};
export const Checkbox: React.FC<CheckboxProps> = ({ checked: _checked, onChange: _onChange }) => {
  const [__checked, __onChange] = React.useState<boolean>(_checked || false);

  let checked = _checked !== undefined && _onChange !== undefined ? _checked : __checked;
  let onChange = _checked !== undefined && _onChange !== undefined ? _onChange : __onChange;

  const classes = useStyles({ checked });
  return <div className={classes.container} onClick={() => onChange(!checked)} />;
};
