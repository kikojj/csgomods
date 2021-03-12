import React from "react";

import { Radio as _Radio } from "@material-ui/core";
import { useStyles } from "./styles";
import { TMargin } from "@utils";

export type RadioProps = {
  label: string;
  marginTop?: TMargin;
  value?: string;
  checked?: boolean;
  onChange?: (e: React.ChangeEvent<HTMLInputElement>, checked: boolean) => void;
};
export const Radio: React.FC<RadioProps> = ({ label, marginTop, checked, value = false, onChange }) => {
  const classes = useStyles({ marginTop });
  return (
    <div className={classes.radio} style={{ marginTop }}>
      <h5 className={classes.radio_label}>{label}</h5>
      <_Radio color="primary" value={value} onChange={onChange} checked={checked} />
    </div>
  );
};
