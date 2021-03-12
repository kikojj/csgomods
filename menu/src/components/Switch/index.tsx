import React from "react";

import { Switch as _Switch } from "@material-ui/core";
import { useStyles } from "./styles";
import { TMargin } from "@utils";

export type SwitchProps = {
  label: string;
  marginTop?: TMargin;
  checked?: boolean;
  onChange?: (e: React.ChangeEvent<HTMLInputElement>, checked: boolean) => void;
};
export const Switch: React.FC<SwitchProps> = ({ label, marginTop, checked = false, onChange }) => {
  const classes = useStyles({ marginTop });
  return (
    <div className={classes.switch} style={{ marginTop }}>
      <h5 className={classes.switch_label}>{label}</h5>
      <_Switch color="primary" checked={checked} onChange={onChange} />
    </div>
  );
};
