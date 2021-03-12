import React from "react";

import { FormControlLabel, Switch as _Switch } from "@material-ui/core";
import { useStyles } from "./styles";
import { TMargin } from "@utils";

export type GroupProps = {
  className?: string;
  title: string;
  marginTop?: TMargin;
  children?: React.ReactNode;
};
export const Group: React.FC<GroupProps> = ({ className, title, marginTop, children }) => {
  const classes = useStyles();
  return (
    <div className={className} style={{ marginTop }}>
      <h6 className={classes.title}>{title}</h6>
      {children}
    </div>
  );
};
