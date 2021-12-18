import React from "react";
import { useProvidableState } from "@components/utils";
import { useStyles } from "./styles";

export type CheckboxProps = {
  checked?: boolean;
  onChange?: (v: boolean) => void;
};
export const Checkbox: React.FC<CheckboxProps> = ({
  checked: _checked,
  onChange: _onChange,
}) => {
  const [checked, onChange] = useProvidableState(false, _checked, _onChange);

  const classes = useStyles({ checked });

  const onClick = React.useCallback(
    () => onChange(!checked),
    [checked, onChange]
  );

  return <div className={classes.container} onClick={onClick} />;
};
